#ifndef NTP_IOCOMPLETIONPORT_H
#define NTP_IOCOMPLETIONPORT_H

#include "ntp_fp.h"
#include "clockstuff.h"
#include "ntservice.h"

#if defined(HAVE_IO_COMPLETION_PORT)

/* NotifyIpInterfaceChange() is available on Windows Vista and later. */
typedef enum ENUM_DONTCARE_MIB_NOTIF_TYPE {
	SomeType_DontCare
} MIB_NOTIF_TYPE;

typedef void
(WINAPI* PMYIPINTERFACE_CHANGE_CALLBACK) (
	PVOID		CallerContext,
	PVOID		Row,
	MIB_NOTIF_TYPE	NotificationType
	);

typedef DWORD (WINAPI* NotifyIpInterfaceChange_ptr)(
	ADDRESS_FAMILY			Family,
	PMYIPINTERFACE_CHANGE_CALLBACK	Callback,
	PVOID				CallerContext,
	BOOLEAN				InitialNotification,
	HANDLE*				NotificationHandle
	);

extern	NotifyIpInterfaceChange_ptr	pNotifyIpInterfaceChange;

/*
 * Timestamping configuration structure and flags, available only on
 * Windows version 10 build 20348 and later.  There are in fact no Windows 10
 * desktop releases of that build or later -- the change was released with
 * Windows Server 2022 version 21H2.  As Windows 11 version information
 * claims Windows 10 starting with build 22000, we can assume that all
 * Windows 11 versions also support this SO_TIMESTAMP.
 * Duplicated from mstcpip.h to avoid requiring claiming building for a
 * newer version of Windows than XP and having a recent SDK to compile.
 */
#ifndef		SIO_TIMESTAMPING
# define	SIO_TIMESTAMPING	_WSAIOW(IOC_VENDOR, 235)
# define	TIMESTAMPING_FLAG_RX	0x1
# define	SO_TIMESTAMP		0x300A

typedef struct _TIMESTAMPING_CONFIG {
	ULONG Flags;
	USHORT TxTimestampsBuffered;
} TIMESTAMPING_CONFIG, * PTIMESTAMPING_CONFIG;

#endif /* !defined(SIO_TIMESTAMPING) */


extern	void	init_io_completion_port(void);
extern	void	uninit_io_completion_port(void);

extern	BOOL	io_completion_port_add_interface(endpt *);
extern	void	io_completion_port_remove_interface(endpt *);

extern	BOOL	io_completion_port_add_socket(SOCKET fd, endpt *, BOOL bcast);
extern	void	io_completion_port_remove_socket(SOCKET fd, endpt *);

extern	int	io_completion_port_sendto(endpt *ep, void *pkt, DWORD len,
					  sockaddr_u *dest);

extern	BOOL	io_completion_port_add_clock_io(struct refclockio *rio);
extern	void	io_completion_port_remove_clock_io(struct refclockio *rio);

extern	int	GetReceivedBuffers(void);
extern	void WINAPI	IpInterfaceChangedCallback(PVOID ctx, PVOID row,
						   MIB_NOTIF_TYPE type);


extern	HANDLE	WaitableExitEventHandle;

#endif	/* !defined(HAVE_IO_COMPLETION_PORT) */
#endif	/* !defined(NTP_IOCOMPLETIONPORT_H) */
