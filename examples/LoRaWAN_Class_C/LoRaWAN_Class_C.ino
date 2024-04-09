#include <Arduino.h>
#include "lorae5.h"
#include "config_application.h"

uint8_t sizePayloadUp = 4;
uint8_t sizePayloadDown = 0;

uint8_t payloadUp[20] = {0x00, 0x01, 0x02, 0x03};
uint8_t payloadDown[20]  ={0};

LORAE5 lorae5(devEUI, appEUI, appKey, devAddr, nwkSKey, appSKey);

/***********************************************************************/
/* Please see README page on https://github.com/SylvainMontagny/LoRaE5 */
/***********************************************************************/

void setup() {
  lorae5.setup(REGION, ACTIVATION_MODE, CLASS, SPREADING_FACTOR, ADAPTIVE_DR, CONFIRMED, PORT_UP, SEND_BY_PUSH_BUTTON, FRAME_DELAY);
  lorae5.printInfo();

  if(ACTIVATION_MODE == OTAA){
    USB_Serial.println("Join Procedure in progress...");
    while(lorae5.join() == false);
    delay(2000);
   }
}

void loop() {
  // Send data
  lorae5.sendData(payloadUp, sizePayloadUp);
  // Await for Downlink Class_A
  if (lorae5.awaitForDownlinkClass_A(payloadDown, &sizePayloadDown) == RET_DOWNLINK){
    processDownlink();
  };
  // Await for Downlink Class_C
  if (lorae5.awaitForDownlinkClass_C(payloadDown, &sizePayloadDown) == RET_DOWNLINK){
    processDownlink();
  };
}

void processDownlink() {
  // You have received "sizePayloadDown" bytes stored in the table "payloadDown"
}