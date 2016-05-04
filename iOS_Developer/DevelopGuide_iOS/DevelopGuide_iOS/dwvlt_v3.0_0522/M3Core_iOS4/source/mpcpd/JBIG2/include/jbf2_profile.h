/*
 * Copyright (c) 2001-2002 by Fuji Xerox Co., Ltd. All rights reserved.
 *
 * $Id: jbf2_profile.h,v 1.4 2009/12/22 08:11:17 chikyu Exp $
 */

#ifndef JBF2_PROFILE_H
#define JBF2_PROFILE_H

#include "jbf2_io.h"

#define JBF2_PROFILE(x) ((JBF2Profile*)(x))
typedef struct _JBF2Profile JBF2Profile;

JBF2Profile	*jbf2_profile_new		(JBF2Error	*error);
void		 jbf2_profile_free		(JBF2Profile	*profile);
void		 jbf2_profile_read		(JBF2Profile	*profile,
						 JBF2IO		*io);
JBF2UInt32	 jbf2_profile_count		(JBF2Profile	*profile);
JBF2UInt32	 jbf2_profile_nth		(JBF2Profile	*profile,
						 JBF2UInt32	 n);

#endif /* JBF2_PROFILE_H */

