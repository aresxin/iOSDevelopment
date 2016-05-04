// File: jpgcodec.h
// Authors: Ryoji Matsumura
// Copyright (C) 1997 by Fuji Xerox Co., Ltd. All rights reserved.

#ifndef _JPEG_CODEC_H_
#define _JPEG_CODEC_H_

//#include <windows.h>
#include "win2mpf.h"

class ReadResource;
class WriteResource;
struct djpeg_dest_struct;
struct jpeg_decompress_struct;
struct jpeg_error_mgr;
struct jpeg_compress_struct;
struct cjpeg_source_struct;
class FileMapping;

class JpegCodec {
public: 
    JpegCodec();
    ~JpegCodec();

    enum body_tag { request_memory, give_memory, file };//fileは常にgive
    //bodyがsrcかつmemoryならば、give_memoryを指定すること
    //bodyがdstかつgive_memoryならば、{jpeg|bmp}.memoryにはallocated-memoryを指定すること
    union body {
        unsigned char *memory;
        HANDLE file;
        body() : memory(0) {}
    };
    struct jpeg_resource {
        unsigned long jpeg_size;
        body_tag tag;
        body jpeg;
    };
    struct bitmap_resource {
        //include palette
        unsigned long bmp_info_size;
        BITMAPINFOHEADER *bmp_info;//bmp_infoは必ずallocateする
        unsigned long bmp_size;
        body_tag tag;
        body bmp;
        bitmap_resource() : bmp_info(0) {}
    };

    typedef bitmap_resource comp_source;
    typedef jpeg_resource comp_result;
    typedef jpeg_resource decomp_source;
    typedef bitmap_resource decomp_result;

    //resultの各メンバ(ポインタ型)はcompress, decompressでallocする場合がある。
    //freeは次の4つの関数を使用する。
    static void free_comp_result(comp_result *result) {
        free_jpeg_resource(result);
    }
    static void free_decomp_result(decomp_result *result) {
        free_bmp_resource(result);
    }
    static void free_jpeg_resource(jpeg_resource *resource);
    static void free_bmp_resource(bitmap_resource *resource);

    enum dct_method_type { 
        dct_islow = 0,
        dct_ifast = 1,
        dct_float = 2
    };
    enum ColorDepth {
        color_8,
        color_24,
        gray_8
    };
    enum Scaling {
        scale_denom_1 = 1,
        scale_denom_2 = 2,
        scale_denom_4 = 4,
        scale_denom_8 = 8
    };
    struct compress_parameters {
        int quality;
        dct_method_type dct_method;
        ColorDepth color_depth;
    };
    struct decompress_parameters {
        dct_method_type dct_method;
        ColorDepth color_depth;
        Scaling scale_denom;
    };
    //pixels per meter for add_resolutions
    struct Resolutions {
        unsigned long x;
        unsigned long y;
    };

    //If these functions succeed, the return value is 0.
    //If these functions fail, the return value is -1.
#ifndef SFXVW
    int compress(const comp_source *src, comp_result *result, const compress_parameters *params = 0);
#endif //SFXVW

    int decompress(const decomp_source *src, decomp_result *result, const decompress_parameters *params = 0);

#ifndef SFXVW
    //line_compress用
    int init_line_compress(const comp_source *src, comp_result *result, const compress_parameters *params);
    int compress_line();
    int finish_line_compress(comp_result *result);
#endif //SFXVW

    //line_decompress用
    int init_line_decompress(const decomp_source *src, decomp_result *result, const decompress_parameters *params = 0);
    //result->tag = JpegCodec::give_memoryとしなければならない
    int get_decompressed_line(unsigned char *buffer);
    int finish_line_decompress();

    int read_header(const jpeg_resource *src, bitmap_resource *result);

#ifndef SFXVW
    int add_resolution(const jpeg_resource *src, const Resolutions *res, jpeg_resource *dst);
	int is_progressive();
    int add_resolution_dpi(const jpeg_resource *src, const Resolutions *res, jpeg_resource *dst);
#endif //SFXVW

private:
    //data members
    compress_parameters compress_params_;
    decompress_parameters decompress_params_;

    //private member functions
#ifndef SFXVW
    int compress_body(ReadResource *src, BITMAPINFOHEADER *bmp_info, WriteResource *dst);
#endif //SFXVW
    int decompress_body(ReadResource *src, WriteResource *dst, BITMAPINFOHEADER *bmp_info);

    int read_header_body(ReadResource *src, BITMAPINFOHEADER *bmp_info);
#ifndef SFXVW
    int add_resolution_aux(const jpeg_resource *src, const Resolutions *res, jpeg_resource *dst, int density_unit);
    int add_resolution_body(ReadResource *input_file, const Resolutions *res, WriteResource *output_file, int density_unit);
#endif //SFXVW

    int is_gray(ReadResource *src);

    //JPEGのパラメータのセット
    void set_compress_params(const compress_parameters *params) {
        compress_params_ = *params;
    }
    void set_decompress_params(const decompress_parameters *params) {
        decompress_params_ = *params;
    }

private://decompress用 privateメンバ

    //面・線単位共通の初期化
    int init_decompress(ReadResource *src, BITMAPINFOHEADER *bmp_info);
    //面・線単位共通の終了化
    int finish_decompress();

    //ライン処理初期化
    int init_line_process();
    //1ライン取得, throw JpegLibException
    int process_line();
    //ライン処理終了
    int finish_line_process();

    jpeg_decompress_struct *dinfo_;
    jpeg_error_mgr *jerr_;
    djpeg_dest_struct *dest_mgr_;

    long dest_y_;//出力するイメージのyピクセル数
    long page_bytes_;//ビットマップイメージのバイト数

    unsigned long dstLineBytes_;//出力ラインのバイト数
    unsigned char *dst_buf_;//出力ラインバッファ

    ReadResource *jpgsrc_;

private://compress用 privateメンバ
#ifndef SFXVW
    int init_compress(ReadResource *src, BITMAPINFOHEADER *bmp_info, WriteResource *dst);
    int finish_compress();
#endif //SFXVW

    jpeg_compress_struct *cinfo_;
    cjpeg_source_struct *src_mgr_;
    ReadResource *bmpsrc_;
    WriteResource *jpgdst_;
    FileMapping *fmap_;
    long comp_line_;
	int is_progressive_;

private:
    //Copy & Assignの禁止
    JpegCodec(const JpegCodec&);
    JpegCodec& operator=(const JpegCodec&);

}; // class JpegCodec

extern const JpegCodec::compress_parameters default_compress_parameters;
extern const JpegCodec::decompress_parameters default_decompress_parameters;

#endif /* !_JPEG_CODEC_H_ */

//CHANGE LOG
//97.10.03 - matsu - 新規作成(V3)
//99.09.06 - Ichiriki - V4 AR4745 自己解凍文書用ビューワサイズ削減
//00.02.03 - nakazawa - V4 AR5335対応:プログレッシブかどうかを返すI/Fを追加
//----V6開発
//2004.10.29 - Tashiro - AR11495 DPIで解像度を書き換える機能を追加
