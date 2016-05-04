//
// qomodec.h
//
// Copyright(C) 2000 by Fuji Xerox Co., Ltd.
// All rights reserved.
//
// Written: Sep.07,2000 by YOKOSE Taro, STD/CP&S/DPC, FujiXerox Co., Ltd.
//
// FUJIXEROX INTERNAL USE ONLY
//

#ifndef _QOMODEC_H_
#define _QOMODEC_H_

//
// QomoHuffDec class -- huffman decoder
//
class QomoHuffDec
{
// decoder status
    int status;

// input buffer
    unsigned char *buffer;
    const unsigned char *codeBuf;
    const unsigned char *bufPtr;
    const unsigned char *limit;
    unsigned int bitBuf; // bit buffer for reading huffman code
    int bitCount;        // bit remaining in bitBuf

//
// addition for callback function
//
    long	  (*readFunc)(void *, void *, unsigned long);
    void	   *clientData;
    unsigned long   bufferSize;
    long            dataSize;

// variables
//
    int            hid;
    unsigned char *codTab;			

// Methods to get bits, bytes
//
    long readBytes();
    unsigned int getByte();
    unsigned int getBits(int);
    void fillBuf();
    void fillBuf(int &, unsigned int &);
    void putBackBits(int, int);

    void skip();

    void setHID(int x);

public:
    QomoHuffDec(long (*)(void *, void *, unsigned long), 
		void *, unsigned long, unsigned long);

    QomoHuffDec(const unsigned char *buf, int size);

    ~QomoHuffDec();

// Methods to get code
//
    int  getCode();
    int  getRun();
    void getDiff(int, int *);
    int  getMarker();

    int  getStatus() { return status; }
    int  isEOF();

    void changeHID();
    void clearBuf();
    int  getCurCode() { return (bufPtr - codeBuf); }
};

//
// QomoDec class -- one object can process one image 
//
class QomoDec
{
// Error Code
   enum QomoStatus { QomoDecoding  = 1, QomoEOF = 0, QomoInvalidDepth = -1,
       QomoNoMemory  = -2, QomoHuffmanError  = -3,
       QomoCodeError = -4 };

// Decoder Status
   int status;

// Image Parameters
    int width;     // in pixel
    int height;    // in line			  
    int component; // depth / 8			  
    int lineSize;  // in byte

// compression paramters
    int outPixel;  // pixel value for out of image area
			       
// double buffer
    int            bufSize;  // buffer size in byte
    unsigned char *buffer;   // buffer address
    unsigned char *previous; // previous line
    unsigned char *current;  // current line

// Huffman Decoder
    QomoHuffDec *huffman;

// decoder variables passing from line to line
    int run;
    int orderShift;       // true just after runs expect MAXRUN
    char order[5]; 
    int lineCount;			 

//
// Decoder internal methods
//
    int decodeLine(); // decoder main routine

    void init(unsigned short);   // initialization
    void reset();  // reset decoder variables for banding
    void mru(int);
    unsigned char *expandRun(int code, unsigned char *, int count);
    unsigned char *setDiff(unsigned char *, int *);

public:
    QomoDec(long (*)(void *, void *, unsigned long), 
	    void *, unsigned long, unsigned long, 
	    unsigned long, unsigned long, unsigned short);

    QomoDec(const unsigned char *, int, 
	    unsigned long, unsigned long, unsigned short);

    ~QomoDec(); // terminate this encoder

    int getLine(const unsigned char * &);
    const unsigned char *getLine();
    
    int  getStatus() { return status; }
    void clearBuf();
    int  getCurCode() { return huffman->getCurCode(); }
};

#endif 
