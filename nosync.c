/*
 * 
 *  nosync - crazy preload to disable sync() function call
 *  for days when we just don't want to sync() (similar to
 *  nohup, just more sync than HUP).
 * 
 *  These libc functions are trapped in dynamically linked 
 *  executables and stripped of their sync features:
 * 
 *   open
 *   openat
 *   fcntl
 *   sync
 *   fdatasync
 *   fsync
 *   sync_file_range
 * 
 *  compile with gcc, or use the attached wrapper:
 *
 *    gcc -Wall -fPIC -shared -o nosync.so nosync.c -lc -ldl
 * 
 *   (c) 2011 
 *   Licence: GNU Public Licence version 2 or above
 */

#define _GNU_SOURCE

#define open            _IGNORE_1
#define open64          _IGNORE_2
#define openat          _IGNORE_3
#define openat64        _IGNORE_4
#define sync_file_range _IGNORE_5

#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <dlfcn.h>

#include <fcntl.h>
#include <unistd.h>


#if defined(RTLD_NEXT)
#define REAL_LIBC RTLD_NEXT
#else
#define REAL_LIBC ((void *) -1L)
#endif

void sync(void)
{
    return;
}

int fsync(int fd)
{
    return 0;
}

int fdatasync(int fd)
{
    return 0;
}

#undef sync_file_range
int sync_file_range(void)
{
    return 0;
}


/* open */
#undef open
typedef int openfn_type(const char *pathname, int flags, mode_t mode);
static openfn_type __find_open;
static openfn_type *_old_open = __find_open;

int __find_open(const char *pathname, int flags, mode_t mode)
{
    openfn_type *functionptr;
    functionptr=dlsym(REAL_LIBC,"open");    
    if (!functionptr) return -1;
    _old_open=functionptr;
    return _old_open(pathname,flags,mode);
}

int open(const char *pathname, int flags, mode_t mode)
{
    flags &= ~ (O_DIRECT | O_SYNC);
    return _old_open(pathname,flags,mode);
}

/* open64 */
#undef open64
typedef int open64fn_type(const char *pathname, int flags, mode_t mode);
static open64fn_type __find_open64;
static open64fn_type *_old_open64 = __find_open64;

int __find_open64(const char *pathname, int flags, mode_t mode)
{
    open64fn_type *functionptr;
    functionptr=dlsym(REAL_LIBC,"open64");    
    if (!functionptr) return -1;
    _old_open64=functionptr;
    return _old_open64(pathname,flags,mode);
}

int open64(const char *pathname, int flags, mode_t mode)
{
    flags &= ~ (O_DIRECT | O_SYNC);
    return _old_open64(pathname,flags,mode);
}

/* openat */
#undef openat
typedef int openatfn_type(int dirfd, const char *pathname, int flags, mode_t mode);
static openatfn_type __find_openat;
static openatfn_type *_old_openat = __find_openat;

int __find_openat(int dirfd, const char *pathname, int flags, mode_t mode)
{
    openatfn_type *functionptr;
    functionptr=dlsym(REAL_LIBC,"openat");    
    if (!functionptr) return -1;
    _old_openat=functionptr;
    return _old_openat(dirfd,pathname,flags,mode);
}

int openat(int dirfd, const char *pathname, int flags, mode_t mode)
{
    flags &= ~ (O_DIRECT | O_SYNC);
    return _old_openat(dirfd,pathname,flags,mode);
}

/* openat64 */
#undef openat64
typedef int openat64fn_type(int dirfd, const char *pathname, int flags, mode_t mode);
static openat64fn_type __find_openat64;
static openat64fn_type *_old_openat64 = __find_openat64;

int __find_openat64(int dirfd, const char *pathname, int flags, mode_t mode)
{
    openat64fn_type *functionptr;
    functionptr=dlsym(REAL_LIBC,"openat64");    
    if (!functionptr) return -1;
    _old_openat64=functionptr;
    return _old_openat64(dirfd,pathname,flags,mode);
}

int openat64(int dirfd, const char *pathname, int flags, mode_t mode)
{
    flags &= ~ (O_DIRECT | O_SYNC);
    return _old_openat64(dirfd,pathname,flags,mode);
}


/* fcntl */
int fcntl(int fd, int cmd, ...)
{
    static int (*real_fcntl)(int, int, ...);
    va_list ap;
    long flags;
    void *ptr;    
    int rc;

    if (real_fcntl == NULL ) {
        real_fcntl = dlsym(REAL_LIBC, "fcntl");
    }
    va_start(ap, cmd);
    switch (cmd) {
        /* long */
        /* this is why we are here */
        case F_SETFL:  /* set flags - no direct or sync please */
            flags = va_arg(ap, long);
            flags &= ~ (O_DIRECT | O_SYNC);
            rc = real_fcntl(fd,cmd,flags);
            break;
        /* void */
        case F_GETOWN:
        case F_GETFD:
        case F_GETFL: 
        case F_GETSIG: 
        case F_GETLEASE: 
#ifdef F_GETPIPE_SZ
        case F_GETPIPE_SZ: 
#endif
            rc = real_fcntl(fd,cmd);
            break;
        /* struct flock * and other pointers */
        case F_GETLK:
        case F_SETLK:
        case F_SETLKW:
#ifdef F_SETOWN_EX
        case F_SETOWN_EX:
#endif
#ifdef F_GETOWN_EX
        case F_GETOWN_EX:
#endif
            ptr = va_arg(ap, void *);
            rc = real_fcntl(fd,cmd,ptr);
            break;
        /* long */
        /* case F_SETOWN: */
        /* case F_DUPFD: */
        /* case F_DUPFD_CLOEXEC: */
        /* case F_SETSIG: */
        /* case F_SETLEASE: */
        /* case F_SETPIPE_SZ: */
        default:
            flags = va_arg(ap, long);
            rc = real_fcntl(fd,cmd,flags);
            break;
    }
    va_end(ap);
    return rc;
}
