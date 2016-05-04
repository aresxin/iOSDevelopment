/*
 * jerror.h
 *
 * Copyright (C) 1994-1995, Thomas G. Lane.
 * This file is part of the Independent JPEG Group's software.
 * For conditions of distribution and use, see the accompanying README file.
 *
 * This file defines the error and message codes for the JPEG library.
 * Edit this file to add new codes, or to translate the message strings to
 * some other language.
 * A set of error-reporting macros are defined too.  Some applications using
 * the JPEG library may wish to include this file to get the error codes
 * and/or the macros.
 */

/*
 * To define the enum list of message codes, include this file without
 * defining macro JMESSAGE.  To create a message string table, include it
 * again with a suitable JMESSAGE definition (see jerror.c for an example).
 */
#ifndef _JERROR_H_
#define _JERROR_H_
class JpegLibException {};

enum J_MESSAGE_CODE {
    /* For maintenance convenience, list is alphabetical by message code name */
    JERR_ARITH_NOTIMPL,//"Sorry, there are legal restrictions on arithmetic coding"
    JERR_BAD_ALIGN_TYPE,//"ALIGN_TYPE is wrong, please fix"
    JERR_BAD_ALLOC_CHUNK,//"MAX_ALLOC_CHUNK is wrong, please fix"
    JERR_BAD_BUFFER_MODE,//"Bogus buffer control mode"
    JERR_BAD_COMPONENT_ID,//"Invalid component ID %d in SOS"
    JERR_BAD_DCTSIZE,// "IDCT output block size %d not supported")
    JERR_BAD_IN_COLORSPACE,// "Bogus input colorspace")
    JERR_BAD_J_COLORSPACE, //"Bogus JPEG colorspace")
    JERR_BAD_LENGTH,// "Bogus marker length")
    JERR_BAD_LIB_VERSION,//"Wrong JPEG library version: library is %d, caller expects %d")
    JERR_BAD_MCU_SIZE,// "Sampling factors too large for interleaved scan")
    JERR_BAD_POOL_ID,// "Invalid memory pool code %d")
    JERR_BAD_PRECISION,// "Unsupported JPEG data precision %d")
    JERR_BAD_PROGRESSION,//"Invalid progressive parameters Ss=%d Se=%d Ah=%d Al=%d")
    JERR_BAD_PROG_SCRIPT,//"Invalid progressive parameters at scan script entry %d")
    JERR_BAD_SAMPLING,// "Bogus sampling factors")
    JERR_BAD_SCAN_SCRIPT,// "Invalid scan script at entry %d")
    JERR_BAD_STATE,// "Improper call to JPEG library in state %d")
    JERR_BAD_STRUCT_SIZE,//"JPEG parameter struct mismatch: library thinks size is %u, caller expects %u")
    JERR_BAD_VIRTUAL_ACCESS,// "Bogus virtual array access")
    JERR_BUFFER_SIZE,// "Buffer passed to JPEG library is too small")
    JERR_CANT_SUSPEND,// "Suspension not allowed here")
    JERR_CCIR601_NOTIMPL,// "CCIR601 sampling not implemented yet")
    JERR_COMPONENT_COUNT,// "Too many color components: %d, max %d")
    JERR_CONVERSION_NOTIMPL,// "Unsupported color conversion request")
    JERR_DAC_INDEX,// "Bogus DAC index %d")
    JERR_DAC_VALUE,// "Bogus DAC value 0x%x")
    JERR_DHT_COUNTS,// "Bogus DHT counts")
    JERR_DHT_INDEX,// "Bogus DHT index %d")
    JERR_DQT_INDEX,// "Bogus DQT index %d")
    JERR_EMPTY_IMAGE,// "Empty JPEG image (DNL not supported)")
    JERR_EMS_READ,// "Read from EMS failed")
    JERR_EMS_WRITE,// "Write to EMS failed")
    JERR_EOI_EXPECTED,// "Didn't expect more than one scan")
    JERR_FILE_READ,// "Input file read error")
    JERR_FILE_WRITE,// "Output file write error --- out of disk space?")
    JERR_FRACT_SAMPLE_NOTIMPL,// "Fractional sampling not implemented yet")
    JERR_HUFF_CLEN_OVERFLOW,// "Huffman code size table overflow")
    JERR_HUFF_MISSING_CODE,// "Missing Huffman code table entry")
    JERR_IMAGE_TOO_BIG,// "Maximum supported image dimension is %u pixels")
    JERR_INPUT_EMPTY,// "Empty input file")
    JERR_INPUT_EOF,// "Premature end of input file")
    JERR_MISMATCHED_QUANT_TABLE,//"Cannot transcode due to multiple use of quantization table %d")
    JERR_MISSING_DATA,// "Scan script does not transmit all data")
    JERR_MODE_CHANGE,// "Invalid color quantization mode change")
    JERR_NOTIMPL,// "Not implemented yet")
    JERR_NOT_COMPILED,// "Requested feature was omitted at compile time")
    JERR_NO_BACKING_STORE,// "Backing store not supported")
    JERR_NO_HUFF_TABLE,// "Huffman table 0x%02x was not defined")
    JERR_NO_IMAGE,// "JPEG datastream contains no image")
    JERR_NO_QUANT_TABLE,// "Quantization table 0x%02x was not defined")
    JERR_NO_SOI,// "Not a JPEG file: starts with 0x%02x 0x%02x")
    JERR_OUT_OF_MEMORY,// "Insufficient memory (case %d)")
    JERR_QUANT_COMPONENTS,//"Cannot quantize more than %d color components")
    JERR_QUANT_FEW_COLORS,// "Cannot quantize to fewer than %d colors")
    JERR_QUANT_MANY_COLORS,// "Cannot quantize to more than %d colors")
    JERR_SOF_DUPLICATE,// "Invalid JPEG file structure: two SOF markers")
    JERR_SOF_NO_SOS,// "Invalid JPEG file structure: missing SOS marker")
    JERR_SOF_UNSUPPORTED,// "Unsupported JPEG process: SOF type 0x%02x")
    JERR_SOI_DUPLICATE,// "Invalid JPEG file structure: two SOI markers")
    JERR_SOS_NO_SOF,// "Invalid JPEG file structure: SOS before SOF")
    JERR_TFILE_CREATE,// "Failed to create temporary file %s")
    JERR_TFILE_READ,// "Read failed on temporary file")
    JERR_TFILE_SEEK,// "Seek failed on temporary file")
    JERR_TFILE_WRITE,//"Write failed on temporary file --- out of disk space?")
    JERR_TOO_LITTLE_DATA,// "Application transferred too few scanlines")
    JERR_UNKNOWN_MARKER,// "Unsupported marker type 0x%02x")
    JERR_VIRTUAL_BUG,// "Virtual array controller messed up")
    JERR_WIDTH_OVERFLOW,// "Image too wide for this implementation")
    JERR_XMS_READ,// "Read from XMS failed")
    JERR_XMS_WRITE,// "Write to XMS failed")
    JMSG_COPYRIGHT,// JCOPYRIGHT)
    JMSG_VERSION,// JVERSION)
    JTRC_16BIT_TABLES,//"Caution: quantization tables are too coarse for baseline JPEG")
    JTRC_ADOBE,//"Adobe APP14 marker: version %d, flags 0x%04x 0x%04x, transform %d")
    JTRC_APP0,// "Unknown APP0 marker (not JFIF), length %u")
    JTRC_APP14,// "Unknown APP14 marker (not Adobe), length %u")
    JTRC_DAC,// "Define Arithmetic Table 0x%02x: 0x%02x")
    JTRC_DHT,// "Define Huffman Table 0x%02x")
    JTRC_DQT,// "Define Quantization Table %d  precision %d")
    JTRC_DRI,// "Define Restart Interval %u")
    JTRC_EMS_CLOSE,// "Freed EMS handle %u")
    JTRC_EMS_OPEN,// "Obtained EMS handle %u")
    JTRC_EOI,// "End Of Image")
    JTRC_HUFFBITS,// "        %3d %3d %3d %3d %3d %3d %3d %3d")
    JTRC_JFIF,// "JFIF APP0 marker, density %dx%d  %d")
    JTRC_JFIF_BADTHUMBNAILSIZE,//"Warning: thumbnail image size does not match data length %u")
    JTRC_JFIF_MINOR,// "Unknown JFIF minor revision number %d.%02d")
    JTRC_JFIF_THUMBNAIL,// "    with %d x %d thumbnail image")
    JTRC_MISC_MARKER,// "Skipping marker 0x%02x, length %u")
    JTRC_PARMLESS_MARKER,// "Unexpected marker 0x%02x")
    JTRC_QUANTVALS,// "        %4u %4u %4u %4u %4u %4u %4u %4u")
    JTRC_QUANT_3_NCOLORS,// "Quantizing to %d = %d*%d*%d colors")
    JTRC_QUANT_NCOLORS,// "Quantizing to %d colors")
    JTRC_QUANT_SELECTED,// "Selected %d colors for quantization")
    JTRC_RECOVERY_ACTION,// "At marker 0x%02x, recovery action %d")
    JTRC_RST,// "RST%d")
    JTRC_SMOOTH_NOTIMPL,//"Smoothing not supported with nonstandard sampling ratios")
    JTRC_SOF,// "Start Of Frame 0x%02x: width=%u, height=%u, components=%d")
    JTRC_SOF_COMPONENT,// "    Component %d: %dhx%dv q=%d")
    JTRC_SOI,// "Start of Image")
    JTRC_SOS,// "Start Of Scan: %d components")
    JTRC_SOS_COMPONENT,// "    Component %d: dc=%d ac=%d")
    JTRC_SOS_PARAMS,// "  Ss=%d, Se=%d, Ah=%d, Al=%d")
    JTRC_TFILE_CLOSE,// "Closed temporary file %s")
    JTRC_TFILE_OPEN,// "Opened temporary file %s")
    JTRC_UNKNOWN_IDS,//"Unrecognized component IDs %d %d %d, assuming YCbCr")
    JTRC_XMS_CLOSE,// "Freed XMS handle %u")
    JTRC_XMS_OPEN,// "Obtained XMS handle %u")
    JWRN_ADOBE_XFORM,// "Unknown Adobe color transform code %d")
    JWRN_BOGUS_PROGRESSION,//"Inconsistent progression sequence for component %d coefficient %d")
    JWRN_EXTRANEOUS_DATA,//"Corrupt JPEG data: %u extraneous bytes before marker 0x%02x")
    JWRN_HIT_MARKER,// "Corrupt JPEG data: premature end of data segment")
    JWRN_HUFF_BAD_CODE,// "Corrupt JPEG data: bad Huffman code")
    JWRN_JFIF_MAJOR,// "Warning: unknown JFIF revision number %d.%02d")
    JWRN_JPEG_EOF,// "Premature end of JPEG file")
    JWRN_MUST_RESYNC,//"Corrupt JPEG data: found marker 0x%02x instead of RST%d")
    JWRN_NOT_SEQUENTIAL,// "Invalid SOS parameters for sequential JPEG")
    JWRN_TOO_MUCH_DATA // "Application transferred too many scanlines")
};

/* Macros to simplify using the error and trace message stuff */
/* The first parameter is either type of cinfo pointer */

/* Fatal errors (print message and exit) */
template <class C, class E>
void ERREXIT(C cinfo, E code) {
    cinfo->err->msg_code = code;
    (*cinfo->err->error_exit)((j_common_ptr)cinfo);
}
template <class C, class E, class I>
void ERREXIT1(C cinfo, E code, I p1) {
    cinfo->err->msg_code = code;
    cinfo->err->msg_parm.i[0] = p1;
    (*cinfo->err->error_exit)((j_common_ptr)cinfo);
}
template <class C, class E>
void ERREXIT2(C cinfo, E code, int p1, int p2) {
    cinfo->err->msg_code = code;
    cinfo->err->msg_parm.i[0] = p1;
    cinfo->err->msg_parm.i[1] = p2;
    (*cinfo->err->error_exit)((j_common_ptr)cinfo);
}
template <class C, class E>
void ERREXIT3(C cinfo, E code, int p1, int p2, int p3) {
    cinfo->err->msg_code = code;
    cinfo->err->msg_parm.i[0] = p1;
    cinfo->err->msg_parm.i[1] = p2;
    cinfo->err->msg_parm.i[2] = p3;
    (*cinfo->err->error_exit)((j_common_ptr)cinfo);
}
template <class C, class E>
void ERREXIT4(C cinfo, E code, int p1, int p2, int p3, int p4) {
    cinfo->err->msg_code = code;
    cinfo->err->msg_parm.i[0] = p1;
    cinfo->err->msg_parm.i[1] = p2;
    cinfo->err->msg_parm.i[2] = p3;
    cinfo->err->msg_parm.i[3] = p4;
    (*cinfo->err->error_exit)((j_common_ptr)cinfo);
}
template <class C, class E>
void ERREXITS(C cinfo, E code, char *str) {
    cinfo->err->msg_code = code;
    strncpy(cinfo->err->msg_parm.s, str, JMSG_STR_PARM_MAX);
    (*cinfo->err->error_exit)((j_common_ptr)cinfo);
}

/* Nonfatal errors (we can keep going, but the data is probably corrupt) */
template <class C, class E>
void WARNMS(C cinfo, E code) {
    cinfo->err->msg_code = code;
    (*cinfo->err->emit_message)((j_common_ptr)cinfo, -1);
}
template <class C, class E, class I>
void WARNMS1(C cinfo, E code, I p1) {
    cinfo->err->msg_code = code;
    cinfo->err->msg_parm.i[0] = p1;
    (*cinfo->err->emit_message)((j_common_ptr)cinfo, -1);
}
template <class C, class E, class I, class J>
void WARNMS2(C cinfo, E code, I p1, J p2) {
    cinfo->err->msg_code = code;
    cinfo->err->msg_parm.i[0] = p1;
    cinfo->err->msg_parm.i[1] = p2;
    (*cinfo->err->emit_message)((j_common_ptr)cinfo, -1);
}

/* Informational/debugging messages */
template <class C, class E>
void TRACEMS(C cinfo, int lvl, E code) {
    cinfo->err->msg_code = code;
    (*cinfo->err->emit_message)((j_common_ptr)cinfo, lvl);
}
template <class C, class E, class I>
void TRACEMS1(C cinfo, int lvl, E code, I p1) {
    cinfo->err->msg_code = code;
    cinfo->err->msg_parm.i[0] = p1;
    (*cinfo->err->emit_message)((j_common_ptr)cinfo, lvl);
}
template <class C, class E, class I, class J>
void TRACEMS2(C cinfo, int lvl, E code, I p1, J p2) {
    cinfo->err->msg_code = code;
    cinfo->err->msg_parm.i[0] = p1;
    cinfo->err->msg_parm.i[1] = p2;
    (*cinfo->err->emit_message)((j_common_ptr)cinfo, lvl);
}
template <class C, class E, class I, class J, class K>
void TRACEMS3(C cinfo, int lvl, E code, I p1, J p2, K p3) {
    int *_mp = cinfo->err->msg_parm.i;
    _mp[0] = p1;
    _mp[1] = p2;
    _mp[2] = p3;
    cinfo->err->msg_code = code;
    (*cinfo->err->emit_message)((j_common_ptr)cinfo, lvl);
}
template <class C, class E, class I, class J, class K, class L>
void TRACEMS4(C cinfo, int lvl, E code, I p1, J p2, K p3, L p4) {
    int *_mp = cinfo->err->msg_parm.i;
    _mp[0] = p1;
    _mp[1] = p2;
    _mp[2] = p3;
    _mp[3] = p4;
    cinfo->err->msg_code = code;
    (*cinfo->err->emit_message)((j_common_ptr)cinfo, lvl);
}
template <class C, class E, class I, class J, class K, class L, class M, class N, class O, class P>
void TRACEMS8(C cinfo, int lvl, E code, I p1, J p2, K p3, L p4, M p5, N p6, O p7, P p8) {
    int *_mp = cinfo->err->msg_parm.i;
    _mp[0] = p1;
    _mp[1] = p2;
    _mp[2] = p3;
    _mp[3] = p4;
    _mp[4] = p5;
    _mp[5] = p6;
    _mp[6] = p7;
    _mp[7] = p8;
    cinfo->err->msg_code = code;
    (*cinfo->err->emit_message)((j_common_ptr)cinfo, lvl);
}
template <class C, class E>
void TRACEMSS(C cinfo, int lvl, E code, char *str) {
    cinfo->err->msg_code = code;
    strncpy(cinfo->err->msg_parm.s, str, JMSG_STR_PARM_MAX);
    (*cinfo->err->emit_message)((j_common_ptr)cinfo, lvl);
}

#endif /* !_JERROR_H_ */
//CHANGE LOG
//97.10.03 - matsu - modified
