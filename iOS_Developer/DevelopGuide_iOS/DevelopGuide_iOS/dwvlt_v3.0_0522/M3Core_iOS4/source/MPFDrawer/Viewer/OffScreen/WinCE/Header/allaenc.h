/*
 * allaenc.h -- Adaptive lossless (Qomolangma) encoder
 *		Limoges PLW Printer Driver version
 *
 *  Copyright(c) MCMXCIX by Fuji Xerox Co.LTD., All rights reserved.
 *  $Id: allaenc.h,v 1.4 2009/12/22 08:11:39 chikyu Exp $
 *
 *  Created: Jan.20,1999 by Masato Toho, CRL 61Lab., Fuji Xerox Co. LTD.
 *  Mar.12, 1999 Interface changes for DocuWorks
 *  Oct.29, 1999 Interface changes for Limoges rewritten in C
 *  Nov.30, 1999        Scan Line Interleave, 16bit compiler 
 *
 *  Last Modified: $Date: 2009/12/22 08:11:39 $ by $Author: chikyu $
 *
 *  Description
 *	Adaptive Encoder Class definition for Limoges version
 *
 *  Usage
 *      void *encoder;
 *      long byte;
 *      int lineCount;
 *      encoder = allaEncInit(width, height, depth);
 *      if (encoder == NULL){ return -1; }
 *
 *	for (lineCount = 0; lineCount < height; lineCount++){
 *          A_UINT8 buf[BUFSIZE];
 *
 *          read(in, line, lineSize); 
 *          bytes = allaEncLine(encoder, line, buf, BUFSIZE);
 *          if (bytes > 0) { write(out, buf, bytes); }
 *	    if (bytes < 0) break;
 *      }
 *
 *      bytes = allaEncTermintage(encoder);
 *      if (bytes > 0){ write(out, buf, bytes);
 */

#ifndef _ALLAENC_H_
#define _ALLAENC_H_

/*
 * Data Types
 */
typedef unsigned long  int A_UINT32;
typedef unsigned       int A_UINT;
typedef unsigned short int A_UINT16;
typedef unsigned char      A_UINT8;
typedef                int A_INT;
typedef          short int A_INT16;
typedef          long  int A_INT32;
typedef          char      A_INT8;

#if defined(_M_I86)
   #define	A_FAR	__far
#else
   #define	A_FAR
#endif

/*
 * Public Functions
 */
/*
 * allaEncInit -- initialize the encoder
 *                returns an encoder handler
 *                returns NULL in case of errors
 */
extern void A_FAR * 
allaEncInit(A_UINT32 biWidth,     /* image width  */
	    A_UINT32 biHeight,    /* image height */
	    A_UINT32 biBitCount); /* image depth  */

/*
 * allaEncLine -- encode one line into the buffer
 *			returns number of bytes encoded
 *                      retunrs negative number in case of errors
 */
extern A_INT32
allaEncLine(void A_FAR *allaHandle,    /* allaEncInit return value */
	    const A_UINT8 A_FAR *line, /* line to be encoded       */
	    A_UINT8 A_FAR *buffer,     /* code buffer              */
	    A_UINT32 size);            /* buffer size in byte      */

/*
 * allaEncNLines -- encode contigous lines into the buffer
 *			returns number of bytes encoded
 *                      retunrs negative number in case of errors
 */
extern A_INT32
allaEncNLines(void A_FAR *allaHandle,    /* allaEncInit return value */
	      const A_UINT8 A_FAR *rect, /* lines to be encoded */
	      A_UINT32 lineCount,	 /* number of lines     */
	      A_INT32 offset,	         /* offset b/w lines    */
	      A_UINT8 A_FAR *buffer,     /* code buffer         */
	      A_UINT32 size);            /* buffer size in byte */

/*
 * allaEncNLinesV -- encode lines into the buffer
 *			returns number of bytes encoded
 *                      retunrs negative number in case of errors
 */
extern A_INT32
allaEncNLinesV(void A_FAR *allaHandle, /* allaEncInit return value */
	      const A_UINT8 A_FAR * A_FAR *lineV, /* pointers to lines   */
	      A_UINT32 lineCount,	/* number of lines     */
	      A_UINT8 A_FAR *buffer,    /* code buffer         */
	      A_UINT32 size);           /* buffer size in byte */

/*
 * Interfaces for Scan line interleave images
 */
/*
 * allaEncLineL -- encode one line into the buffer 
 *			returns number of bytes encoded
 *                      retunrs negative number in case of errors
 */
extern A_INT32
allaEncLineL(void A_FAR *allaHandle, /* allaEncInits' return value */
	    const A_UINT8 A_FAR *comp1, /* 1st comp. to be coded  */
	    const A_UINT8 A_FAR *comp2, /* 2nd comp. to be coded  */
	    const A_UINT8 A_FAR *comp3, /* 3rd comp. to be coded  */
	    const A_UINT8 A_FAR *comp4, /* 4th comp. to be coded  */
	    A_UINT8 A_FAR *buffer,      /* code buffer            */
	    A_UINT32 size);             /* buffer size in byte    */

/*
 * allaEncNLinesLV -- encode lines into the buffer
 *			returns number of bytes encoded
 *                      retunrs negative number in case of errors
 */
extern A_INT32
allaEncNLinesLV(void A_FAR *allaHandle, /* allaEncInit's return value */
	      const A_UINT8 A_FAR * A_FAR *compV, /* pointers to components */
	      A_UINT32 lineCount,    /* number of lines     */
	      A_UINT8 A_FAR *buffer, /* code buffer         */
	      A_UINT32 size);        /* buffer size in byte */

/*
 * allaEncTerminate -- terminate the encoding
 *			returns number of bytes encoded
 *                      retunrs negative number in case of errors
 */
extern A_INT32
allaEncTerminate(void A_FAR *allaHandle, /* allaEncInit return value */
		 A_UINT8  A_FAR *buffer,     /* code buffer         */
		 A_UINT32  size);      /* buffer size in byte */

#endif

/*
 *$Log: allaenc.h,v $
 *Revision 1.4  2009/12/22 08:11:39  chikyu
 **** empty log message ***
 *
 *Revision 1.2  2009/12/22 06:45:20  chikyu
 **** empty log message ***
 *
 *Revision 1.1  2009/02/26 11:58:28  komoda
 **** empty log message ***
 *
 *Revision 1.1  2008/12/19 10:29:22  kitahashi
 *initial version
 *
 *Revision 1.1.1.1  2003/09/04 07:11:46  ito
 *LIBRARY  SOURCE
 *
 *Revision 1.5  1999/11/30 14:15:40  toho
 *Scan line interleave interfaces have added.
 *Work with 16bit compilers.
 *
 *Revision 1.4  1999/11/13 09:12:32  toho
 *Tested on VxWorks/PowerPC.
 *Add more test cases.
 *
 *Revision 1.3  1999/11/12 13:50:45  toho
 *Debugged on Windows / Intel Machine.
 *
 *Revision 1.2  1999/11/07 13:24:04  toho
 *Made compatible for 16bit compilers.
 *Cleaning up.
 *
 *Revision 1.1  1999/11/07 10:29:54  toho
 *Add files for Limoges Printer Driver.
 *C version of the encoder is now available in allaenc.c
 *
 */
