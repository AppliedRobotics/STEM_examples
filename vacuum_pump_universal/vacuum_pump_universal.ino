/*******************************************************************************
* Copyright 2016 ROBOTIS CO., LTD.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/* Authors: Taehun Lim (Darby) */



#if defined(__OPENCM904__)
  #define DEVICE_NAME "3" //Dynamixel on Serial23(USART3)  <-OpenCM 485EXP
  #define vacuum_pump 8
  #define vacuum_key 9
  #define RED_BUTTON 10
  #define NanoPiSerial Serial1
#elif defined(__OPENCR__)
  #define vacuum_pump 51
  #define vacuum_key 57
  #define RED_BUTTON 63
  #define NanoPiSerial Serial2
  #define DEVICE_NAME ""
#endif

void setup() {
  // put your setup code here, to run once:
  pinMode(RED_BUTTON, INPUT_PULLUP);
  pinMode(vacuum_pump, OUTPUT);
  pinMode(vacuum_key, OUTPUT);
  digitalWrite(vacuum_pump, LOW);
  digitalWrite(vacuum_key, LOW);
  NanoPiSerial.begin(115200);
  //while(NanoPiSerial.read() != 's') {
    //loop();
//  };  
  //NanoPiSerial.println("start");
}

void loop() {
  if(!digitalRead(RED_BUTTON))
  { 
    NanoPiSerial.println("push up");  
  }
  else
  {
    NanoPiSerial.println("push down"); 
  }
  int c = NanoPiSerial.parseInt(); 
  if(c == 2){
    digitalWrite(vacuum_pump, LOW);
    digitalWrite(vacuum_key, LOW);
    }
  if(c == 1){
    digitalWrite(vacuum_pump, HIGH);
    digitalWrite(vacuum_key, HIGH);
    }
  delay(100);
}
