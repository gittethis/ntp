#ifndef RECVBUFF_H
#define RECVBUFF_H

#include "ntp.h"
#include "ntp_net.h"
#include "ntp_lists.h"

#include <isc/result.h>

/*
 * recvbuf memory management
 */
#define RECV_INIT	64	/* 64 buffers initially */
#define RECV_LOWAT	3	/* when we're down to three buffers get more */
#define RECV_INC	32	/* [power of 2] get 32 more at a time */
#define RECV_BATCH	128	/* [power of 2] max increment in one sweep */
#define RECV_TOOMANY	4096	/* this should suffice, really. TODO: tos option? */

/* If we have clocks, keep an iron reserve of receive buffers for
 * clocks only.
 */
#if defined(REFCLOCK)
# if !defined(RECV_CLOCK) || RECV_CLOCK == 0
#  undef RECV_CLOCK
#  define RECV_CLOCK	16
# endif
#else
# if defined(RECV_CLOCK)
#  undef RECV_CLOCK
# endif
# define RECV_CLOCK 0
#endif

 /*
  * Packet timestamping support.  Prefer most accurate method available.
  */
#ifdef CMSG_FIRSTHDR
# if defined(SO_TS_BINTIME) || defined(SO_TIMESTAMPNS) || defined(SO_TIMESTAMP)
#  define HAVE_PACKET_TIMESTAMP

#  if defined(SO_TS_BINTIME)	/* 64 bit FP fraction */
#   define HAVE_TS_BINTIME
#   define NTP_SO_TS		SO_TIMESTAMP
#   define NTP_SO_TS_STRING	"SO_TIMESTAMP"
#   define NTP_SCM_TS		SCM_BINTIME
#   define NTP_SCM_TS_STRING	"SCM_BINTIME"
#   define CMSG_TS_BUFSIZE	CMSG_SPACE(sizeof(struct bintime))
#  elif defined(SO_TIMESTAMPNS)	/* SO_TIMESTAMPNS is second best */
#   define HAVE_TIMESTAMPNS
#   define NTP_SO_TS		SO_TIMESTAMPNS
#   define NTP_SO_TS_STRING	"SO_TIMESTAMPNS"
#   define NTP_SCM_TS		SCM_TIMESTAMPNS
#   define NTP_SCM_TS_STRING	"SCM_TIMESTAMPNS"
#   define CMSG_TS_BUFSIZE	CMSG_SPACE(sizeof(struct timespec))
#  elif defined(SO_TIMESTAMP)	/* SO_TIMESTAMP is least loved */
#   define HAVE_TIMESTAMP
#   define NTP_SO_TS		SO_TIMESTAMP
#   define NTP_SO_TS_STRING	"SO_TIMESTAMP"
#   define NTP_SCM_TS		SCM_TIMESTAMP
#   define NTP_SCM_TS_STRING	"SCM_TIMESTAMP"
#   define CMSG_TS_BUFSIZE	CMSG_SPACE(sizeof(struct timeval))
#  endif

#  ifdef SCM_TIME_INFO		/* HW timestamp info (uncommon) */
#   define CMSG_TI_BUFSIZE CMSG_SPACE(sizeof(struct sock_timestamp_info))
#  else
#   define CMSG_TI_BUFSIZE 0
#  endif

#  define CMSG_BUFSIZE	(32 + CMSG_TS_BUFSIZE + CMSG_TI_BUFSIZE)

# endif		/* SO_TS_BINTIME || SO_TIMESTAMPNS || SO_TIMESTAMP */
#endif		/* CMSG_FIRSTHDR */

#if defined HAVE_IO_COMPLETION_PORT
# include "ntp_iocompletionport.h"
# include "ntp_timer.h"

/*  Return the event which is set when items are added to the full list
 */
extern HANDLE	get_recv_buff_event(void);

# define RECV_BLOCK_IO()	EnterCriticalSection(&RecvCritSection)
# define RECV_UNBLOCK_IO()	LeaveCriticalSection(&RecvCritSection)
#else
# define RECV_BLOCK_IO()	do {} while (FALSE)
# define RECV_UNBLOCK_IO()	do {} while (FALSE)
#endif


/*
 * Format of a recvbuf.  These are used by the asynchronous receive
 * routine to store incoming packets and related information.
 */

/*
 *  the maximum length NTP packet contains the NTP header, one Autokey
 *  request, one Autokey response and the MAC. Assuming certificates don't
 *  get too big, the maximum packet length is set arbitrarily at 1200.
 *  (was 1000, but that bumps on 2048 RSA keys)
 */   
#define	RX_BUFF_SIZE	1200		/* hail Mary */


typedef struct recvbuf recvbuf_t;

struct recvbuf {
	recvbuf_t *	link;		/* must be first - gen_fifo */
	endpt *		dstadr;		/* address pkt arrived on */
	void		(*receiver)(struct recvbuf *); /* callback */
	l_fp		recv_time;	/* time of arrival */
	SOCKET		fd;		/* fd on which it was received */
	int		used;		/* reference count */
	int		recv_length;	/* number of octets received */
	union {
		sockaddr_u	X_recv_srcadr;
		struct peer *	X_recv_peer;	/* refclock peer */
	} X_from_where;
#define recv_srcadr		X_from_where.X_recv_srcadr
#define recv_peer		X_from_where.X_recv_peer
#ifdef SYS_WINNT
	WSAMSG		wsamsg;		/* WSARecvMsg() async */
	char		cmsgbuf[CMSG_BUFSIZE];
#endif
	union {
		struct pkt	X_recv_pkt;
		u_char		X_recv_buffer[RX_BUFF_SIZE];
	} recv_space;
#define	recv_pkt		recv_space.X_recv_pkt
#define	recv_buffer		recv_space.X_recv_buffer
};

extern	void	init_recvbuff(int);

/* freerecvbuf - make a single recvbuf available for reuse
 */
extern	void	freerecvbuf(struct recvbuf *);

/*  Get a free buffer (typically used so an async
 *  read can directly place data into the buffer
 *
 *  The buffer is removed from the free list. Make sure
 *  you put it back with freerecvbuf() or 
 */

/* signal safe - no malloc, returns NULL when no bufs */
extern	struct recvbuf *get_free_recv_buffer(int /*BOOL*/ urgent);
/* signal unsafe - may malloc, returns NULL when no bufs */
extern	struct recvbuf *get_free_recv_buffer_alloc(int /*BOOL*/ urgent);

/*   Add a buffer to the full list
 */
extern	void	add_full_recv_buffer(struct recvbuf *);

/* number of recvbufs on freelist */
extern u_long free_recvbuffs(void);		
extern u_long full_recvbuffs(void);		
extern u_long total_recvbuffs(void);
extern u_long lowater_additions(void);
		
/*  Returns the next buffer in the full list.
 *
 */
extern	struct recvbuf *get_full_recv_buffer(void);

/*
 * purge_recv_buffers_for_fd() - purges any previously-received input
 *				 from a given file descriptor.
 */
extern	void purge_recv_buffers_for_fd(int);

/*
 * Checks to see if there are buffers to process
 */
extern isc_boolean_t has_full_recv_buffer(void);

#endif	/* RECVBUFF_H */
