#ifndef _CDJPEG_H_
#define _CDJPEG_H_

/*
 * cdjpeg.h
 *
 * Copyright (C) 1994-1996, Thomas G. Lane.
 * This file is part of the Independent JPEG Group's software.
 * For conditions of distribution and use, see the accompanying README file.
 *
 * This file contains common declarations for the sample applications
 * cjpeg and djpeg.  It is NOT used by the core JPEG library.
 */

#define JPEG_CJPEG_DJPEG	/* define proper options in jconfig.h */
#define JPEG_INTERNAL_OPTIONS	/* cjpeg.c,djpeg.c need to see xxx_SUPPORTED */
#include "jinclude.h"
#include "jpeglib.h"
#include "jerror.h"		/* get library error codes too */
#include "cderror.h"		/* get application-specific error codes */


class ReadResource;
class WriteResource;
/*
 * Object interface for cjpeg's source file decoding modules
 */
typedef struct cjpeg_source_struct * cjpeg_source_ptr;

struct cjpeg_source_struct {
  JMETHOD(void, start_input, (j_compress_ptr cinfo, cjpeg_source_ptr sinfo, void *arg));
  JMETHOD(JDIMENSION, get_pixel_rows, (j_compress_ptr cinfo, cjpeg_source_ptr sinfo, unsigned long line));
  JMETHOD(void, finish_input, (j_compress_ptr cinfo, cjpeg_source_ptr sinfo));

  //FILE *input_file;
  ReadResource *input_file;

  JSAMPARRAY buffer;
  JDIMENSION buffer_height;
};


/*
 * Object interface for djpeg's output file encoding modules
 */

typedef struct djpeg_dest_struct * djpeg_dest_ptr;

struct djpeg_dest_struct {
  /* start_output is called after jpeg_start_decompress finishes.
   * The color map will be ready at this time, if one is needed.
   */
  JMETHOD(void, start_output, (j_decompress_ptr cinfo,
			       djpeg_dest_ptr dinfo));
  /* Emit the specified number of pixel rows from the buffer. */
  JMETHOD(void, put_pixel_rows, (j_decompress_ptr cinfo,
				 djpeg_dest_ptr dinfo,
				 unsigned char *));
  /* Finish up at the end of the image. */
  JMETHOD(void, finish_output, (j_decompress_ptr cinfo,
				djpeg_dest_ptr dinfo));

  /* Target file spec; filled in by djpeg.c after object is created. */
  //FILE * output_file;
  WriteResource *output_file;

  /* Output pixel-row buffer.  Created by module init or start_output.
   * Width is cinfo->output_width * cinfo->output_components;
   * height is buffer_height.
   */
  JSAMPARRAY buffer;
  JDIMENSION buffer_height;
};


/*
 * cjpeg/djpeg may need to perform extra passes to convert to or from
 * the source/destination file format.  The JPEG library does not know
 * about these passes, but we'd like them to be counted by the progress
 * monitor.  We use an expanded progress monitor object to hold the
 * additional pass count.
 */

struct cdjpeg_progress_mgr {
  struct jpeg_progress_mgr pub;	/* fields known to JPEG library */
  int completed_extra_passes;	/* extra passes completed */
  int total_extra_passes;	/* total extra */
  /* last printed percentage stored here to avoid multiple printouts */
  int percent_done;
};

typedef struct cdjpeg_progress_mgr * cd_progress_ptr;

/* Module selection routines for I/O modules. */

EXTERN(cjpeg_source_ptr) jinit_read_bmp JPP((j_compress_ptr cinfo));
EXTERN(djpeg_dest_ptr) jinit_write_bmp JPP((j_decompress_ptr cinfo,
					    Boolean is_os2));
/* cjpeg support routines (in rdswitch.c) */

EXTERN(Boolean) read_quant_tables JPP((j_compress_ptr cinfo, char * filename,
				    int scale_factor, Boolean force_baseline));
EXTERN(Boolean) read_scan_script JPP((j_compress_ptr cinfo, char * filename));
EXTERN(Boolean) set_quant_slots JPP((j_compress_ptr cinfo, char *arg));
EXTERN(Boolean) set_sample_factors JPP((j_compress_ptr cinfo, char *arg));

/* djpeg support routines (in rdcolmap.c) */

EXTERN(void) read_color_map JPP((j_decompress_ptr cinfo, FILE * infile));

/* common support routines (in cdjpeg.c) */

EXTERN(void) enable_signal_catcher JPP((j_common_ptr cinfo));
EXTERN(void) start_progress_monitor JPP((j_common_ptr cinfo,
					 cd_progress_ptr progress));
EXTERN(void) end_progress_monitor JPP((j_common_ptr cinfo));
EXTERN(Boolean) keymatch JPP((char * arg, const char * keyword, int minchars));
EXTERN(FILE *) read_stdin JPP((void));
EXTERN(FILE *) write_stdout JPP((void));

/* miscellaneous useful macros */

#ifdef DONT_USE_B_MODE		/* define mode parameters for fopen() */
#define READ_BINARY	"r"
#define WRITE_BINARY	"w"
#else
#define READ_BINARY	"rb"
#define WRITE_BINARY	"wb"
#endif

#ifndef EXIT_FAILURE		/* define exit() codes if not provided */
#define EXIT_FAILURE  1
#endif
#ifndef EXIT_SUCCESS
#ifdef VMS
#define EXIT_SUCCESS  1		/* VMS is very nonstandard */
#else
#define EXIT_SUCCESS  0
#endif
#endif
#ifndef EXIT_WARNING
#ifdef VMS
#define EXIT_WARNING  1		/* VMS is very nonstandard */
#else
#define EXIT_WARNING  2
#endif
#endif

#endif /* !_CDJPEG_H_ */
//CHANGE LOG
//97.10.03 - matsu - modified
