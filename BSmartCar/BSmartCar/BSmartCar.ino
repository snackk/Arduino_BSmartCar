/*
 Name:		BSmartCar.ino
 Created:	7/8/2016 5:59:48 PM
 Author:	snackk
*/

#include <SmartCarLib.h>
#include <SoftwareSerial.h>

//BLUETOOTH
#define rxPin 2
#define txPin 3

SoftwareSerial swSerial(txPin, rxPin);

#define BUFF_SIZE 256
uint8_t buffer[BUFF_SIZE];
uint8_t index = 0;
uint8_t data;

String data_b;

//SMARTCAR
SmartCar smartcar(10, 11, 6, 12, 13, 5);

void setup() {
	//Initialize BT serial and serial port
	swSerial.begin(9600);
	Serial.begin(9600);
}

void loop() {
	while (!swSerial.available());

	while (swSerial.available()) {
		data = swSerial.read();

		buffer[index++] = data;

		if (index == BUFF_SIZE || data == '\0') break;
		delay(1);
	}

	for (uint8_t i = 0; i < index; ++i) {
		//swSerial.write(buffer[i]);  //Echo message received
		data_b += (char)buffer[i];    //Store received char on data
	}

	smartcar.handleCar(data_b);

	data_b = "";
	index = 0;
}
