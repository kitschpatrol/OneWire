#include <OneWire.h>
#include "OneWireSequence.h"

// OneWire DS28EA00 Sequence Detect Example
//
// The OneWire library's default "search" method will return all devices on a bus, but not
// necessarily in the order they're actually attached. The DS28EA00 Thermometer implements 
// a feature called Sequence Detect which allows OneWire devices to be enumerated in the actual
// order they're physically attached.
//
// The OneWireSequence subclass which encapsulates the sequence detection process. It imlements methods
// with the same signatures and usage as the search function, but which returns devices in their physically
// attached order.
// 
// Read more about sequence detect here: http://www.maximintegrated.com/en/products/analog/sensors-and-sensor-interface/DS28EA00.html
// Read more about the implementation on page 28 of datasheet: http://pdfserv.maximintegrated.com/en/ds/DS28EA00.pdf
//
// See the DS28EA00_Sequence_Detect.ino file for an example of this functionality in use:
// https://github.com/kitschpatrol/OneWire/blob/master/examples/DS28EA00_Sequence_Detect/DS28EA00_Sequence_Detect.ino
//
// Documentation for the base library is abailable here:
// http://www.pjrc.com/teensy/td_libs_OneWire.html

OneWireSequence  ds(10);  // on pin 10 (a 4.7K resistor is necessary)

void setup(void) {
	Serial.begin(9600);
	while (!Serial); // Leonardo/Micro should wait for serial init

	Serial.println("Starting OneWire device sequencing");	
	
	if (ds.reset_sequence()) {
		uint8_t address[8];
		int index = 0;
		while(ds.sequence(address)) {
			// Prints the IDs of each device in the order they're attached.
			Serial.print("Device " + String(index) + " = ");
			for (int i = 0; i < 8; i++) {
				Serial.print(String(address[i], HEX));
			}
			Serial.println();
			index++;
		}
		Serial.println("Finished sequencing");
	}
	else {
		Serial.println("Reset sequence failed.");
	}
}

void loop(void) {

}
