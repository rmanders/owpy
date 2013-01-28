#include "owpy.h"

/**
===============================================================================
owTestFunction
===============================================================================
**/
static PyObject* owpy_owTestFunction(PyObject* self, PyObject* args) {
	printf("Test Successfull!");
	return Py_BuildValue("i",1);
}

/*:::::::::::::::::::::::::: LINK LAYER CALLS :::::::::::::::::::::::::::::::*/

/**
===============================================================================
owTouchReset
===============================================================================
**/
static PyObject* owpy_owTouchReset(PyObject* self, PyObject* args) {

	int portNum;
	SMALLINT ret;

	if(!PyArg_ParseTuple(args, "i", &portNum)) {
		return NULL;
	}
	ret = owTouchReset(portNum);
	if(ret){
		Py_RETURN_TRUE;
	} else {
		Py_RETURN_FALSE;
	}
}

/**
===============================================================================
owTouchBit
===============================================================================
**/
static PyObject* owpy_owTouchBit(PyObject* self, PyObject* args) {

        int portNum;
	SMALLINT sendBit;
        SMALLINT ret;

        if(!PyArg_ParseTuple(args, "ib", &portNum, &sendBit)) {
                return NULL;
        }
	ret = owTouchBit(portNum, sendBit);
        if(ret){
                Py_RETURN_TRUE;
        } else {
                Py_RETURN_FALSE;
        }
}

/**
===============================================================================
owTouchByte
===============================================================================
**/
static PyObject* owpy_owTouchByte(PyObject* self, PyObject* args) {

        int portNum;
	SMALLINT sendByte;
        SMALLINT ret;

        if(!PyArg_ParseTuple(args, "ib", &portNum, &sendByte)) {
                return NULL;
        }
	ret = owTouchByte(portNum, sendByte);
        if(ret){
                Py_RETURN_TRUE;
        } else {
                Py_RETURN_FALSE;
        }
}
/**
===============================================================================
owWriteByte
===============================================================================
**/
static PyObject* owpy_owWriteByte(PyObject* self, PyObject* args) {

        int portNum;
	SMALLINT sendByte;
        SMALLINT ret;

        if(!PyArg_ParseTuple(args, "ib", &portNum, &sendByte)) {
                return NULL;
        }
	ret = owWriteByte(portNum, sendByte);
        if(ret){
                Py_RETURN_TRUE;
        } else {
                Py_RETURN_FALSE;
        }
}

/**
===============================================================================
owReadByte
===============================================================================
**/
static PyObject* owpy_owReadByte(PyObject* self, PyObject* args) {

        int portNum;
        SMALLINT ret;

        if(!PyArg_ParseTuple(args, "i", &portNum)) {
                return NULL;
        }
	ret = owReadByte(portNum);
        if(ret){
                Py_RETURN_TRUE;
        } else {
                Py_RETURN_FALSE;
        }
}

/**
===============================================================================
owSpeed - Set the ow speed.
	MODE_NORMAL     0x00
	MODE_OVERDRIVE  0x01
===============================================================================
**/
static PyObject* owpy_owSpeed(PyObject* self, PyObject* args) {

        int portNum;
	SMALLINT newSpeed;
        SMALLINT ret;

        if(!PyArg_ParseTuple(args, "ib", &portNum, &newSpeed)) {
                return NULL;
        }
	if(newSpeed > 0x01) {
		PyErr_SetString(OwpyError,"speed parameter was outside permissible range (0x00-0x01)");
		return NULL;
	}
	ret = owSpeed(portNum, newSpeed);
	return Py_BuildValue("b",ret);
}

/**
===============================================================================
owLevel - Set the 1-Wire Net line level
	MODE_NORMAL     0x00
	MODE_STRONG5    0x02
	MODE_PROGRAM    0x04
	MODE_BREAK      0x08
===============================================================================
**/
static PyObject* owpy_owLevel(PyObject* self, PyObject* args) {

        int portNum;
	SMALLINT newLevel;
        SMALLINT ret;

        if(!PyArg_ParseTuple(args, "ib", &portNum, &newLevel)) {
                return NULL;
        }
	if(newLevel != 0x00 || newLevel != 0x02 ||
	   newLevel != 0x04 || newLevel != 0x08) {
		PyErr_SetString(OwpyError,"ow level parameter was outside permissible range (0x00,0x02,0x04,0x08)");
		return NULL;
	}
	ret = owLevel(portNum, newLevel);
	return Py_BuildValue("b",ret);
}

/**
===============================================================================
owProgramPulse
===============================================================================
**/
static PyObject* owpy_owProgramPulse(PyObject* self, PyObject* args) {

        int portNum;
        SMALLINT ret;

        if(!PyArg_ParseTuple(args, "i", &portNum)) {
                return NULL;
        }
	ret = owProgramPulse(portNum);
        if(ret){
                Py_RETURN_TRUE;
        } else {
                Py_RETURN_FALSE;
        }
}

/**
===============================================================================
owTouchBytePower - returns byte read or 0 if failure
===============================================================================
**/
static PyObject* owpy_owTouchBytePower(PyObject* self, PyObject* args) {

        int portNum;
	SMALLINT sendByte;
        SMALLINT ret;

        if(!PyArg_ParseTuple(args, "ib", &portNum, &sendByte)) {
                return NULL;
        }
	ret = owTouchBytePower(portNum, sendByte);
	return Py_BuildValue("b", ret);
}

/**
===============================================================================
owWriteBytePower
===============================================================================
**/
static PyObject* owpy_owWriteBytePower(PyObject* self, PyObject* args) {

        int portNum;
	SMALLINT sendByte;
        SMALLINT ret;

        if(!PyArg_ParseTuple(args, "ib", &portNum, &sendByte)) {
                return NULL;
        }
	ret = owWriteBytePower(portNum, sendByte);
        if(ret){
                Py_RETURN_TRUE;
        } else {
                Py_RETURN_FALSE;
        }
}

/**
===============================================================================
owReadBytePower
===============================================================================
**/
static PyObject* owpy_owReadBytePower(PyObject* self, PyObject* args) {

        int portNum;
        SMALLINT ret;

        if(!PyArg_ParseTuple(args, "i", &portNum)) {
                return NULL;
        }
	ret = owReadBytePower(portNum);
	return Py_BuildValue("b", ret);
}

/**
===============================================================================
owReadBitPower
===============================================================================
**/
static PyObject* owpy_owReadBitPower(PyObject* self, PyObject* args) {

        int portNum;
	SMALLINT applyPowerResponse;
        SMALLINT ret;

        if(!PyArg_ParseTuple(args, "ib", &portNum, &applyPowerResponse)) {
                return NULL;
        }
	ret = owReadBitPower(portNum, applyPowerResponse);
        if(ret){
                Py_RETURN_TRUE;
        } else {
                Py_RETURN_FALSE;
        }
}

/**
===============================================================================
owHasPowerDelivery
===============================================================================
**/
static PyObject* owpy_owHasPowerDelivery(PyObject* self, PyObject* args) {

        int portNum;
        SMALLINT ret;

        if(!PyArg_ParseTuple(args, "i", &portNum)) {
                return NULL;
        }
	ret = owHasPowerDelivery(portNum);
        if(ret){
                Py_RETURN_TRUE;
        } else {
                Py_RETURN_FALSE;
        }
}

/**
===============================================================================
owHasOverDrive
===============================================================================
**/
static PyObject* owpy_owHasOverDrive(PyObject* self, PyObject* args) {

        int portNum;
        SMALLINT ret;

        if(!PyArg_ParseTuple(args, "i", &portNum)) {
                return NULL;
        }
	ret = owHasOverDrive(portNum);
        if(ret){
                Py_RETURN_TRUE;
        } else {
                Py_RETURN_FALSE;
        }
}

/**
===============================================================================
owHasProgramPulse
===============================================================================
**/
static PyObject* owpy_owHasProgramPulse(PyObject* self, PyObject* args) {

        int portNum;
        SMALLINT ret;

        if(!PyArg_ParseTuple(args, "i", &portNum)) {
                return NULL;
        }
	ret = owHasProgramPulse(portNum);
        if(ret){
                Py_RETURN_TRUE;
        } else {
                Py_RETURN_FALSE;
        }
}

/*::::::::::::::::::::::::: NETWORK LAYER CALLS :::::::::::::::::::::::::::::*/
/*
SMALLINT owFirst(int portnum, SMALLINT do_reset, SMALLINT alarm_only);
SMALLINT owNext(int portnum, SMALLINT do_reset, SMALLINT alarm_only);
void owSerialNum(int portnum, uchar *serialnum_buf, SMALLINT do_read);
void owFamilySearchSetup(int portnum, SMALLINT search_family);
void owSkipFamily(int portnum);
SMALLINT owAccess(int portnum);
SMALLINT owVerify(int portnum, SMALLINT alarm_only);
SMALLINT owOverdriveAccess(int portnum);
*/


/**
===============================================================================
owWriteMaxQCmdBufferExtStart
===============================================================================
**/
static PyObject* owpy_owWriteMaxQCmdBufferExtStart(PyObject* self,
	PyObject* args) {

	int portNum;
	char* owAddress;
	char* pyStringBytes;
	uchar owAddrBytes[8];
	uchar writeBytes[32];
        Py_ssize_t writeLen;
        PyObject* pyString;
	SMALLINT ret;

	if(!PyArg_ParseTuple(args, "isO", &portNum, &owAddress, &pyString)) {
		return NULL;
	}

        // Convert string serial to address bytes
        if(!checkSerial(owAddress, owAddrBytes)) {
                return NULL;
        }

	// Get the size of the write buffer
        writeLen = PyString_Size(pyString);
        if(writeLen <= 0 || writeLen > 32) {
                PyErr_SetString(OwpyError, "owWriteMaxQCmdBufferExtStart: "
		"The string parameter length was outside the required range of "
                "between 1 and 32 bytes inclusive.");
                return NULL;
        }

	// Get the contents of write buffer
        pyStringBytes = (uchar*) PyString_AsString(pyString);
        if(NULL == pyStringBytes) {
                return NULL;
        }

        // Copy Python string bytes to writeBuffer
        memcpy(writeBytes, pyStringBytes, sizeof(uchar)*writeLen);

	ret = writeMaxQCmdBufferExtStart(
		portNum,
		owAddrBytes,
		writeBytes,
		writeLen);

        //TODO: fail with python exception?

        if(ret){
                Py_RETURN_TRUE;
        } else {
                Py_RETURN_FALSE;
        }

}
/**
===============================================================================
owMaxQStartProgram
===============================================================================
**/
static PyObject* owpy_owMaxQStartProgram(PyObject* self, PyObject* args) {

	int portNum;
	char* owAddress;
	uchar owAddrBytes[8];
	SMALLINT ret;

        if(!PyArg_ParseTuple(args, "is", &portNum, &owAddress)) {
                return NULL;
        }

	// Convert string serial to address bytes
        if(!checkSerial(owAddress, owAddrBytes)) {
                return NULL;
        }

	ret = maxQStartProgram(portNum, owAddrBytes);

        if(ret){
                Py_RETURN_TRUE;
        } else {
                Py_RETURN_FALSE;
        }
}

/**
===============================================================================
owReadMaxQCmdBuffer
===============================================================================
**/
static PyObject* owpy_owReadMaxQCmdBuffer(PyObject* self, PyObject* args) {

	int portNum, readLen;
	char* owAddress;
	uchar owAddrBytes[8];
	uchar readBytes[32];

	// TODO: Change "isi" to read unsigned small int
        if(!PyArg_ParseTuple(args, "isi", &portNum, &owAddress, &readLen)) {
                return NULL;
        }

	if(readLen > 32 || readLen < 1) {
	        // Convert string serial to address bytes
		PyErr_SetString(OwpyError, "owReadMaxQCmdBuffer: "
		"Number of bytes to read was not within the required "
		"range of 1-32 inclusive");
		return NULL;
	}

        // Convert string serial to address bytes
        if(!checkSerial(owAddress, owAddrBytes)) {
                return NULL;
        }

	if(!readMaxQCmdBuffer(portNum, owAddrBytes, readBytes, (SMALLINT)readLen)) {
                PyErr_SetString(OwpyError, "owReadMaxQCmdBuffer: A 1-wire error "
                "occurred while attempting to read from the MaxQ 1-wire Command "
		"Buffer. Please check the 1-wire error stack for more details");
                return NULL;
	}

	return Py_BuildValue("s#", readBytes, readLen);
}

/**
===============================================================================
owWriteMaxQCmdBuffer
===============================================================================
**/
static PyObject* owpy_owWriteMaxQCmdBuffer(PyObject* self, PyObject* args) {

	int portNum;
	char* owAddress;
	char* pyStringBytes;
	uchar owAddrBytes[8];
	uchar writeBytes[32];
        Py_ssize_t writeLen;
        PyObject* pyString;
	SMALLINT ret;

        if(!PyArg_ParseTuple(args, "isO", &portNum, &owAddress, &pyString)) {
                return NULL;
        }

        // Convert string serial to address bytes
        if(!checkSerial(owAddress, owAddrBytes)) {
                return NULL;
        }

        writeLen = PyString_Size(pyString);
        if(writeLen <= 0 || writeLen > 32) {
                PyErr_SetString(OwpyError, "owWriteMaxQCmdBuffer: The string "
                "parameter length was outside the required range of "
                "between 1 and 32 bytes inclusive.");
                return NULL;
        }

        pyStringBytes = PyString_AsString(pyString);
        if(NULL == pyStringBytes) {
                return NULL;
        }

        // Copy Python bytes to byte array
        memcpy(writeBytes, pyStringBytes, sizeof(uchar)*writeLen);

        ret = writeMaxQCmdBuffer(portNum, owAddrBytes, writeBytes, (SMALLINT) writeLen);

	//TODO: fail with python exception

        if(ret){
                Py_RETURN_TRUE;
        } else {
                Py_RETURN_FALSE;
        }
}

/**
===============================================================================
owReadMaxQStatus
===============================================================================
**/

static PyObject* owpy_owReadMaxQStatus(PyObject* self, PyObject* args) {
        int portNum;
        char* owAddress;
        uchar owAddrBytes[8];
        uchar readBytes[7];

        if(!PyArg_ParseTuple(args, "is", &portNum, &owAddress)) {
                return NULL;
        }

        // Convert string serial to address bytes
        if(!checkSerial(owAddress, owAddrBytes)) {
                return NULL;
        }

        // TODO: Integrate 1-wire error stack into python exception handling
        if(!readMaxQStatus(portNum, owAddrBytes, readBytes)) {
                PyErr_SetString(OwpyError, "owReadMaxQStatus: A 1-wire error "
                "occurred while attempting to read from the MaxQ status register. Please "
                "check the 1-wire error stack for more details");
                return NULL;
        }

        return Py_BuildValue("s#", readBytes, 7);
}


/**
===============================================================================
owWriteMaxQIO
===============================================================================
**/

static PyObject* owpy_owWriteMaxQIO(PyObject* self, PyObject* args) {

        int portNum, ret;
        char* owAddress;
        uchar owAddrBytes[8];
        uchar writeBytes[8];
	char* pyStringBytes;
        Py_ssize_t writeLen;
	PyObject* pyString;

        if(!PyArg_ParseTuple(args, "isO", &portNum, &owAddress, &pyString)) {
                return NULL;
        }


        // Convert string serial to address bytes
        if(!checkSerial(owAddress, owAddrBytes)) {
                return NULL;
        }

	writeLen = PyString_Size(pyString);
	if(writeLen <= 0 || writeLen > 8) {
		PyErr_SetString(OwpyError, "owWriteMaxQIO: The string "
		"parameter length was outside the required range of "
		"between 1 and 8 bytes inclusive.");
		return NULL;
	}

	pyStringBytes = PyString_AsString(pyString);
	if(NULL == pyStringBytes) {
		return NULL;
	}

	// Copy Python bytes to byte array
	memcpy(writeBytes, pyStringBytes, sizeof(uchar)*writeLen);

        ret = writeMaxQIO(portNum, owAddrBytes, writeBytes, (SMALLINT) writeLen);

        if(ret){
                Py_RETURN_TRUE;
        } else {
                Py_RETURN_FALSE;
        }
}

/**
===============================================================================
owReadMaxQIO
===============================================================================
**/

static PyObject* owpy_owReadMaxQIO(PyObject* self, PyObject* args) {

	int portNum, readLen;
	char* owAddress;
	uchar owAddrBytes[8];
	uchar readBytes[8];

	if(!PyArg_ParseTuple(args, "isi", &portNum, &owAddress, &readLen)) {
		return NULL;
	}

	if(readLen <= 0 || readLen > 8) {
		PyErr_SetString(OwpyError, "owReadMaxQIO: The number of bytes "
		"to read parameter was outside the required range of between "
		"1 and 8 bytes inclusive.");
		return NULL;
	}

	// Convert string serial to address bytes
        if(!checkSerial(owAddress, owAddrBytes)) {
                return NULL;
        }

	// TODO: Integrate 1-wire error stack into python exception handling
	if(!readMaxQIO(portNum, owAddrBytes, readBytes, (SMALLINT) readLen)) {
		PyErr_SetString(OwpyError, "owReadMaxQIO: A 1-wire error "
		"occurred while attempting to read from the MaxQ. Please "
		"check the 1-wire error stack for more details");
                return NULL;
	}


	return Py_BuildValue("s#", readBytes, readLen);
}

/*
===============================================================================
owReadCounter
===============================================================================
**/
static PyObject* owpy_owReadCounter(PyObject* self, PyObject* args) {

	int portNum;
	char* owAddress;
	uchar owAddrBytes[8];
	int pageNum;
	ulong count;

        if(!PyArg_ParseTuple(args, "isi", &portNum, &owAddress, &pageNum)) {
                return NULL;
        }

        if(!checkSerial(owAddress, owAddrBytes)) {
                return NULL;
        }

	// Check for supported device compatibility
	/*
	if(owAddrBytes[0] != 0x1D) {
		PyErr_SetString(OwpyError, "In owReadCounter: Specified "
		"device family code not supported");
		return NULL;
	}

	else */ if(pageNum < 12 || pageNum > 15) {
		PyErr_SetString(OwpyError, "In owReadCounter: specified "
		"counter address page was outside range of 12-15");
		return NULL;
	}

	if(!ReadCounter(portNum, owAddrBytes, pageNum, &count)) {
		count = -1;
	}

        return Py_BuildValue("k",count);
}

/**
===============================================================================
owListDevices
===============================================================================
**/
static PyObject* owpy_owListDevices(PyObject* self, PyObject* args) {

        int ret, count, i, j, k;
	int portNum;
	uchar familySn[MAXDEVICES][8];
	uchar convertedSn[16];
	PyObject* list;
	PyObject* obj;

        // Check that parameter is an int
        if(!PyArg_ParseTuple(args, "i", &portNum)) {
                return NULL;
        }

        ret = owFirst(portNum, TRUE, FALSE);

        // If no device was found, there is a problem. The busmaster
        // should at least show up for the DS2490.
        if(ret == 0) {
		// TODO: change to return empty list
		Py_RETURN_NONE;
        }

        count = 0;
        while(ret == 1 && count < MAXDEVICES) {
                owSerialNum(portNum, &familySn[count++][0], TRUE);
                ret = owNext(portNum, TRUE, FALSE);
        }

	// Create a new python list object
	list = PyList_New((Py_ssize_t) count);
	if(NULL == list) {
		return NULL;
	}

        for(i=0; i<count; i++) {

		// Format the owAddress for output
		k=0;
		for(j=7; j>=0; j--) {
			sprintf(&convertedSn[(k++*2)],"%02X", familySn[i][j]);
		}

		// Build a python string from converted output and add to PyList
		obj = Py_BuildValue("s#", convertedSn, 16);
		if(NULL == obj) {
			//Python Error assumed to be set
			return NULL;
		}

		ret = PyList_SetItem(list, (Py_ssize_t)i, obj);
		if(ret == -1){
			//Python Error assumed to be set
			return NULL;
		}
        }
	return list;
}

/**
===============================================================================
owReadTemperature - Reads temperature value from specified ow temp sensor
===============================================================================
**/
static PyObject* owpy_owReadTemperature(PyObject* self, PyObject* args) {

        int portNum;
        char* owAddress;
	uchar owAddrBytes[8];
        float temperature;
	int ret;

        // Check that parameter is an int
        if(!PyArg_ParseTuple(args, "is", &portNum, &owAddress)) {
                return NULL;
        }

	if(!checkSerial(owAddress, owAddrBytes)) {
		return NULL;
	}

	ret = ReadTemperatureAny(portNum, owAddrBytes, &temperature);
	if(ret){
		return Py_BuildValue("f", temperature);
	} else {
		Py_RETURN_NONE;
	}
}

/**
===============================================================================
owSerialNum
===============================================================================
**/
static PyObject* owpy_owSerialNum(PyObject* self, PyObject* args) {

	int portNum;
	uchar* serialNumBuffer;
	SMALLINT doRead;

        // Check that parameter is an int
        if(!PyArg_ParseTuple(args, "isc", &portNum, &serialNumBuffer, &doRead )) {
                return NULL;
        }
        owSerialNum(portNum, (uchar*) serialNumBuffer, (uchar)doRead );
	Py_RETURN_NONE;
}

/**
===============================================================================
owGetErrorMsg
===============================================================================
**/
static PyObject* owpy_owGetErrorMsg(PyObject* self, PyObject* args) {

        char* errMsg;
        int errNum;

        // Check that parameter is an int
        if(!PyArg_ParseTuple(args, "i", &errNum)) {
                return NULL;
        }
        errMsg = owGetErrorMsg(errNum);
        return Py_BuildValue("s", errMsg);
}

/**
===============================================================================
owHasErrors
===============================================================================
**/
static PyObject* owpy_owHasErrors(PyObject* self, PyObject* args) {

        int isErrorPresent;
        isErrorPresent = owHasErrors();
	if(isErrorPresent) {
		Py_RETURN_TRUE;
	} else {
		Py_RETURN_FALSE;
	}
}

/**
===============================================================================
owGetErrorNum
===============================================================================
**/
static PyObject* owpy_owGetErrorNum(PyObject* self, PyObject* args) {

        int owErrorNum;
 	owErrorNum = owGetErrorNum();
        return Py_BuildValue("i", owErrorNum);
}

/**
===============================================================================
owAquireEx
===============================================================================
**/
static PyObject* owpy_owAcquireEx(PyObject* self, PyObject* args) {

	char* portName;	// Maybe this shouldn't be const
	int portNum;

	// Check that parameter is a string
	if(!PyArg_ParseTuple(args, "s", &portName)) {
		return NULL;
	}
	portNum = owAcquireEx(portName);
	return Py_BuildValue("i", portNum);
}

/**
===============================================================================
owRelease
===============================================================================
**/
static PyObject* owpy_owRelease(PyObject* self, PyObject* args) {

	int portNum;
	int ret = 1;

	if(!PyArg_ParseTuple(args, "i", &portNum)) {
		return NULL;
	}
	owRelease(portNum);
	// TODO: Add error checking here to see if release was successfull
	return Py_BuildValue("i", ret);
}

/* Array of 1-wire lib exposed methods */
static PyMethodDef OwpyMethods[] = {
	{"owAcquireEx", owpy_owAcquireEx, METH_VARARGS,
		"Aquire 1-wire USB busmaster"},
	{"owRelease",  owpy_owRelease,  METH_VARARGS,
		"Release 1-wire USB busmaster"},
	{"owTestFunction", owpy_owTestFunction,  METH_NOARGS,
		"Prints test message if successful"},
	{"owGetErrorNum", owpy_owGetErrorNum,  METH_NOARGS,
		"Gets top error num from ow error stack"},
	{"owHasErrors", owpy_owHasErrors,  METH_NOARGS,
		"Returns true if errors exist on the stack"},
	{"owGetErrorMsg",  owpy_owGetErrorMsg,  METH_VARARGS,
		"Gets the specified error message string"},
	{"owSerialNum",  owpy_owSerialNum, METH_VARARGS,
		"Reads or sets the serial number buffer"},
	{"owReadTemperature",  owpy_owReadTemperature, METH_VARARGS,
		"Returns temperature from specified device serial number. "
		"Returns None if error or device is not a temperature device"},
	{"owListDevices",  owpy_owListDevices,  METH_VARARGS,
		"Returns a list of device serial numbers on the specified port"
		" or None if there were errors"},
	{"owReadCounter",  owpy_owReadCounter,  METH_VARARGS,
		"Returns the counter value from the specified page of a 0x1D "
		"family counter. Valid page ranges are 12-15 inclusive"},
	{"owTouchReset",  owpy_owTouchReset,  METH_VARARGS,
		"Reset all of the devices on the 1-Wire Net and return the "
		"result"},
	{"owTouchBit",  owpy_owTouchBit,  METH_VARARGS,
		"Send 1 bit of communication to the 1-Wire Net and return the "
		"result 1 bit read from the 1-Wire Net"},
	{"owTouchByte",  owpy_owTouchByte,  METH_VARARGS,
		"Send 8 bits of communication to the 1-Wire Net and verify "
		"that the 8 bits read from the 1-Wire Net is the same (write "
		"operation)"},
	{"owWriteByte",  owpy_owWriteByte,  METH_VARARGS,
		"Send 8 bits of communication to the MicroLAN and verify that "
		"the 8 bits read from the MicroLAN is the same (write "
		"operation)"},
	{"owReadByte",  owpy_owReadByte,  METH_VARARGS,
		"Send 8 bits of read communication to the 1-Wire Net and and "
		"return the result 8 bits read from the 1-Wire Net"},
	{"owSpeed",  owpy_owSpeed,  METH_VARARGS,
		"Set the 1-Wire Net communucation speed"},
	{"owLevel",  owpy_owLevel,  METH_VARARGS,
		"Set the 1-Wire Net line level"},
	{"owProgramPulse",  owpy_owProgramPulse,  METH_VARARGS,
		"Creates a fixed 480 microseconds 12 volt pulse on the 1-Wire "
		"Net for programming EPROM iButtons"},
	{"owTouchBytePower",  owpy_owTouchBytePower,  METH_VARARGS,
		"Send and recieve 8 bits of communication to the 1-Wire Net. "
		"After the 8 bits are sent change the level of the 1-Wire net "
		"to strong pullup power delivery."},
	{"owWriteBytePower",  owpy_owWriteBytePower,  METH_VARARGS,
		"Send 8 bits of communication to the 1-Wire net and verify "
		"that the 8 bits read from the 1-Wire Net is the same (write "
		"operation). After the 8 bits are sent change the level of "
		"the 1-Wire net"},
	{"owReadBytePower",  owpy_owReadBytePower,  METH_VARARGS,
		"Read 8 bits of communication from the 1-Wire net and provide"
		" strong pullup power"},
	{"owReadBitPower",  owpy_owReadBitPower,  METH_VARARGS,
		"Read 1 bit of communication from the 1-Wire net and verify "
		"that the response matches the 'applyPowerResponse' bit and "
		" apply power delivery to the 1-Wire net.  Note that some "
		"implementations may apply the power first and then turn it "
		"off if the response is incorrect"},
	{"owHasPowerDelivery",  owpy_owHasPowerDelivery,  METH_VARARGS,
		"Indicates whether the adapter can deliver power"},
	{"owHasOverDrive",  owpy_owHasOverDrive,  METH_VARARGS,
		"Indicates whether the adapter has overdrive speed."},
	{"owHasProgramPulse",  owpy_owHasProgramPulse,  METH_VARARGS,
		"Indicates whether the device can receive a program pulse"},
	{"owReadMaxQIO",  owpy_owReadMaxQIO,  METH_VARARGS,
		"EXPERIMENTAL: attemps to read 8 bytes from MaxQ1004 I/O register"},
	{"owWriteMaxQIO",  owpy_owWriteMaxQIO,  METH_VARARGS,
		"EXPERIMENTAL: attemps to write up to 8 bytes to MaxQ1004 I/O register"},
	{"owReadMaxQStatus",  owpy_owReadMaxQStatus,  METH_VARARGS,
		"EXPERIMENTAL: attemps to read the MaxQ1004 status register"},
	{"owReadMaxQCmdBuffer",  owpy_owReadMaxQCmdBuffer,  METH_VARARGS,
		"EXPERIMENTAL: read the MaxQ1004 command buffer. Up to 32 bytes."},
	{"owWriteMaxQCmdBuffer",  owpy_owWriteMaxQCmdBuffer,  METH_VARARGS,
		"EXPERIMENTAL: write to the MaxQ1004 command buffer. Up to 32 bytes."},
	{"owMaxQStartProgram",  owpy_owMaxQStartProgram,  METH_VARARGS,
		"EXPERIMENTAL: Sends a command to the MAXQ1004 telling the application "
		"code to begin execution."},
	{"owWriteMaxQCmdBufferExtStart",  owpy_owWriteMaxQCmdBufferExtStart,  METH_VARARGS,
		"EXPERIMENTAL:  write to the MaxQ1004 command buffer(Up to 32 bytes) "
		"and intructs the MAXQ1004 application code to begin execution."},
	{NULL, NULL, 0, NULL}	/* Sentinel */
};

PyMODINIT_FUNC initowpy(void){
	PyObject* ret;
	ret = Py_InitModule("owpy", OwpyMethods);
	if(NULL == ret) {
		return;
	}
	OwpyError = PyErr_NewException("owpy.error", NULL, NULL);
	Py_INCREF(OwpyError);
	PyModule_AddObject(ret, "error", OwpyError);
}

int main (int argc, char* argv[]) {
	Py_SetProgramName(argv[0]);
	Py_Initialize();
	initowpy();
	return 0;
}

// ===== Utility Functions =====

/**
===============================================================================
btohc - byte to hexadecimal char
===============================================================================
**/
int btohc( unsigned char* buffer_from, unsigned char* buffer_to, size_t len_from,
	size_t len_to) {
	int i;

	if(len_to < len_from*2) {
		return 0;
	}

	for(i=0; i<len_from; i++){
		buffer_to[(i*2)]   = (buffer_from[i]>>4) & 0x0F;
		buffer_to[(i*2)+1] = (buffer_from[i]) & 0x0F;

		if(buffer_to[i*2] < 0x0A) {
			buffer_to[i*2] += 48;
		} else {
			buffer_to[i*2] += 55;
		}
		if(buffer_to[(i*2)+1] < 10) {
			buffer_to[(i*2)+1] += 48;
		} else {
			buffer_to[(i*2)+1] += 55;
		}
	}
	return 1;
}

/**
===============================================================================
revstring - reverse a string
===============================================================================
**/
int revstring(unsigned char* buffer, size_t len) {
	int i;
	unsigned char tmp;

	for(i=0; i<len/2; i++) {
		tmp = buffer[i];
		buffer[i] = buffer[len-1-i];
		buffer[len-1-i] = tmp;
	}
	return 1;
}


/**
===============================================================================
checkSerial:
        Takes a string (of expected length 16) passed in by serialStr,
        converts it to a valid 8-byte serial number and stores it in
        serialNum. Returns TRUE if the operation was successful and FALSE
        otherwise. NOTE: the serialStr will be left in an undefined state
        if FALSE was returned.
===============================================================================
*/
int checkSerial( const char* serialStr, uchar* outputSerial ) {

        int len, i, a, b;       // String length, iterator, and test vars
        uchar testSerial[8];

        // Check that the string is the proper length (16 chars)
        len = strlen(serialStr);
        if(len != (int)(SERIALNUMLEN<<1)) {
		PyErr_SetString(OwpyError, "In checkSerial: parameter serialStr is not proper length");
                return 0;
	}

        // Convert the hex string to a byte array and fail if any
        // invalid characters
        for(i=0; i<len; i+=2) {
                a = chartohi(serialStr[i]);
                b = chartohi(serialStr[i+1]);
                if(a == -1 || b == -1) {
			PyErr_SetString(OwpyError, "In checkSerial: Failed to convert char to hex value");
			return 0;
		}
                testSerial[SERIALNUMLEN - 1 - (i>>1)] =
                        (uchar)((a << 4) & 0xF0) + (b & 0x0F);
        }
        memcpy(outputSerial, testSerial, sizeof(uchar)*SERIALNUMLEN);
        return 1;
}


/**
===============================================================================
chartohi:
        Converts a single ascii encoded hex digit to an integer. Returns -1
if the input character is not a valid hex digit.
===============================================================================
*/
int chartohi( char value ) {
        if(isdigit(value))
                return (int)(value - '0');
        else if(toupper(value) >= 'A' && toupper(value) <= 'F')
                return (int)(toupper(value) - 'A' + 10);
        return -1;
}

