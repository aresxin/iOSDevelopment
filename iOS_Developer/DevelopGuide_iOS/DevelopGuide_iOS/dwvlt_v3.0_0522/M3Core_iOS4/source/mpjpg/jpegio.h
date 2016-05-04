// File: jpegio.h
// Authors: Ryoji Matsumura
// Copyright (C) 1997 by Fuji Xerox Co., Ltd. All rights reserved.

#ifndef _JPEG_IO_H_
#define _JPEG_IO_H_

//#include <windows.h>
#include "win2mpf.h"

#include <stdio.h>
#include <assert.h>

class ReadResource {
public:
    ReadResource() {};
    virtual ~ReadResource() {};
    virtual unsigned long fread(unsigned char *buffer, unsigned long size) = 0;
    virtual void reset() = 0;
};

class ReadFromMemory : public ReadResource {
public:
    ReadFromMemory(unsigned char *memory, unsigned long size) :
	base_(memory), current_(memory), rest_(size), size_(size) { assert(memory); }
    ~ReadFromMemory() {};

    unsigned long fread(unsigned char *buffer, unsigned long size);
    unsigned char *get_pointer(unsigned long index) {
	return &base_[index];
    }
    void reset() { rest_ = size_; current_ = base_; }

private:
    unsigned char *current_;
    unsigned char *base_;
    unsigned long rest_;
    unsigned long size_;
};

class ReadFromFile : public ReadResource {
public:
    ReadFromFile(HANDLE handle, unsigned long size);
    ~ReadFromFile();

    unsigned long fread(unsigned char *buffer, unsigned long size);
    void reset();

private:
    enum { READ_BUFFER_SIZE = 256 * 1024 };
    unsigned char *read_buffer_;
    unsigned char *current_;
    unsigned long buf_rest_;
    unsigned long file_rest_;
    HANDLE handle_;
    unsigned long start_point_;//コンストラクト時のpositionを記憶
    unsigned long file_size_;//コンストラクタで渡されたsizeを記憶
};


class WriteResource {
public:
    WriteResource(int type) : type_(type) {};
    virtual ~WriteResource() {};
    virtual int open(unsigned long size = 0) = 0;
    virtual int close() = 0;
    virtual unsigned long fwrite(unsigned char *buffer, unsigned long size) = 0;
    virtual unsigned char *get_data() = 0;//メモリデータであれば抜き取り、残さない
    virtual void add_total_size(unsigned long size) = 0;
    //これはfwriteと併用してはいけない(memory-write-access用)
protected:
    //本当はdynamic_castで解決したいが、全モジュール(?)でコンパイルオプションを
    //設定しなければならない。また、遅くなるという懸念も。
    //ここでは、self-dynamic_castを使用する。
    int type_;
public:
    enum {
	known_memory,//WriteToKnownMemory
	unknown_memory,//WriteToUnknownMemory
	given_memory,//WriteToGivenMemory
	file//WriteToFile
    };
    int type() const { return type_; }
};

//既にサイズが確定しているかつメモリをアロケートする場合に使用
class WriteToKnownMemory : public WriteResource {
public:
    WriteToKnownMemory() :
	data_(0), current_(0), rest_(0), total_write_size_(0),
	WriteResource(WriteResource::known_memory) {}
    ~WriteToKnownMemory();

    int open(unsigned long size); // memory alloc
    int close() { return 0; } // no work
    unsigned long fwrite(unsigned char *buffer, unsigned long size);
    unsigned char *get_pointer(unsigned long index) {
	return &data_[index];
    }

    unsigned long total_write_size() const { return total_write_size_; }
    unsigned char *get_data();
    void add_total_size(unsigned long size) { total_write_size_+= size; }

private:
    unsigned char *data_;
    unsigned char *current_;
    unsigned long rest_;
    unsigned long total_write_size_;
};
//既にサイズが確定しているかつメモリが与えられた場合に使用
class WriteToGivenMemory : public WriteResource {
public:
    WriteToGivenMemory(unsigned char *given_mem = 0) :
	data_(given_mem), current_(0), total_write_size_(0),
	WriteResource(WriteResource::given_memory) {}
    ~WriteToGivenMemory() {};

    int open(unsigned long) { return 0; } // no work
    int close() { return 0; } // no work
    unsigned long fwrite(unsigned char *buffer, unsigned long size);
    unsigned char *get_pointer(unsigned long index) {
	return &data_[index];
    }

    unsigned long total_write_size() const { return total_write_size_; }
    unsigned char *get_data();
    void add_total_size(unsigned long size) { total_write_size_+= size; }

private:
    unsigned char *data_;
    unsigned char *current_;
    unsigned long total_write_size_;
};

//サイズが未確定の場合
#define USE_TMPFILE
#ifdef USE_TMPFILE
#if 0
class WriteToUnknownMemory : public WriteResource {
public:
    WriteToUnknownMemory() :
	tmpfile_(0), data_(0), total_write_size_(0),
	WriteResource(WriteResource::unknown_memory) {}
    ~WriteToUnknownMemory();

    int open(unsigned long size = 0); //tempfile create?
    int close();//tempfile close & delete? & memory alloc
    unsigned long fwrite(unsigned char *buffer, unsigned long size);

    unsigned long total_write_size() const { return total_write_size_; }
    unsigned char *get_data();
    void add_total_size(unsigned long size) { total_write_size_+= size; }

private:
    FILE *tmpfile_;
    unsigned char *data_;
    unsigned long total_write_size_;
};
#else //!0
class WriteToUnknownMemory : public WriteResource {
public:
    WriteToUnknownMemory() :
	hFile_(INVALID_HANDLE_VALUE), data_(0), total_write_size_(0),
	WriteResource(WriteResource::unknown_memory) {}
    ~WriteToUnknownMemory();

    int open(unsigned long size = 0); //tempfile create?
    int close();//tempfile close & delete? & memory alloc
    unsigned long fwrite(unsigned char *buffer, unsigned long size);

    unsigned long total_write_size() const { return total_write_size_; }
    unsigned char *get_data();
    void add_total_size(unsigned long size) { total_write_size_+= size; }

private:
    HANDLE hFile_;
    unsigned char *data_;
    unsigned long total_write_size_;
};
#endif //0
#else //!USE_TMPFILE
#include <list>
class WriteToUnknownMemory : public WriteResource {
public:
    WriteToUnknownMemory() : mbp_(0), data_(0), total_write_size_(0),
	WriteResource(WriteResource::unknown_memory) {}
    ~WriteToUnknownMemory();

    int open(unsigned long size = 0);
    int close();
    unsigned long fwrite(unsigned char *buffer, unsigned long size);

    unsigned long total_write_size() const { return total_write_size_; }
    unsigned char *get_data();
    void add_total_size(unsigned long size) { total_write_size_+= size; }

private:
    class mem_block {
    public:
	mem_block(unsigned long size) :
	    data_(0), rest_(0), current_(0), size_(0)
	{
	    if (current_ = data_ = new unsigned char[size])
		rest_ = size;
	}
	~mem_block() {
	    if (data_)
		delete [] data_;
	}
	unsigned long write(unsigned char *buffer, unsigned long write_size) {
	    if (write_size <= rest_) {
		memcpy(current_, buffer, write_size);
		current_ += write_size;
		size_ += write_size;
		rest_ -= write_size;
		return write_size;
	    }
	    // buffer full
	    return 0;
	}
	unsigned long size() const { return size_; }
	const unsigned char *data() const { return data_; }

    private:
	unsigned char *data_;
	unsigned char *current_;
	unsigned long rest_;
	unsigned long size_;
    };
    typedef list<mem_block *, allocator<mem_block *> > mem_block_list;
    enum { BLOCK_SIZE = 256 * 1024 };
    mem_block_list mem_block_list_;
    mem_block *mbp_;
    unsigned long total_write_size_;
    unsigned char *data_;
};
#endif//end of !USE_TMPFILE

//ファイルに書き込む場合
class WriteToFile : public WriteResource {
public:
    WriteToFile(HANDLE handle) :
	handle_(handle), total_write_size_(0),
	WriteResource(WriteResource::file) {}
    ~WriteToFile() {};

    int open(unsigned long size = 0) { return 0; } //no work
    int close();
    unsigned long fwrite(unsigned char *buffer, unsigned long size);
    unsigned long total_write_size() const { return total_write_size_; }
    unsigned char *get_data() { return 0; }//no work
    void add_total_size(unsigned long size) { total_write_size_+= size; }
    HANDLE get_handle() { return handle_; }

private:
    HANDLE handle_;
    unsigned long total_write_size_;
};

#endif /* !_JPEG_IO_H_ */

//CHANGE LOG
//97.10.03 - matsu - 新規作成(V3)
