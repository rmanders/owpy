#include "test.h"

int portNum;
char portName[30];
char serial[20];



int main(void) {

	uchar owAddrBytes[8];
	uchar writeBuffer[] = {0x64, 0xEE, 0x00, 0x00, 0x00, 0x02, 0x03};

	portNum = 0;
	strcpy(portName,"DS2490-1");
	strcpy(serial, "FA00000001743763");

	portNum = owAcquireEx(portName);
	if(portNum <= 0 ) {
		printf("Error acquiring 1-wire USB device\n");
		return 1;
	}

	// Convert string-based serial to owAddress
	if(!checkSerial(serial, owAddrBytes)) {
		owRelease(portNum);
		return 1;
	}

	// DO STUFF HERE

	owSerialNum(portNum, owAddrBytes, FALSE);

	// 1) Test Maxq Read status
	testMaxQReadStatus(portNum, owAddrBytes);

	// 2) See what's in the command buffer initially
	testReadCmdBuffer(portNum, owAddrBytes, 7);

	// 3) Write something to the command buffer
	testWriteCmdBufferExStart(portNum, owAddrBytes, writeBuffer, 7);

	// 4) Test Maxq Read status
	testMaxQReadStatus(portNum, owAddrBytes);

	// 5) Read back what we wrote
	testReadCmdBuffer(portNum, owAddrBytes, 7);

	// Notice that the write succeeds but the release sequence response fails.

	owRelease(portNum);

	printf("Finished Successfully\n");
	return 0;
}


/**
===============================================================================
testWriteCmdBufferExStart
===============================================================================
*/
void testWriteCmdBufferExStart(int portNum, uchar* owAddrBytes, uchar* writeBuffer, int writeLen) {

	int i;
	if(!writeMaxQCmdBufferExtStart(portNum, owAddrBytes, writeBuffer, writeLen)) {
		printf("An Error occurred while writing to the cmd buffer\n");
		owErrorOutput();
		printf("\n");

		owRelease(portNum);
		exit(1);
	}

	printf("Bytes Written with Start cmd[%d]: ", writeLen);
	for(i=0; i<writeLen; i++) {
		printf("0x%02X ",writeBuffer[i]);
	}
	printf("\n\n");
}

/**
===============================================================================
testReadCmdBuffer
===============================================================================
*/
void testReadCmdBuffer(int portNum, uchar* owAddrBytes, int readLen) {
	uchar readBytes[32];
	int i;

	if(!readMaxQCmdBuffer(portNum, owAddrBytes, readBytes, readLen)) {
		printf("An error occurred while reading  from teh maxq cmd buffer\n");
		owErrorOutput();
		owRelease(portNum);
		exit(1);
	}
	printf("Bytes Read[%d]: ", readLen);
	for(i=0; i<readLen; i++) {
		printf("0x%02X ",readBytes[i]);
	}
	printf("\n\n");
}

/**
===============================================================================
testMaxQReadStatus
===============================================================================
*/
void testMaxQReadStatus(int portNum, uchar* owAddrBytes) {
	uchar status[7];

	 if(!readMaxQStatus(portNum, owAddrBytes, status)) {
                printf("Error reading MaxQ status register\n");
		owErrorOutput();
                owRelease(portNum);
                exit(1);
        }
        printf("MaxQ Status Read:\n\tFree Input Buffer Bytes: %d\n\t"
        "Used Output Buffer Bytes: %d\n\tOWMS Register contents: 0x%X\n",
        status[1], status[2], status[3] & 0x3F);

	printf("\tPower on reset occurred?: ");
	if( ((status[3] >> 6) & 0x01) == 1 )
		printf("YES\n");
	else
		printf("NO\n");

	printf("\t1-wire IO status: ");
	if( ((status[3] >> 7) & 0x01) == 1 )
		printf("Master can read/write to IO buffer only\n");
	else
		printf("Master can read/write to IO and Cmd Buffers\n");
	printf("\n");
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
                printf("In checkSerial: parameter serialStr is not proper length\n");
                return 0;
        }

        // Convert the hex string to a byte array and fail if any
        // invalid characters
        for(i=0; i<len; i+=2) {
                a = chartohi(serialStr[i]);
                b = chartohi(serialStr[i+1]);
                if(a == -1 || b == -1) {
                        printf("In checkSerial: Failed to convert char to hex value\n");
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

/**
===============================================================================
owErrorOutput:
        Outputs an error string from the 1-wire subsystem if any errors exist.
        If there are no errors on the 1-wire error stack, nothing is printed.
        Prints to stderr
===============================================================================
*/
void owErrorOutput( void ) {
        int curErrNum = 0;
        if(owHasErrors()) {
                printf("OW_ERROR_MSG: ");
        } else {
                return;
        }
        while(owHasErrors()) {
                curErrNum = owGetErrorNum();
                printf("[%d]%s", curErrNum, owGetErrorMsg(curErrNum) );
                if(owHasErrors()) {
                        printf(" : ");
                }
        }
        printf("\n");
}
