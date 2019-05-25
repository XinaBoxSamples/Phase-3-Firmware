/*
	This is a library for the SW10 
	DIGITAL TEMPERATURE SENSOR

	The board uses I2C for communication.
	
	The board communicates with the following I2C device:
	-	LM75B
	
	Data Sheets:
	LM75B - https://www.nxp.com/docs/en/data-sheet/LM75B.pdf
*/

#include "vaSW10.h"
#include <math.h>
  
/*--Public Class Function--*/

/********************************************************
 	Constructor
*********************************************************/
vaSW10::vaSW10(void)
{
	tempC = 0.0;
    LM75B_I2C_ADDR = 0x48;
}

vaSW10::vaSW10(uint8_t addr)
{
	tempC = 0.0;
    LM75B_I2C_ADDR = addr; 
}

/********************************************************
 	Configure Sensor
*********************************************************/
bool vaSW10::begin(void)
{
    if(xCore.ping(LM75B_I2C_ADDR)) {
        return true;
    } else {
        return false;
    }
} 

/********************************************************
 	Read Data from LM75B Sensor
*********************************************************/
void vaSW10::poll(void)
{
	readTemperature();
}


/********************************************************
 	Temperature from LM75B Sensor in Celcuis
*********************************************************/
uint8_t vaSW10::getTempC(void)
{
	uint8_t temp_calc;
	temp_calc = map(tempC, -55, 125, 0, 200);
    return temp_calc;	
}

/*--Private Class Function--*/
/********************************************************
 	Read Temperature from LM75B Sensor 
*********************************************************/
void vaSW10::readTemperature(void)
{
  uint16_t data = xCore.read16(LM75B_I2C_ADDR, LM75B_REG_TEMP);
  tempC = (data >> 5) * 0.125; 
}

