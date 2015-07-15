#include <OneWire.h>

// OneWire DS18S20, DS18B20, DS1822 Temperature Example
//
// http://www.pjrc.com/teensy/td_libs_OneWire.html
//
// The DallasTemperature library can do all this work for you!
// http://milesburton.com/Dallas_Temperature_Control_Library

OneWire  ds(10);  // on pin 10 (a 4.7K resistor is necessary)

void setup(void) {
  Serial.begin(9600);
  while (!Serial); // Leonardo/Micro should wait for serial init


	uint8_t address[8];

	println("Starting OneWire device sequencing");	
	int index = 0;	
	reset_sequence();
	while(sequence(&address)) {
        print("Device " + String(index) + " = ");
        for (int i = 0; i < 8; i++) {
          print(String(address[i], HEX));
        }
        println();
        index++;
	}
	println("Finished sequencing");
  
}

void loop(void) {


}
