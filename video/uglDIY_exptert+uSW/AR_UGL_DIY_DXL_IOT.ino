#include "DxlMaster.h"

const uint8_t id1 = 1;
const uint8_t id2 = 2;
const uint8_t id3 = 3;
const uint8_t id4 = 4;
const uint8_t id5 = 5;
const uint8_t id6 = 6;

const uint8_t id = 23;

int16_t speed = 50;
const long unsigned int baudrate = 1000000;

int16_t operating_mode_reg = 11;
int16_t position_control_mode = 3;
int16_t torque_reg = 64;
int16_t moving_speed = 112;
int16_t goal_position = 116;

uint8_t data = 0;

DynamixelDevice motor1(id1);
DynamixelDevice motor2(id2);
DynamixelDevice motor3(id3);
DynamixelDevice motor4(id4);
DynamixelDevice motor5(id5);
DynamixelDevice motor6(id6);

DynamixelDevice mod(id);

void setup() {
  DxlMaster.begin(baudrate);

  Serial.begin(57600);

  motor1.init();
  motor2.init();
  motor3.init();
  motor4.init();
  motor5.init();
  motor6.init();

  motor1.write(operating_mode_reg, position_control_mode);
  motor2.write(operating_mode_reg, position_control_mode);
  motor3.write(operating_mode_reg, position_control_mode);
  motor4.write(operating_mode_reg, position_control_mode);
  motor5.write(operating_mode_reg, position_control_mode);
  motor6.write(operating_mode_reg, position_control_mode);

  delay(100);
  mod.init();  

  motor1.write(torque_reg, 1);
  motor2.write(torque_reg, 1);
  motor3.write(torque_reg, 1);  
  motor4.write(torque_reg, 1);
  motor5.write(torque_reg, 1);  
  motor6.write(torque_reg, 1);  

  motor1.write(moving_speed, speed);
  motor2.write(moving_speed, speed);
  motor3.write(moving_speed, speed);
  motor4.write(moving_speed, speed);
  motor5.write(moving_speed, speed); 
  motor6.write(moving_speed, speed); 

  delay(3000);

}

void loop() {
  
  motor1.write(goal_position, 8192);
  motor2.write(goal_position, 8192);
  motor3.write(goal_position, 8192);
  motor4.write(goal_position, 8192);
  motor5.write(goal_position, 8192);
  motor6.write(goal_position, 9000);
  delay(3000);

  button();

  motor1.write(goal_position, 8192);
  motor2.write(goal_position, 9800);
  motor3.write(goal_position, 9471);
  motor4.write(goal_position, 6049);
  motor5.write(goal_position, 8354);
  motor6.write(goal_position, 9000);
  delay(3000);

  button();
  
  motor1.write(goal_position, 8192);
  motor2.write(goal_position, 9800);
  motor3.write(goal_position, 9471);
  motor4.write(goal_position, 6049);
  motor5.write(goal_position, 8354);
  motor6.write(goal_position, 5200);
  delay(1000);

  button();

  motor1.write(goal_position, 8192);
  motor2.write(goal_position, 8800);
  motor3.write(goal_position, 9471);
  motor4.write(goal_position, 6049);
  motor5.write(goal_position, 8354);
  motor6.write(goal_position, 5200);
  delay(1000);

  button();

  motor1.write(goal_position, 4188);
  motor2.write(goal_position, 8310);
  motor3.write(goal_position, 12466);
  motor4.write(goal_position, 8312);
  motor5.write(goal_position, 16113);
  motor6.write(goal_position, 5200);
  delay(1000);

  button();

  motor1.write(goal_position, 8192);
  motor2.write(goal_position, 8192);
  motor3.write(goal_position, 16383);
  motor4.write(goal_position, 8192);
  motor5.write(goal_position, 16383);
  motor6.write(goal_position, 5200);
  delay(1000);      

  button();  

  motor1.write(goal_position, 8192);
  motor2.write(goal_position, 6584);
  motor3.write(goal_position, 15104);
  motor4.write(goal_position, 10335);
  motor5.write(goal_position, 16221);
  motor6.write(goal_position, 5200);
  delay(3000);   

  button();

  motor1.write(goal_position, 8192);
  motor2.write(goal_position, 6584);
  motor3.write(goal_position, 15104);
  motor4.write(goal_position, 10335);
  motor5.write(goal_position, 16221);
  motor6.write(goal_position, 9000);
  delay(2000);   

  button();

  motor1.write(goal_position, 8192);
  motor2.write(goal_position, 7584);
  motor3.write(goal_position, 15104);
  motor4.write(goal_position, 10335);
  motor5.write(goal_position, 16221);
  motor6.write(goal_position, 9000);
  delay(1000);  

  button();

  motor1.write(goal_position, 4177);
  motor2.write(goal_position, 8310);
  motor3.write(goal_position, 12466);
  motor4.write(goal_position, 8312);
  motor5.write(goal_position, 16113);
  motor6.write(goal_position, 9000);
  delay(1000);  

  button();

}

void button() {
  mod.read(27, data);
  Serial.println(data);
  delay(100);
  if (data == 1) {
    speed = 0;
    motor1.write(moving_speed, speed);
    motor2.write(moving_speed, speed);
    motor3.write(moving_speed, speed);
    motor4.write(moving_speed, speed);
    motor5.write(moving_speed, speed); 
    motor6.write(moving_speed, speed); 
    while (data == 1) {
      mod.read(27, data);
      Serial.println(data);
      delay(500);
      if (data == 0) {
        speed = 50;
        motor1.write(moving_speed, speed);
        motor2.write(moving_speed, speed);
        motor3.write(moving_speed, speed);
        motor4.write(moving_speed, speed);
        motor5.write(moving_speed, speed); 
        motor6.write(moving_speed, speed); 
        break;
      }
    }
  }
}

