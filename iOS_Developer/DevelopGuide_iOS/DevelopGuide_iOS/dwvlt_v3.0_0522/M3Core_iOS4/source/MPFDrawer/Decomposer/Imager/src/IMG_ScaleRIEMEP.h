/* IMG_ScaleRIEMEP.h */

//  #include "IMG_Common.h"
//  #include "IMG_Context.h"
//  #include "IMG_Matrix.h"

// リングバッファのための構造体
typedef struct {
    unsigned char* idata;
    unsigned char* rbufptr;
    unsigned char* tmpbufptr;
    unsigned char* tmpbuf;
    int  width;
    int  height;
    int  chan;
    int  ilines;
    int  xoffset;
    int  yoffset;
    unsigned char* buf[6]; 
} RingBuffer;


/* 2x2ブロック特徴量を表す構造体*/
typedef struct {
    int fdirec;
    int fdirec90;
    unsigned char exception;
    unsigned char exception90;
    unsigned char initdirec;
    unsigned char flatness;
    unsigned char patterns;
} BlockCharacteristics;

/* エッジパターン検出のための構造体*/
typedef struct {
    int ow;
    int chan;
    int olines;
    BlockCharacteristics *bcptr;    /*ブロック特徴量バッファへの先頭ポインタ*/
    BlockCharacteristics *bcbuf[3]; /*ブロック特徴量リングバッファへのポインタ*/
    const int *atbl;                /*ArcTangentテーブル*/
} detectAngle;

/* 2x2ブロック拡大のための構造体*/
typedef struct {
    unsigned char* aptr;      /*エッジパターンバッファへのポインタ*/
    unsigned char* abuf;      /*エッジパターンバッファへのポインタ*/
    int ow;
    int ilen;
    int* eptr;
    int* optr;
    int* ebuf[4];             /*エッジ強調画像用リングバッファへのポインタ*/
    int* obuf[4];             /*出力画像用リングバッファへのポインタ*/
    unsigned char* mulptr;  
    unsigned char* multi[2];  /*１画素出力するための重み係数（多重度）*/
} enlargeBlock;

