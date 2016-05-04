//
// readOnlyData.h -- temporary file handler of ACCES for DocuWorks
// ACCES : Automatic Compression Choice on Estimated Statistics
//
// Copyright (C) 2000 by Fuji Xerox Co., Ltd.
// All rights reserved.
//
// Written: Jul.18,2000 by YOKOSE Taro, STD/CP&S/DPC, Fuji Xerox Co., Ltd.
//
// Description
//
//
//
#ifndef _READONLYDATA_H_
#define _READONLYDATA_H_


class CReadOnlyData {
public:
    virtual long Seek(const long seek_pos) = 0;  // **現在の位置から**
    virtual long Read(void * buff, const long size) = 0;
    enum rodState {BADFILE = -2, EOFILE = -1, GOOD = 1};
};



#endif // #ifndef _READONLYDATA_H_

