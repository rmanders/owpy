#ifndef __MAXQ1004__
#define __MAXQ1004__

#include "ownet.h"


// Transport layer commands
#define MAXQ_WRITE_STATUS		0xD2
#define MAXQ_READ_STATUS		0xE1
#define MAXQ_RESET_MICRO		0xDD
#define MAXQ_READ_CMDBUFF_EXT		0x69
#define MAXQ_START_PROGRAM		0x77
#define MAXQ_CONTINUE_PROGRAM		0x87
#define MAXQ_READ_CMDBUFF		0xAA
#define MAXQ_WRITE_CMDBUFF		0x0F
#define MAXQ_READ_IOBUFF		0x22
#define MAXQ_WRITE_IOBUFF		0x2D

#define MAXQ_WRITE_CMDEXT		0x96
#define MAXQ_WRITE_CMDEXT_START		0x55
#define MAXQ_WRITE_CMDEXT_CONTINUE	0x5A

// Release Sequences
#define MAXQ_WRITE_CMDEXT_START_RELSEQ	0x837A
#define MAXQ_WRITE_CMDEXT_CONT_RELSEQ	0x6BE2
#define MAXQ_CONTINUE_PGM_RELSEQ	0x5D73
#define MAXQ_START_PGM_RELSEQ		0x6D43
#define MAXQ_RESET_MICRO_RELSEQ		0x92BC
#define MAXQ_WRITE_STATUS_RELSEQ	0x517F
#define MAXQ_READ_IOBUFF_RELSEQ		0x624C
#define MAXQ_WRITE_IOBUFF_RELSEQ	0x9DB3


SMALLINT writeMaxQCmdBufferExt(int portNum, uchar* owAddrBytes,
        uchar* writeBuffer, ushort writeLen);

SMALLINT writeMaxQCmdBufferExtStart(int portNum, uchar* owAddrBytes,
        uchar* writeBuffer, ushort writeLen);

SMALLINT writeMaxQCmdBufferExtContinue(int portNum, uchar* owAddrBytes,
        uchar* writeBuffer, ushort writeLen);

SMALLINT writeMaxQCmdBufferExtCmd(int portNum, uchar* owAddrBytes,
        uchar* writeBuffer, ushort writeLen, uchar command);

SMALLINT maxQContinueProgram(int portNum, uchar* owAddrBytes);

SMALLINT maxQStartProgram(int portNum, uchar* owAddrBytes);

SMALLINT readMaxQCmdBufferExt(int portNum, uchar* owAddrBytes,
        uchar* readBuffer, ushort* readLen);

SMALLINT maxQResetMicro(int portNum, uchar* owAddrBytes);

SMALLINT writeMaxQStatus(int portNum, uchar* owAddrBytes,
        uchar writeByte);

SMALLINT readMaxQCmdBuffer(int portNum, uchar* owAddrBytes,
        uchar* readBuffer, SMALLINT readLen);

SMALLINT writeMaxQCmdBuffer(int portNum, uchar* owAddrBytes,
        uchar* writeBuffer, SMALLINT writeLen);

SMALLINT readMaxQIO(int portNum, uchar* owAddrBytes,
        uchar* readBytes, SMALLINT readLen );

SMALLINT writeMaxQIO(int portNum, uchar* owAddrBytes,
        uchar* writeBytes, SMALLINT writeLen );

SMALLINT readMaxQStatus(int portNum, uchar* owAddrBytes,
	uchar* statusBytes);

#endif

