#include <SPI.h>
#include "RF24.h"
#include <printf.h>

// Hardware configuration
// Set up nRF24L01 radio on SPI bus plus pins 7 & 8
RF24 radio(7, 8);

// Use the same address for both devices
uint8_t address[] = { "flash" };

// Some fake payload
uint8_t payload = 0;

void setup() {
    radio.begin();
    // Use dynamic payloads to improve response time
    radio.enableDynamicPayloads();
    radio.openWritingPipe(address);// communicate back and forth.    One listens on it, the other talks to it.
    radio.openReadingPipe(1, address);
}

void loop() {
    if (1) {
        radio.startWrite( &payload, sizeof(uint8_t), 0 );
    }
}
