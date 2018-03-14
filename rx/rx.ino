#include <SPI.h>
#include "RF24.h"

// Hardware configuration
// CE on 7, CSN on 8
RF24 radio(7, 8);

// Use the same address for both devices
uint8_t address[] = { "flash" };

void setup() {
    radio.begin();
    // Use dynamic payloads to improve response time
    radio.enableDynamicPayloads();
    radio.openReadingPipe(1, address);
    radio.startListening();
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);
    pinMode(5, OUTPUT);
    digitalWrite(5, LOW);
}

void loop() {
    while(!radio.available());
    digitalWrite(4, HIGH);
    delay(17);// 1/60s shutter simulation
    digitalWrite(4, LOW);
    radio.flush_rx();
}
