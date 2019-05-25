/*
	This is a library for the SL19 Infra Red Thermometer

	The board uses I2C for communication.
	
	The board communicates with two I2C devices:
	*	MLX90614
	
	Data Sheets:
	MLX90614	- https://www.melexis.com/-/media/files/documents/datasheets/mlx90614-datasheet-melexis.pdf
*/

#include "vaSL19.h"

/*---Public Function---*/
/********************************************************
 	Constructor
*********************************************************/
vaSL19::vaSL19(void) 
{
	ambient_temp = 0;
	object_temp = 0;
	MLX90614_I2C_ADDR = 0x5A;
}

/********************************************************
 	Configure Sensor
*********************************************************/
bool vaSL19::begin(void)
{
	if(xCore.ping(MLX90614_I2C_ADDR)){
		return true;
	} else {
		return false;
	}
}

/********************************************************
 	Reads Sensor Data
*********************************************************/
void vaSL19::poll(void) 
{
	readAmbient();
	readObject();
}

/********************************************************
 	Get the Ambient Temperature from MLX90614 (C)
*********************************************************/
uint8_t vaSL19::getAmbientTempC(void)
{
	uint8_t temp_calc;
	temp_calc = map(ambient_temp, -40, 125, 0, 165);
	return temp_calc;
}

/********************************************************
 	Get the Object Temperature from MLX90614 (C)
*********************************************************/
uint16_t vaSL19::getObjectTempC(void)
{
	uint16_t temp_calc;
	temp_calc = (object_temp+70)*50;
	//temp_calc = map(object_temp, -70, 380, 0, 22500);
	return temp_calc;
}

/*---Private Function---*/

/********************************************************
 	Read temperature Data from MLX90614
*********************************************************/
void vaSL19::readAmbient(void) 
{
	float tempData; 
	tempData = readTemp(MLX90614_REG_TA);
	tempData *= .02;
  	tempData -= 273.15;
	ambient_temp = tempData;
}

void vaSL19::readObject(void) 
{
	float tempData;
	tempData = readTemp(MLX90614_REG_TOBJ1);
  	tempData *= .02;
  	tempData -= 273.15;
	object_temp = tempData;
}

uint16_t vaSL19::readTemp(uint8_t reg)
{
  	uint32_t data;
  	data = xCore.read24(MLX90614_I2C_ADDR, reg);

	uint8_t HB,LB;
	HB = data >> 8;
	LB = data >> 16;

  	return ((HB << 8)| LB);
}