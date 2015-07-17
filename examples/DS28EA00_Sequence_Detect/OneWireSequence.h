#ifndef OneWireSequence_h
#define OneWireSequence_h

#include "Arduino.h"
#include "OneWire.h"

#ifndef ONEWIRE_SEQUENCE_BUS_POWER
#define ONEWIRE_SEQUENCE_BUS_POWER true
#endif

class OneWireSequence : public OneWire
{
  public:
    using OneWire::OneWire;
		// This subclass API imlements methods with the same signatures and usage as the search function,
		// but which return devices in order.

		// Returns true if reset succeeds.
    bool reset_sequence();

    // Returns true if there's another device available,
		// and fills an 8-byte array parameter newAddr with the device's unique address.
    bool sequence(uint8_t *newAddr);
		
  private:
    bool chainOn();
    bool chainOff();
};

#endif