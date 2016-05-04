// File: OSDEPS.H
// Auther: Hideki Ichiriki
// Copyright(C) 1996 by Fuji Xerox Co,. Ltd. All right reserved.

//

#include <mpc_api.h>

void MPsplitpath( const char *path, char *drive, char *dir, char *fname, char *ext );
long MPmemcmp( const void *buf1, const void *buf2, unsigned long count );

void *MPmemcpy( void *dest, const void *src, unsigned long count );

long MPstrcmp( const char *string1, const char *string2 );
//long MPstricmp( const char *string1, const char *string2 );
unsigned long MPstrlen( const char *string );
char *MPstrcpy( char *string1, const char *string2 );
char *MPstrncpy( char *string1, const char *string2, unsigned long count );
char *MPstrcat( char *string1, const char *string2 );

void *MPmemset( void *dest, int c, unsigned long count );

int MPstricmp( const MP_Text* string1, const MP_Text* string2 );

#include <mpcwcstr.h>
void MPmbtowc(mpcwcstring& outstring, const char* ptext, int length = -1);
void MPwctomb(std::string& outstring, const MP_Text* ptext, int length = -1);


//
//CHANGE LOG
//96.2.1 - Ichiriki - 作成
//96.6.10 - Ichiriki - Integ用変更
//99.06.09 - Tashiro - V4開発: MPmenset追加
// V5
//2002.08.01 - Tashiro - AR8199 MPstricmpを追加
// 64bit
//2005.07.26 - Kudo - MPtimeを削除
