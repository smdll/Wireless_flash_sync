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
uint8_t pong = 222;

volatile uint32_t round_trip_timer = 0;

void setup() {
    radio.begin();
    // Use dynamic payloads to improve response time
    radio.enableDynamicPayloads();
    radio.openWritingPipe(address);// communicate back and forth.    One listens on it, the other talks to it.
    radio.openReadingPipe(1, address);
    radio.startListening();
    attachInterrupt(0, check_radio, LOW);// Attach interrupt handler to interrupt #0 (using pin 2) on BOTH the sender and receiver
}

void loop() {
    //Do nothing but wait for interruption
}

void check_radio(void)// Receiver role: Does nothing!    All the work is in IRQ
{
    bool tx, fail, rx;
    radio.whatHappened(tx, fail, rx);// What happened?

    // If data is available, handle it accordingly
    if ( rx ) {
        if (radio.getDynamicPayloadSize() < 1) {
            // Corrupt payload has been flushed
            return;
        }
        // Read in the data
        uint8_t received;
        radio.read(&received, sizeof(received));

        // If this is a ping, send back a pong
        if (received == ping) {
            radio.stopListening();
            // Normal delay will not work here, so cycle through some no-operations (16nops @16mhz = 1us delay)
            for (uint32_t i = 0; i < 130; i++) {
                __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
            }
            radio.startWrite(&pong, sizeof(pong), 0);
            Serial.print("pong");
        } else
            // If this is a pong, get the current micros()
            if (received == pong) {
                round_trip_timer = micros() - round_trip_timer;
                Serial.print(F("Received Pong, Round Trip Time: "));
                Serial.println(round_trip_timer);
            }
    }
    // Start listening if transmission is complete
    if ( tx || fail ) {
        radio.startListening();
        Serial.println(tx ? F(":OK") : F(":Fail"));
    }
}
