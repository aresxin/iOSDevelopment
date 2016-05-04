// File: jpgalloc.h
// Authors: Ryoji Matsumura
// Copyright (C) 1997 by Fuji Xerox Co., Ltd. All rights reserved.

#ifndef _JPEG_ALLOC_H_
#define _JPEG_ALLOC_H_

inline unsigned char *jpeg_alloc(unsigned long size) {
    return new unsigned char[size];
}
inline void jpeg_free(void *p) {
    delete [] ((unsigned char *)p);
}

#endif
//CHANGE LOG
//97.10.03 - matsu - 新規作成(V3)
