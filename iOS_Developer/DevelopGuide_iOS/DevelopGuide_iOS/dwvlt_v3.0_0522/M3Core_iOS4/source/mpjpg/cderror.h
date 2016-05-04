/*
 * cderror.h
 *
 * Copyright (C) 1994, Thomas G. Lane.
 * This file is part of the Independent JPEG Group's software.
 * For conditions of distribution and use, see the accompanying README file.
 *
 * This file defines the error and message codes for the cjpeg/djpeg
 * applications.  These strings are not needed as part of the JPEG library
 * proper.
 * Edit this file to add new codes, or to translate the message strings to
 * some other language.
 */

/*
 * To define the enum list of message codes, include this file without
 * defining macro JMESSAGE.  To create a message string table, include it
 * again with a suitable JMESSAGE definition (see jerror.c for an example).
 */
#ifndef _CDERROR_H_
#define _CDERROR_H_

enum ADDON_MESSAGE_CODE {
    JERR_BMP_BADCMAP = 1000,
    JERR_BMP_BADDEPTH,
    JERR_BMP_BADHEADER,
    JERR_BMP_BADPLANES,
    JERR_BMP_COLORSPACE,
    JERR_BMP_COMPRESSED,
    JERR_BMP_NOT
};

#endif /* !_CDERROR_H_ */

//CHANGE LOG
//97.10.03 - matsu - modified(V3)

