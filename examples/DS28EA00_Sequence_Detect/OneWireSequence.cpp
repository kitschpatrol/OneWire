#include "OneWireSequence.h"

bool OneWireSequence::reset_sequence() {
  return chainOn();
}

bool OneWireSequence::sequence(uint8_t *newAddr) {
  reset();
  write(0x0F, ONEWIRE_SEQUENCE_BUS_POWER);
  read_bytes(newAddr, 8);
  bool success = false;
  bool moreDevices = false;

  // Solid block of 0xFF back signifies end of chain
  for (int i = 0; i < 8; i++) {
    if (newAddr[i] != 0xFF) {
      moreDevices = true;
      break;
    }
  }

  if (moreDevices) {
    if (OneWire::crc8(newAddr, 7) != newAddr[7]) {
      // CRC is not valid!
      success = false;
    }
    else {
      uint8_t chainDoneCommands[] = {0x99, 0x96, 0x69};
      write_bytes(chainDoneCommands, 3, ONEWIRE_SEQUENCE_BUS_POWER);
      success = true;
    }

    depower();
  }
  else {
    chainOff();
  }

  return success;
}

bool OneWireSequence::chainOn() {
  reset();
  uint8_t chainOnCommands[] = {0xCC, 0x99, 0x5A, 0xA5};
  write_bytes(chainOnCommands, 4, ONEWIRE_SEQUENCE_BUS_POWER);
  bool success = read() == 0xAA; // success if response is 0xAA}
  depower();
  return success;
}

bool OneWireSequence::chainOff() {
  reset();
  uint8_t chainOffCommands[] = {0xCC, 0x99, 0x3C, 0xC3};
  write_bytes(chainOffCommands, 4, ONEWIRE_SEQUENCE_BUS_POWER);
  bool success = read() == 0xAA; // success if response is 0xAA
  depower();
  return success;
}