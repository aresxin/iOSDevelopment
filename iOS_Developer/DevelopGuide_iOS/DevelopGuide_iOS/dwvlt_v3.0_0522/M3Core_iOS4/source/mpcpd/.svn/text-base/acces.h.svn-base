//
// acces.h -- library of ACCES for DocuWorks
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

#ifndef _ACCES_H_
#define _ACCES_H_
#include <exception>
#include "readonlydata.h"

//////////////////// Exception class "CAccesException"
///
class CAccesException : public std::exception {
private:
    const int error;

	//07.09.13 - M.Chikyu UNICODE対応
	const CAccesException& operator=(const CAccesException&) {return *this;};

public:
    enum {
	ACCES_NO_ERROR = 0, ACCES_BAD_ALLOC = -1, ACCES_BAD_FILE = -2,
	ACCES_INVALID_PARAM = -4
    };
    CAccesException(const int E = 0) throw()
	: error(E) {};
    virtual ~CAccesException() throw() {};
    const int accesErrno() const {return error;}
};

//////////////////// Class "CAcces"
///
class CAcces {
private:
    //////////////////// Internal type declaration
    ///
    typedef struct tagJLTH JLTH;

    //////////////////// Internal member attributes
    ///
    CReadOnlyData	*file;
    const int		width;
    const int		height;
    const int		bytesPerPel;
    int			suggedSF;
    double		data0;
    double		data1;

    //////////////////// Internal member functions
    ///
    CAcces(const CAcces &);		// dummy of copy constructor
    void predSim(   int &, int &, unsigned char *,
		    const int, const int, const int);
    void calcData(  double &, double &, CReadOnlyData *,
		    const int, const int, const int);
    template<class T> void Allocator(T *& pt, const size_t size = 1);
    template<class T> void Deallocator(T *& pt);
    int nearestElder(const int, JLTH const *);

	//07.09.13 - M.Chikyu UNICODE対応
	// 代入演算子は使用しない
	const CAcces& operator=(const CAcces&) {return *this;};

public:
    //////////////////// Return value
    ///
    enum AccesResult {
	ALLA = 1, JPEG = 2, OKD = 3
    };

    //////////////////// Member functions
    ///
    CAcces( CReadOnlyData * pROD,		// pointer to CReadOnlyData
	    const int	biWidth,		// width in pixels
	    const int 	biHeight,		// height in pixels
	    const int	biDepth,		// depth in bits
	    const int	biPelsPerMeter = 11811, // resolution
	    const int 	baseSF = 90,		// standard SF
	    const int	baseReso = 11811);	// standard resolution
    ~CAcces() {};
    int selCompression(const int = 0);

    ///
    /// getSF - get SF tuned according to input resolution
    ///
    int getSF() {return suggedSF;};

    ///
    /// setSF - state SF with clipping
    ///
    int setSF(const int statedSF) {
	suggedSF = (statedSF < 6) ? 6 : statedSF;
	suggedSF = (suggedSF > 1000) ? 1000 : suggedSF;
	return suggedSF;
    };
};
#endif
