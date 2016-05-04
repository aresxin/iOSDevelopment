/*
 * Copyright (c) 2001-2002 by Fuji Xerox Co., Ltd. All rights reserved.
 *
 * $Id: jbf2_list.h,v 1.4 2009/12/22 08:11:18 chikyu Exp $
 */

#ifndef JBF2_LIST_H
#define JBF2_LIST_H

#include "jbf2_error.h"
#include "jbf2_types.h"

#define JBF2_LIST(x) ((JBF2List*)(x))
typedef struct _JBF2List JBF2List;


JBF2List	*jbf2_list_new		(JBF2Error	*error,
					 JBF2Pointer	 data);
JBF2List	*jbf2_list_free		(JBF2List	*list);
void		 jbf2_list_free_all	(JBF2List	*list);
JBF2List	*jbf2_list_concat	(JBF2List	*list1,
					 JBF2List	*list2);
JBF2List	*jbf2_list_first	(JBF2List	*list);
JBF2List	*jbf2_list_last		(JBF2List	*list);
JBF2List	*jbf2_list_prev		(JBF2List	*list);
JBF2List	*jbf2_list_next		(JBF2List	*list);
void		 jbf2_list_foreach	(JBF2List	*list,
					 JBF2Func1	 func);
void		 jbf2_list_foreach_with	(JBF2List	*list,
					 JBF2Func2	 func,
					 JBF2Pointer	 user_data);
JBF2Pointer	 jbf2_list_find		(JBF2List	*list,
					 JBF2Compare	 func,
					 JBF2Pointer	 user_data);
JBF2Pointer	 jbf2_list_get_data	(JBF2List	*list);
void		 jbf2_list_set_data	(JBF2List	*list,
					 JBF2Pointer	 data);

#endif /* JBF2_LIST_H */
