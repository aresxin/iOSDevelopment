/*
 * Copyright (c) 2001-2002 by Fuji Xerox Co., Ltd. All rights reserved.
 *
 * $Id: unittest.h,v 1.4 2009/12/22 08:11:16 chikyu Exp $
 */

#ifndef JBFUNIT_UNITTEST_H
#define JBFUNIT_UNITTEST_H 

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif


#ifdef JBFUNIT_ENABLE_UNITTEST

#include <jbfunit.h>

#define JBFUNIT_FOREACH_CHECK_FUNCTION(macro)	\
	macro (test_jbf2_error)			\
	macro (test_jbf2_array)			\
	macro (test_jbf2_bitarray)		\
	macro (test_jbf2_list)			\
	macro (test_jbf2_io)			\
	macro (test_jbf2_bitmap)		\
	macro (test_jbf2_pixmap)		\
	macro (test_jbf2_segment)		\
	macro (test_jbf2_page)			\
	macro (test_jbf2_profile)		\
	macro (test_jbf2_extension)		\
	macro (test_jbf2_generic)		\
	macro (test_jbf2_refine)		\
	macro (test_jbf2_halftone)		\
	macro (test_jbf2_text)			\
	macro (test_jbf2_pattern)		\
	macro (test_jbf2_symbol)		\
	macro (test_jbf2_arith)			\
	macro (test_jbf2_huffman)		\
	macro (test_jbf2_document)		\
	macro (test_jbf2_memory)
/* Add new check functions to the list above this line. */

/* Generate prototypes for all functions. */

JBFUNIT_FOREACH_CHECK_FUNCTION (JBFUNIT_CHECK_FUNCTION_PROTOTYPE)

#endif /* JBFUNIT_ENABLE_UNITTEST */
#endif /* JBFUNIT_UNITTEST_H */

