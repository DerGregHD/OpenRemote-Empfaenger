#include <SPI.h>
#include "printf.h"
#include "RF24.h"
#include <Servo.h>

//RFM95W
#define rfm95w_mosi 19
#define rfm95w_miso 16
#define rfm95w_sck 18
#define rfm95w_cs 17
#define rfm95w_reset 20

//RF24
//RF24 radio(7, 8);
//uint8_t address[][6] = {"00001"};

int PWMValue = 90;

Servo servo1;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
  }
  Serial.println("LoRa Receiver");
  LoRa.setPins(rfm95w_cs, rfm95w_reset, 2);
  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  else {
    Serial.println("Starting LoRa successfull!");
  }

  servo1.attach(21);
}

void loop() {
  Serial.println(F("Start the loop!"));
  
  uint8_t pipe;
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
    servo1.write(PWMValue);
    Serial.println(PWMValue);
    delay(10);
    Serial.println(F("radio is not available"));
  
}
