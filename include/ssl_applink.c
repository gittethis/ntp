/*
 * include/ssl_applink.c -- common NTP code for openssl/applink.c
 *
 * Each program which uses OpenSSL should include this file in _one_
 * of its source files and call ssl_applink() before any OpenSSL
 * functions.
 */

#if defined(OPENSSL) && defined(SYS_WINNT)
# ifdef _MSC_VER
#  pragma warning(push)
#  pragma warning(disable: 4152)
#  ifndef OPENSSL_NO_AUTOLINK
#   include "msvc_ssl_autolib.h"
#  endif
# endif
# if OPENSSL_VERSION_NUMBER < 0x10100000L || OPENSSL_VERSION_NUMBER >= 0x10101000L
#  include <openssl/applink.c>
# endif
# ifdef _MSC_VER
#  pragma warning(pop)
# endif
#endif

#if defined(OPENSSL) && defined(_MSC_VER) && defined(_DEBUG)
#define WRAP_DBG_MALLOC
#endif

#ifdef WRAP_DBG_MALLOC
static void *	wrap_dbg_malloc_ex(size_t s, const char *f, int l);
static void *	wrap_dbg_realloc_ex(void *p, size_t s, const char *f, int l);
static void	wrap_dbg_free_ex(void *p, const char *f, int l);
#endif


#if defined(OPENSSL) && defined(SYS_WINNT)

void ssl_applink(void);

void
ssl_applink(void)
{
# ifdef WRAP_DBG_MALLOC
#  if OPENSSL_VERSION_NUMBER >= 0x10100000L
	CRYPTO_set_mem_functions(&wrap_dbg_malloc_ex, &wrap_dbg_realloc_ex,
				 &wrap_dbg_free_ex);
#  else
	CRYPTO_set_mem_ex_functions(&wrap_dbg_malloc_ex, &wrap_dbg_realloc_ex,
				    &wrap_dbg_free_ex);
#  endif
# endif
}
#else	/* !OPENSSL || !SYS_WINNT */
#define ssl_applink()	do {} while (0)
#endif


#ifdef WRAP_DBG_MALLOC
/*
 * Avoid showing OpenSSL memory allocations in MS debug heap leak reports
 * by clearing _CRTDBG_ALLOC_MEM_DF before each crypto allocation and
 * restoring it afterward.  That causes those allocations to be marked
 * as _IGNORE_BLOCK type.
 * 
 */
# ifdef USING_DEBUG_HEAP_FLAGS
#  define IGNORE_CRYPTO_ALLOCS(ret, alloc_call)				\
	do {								\
		_CrtSetDbgFlag(debug_heap_flags);			\
		ret = alloc_call;					\
		_CrtSetDbgFlag(debug_heap_flags | _CRTDBG_ALLOC_MEM_DF);\
	} while (0)
# else
#  define IGNORE_CRYPTO_ALLOCS(ret, alloc_call)				\
	do {								\
		ret = alloc_call;					\
	} while (0)
# endif

static void* wrap_dbg_malloc_ex(size_t s, const char *f, int l)
{
	void *	ret;

	IGNORE_CRYPTO_ALLOCS(ret, _malloc_dbg(s, _NORMAL_BLOCK, f, l));
	return ret;
}

static void* wrap_dbg_realloc_ex(void* p, size_t s, const char *f, int l)
{
	void* ret;

	IGNORE_CRYPTO_ALLOCS(ret, _realloc_dbg(p, s, _NORMAL_BLOCK, f, l));
	return ret;
}

static void wrap_dbg_free_ex(void *p, const char *f, int l)
{
	UNUSED_ARG(f);
	UNUSED_ARG(l);

	_free_dbg(p, _NORMAL_BLOCK);
}

#endif	/* WRAP_DBG_MALLOC */
