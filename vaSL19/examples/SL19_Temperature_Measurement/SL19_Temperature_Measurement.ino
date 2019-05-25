/*************************************************************
	This is an examples for the SL19
	IR Temperature Measurement
	
	You can buy one on our store!
	-----> https://xinabox.cc/SL19/
	
	This example request a temperature measurement to be made
	by the SL19.
	
	The sensor communicates over the I2C Bus.
	
*************************************************************/

#include <xCore.h>
#include <vaSL19.h>

vaSL19 SL19;

const int DELAY_TIME = 1000;

void setup() {
	// Start the Serial Monitor
	Serial.begin(115200);
	
	// Set the I2C Pins for CW01
	#ifdef ESP8266
	  Wire.pins(2, 14);
	  Wire.setClockStretchLimit(15000);
	#endif
	
	// Start the I2C Comunication
	Wire.begin();
	
	// Start the  SL19 Sensor
	SL19.begin();

	// Delayy for Sensor to normalise
	delay(1000);
	
	Serial.println("================================");
	Serial.println("    XINABOX SL19 Temperature    ");
	Serial.println("================================"); 
}

void loop() {
	  // Create a variable to store the incoming measurements
	  float tempC;
	  tempC = 0;

	  // Poll Sensor for collect data
	  SL19.poll();

	  tempC = SL19.getAmbientTempC();

	  // Display Data on the Serial monitor
	  Serial.print("Ambient Temperaturel: ");
	  Serial.print(tempC);
	  Serial.println(" *C");
	  
	  Serial.println();

	  delay(DELAY_TIME);
}
