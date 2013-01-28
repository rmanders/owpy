#include "ownet.h"
#include "tempall.h"
#include "temp10.h"
#include "temp28.h"

//----------------------------------------------------------------------
// Read the temperature of a DS1920/DS1820/DS18B20
//
// 'portnum'     - number 0 to MAX_PORTNUM-1.  This number was provided to
//                 OpenCOM to indicate the port number.
// 'serialNum'   - Serial Number of DS1920/DS1820 to read temperature from
// 'temp '       - pointer to variable where that temperature will be
//                 returned
//
// Returns: TRUE(1)  temperature has been read and verified
//          FALSE(0) could not read the temperature, perhaps device is not
//                   in contact
//
//----------------------------------------------------------------------

int ReadTemperatureAny(int portnum, uchar* serialNum, float* temp) {

	switch (serialNum[0]) {
	case 0x10:
		return ReadTemperature(portnum, serialNum, temp);
	case 0x28:
		return ReadTemperature28(portnum, serialNum, temp);
	default:
		return FALSE;
	}
	return FALSE;
}


