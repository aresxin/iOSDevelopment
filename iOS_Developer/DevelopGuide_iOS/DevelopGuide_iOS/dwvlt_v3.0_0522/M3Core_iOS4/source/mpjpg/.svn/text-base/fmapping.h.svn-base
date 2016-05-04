// File: fmapping.h
// Authors: Ryoji Matsumura
// Copyright (C) 1997 by Fuji Xerox Co., Ltd. All rights reserved.

#ifndef _FILE_MAPPING_H_
#define _FILE_MAPPING_H_

//#include <windows.h>
#include "mpc_api.h"

class FileMapping {
public:
    enum access_mode { read, read_write };

    //mode = read: filenameは存在しなければならない
    //     = read_write: filenameが存在しなければファイルを作る
    //size = 0: MAXサイズ(ファイルサイズ)
    //     = !0: 最大マップサイズ
    //offset: マップする位置を指定

    FileMapping(const char *filename, access_mode mode, unsigned long size = 0, unsigned long offset = 0);

	//07.09.13 - M.Chikyu UNICODE対応
    FileMapping(const MP_WPath *filenameW, access_mode mode, unsigned long size = 0, unsigned long offset = 0);

    //この関数は、現在のseekポイントを基準にマップする
    //mode: file-openしたときのモードと同等なモードを指定する
    //size =  0: MAXサイズ(ファイルサイズ)
    //     = !0: 現在のseekポイントからの最大マップサイズ
    //offset: 現在のseekポイントからの、マップする位置を指定
    FileMapping(HANDLE hFile, access_mode mode, unsigned long size = 0, unsigned long offset = 0);

    //適当なテンポラリファイルを作成し、read_writeでマップする。
    //size = 0のときはエラー
    FileMapping(unsigned long size); //for temp-file
    ~FileMapping();

    unsigned char *get_pointer() const {
        return isOK() ? base_ + offset_ : 0;
    }
    int isOK() const {
        return state_ == ok ? 1 : 0;
    }
    DWORD get_error_code() const {
        return error_code_;
    }

private:
    int create_file_mapping(HANDLE hFile, access_mode mode, unsigned long size, unsigned long offset);
    int delete_file_mapping();

	//07.09.13 - M.Chikyu UNICODE対応
	void InitObject(const MP_WPath *filenameW, access_mode mode, unsigned long size, unsigned long offset);

private:
    HANDLE hMap_;
    HANDLE hFile_;
    unsigned char *base_;
    unsigned long offset_;
    int is_self_open_;
    enum { ok = 0, error = 1 } state_;
    DWORD error_code_;
};
#endif

//CHANGE LOG
//97.10.03 - matsu - 新規作成(V3)
//98.05.11 - matsu - V3.1対応: File I/O系のエラーを返せるようにした。get_error_code()を追加。
//07.09.13 - M.Chikyu UNICODE対応
