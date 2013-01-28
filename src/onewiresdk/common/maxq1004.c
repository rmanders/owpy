#include <string.h>
#include "maxq1004.h"

/**
===============================================================================
 writeMaxQCmdBufferExtContinue

 Writes up to 32 bytes to the MAXQ command buffer.

 @param portNum - bus master port number
 @param owAddrBytes - 8 byte uchar buffer containing the device serial number
        contain the read data from the MAXQ1004 Command buffer.
 @param writeBuffer - buffer of up to 32 bytes to write to the MAXQ1004
 @param writeLen - The number of bytes to write
 @return 1: success, 0: failed (check owError)
===============================================================================
**/
SMALLINT writeMaxQCmdBufferExt(int portNum, uchar* owAddrBytes,
	uchar* writeBuffer, ushort writeLen) {

	return writeMaxQCmdBufferExtCmd(
		portNum,
		owAddrBytes,
		writeBuffer,
		writeLen,
		MAXQ_WRITE_CMDEXT);
}

/**
===============================================================================
 writeMaxQCmdBufferExtStart

 Writes up to 32 bytes to the MAXQ command buffer and signals the firmware on
 the device to begin execution.

 @param portNum - bus master port number
 @param owAddrBytes - 8 byte uchar buffer containing the device serial number
        contain the read data from the MAXQ1004 Command buffer.
 @param writeBuffer - buffer of up to 32 bytes to write to the MAXQ1004
 @param writeLen - The number of bytes to write
 @return 1: success, 0: failed (check owError)
===============================================================================
**/
SMALLINT writeMaxQCmdBufferExtStart(int portNum, uchar* owAddrBytes,
	uchar* writeBuffer, ushort writeLen) {

	return writeMaxQCmdBufferExtCmd(
		portNum,
		owAddrBytes,
		writeBuffer,
		writeLen,
		MAXQ_WRITE_CMDEXT_START);
}

/**
===============================================================================
 writeMaxQCmdBufferExtContinue

 Writes up to 32 bytes to the MAXQ command buffer and signals the firmware on
 the device to continue execution.

 @param portNum - bus master port number
 @param owAddrBytes - 8 byte uchar buffer containing the device serial number
        contain the read data from the MAXQ1004 Command buffer.
 @param writeBuffer - buffer of up to 32 bytes to write to the MAXQ1004
 @param writeLen - The number of bytes to write
 @return 1: success, 0: failed (check owError)
===============================================================================
**/
SMALLINT writeMaxQCmdBufferExtContinue(int portNum, uchar* owAddrBytes,
	uchar* writeBuffer, ushort writeLen) {

	return writeMaxQCmdBufferExtCmd(
		portNum,
		owAddrBytes,
		writeBuffer,
		writeLen,
		MAXQ_WRITE_CMDEXT_CONTINUE);
}

/**
===============================================================================
 writeMaxQCmdBufferExtCmd

 Almost the same as writeMaxQCmdBuffer but allows to two bytes-worth of
 length data to be transmitted. However, since the MAXQ1004 command buffer
 can only hold up to 32 bytes, this is effectlively the same. This function
 accepts three different command bytes that tell it to either just write
 to the command buffer, write and issue a start program command or wright and
 issue a continue program command

 @param portNum - bus master port number
 @param owAddrBytes - 8 byte uchar buffer containing the device serial number
        contain the read data from the MAXQ1004 Command buffer.
 @param writeBuffer - buffer of up to 32 bytes to write to the MAXQ1004
 @param writeLen - The number of bytes to write
 @param command - what action to take after the write has completed
 @return 1: success, 0: failed (check owError)
===============================================================================
**/
SMALLINT writeMaxQCmdBufferExtCmd(int portNum, uchar* owAddrBytes,
	uchar* writeBuffer, ushort writeLen, uchar command) {

        uchar xferBuff[37];
	uchar relSeq[3];
        SMALLINT len, byteCnt, i;
        ushort lastcrc16;

	if(command != MAXQ_WRITE_CMDEXT &&
	   command != MAXQ_WRITE_CMDEXT_START &&
	   command != MAXQ_WRITE_CMDEXT_CONTINUE) {
		OWERROR(OWERROR_FUNC_NOT_SUP);
		return FALSE;
	}

        // Check and truncate writeLen to 32 if needed
        len = (writeLen <= 32) ? writeLen : 32;

        // Set the device serial to MaxQ
        //owSerialNum(portNum, owAddrBytes, FALSE);

        // Signal communication with target device
        if(!owAccess(portNum)) {
                return FALSE;
        }

        byteCnt = 0;

        // Load the Write command buffer commmand
        xferBuff[byteCnt++] = command;
        xferBuff[byteCnt++] = (len & 0x0FF);
        xferBuff[byteCnt++] = 0x00;

        // Fill the xferBuffer with the bytes to write
	memcpy(&xferBuff[3], writeBuffer, sizeof(uchar)*len);
	byteCnt += len;

	// Initialize the CRC bytes
	xferBuff[byteCnt++] = 0xFF;
	xferBuff[byteCnt++] = 0xFF;

        //Send the command for reading
        if(!owBlock(portNum, FALSE, xferBuff, byteCnt)) {
                return FALSE;
        }

        // Check CRC values
        lastcrc16 = 0;
        setcrc16(portNum, 0);

        for(i=0; i<byteCnt; i++) {
                lastcrc16 = docrc16(portNum, xferBuff[i]);
        }

        if(lastcrc16 != 0xB001) {
                OWERROR(OWERROR_CRC_FAILED);
                return FALSE;
        }

	// Check for release sequence based on which command was specified
	switch(command) {
	case MAXQ_WRITE_CMDEXT_START:
		relSeq[0] =  MAXQ_WRITE_CMDEXT_START_RELSEQ & 0x0FF;
		relSeq[1] = (MAXQ_WRITE_CMDEXT_START_RELSEQ >> 4) & 0x0FF;
		relSeq[2] = 0xFF;
		if(!owBlock(portNum, FALSE, relSeq, 3)) {
			return FALSE;
		}
		if((relSeq[2] & 0x01) != 0x00) {
			OWERROR(OWERROR_READ_BACK_INCORRECT);
			return FALSE;
		}
		//TODO: add strong pull-up for power?
		break;
	case MAXQ_WRITE_CMDEXT_CONTINUE:
		relSeq[0] =  MAXQ_WRITE_CMDEXT_CONT_RELSEQ & 0x0FF;
		relSeq[1] = (MAXQ_WRITE_CMDEXT_CONT_RELSEQ >> 4) & 0x0FF;
		relSeq[2] = 0xFF;
		if(!owBlock(portNum, FALSE, relSeq, 3)) {
			return FALSE;
		}
		if((relSeq[2] & 0x01) != 0x00) {
			OWERROR(OWERROR_READ_BACK_INCORRECT);
			return FALSE;
		}
		//TODO: add strong pull-up for power?
		break;
	case MAXQ_WRITE_CMDEXT:
		break;
	default:
		break;
	}


        return TRUE;
}

/**
===============================================================================
 maxQContinueProgram

 Tells the MAXQ1004 to continue program execution. The microcontroller hardware
 does not responde to this signal, onlhy the application code.

 @param portNum - bus master port number
 @param owAddrBytes - 8 byte uchar buffer containing the device serial number
        contain the read data from the MAXQ1004 Command buffer.
 @return 1: success, 0: failed (check owError)
===============================================================================
**/
SMALLINT maxQContinueProgram(int portNum, uchar* owAddrBytes) {

        uchar xferBuff[] = {
		MAXQ_CONTINUE_PROGRAM,
		(MAXQ_CONTINUE_PGM_RELSEQ & 0x0FF),
		(MAXQ_CONTINUE_PGM_RELSEQ >> 4) & 0x0FF,
		0xFF};

        // Set the device serial to MaxQ
        owSerialNum(portNum, owAddrBytes, FALSE);

        // Signal communication with target device
        if(!owAccess(portNum)) {
                return FALSE;
        }

        // Send the reset command
        if(!owBlock(portNum, FALSE, xferBuff, 4)) {
                return FALSE;
        }

        // Check if reset command was understood
        if((xferBuff[3] & 0x01) != 0x00) {
                // Command was not understood
                OWERROR(OWERROR_READ_BACK_INCORRECT);
                return FALSE;
        }

        return TRUE;
}

/**
===============================================================================
 maxQStartProgram

 Tells the MAXQ1004 to start program execution. The microcontroller hardware
 does not responde to this signal, only the applicaton code.

 @param portNum - bus master port number
 @param owAddrBytes - 8 byte uchar buffer containing the device serial number
        contain the read data from the MAXQ1004 Command buffer.
 @return 1: success, 0: failed (check owError)
===============================================================================
**/
SMALLINT maxQStartProgram(int portNum, uchar* owAddrBytes) {

        uchar xferBuff[] = {
		MAXQ_START_PROGRAM,
		(MAXQ_START_PGM_RELSEQ & 0x0FF),
		(MAXQ_START_PGM_RELSEQ >> 4) & 0x0FF,
		0xFF};

        // Set the device serial to MaxQ
        owSerialNum(portNum, owAddrBytes, FALSE);

        // Signal communication with 	target device
        if(!owAccess(portNum)) {
                return FALSE;
        }

        // Send the start command
        if(!owBlock(portNum, FALSE, xferBuff, 4)) {
                return FALSE;
        }
        // Check if start command was understood
        if((xferBuff[3] & 0x01) != 0x00) {
                // Command was not understood
                OWERROR(OWERROR_READ_BACK_INCORRECT);
                return FALSE;
        }

        return TRUE;
}

/**
===============================================================================
 readMaxQCmdBufferExt

 Reads a number of bytew of data from the MAXQ1004 device where the size of the
 data is determined by the MAXQ1004.

 @param portNum - bus master port number
 @param owAddrBytes - 8 byte uchar buffer containing the device serial number
        contain the read data from the MAXQ1004 Command buffer.
 @param readData - Pointer to the bytes read in from the MaxQ. NOTE: these
	bytes are dynamically allocated by this function and must should
	eventually be freed.
 @param readLen - Pointer to an unsigned integer that will contain the number
	of bytes read from the maxQ and stored in the readData buffer.
 @return 1: success, 0: failed (check owError)
===============================================================================
**/
SMALLINT readMaxQCmdBufferExt(int portNum, uchar* owAddrBytes,
	uchar* readBuffer, ushort* readLen) {

	uchar lenBytes[3] = {MAXQ_READ_CMDBUFF_EXT, 0x00, 0x00};
	uchar* xferBuff;
	ushort lastcrc16, len, byteCnt, i;

	// Set the device serial to MaxQ
	owSerialNum(portNum, owAddrBytes, FALSE);

	// Signal communication with target device
        if(!owAccess(portNum)) {
                return FALSE;
        }

	// Issue command and try to get the number of bytes to read
	if(!owBlock(portNum, FALSE, lenBytes, 3)) {
		return FALSE;
        }

	// Read the number of bytes to read into len
	len = (0x00FF & lenBytes[1]) + (0xFF00 & (lenBytes[2]<<8));
	if(len == 0) {
		// Todo: Set 1-wire error
		return FALSE;
	}

	// Allocate space for the command, length, data, and crc bytes
	xferBuff = (uchar*)calloc((5+len), sizeof(uchar));
	if(NULL == xferBuff) {
		OWERROR(OWERROR_OUT_OF_SPACE);
		return FALSE;
	}

	byteCnt = len+5;
	memcpy(xferBuff, lenBytes, 3);

	// Try to read the remaining data and CRC16 bytes
        if(!owBlock(portNum, FALSE, &xferBuff[3], len+2)) {
		free(xferBuff);
                return FALSE;
        }

	// Check CRC values
	lastcrc16 = 0;
	setcrc16(portNum, 0);

	for(i=0; i<byteCnt; i++) {
		lastcrc16 = docrc16(portNum, xferBuff[i]);
	}

        if(lastcrc16 != 0xB001) {
                OWERROR(OWERROR_CRC_FAILED);
		free(xferBuff);
                return FALSE;
        }

	// Allocate new memory for the subset of the xferBuff that
	// contains the raw data from the maxq.
	// TODO: make more efficient so two mallocs aren't needed

	readBuffer = (uchar*) malloc(len*sizeof(uchar));
	if(NULL == readBuffer) {
		OWERROR(OWERROR_OUT_OF_SPACE);
		free(xferBuff);
		return FALSE;
	}
	*readLen = len;
	memcpy(readBuffer, &xferBuff[3], sizeof(uchar)*len);

	// Free the allocated memory
	free(xferBuff);

	return TRUE;
}

/**
===============================================================================
 maxQResetMicro

 This does not reset the microconroller, but clears the input and output
 buffers. The application code running on the maxq can also recognize and
 react to this signal.

 @param portNum - bus master port number
 @param owAddrBytes - 8 byte uchar buffer containing the device serial number
        contain the read data from the MAXQ1004 Command buffer.
 @return 1: success, 0: failed (check owError)
===============================================================================
**/
SMALLINT maxQResetMicro(int portNum, uchar* owAddrBytes) {

        uchar xferBuff[] = {MAXQ_RESET_MICRO,
		(MAXQ_RESET_MICRO_RELSEQ & 0x0FF),
		(MAXQ_RESET_MICRO_RELSEQ >> 4) & 0x0FF,
		0xFF};

        // Set the device serial to MaxQ
        owSerialNum(portNum, owAddrBytes, FALSE);

        // Signal communication with target device
        if(!owAccess(portNum)) {
                return FALSE;
        }

	// Send the reset command
        if(!owBlock(portNum, FALSE, xferBuff, 4)) {
                return FALSE;
        }

	// Check if reset command was understood
        if((xferBuff[3] & 0x01) != 0x00) {
                // Command was not understood
                OWERROR(OWERROR_READ_BACK_INCORRECT);
                return FALSE;
        }

	return TRUE;
}

/**
===============================================================================
 writeMaxQStatus

 Used to write status information to the slave's OWUS register

 @param portNum - bus master port number
 @param owAddrBytes - 8 byte uchar buffer containing the device serial number
        contain the read data from the MAXQ1004 Command buffer.
 @param writeByte - the byte of data to write to the OWUS register. Note:
	only the lower four bits will be written to the OWUS.
 @return 1: success, 0: failed (check owError)
===============================================================================
**/
SMALLINT writeMaxQStatus(int portNum, uchar* owAddrBytes,
	uchar writeByte) {

	uchar xferBuff[4];
	uchar relSeq[] = {
		(MAXQ_WRITE_STATUS_RELSEQ & 0x0FF),
		(MAXQ_WRITE_STATUS_RELSEQ >> 4) & 0x0FF, 
		0xFF};
	SMALLINT byteCnt, i;
	ushort lastcrc16;

        // Set the device serial to MaxQ
        owSerialNum(portNum, owAddrBytes, FALSE);

        // Signal communication with target device
        if(!owAccess(portNum)) {
                return FALSE;
        }

        byteCnt = 0;
	xferBuff[byteCnt++] = MAXQ_WRITE_STATUS;
	xferBuff[byteCnt++] = writeByte;
	xferBuff[byteCnt++] = 0xFF;
	xferBuff[byteCnt++] = 0xFF;

        //Send the command for writing
        if(!owBlock(portNum, FALSE, xferBuff, byteCnt)) {
                return FALSE;
        }

        // Check CRC values
        lastcrc16 = 0;
        setcrc16(portNum, 0);

        for(i=0; i<byteCnt; i++) {
                lastcrc16 = docrc16(portNum, xferBuff[i]);
        }

        if(lastcrc16 != 0xB001) {
                OWERROR(OWERROR_CRC_FAILED);
                return FALSE;
        }

	// Send the release sequence
        if(!owBlock(portNum, FALSE, relSeq, 3)) {
                return FALSE;
        }

	// Check if release sequence was understood
        if((relSeq[2] & 0x01) != 0x00) {
                // Command was not understood
                OWERROR(OWERROR_READ_BACK_INCORRECT);
                return FALSE;
        }

	return TRUE;
}

/**
===============================================================================
 readMaxQCmdBuffer

 Reads up to 32 bytes from the MaxQ1004 command buffer.

 @param portNum - bus master port number
 @param owAddrBytes - 8 byte uchar buffer containing the device serial number
 @param readBuffer - pointer to uchar buffer of up to 32 bytes that will
	contain the read data from the MAXQ1004 Command buffer.
 @param readLen - The number of bytes to read (1 to 32)
 @return 1: Read success, 0: Read failed (check owError)
===============================================================================
**/
SMALLINT readMaxQCmdBuffer(int portNum, uchar* owAddrBytes,
	uchar* readBuffer, SMALLINT readLen) {

	uchar xferBuff[36];
	SMALLINT len, byteCnt, i;
	ushort lastcrc16;

	// Check and truncate readLen to 32 if needed
	len = (readLen <= 32) ? readLen : 32;

	// Set the device serial to MaxQ
	//owSerialNum(portNum, owAddrBytes, FALSE);

	// Signal communication with target device
        if(!owAccess(portNum)) {
                return FALSE;
        }

	byteCnt = 0;

	// Load the Read command buffer commmand
	xferBuff[byteCnt++] = MAXQ_READ_CMDBUFF;
	xferBuff[byteCnt++] = len;

	// Fill the read byte plus crc16 bytes with all 1's
	for(i=0; i<len+2; i++) {
		xferBuff[byteCnt++] = 0xFF;
	}

	//Send the command for reading
	if(!owBlock(portNum, FALSE, xferBuff, byteCnt)) {
		return FALSE;
	}

	// Check CRC values
	lastcrc16 = 0;
	setcrc16(portNum, 0);

	for(i=0; i<byteCnt; i++) {
		lastcrc16 = docrc16(portNum, xferBuff[i]);
	}

        if(lastcrc16 != 0xB001) {
                OWERROR(OWERROR_CRC_FAILED);
                return FALSE;
        }

	memcpy(readBuffer, &xferBuff[2], sizeof(uchar)*len);

	return TRUE;
}

/**
===============================================================================
 writeMaxCmdBuffer

 Write up to 32 bytes of data to the MAXQ1004 command buffer.

 @param portNum - bus master port number
 @param owAddrBytes - 8 byte uchar buffer containing the device serial number
 @param writeBuffer - Up to 32 byte buffer containing data to be written.
        NOTE: this is expected to be formated in transmission order. That
        is, the writeBuffer array should have the LSB at index 0.
 @param writeLen - The number of bytes to write (up to 32)
 @return 1: Write success, 0: Write failed (check owError)

===============================================================================
**/
SMALLINT writeMaxQCmdBuffer(int portNum, uchar* owAddrBytes,
        uchar* writeBuffer, SMALLINT writeLen) {

        uchar xferBuff[36];
        SMALLINT len, byteCnt, i;
        ushort lastcrc16;

        // Check and truncate writeLen to 32 if needed
        len = (writeLen <= 32) ? writeLen : 32;

        // Set the device serial to MaxQ
        owSerialNum(portNum, owAddrBytes, FALSE);

        // Signal communication with target device
        if(!owAccess(portNum)) {
                return FALSE;
        }

        byteCnt = 0;

        // Load the Write command buffer commmand
        xferBuff[byteCnt++] = MAXQ_WRITE_CMDBUFF;
        xferBuff[byteCnt++] = len;

        // Fill the xferBuffer with the bytes to write
	memcpy(&xferBuff[2], writeBuffer, sizeof(uchar)*len);
	byteCnt += len;

	// Initialize the CRC bytes
	xferBuff[byteCnt++] = 0xFF;
	xferBuff[byteCnt++] = 0xFF;

        //Send the command for reading
        if(!owBlock(portNum, FALSE, xferBuff, byteCnt)) {
                return FALSE;
        }

        // Check CRC values
        lastcrc16 = 0;
        setcrc16(portNum, 0);

        for(i=0; i<byteCnt; i++) {
                lastcrc16 = docrc16(portNum, xferBuff[i]);
        }

        if(lastcrc16 != 0xB001) {
                OWERROR(OWERROR_CRC_FAILED);
                return FALSE;
        }

	// TODO: Compare the xferBuffer with writeBuffer for sanity
	//       check?

        return TRUE;
}

/**
===============================================================================
 readMaxQIO

 Reads up to 8 bytes of data from the MaxQ1004 1-wire slave interface I/O
 buffer. The caller must check for compatible target family code.

 Note1: If the readLen paramter is greater than 8, this function truncates it
 to 8.

 Note2: If any computation is to be done, strong pull up must be enabled

 @param portNum - bus master port number
 @param owAddrBytes - 8 byte uchar buffer containing the device serial number
 @param readBytes - 8 byte buffer to place the read results in
 @param readLen - The number of bytes to read (up to 8)
 @return 1: Read success, 0: Read failed (check owError)

 TODO: Wrap CRC16 code in a loop so that the I/O read is attepmted multiple
       times if the CRC16 fails.
===============================================================================
**/
SMALLINT readMaxQIO(int portNum, uchar* owAddrBytes,
        uchar* readBytes, SMALLINT readLen ) {

        uchar xferBuffer[12];
	uchar releaseSeq[] = {
		(MAXQ_READ_IOBUFF_RELSEQ & 0x0FF),
		(MAXQ_READ_IOBUFF_RELSEQ >> 4) & 0x0FF,
		0xFF };
        int byteCnt, i, len;
        ushort lastcrc16;

        // If the number of byte to read is larger than 8, truncate to 8
        len = readLen <= 8 ? readLen : 8;

        // Set device serial to MaxQ
        owSerialNum(portNum, owAddrBytes, FALSE);

        // Signal communication with target device
        if(!owAccess(portNum)) {
                return FALSE;
        }

        // Load the read I/O command into first pos
        byteCnt = 0;
        xferBuffer[byteCnt++] = MAXQ_READ_IOBUFF;

        // Initialize the number of bytes to be read (8 or less)
        xferBuffer[byteCnt++] = (readLen <= 8) ? readLen : 8;

        // Init the bytes that read values will be placed into plus the CRC16
        for(i=0; i<readLen+2; i++) {
                xferBuffer[byteCnt++] = 0xFF;
        }

        if(!owBlock(portNum, FALSE, xferBuffer, byteCnt)) {
                return FALSE;
        }

        // Do CRC checks
        lastcrc16 = 0;
        setcrc16(portNum, 0);
        for(i=0; i<=len+4; i++)
                lastcrc16 = docrc16(portNum,xferBuffer[i]);

	if(lastcrc16 != 0xB001) {
		OWERROR(OWERROR_CRC_FAILED);
		return FALSE;
	}

        memcpy(readBytes, &xferBuffer[2], sizeof(uchar)*len);

	// Send the terminate sequence
	if(!owBlock(portNum, FALSE, releaseSeq, 3)){
		return FALSE;
	}

	if((releaseSeq[2] & 0x01) != 0x00) {
		// Command was not understood
		OWERROR(OWERROR_READ_BACK_INCORRECT);
		return FALSE;
	}
	return TRUE;
}

/**
===============================================================================
 writeMaxQIO

 Writes up to 8 bytes of data to the MaxQ1004 1-wire slave interface I/O
 buffer. The caller must check for compatible target family code.

 Note1: If the writeLen paramter is greater than 8, this function truncates it
 to 8.

 Note2: If any computation is to be done, strong pull up must be enabled

 @param portNum - bus master port number
 @param owAddrBytes - 8 byte uchar buffer containing the device serial number
 @param writeBytes - 8 byte buffer containing data to be write.
	NOTE: this is expected to be formated in transmission order. That
	is, the writeBytes array should have the LSB in the lowest indexed
	position and the MSB in the highest.
 @param writeLen - The number of bytes to write (up to 8)
 @return 1: Write success, 0: Write failed (check owError)

===============================================================================
**/
SMALLINT writeMaxQIO(int portNum, uchar* owAddrBytes,
        uchar* writeBytes, SMALLINT writeLen ) {

	int i, byteCnt;
	SMALLINT len;
	uchar xferBuff[12];
	uchar releaseSeq[] = {
		(MAXQ_WRITE_IOBUFF_RELSEQ & 0x0FF),
		(MAXQ_WRITE_IOBUFF_RELSEQ >> 4) & 0x0FF,
		0xFF };
	ushort lastcrc16;

	// Set and access the device
	owSerialNum(portNum, owAddrBytes, FALSE);

	if(!owAccess(portNum)) {
		return FALSE;
	}

	// Init parameters
	len = (writeLen <=8) ? writeLen : 8;
	byteCnt = 0;

	// Load xfer buffer with I/O write command
	xferBuff[byteCnt++] = 0x2D;
	xferBuff[byteCnt++] = (uchar)len;

	// Load the xfer buffer in transmission order
	for(i=0; i<len; i++) {
		xferBuff[byteCnt++] = writeBytes[len-1-i];
	}

	// Add space for CRC16
	xferBuff[byteCnt++] = 0xFF;
	xferBuff[byteCnt++] = 0xFF;

	// Send the data to the MaxQ
	if(!owBlock(portNum, FALSE, xferBuff, byteCnt)) {
		return FALSE;
	}

	// Check CRC16

        lastcrc16 = 0;
        setcrc16(portNum, 0);
        for(i=0; i<=len+4; i++)
                lastcrc16 = docrc16(portNum,xferBuff[i]);

	if(lastcrc16 != 0xB001) {
		OWERROR(OWERROR_CRC_FAILED);
                return FALSE;
        }

	// Send release sequence
	if(!owBlock(portNum, FALSE, releaseSeq, 3)) {
		return FALSE;
	}

	// Check that release sequence command was understood
	if((releaseSeq[2] & 0x01) != 0x00) {
		 OWERROR(OWERROR_READ_BACK_INCORRECT);
		return FALSE;
	}

	return TRUE;
}

/**
===============================================================================
 readMaxQStatus

 Read the contents of the 1-wire micro status (OWMS) register on the MaxQ. This
 register can be written to by the MaxQ application firmware for status updates
 and communication with the 1-wire master.

 @param portNum - bus master port number
 @param owAddrBytes - 8 byte uchar buffer containing the device serial number
 @param statusBytes - 7 byte buffer that the status bytes including crc will
	be written to.
 @return 1: Read success, 0: Read failed (check owError)

===============================================================================
**/
SMALLINT readMaxQStatus(int portNum, uchar* owAddrBytes, uchar* statusBytes) {
	uchar xferBuffer[7];
	int byteCnt, i;
	ushort lastcrc16;

       // Set device serial to MaxQ
        //owSerialNum(portNum, owAddrBytes, FALSE);

        // Signal communication with target device
        if(!owAccess(portNum)) {
                return FALSE;
        }

	// Initialize the transfer buffer
	byteCnt = 0;
	xferBuffer[byteCnt++] = MAXQ_READ_STATUS;
	while(byteCnt < 7) {
		xferBuffer[byteCnt++] = 0xFF;
	}

	if(!owBlock(portNum, FALSE, xferBuffer, byteCnt)) {
		return FALSE;
	}

	// Do CRC16 check
	setcrc16(portNum, 0);
	for(i=0; i<7; i++) {
		lastcrc16 = docrc16(portNum, xferBuffer[i]);
	}

	// TODO: check crc16
	if(lastcrc16 != 0xB001) {
		OWERROR(OWERROR_CRC_FAILED);
		return FALSE;
	}

	memcpy(statusBytes, xferBuffer, sizeof(uchar)*7);

	return TRUE;
}

