#ifndef _DUMMY_DEFINE_H_INCLUDED_
#define _DUMMY_DEFINE_H_INCLUDED_

/*#include <io.h>*/
#include <unistd.h>

#include <stdio.h>
#include <stddef.h>
#include <malloc.h>

#define	PROT_READ	0x1		/* pages can be read */
#define	PROT_WRITE	0x2		/* pages can be written */
#define	PROT_EXEC	0x4		/* pages can be executed */
#define	PROT_NONE	0x0		/* pages cannot be accessed */

#define	MAP_SHARED	1		/* share changes */
#define	MAP_PRIVATE	2		/* changes are private */
#define	MAP_FIXED	0x10		/* user assigns address */

typedef char            *caddr_t;       /* ?<core address> type */
typedef long            daddr_t;        /* <disk address> type */
typedef short           cnt_t;          /* ?<count> type */


inline void *mmap(void *addr, size_t len, int prot, int flags,  int fildes, off_t off)
{
    char *p = NULL;
    if((p = (char *)malloc( len )) == NULL){
	return (void *)(-1);
    }
  
    read(fildes, p, len);

    return (void *)p;
}

inline int munmap(void *addr, size_t len)
{
    if(addr == NULL) return (-1);
    free(addr);

    return (0);
}

inline void *memalign(size_t align, size_t size)
{
  return ( malloc( size ) );
}

#endif
