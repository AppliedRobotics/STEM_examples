/** Arduino UART blobs example.
 * Settings: Blob detector, UART full duplex, addr 51, Dynamixel API, 5V.
 * Wiring:
 *       Camera         Arduino Camera
 * 1-VF >|O O|  2-+5      TX1  -  RX
 * 3-Gnd |O O|  4-Gnd     RX1  -  TX
 * 5-TX   O O|  6-RX      5V   -  +5
 * 7-SCK |O O|  8-SNS     Gnd  -  Gnd
 * 9-IC0 |O O| 10-ID1     
 */

#include "TrackingCamDxlUart.h"

TrackingCamDxlUart trackingCam;
unsigned long previousMillis = 0; // stores last time cam was updated

void setup() {
  /*  TrackingCamDxlUart::init(uint8_t cam_id, uint8_t serial_port, uint32_t baud_rate, uint8_t timeout)
   *    cam_id - 1..252, default 51
   *    Serial_port:
   *      Serial (Rx\Tx) - 0
   *      Serial1 (Rx1\Tx1) - 1
   *      Serial2 (Rx2\Tx2) - 2
   *      Serial3 (Rx3\Tx3) - 3
   *    baud_rate - default 115200
   *    timeout - in ms - default 30
   */
  trackingCam.init(51, 1, 115200, 30);
  Serial.begin(115200);
  delay(5000);
}

void loop() {
  uint8_t n = trackingCam.readBlobs(5); // read data about first 5 blobs
  Serial.println("All blobs");
  Serial.println(n); // print numbers of blobs
  for(int i = 0; i < n; i++) // print information about all blobs
  {
    Serial.print(trackingCam.blob[i].type, DEC);
    Serial.print(" ");
    Serial.print(trackingCam.blob[i].dummy, DEC);
    Serial.print(" ");
    Serial.print(trackingCam.blob[i].cx, DEC);
    Serial.print(" ");
    Serial.print(trackingCam.blob[i].cy, DEC);
    Serial.print(" ");
    Serial.print(trackingCam.blob[i].area, DEC);
    Serial.print(" ");
    Serial.print(trackingCam.blob[i].left, DEC);
    Serial.print(" ");
    Serial.print(trackingCam.blob[i].right, DEC);
    Serial.print(" ");
    Serial.print(trackingCam.blob[i].top, DEC);
    Serial.print(" ");
    Serial.print(trackingCam.blob[i].bottom, DEC);
    Serial.println(" ");
  }
  
  // wait for the next frame
  while(millis() - previousMillis < 33) 
  {};
  previousMillis = millis();
}



