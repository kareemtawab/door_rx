#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
int msg[1];
RF24 radio(10, 9);
const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup(void) {
  pinMode(8, OUTPUT);
  Serial.begin(115200);
  radio.begin();
  radio.setChannel(75);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.openReadingPipe(1, pipe);
  radio.startListening();
  delay(500);
}

void loop(void) {
  while (radio.available()) {
    radio.read(msg, 1);
    if (msg[0] == 111) {
      Serial.print(msg[0]);
      Serial.println(": RX OK");
      digitalWrite(8, LOW);
    }
    delay(80);
  }
  Serial.println("RX NOT OK");
  digitalWrite(8, HIGH);
  delay(80);
}
