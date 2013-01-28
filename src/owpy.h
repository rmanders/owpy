#ifndef __OWPYMODULE__
#define __OWPYMODULE__

#include <Python.h>
#include <stdio.h>
#include <string.h>
#include "ownet.h"
#include "findtype.h"
//#include "temp10.h"
#include "tempall.h"
#include "cnt1d.h"
#include "maxq1004.h"

#define MAXDEVICES 20
#define SERIALNUMLEN 8
#define OWPY_VERSION 1.1

// Module Exception reference
static PyObject* OwpyError;

int checkSerial( const char* serialStr, uchar* outputSerial );

int chartohi( char value );

int btohc(unsigned char* buffer_from, unsigned char* buffer_to, 
	size_t len_from, size_t len_to);

int revstring(unsigned char* buffer, size_t len);


//SMALLINT readMaxQIO(int portNum, uchar* owAddrBytes,
//	uchar* readBytes, SMALLINT readLen );
#endif
