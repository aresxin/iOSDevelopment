//
// qomoenc.h
//
// Copyright(C) 2000 by Fuji Xerox Co., Ltd.
// All rights reserved.
//
// Written: Sep.07,2000 by YOKOSE Taro, STD/CP&S/DPC, FujiXerox Co., Ltd.
//
// FUJIXEROX INTERNAL USE ONLY
//

#ifndef _QOMOENC_H_
#define _QOMOENC_H_

//
// QomoHuffEnc class -- huffman encoder
//
class QomoHuffEnc
{
    unsigned char *codeBuf;
    unsigned char *bufPtr;
    unsigned char *limit;

    int bitBuf;		// bit buffer left aligned to byte
    int bitCount;	// bit count from the beginning

// variables
//
    unsigned char *codTab;			      
    unsigned char *lenTab;
			       
    int hid;		// current huffman table index

// Internal Methods to put bits, bytes
//
    int putByte(const unsigned char);
    int putBits(unsigned int, const int);
    int stuff();

    int putCode(int);
    int putRun(int, int);
    int putDiff(const unsigned char);

    void setHID(int);

public:
    QomoHuffEnc(unsigned char *, int);

// Method to put code
//
    // int encodeDiff(int, const unsigned char *);
    int encodeDiff(const unsigned char *, const unsigned char *, const int);
    // int encodePlainDiff(const unsigned char diff);
    int encodeRun(int ord, int run);
    int encodeDHT();
    int encodeEOI();

    int terminate();

    int size(){ return bitCount / 8; }
    int getHID(){ return hid; }
    void clearBuf();
};

//
// QomoEnc -- Qomolangma (Adaptive lossless) encoder
//
class QomoEnc
{
    enum QomoStatus{
	QomoEncoding = 1, QomoEOF = 0, QomoInvalidDepth = -1,
	QomoNoMemory = -2, QomoHuffmanError = -3,
	QomoOverflow = -4
    };
// Data members

// Encoder Status
    int            status;

// Image Parameters
    unsigned long  width;       // in pixel
    unsigned long  height;      // in line			  
    int            component;   // number of components (depth / 8)
    int            lineSize;    // in byte without alignment
    int	           pixelOffset; // offset bytes between neighbour pixels
                                // component == 3 ? 4 : component

// Compression Parameter
    int            outPixel;  // pixel value for out of image area

// Double Buffer
    int            bufSize;   // buffer size in byte
    unsigned char *buffer;
    unsigned char *previous;  // previous line
    unsigned char *current;   // current line

// Huffman Encoder
    QomoHuffEnc *huffman;

// Encoder Variables passing from line to line
    int  run;
    int  ord;
    int  orderShift;
    char order[5]; 
    int lineCount;

// internal methods
    int encodeLine();

    void reset();
    void mru(int);

    int  findLongestRun(unsigned char *, int &);
    int  countRun(unsigned char *, int);
    void setSentinel();

    // unsigned char *computeDiff(unsigned char *, int *);

public:
    QomoEnc(unsigned char *outBuf, int bufSiz, 
	    unsigned long w, unsigned long h, unsigned short d);

    ~QomoEnc(); // terminate this encoder

    int putLine(const unsigned char *);	// compress one line
    int terminate();                    // terminate compression

    int getStatus() const { return status; }
    void clearBuf();
};

#endif
