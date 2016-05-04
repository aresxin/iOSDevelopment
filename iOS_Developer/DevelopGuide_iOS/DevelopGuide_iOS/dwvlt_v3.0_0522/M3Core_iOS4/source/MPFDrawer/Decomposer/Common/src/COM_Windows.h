#if !defined(COM_WINDOWS_H_INCLUDED)
#define COM_WINDOWS_H_INCLUDED


#if (defined(WIN32) && !defined(DOCUWORKS_VIEWER)) || defined(CYGWIN) || defined(_WIN32_WCE)

#include <Windows.h>

#else

#define WORD	unsigned short
#define DWORD	unsigned long
#define BOOL	int
#define UINT	unsigned int
#define BYTE	unsigned char
typedef char *	LPSTR;
typedef unsigned char * LPBYTE;
typedef unsigned long * LPDWORD;

typedef struct {
	long x;
	long y;
}POINT;

#define TRUE	1
#define FALSE	0

#define HFILE_ERROR	-1

#if !defined(DOCUWORKS_VIEWER)
#define __declspec(a) extern
#define __stdcall
#endif

#endif


#endif
