#include <SPI.h>
#include "RF24.h"
#include <printf.h>

// Hardware configuration
// Set up nRF24L01 radio on SPI bus plus pins 7 & 8
RF24 radio(7, 8);

// Use the same address for both devices
uint8_t address[] = { "flash" };

void setup() {
    radio.begin();
    // Use dynamic payloads to improve response time
    radio.enableDynamicPayloads();
    radio.openWritingPipe(address);// communicate back and forth.    One listens on it, the other talks to it.
    radio.openReadingPipe(1, address);
    radio.startListening();
    attachInterrupt(0, recv, LOW);// Attach interrupt handler to interrupt #0 (using pin 2) on BOTH the sender and receiver
}

void loop() {
    //Do nothing, only wait for interruption
}

void recv(void)//Trigger the flash
{
    
}
