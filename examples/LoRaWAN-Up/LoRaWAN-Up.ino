#include <Arduino.h>
#include "lorae5.h"
#include "config_application.h"

uint8_t sizePayloadUp = 4;

uint8_t payloadUp[20] = {0x00, 0x01, 0x02, 0x03};

LORAE5 lorae5(devEUI, appEUI, appKey, devAddr, nwkSKey, appSKey); 

void setup() {
  lorae5.setup(ACTIVATION_MODE, CLASS, SPREADING_FACTOR, ADAPTIVE_DR, CONFIRMED, PORTUP);
  lorae5.printInfo(SEND_BY_PUSH_BUTTON, FRAME_DELAY);

  if(ACTIVATION_MODE == OTAA){
    USB_Serial.println("Join Procedure in progress...");
    while(lorae5.join() == false);
    delay(2000);
   }
}

void loop() {
  // Send "sizePayloadUp" bytes from "uplink" table
  lorae5.sendData(payloadUp, sizePayloadUp);

  delay(FRAME_DELAY-6000);  // Wait
}