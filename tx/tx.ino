#include <SPI.h>
#include "RF24.h"
#include <printf.h>

// Hardware configuration
// Set up nRF24L01 radio on SPI bus plus pins 7 & 8
RF24 radio(7, 8);

// Use the same address for both devices
uint8_t address[] = { "radio" };

// Simple messages to represent a 'ping' and 'pong'
uint8_t ping = 111;

volatile uint32_t round_trip_timer = 0;

void setup() {
    radio.begin();
    // Use dynamic payloads to improve response time
    radio.enableDynamicPayloads();
    radio.openWritingPipe(address);// communicate back and forth.    One listens on it, the other talks to it.
    radio.openReadingPipe(1, address);
    attachInterrupt(0, check_radio, LOW);// Attach interrupt handler to interrupt #0 (using pin 2) on BOTH the sender and receiver
}

void loop() {
    if () {
        radio.startWrite( &ping, sizeof(uint8_t), 0 );
    }
}
