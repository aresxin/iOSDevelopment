// File: jpegmem.h
// Authors: Ryoji Matsumura
// Copyright (C) 1997 by Fuji Xerox Co., Ltd. All rights reserved.

#ifndef _JPEG_MEMORY_H_
#define _JPEG_MEMORY_H_

#include <memory>

//#if _MSC_VER >= 1100	// VC++5.0以上から必要
//	using namespace std;
//#endif

// TEMPLATE CLASS array_auto_ptr
template<class _TYPE>
class array_auto_ptr {
public:
    typedef _TYPE element_type;
    explicit array_auto_ptr(_TYPE *_P = 0) : _Owns(_P != 0), _Ptr(_P) {}
    typedef _TYPE _U;
    array_auto_ptr(const array_auto_ptr<_U>& _Y)
	: _Owns(_Y._Owns), _Ptr((_TYPE *)_Y.release()) {}
    array_auto_ptr<_TYPE>& operator=(const array_auto_ptr<_U>& _Y) {
	if ((void *)this != (void *)&_Y) {
	    if (_Owns)
		delete [] _Ptr;
	    _Owns = _Y._Owns;
	    _Ptr = (_TYPE *)_Y.release();
	}
	return (*this);
    }
    ~array_auto_ptr() {
	if (_Owns)
	    delete [] _Ptr;
    }
    operator _TYPE *() const {
	return (_Ptr);
    }
    _TYPE *get() const {
	return (_Ptr);
    }
    _TYPE *release() const {
	((array_auto_ptr<_TYPE> *)this)->_Owns = false;
        return (_Ptr);
    }
private:
    bool _Owns;
    _TYPE *_Ptr;
};

#endif
//CHANGE LOG
//97.10.03 - matsu - 新規作成(V3)
//99.01.07 - nakazawa - VC++5.0以上でコンパイルできるように、名前空間stdのusingを宣言
