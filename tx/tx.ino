#include <SPI.h>
#include "RF24.h"
#include <PinChangeInt.h>

// Hardware configuration
// CE on 7, CSN on 8
RF24 radio(7, 8);

// Use the same address for both devices
uint8_t address[] = { "flash" };

// Some fake payload
const byte payload = 13;

void setup() {
    radio.begin();
    // Use dynamic payloads to improve response time
    radio.enableDynamicPayloads();
    radio.openWritingPipe(address);
    pinMode(4, INPUT_PULLUP);
    attachPinChangeInterrupt(4, trigger, FALLING);
}

void loop() {
  // Do nothing but wait for interruption
}

void trigger(){
    radio.write(&payload, 1);
}

