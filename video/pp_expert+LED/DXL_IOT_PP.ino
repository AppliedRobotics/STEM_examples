#include "DxlMaster2.h"

const uint8_t id1 = 1;
const uint8_t id2 = 2;
const uint8_t id3 = 3;
const uint8_t id4 = 4;
const uint8_t id5 = 5;

const uint8_t id = 9;

int16_t speed = 80;
int16_t operating_mode_reg = 11;
int16_t position_control_mode = 3;
int16_t torque_reg = 64;
int16_t moving_speed = 112;
int16_t goal_position = 116;

const long unsigned int baudrate = 1000000;

DynamixelDevice motor1(id1);
DynamixelDevice motor2(id2);
DynamixelDevice motor3(id3);
DynamixelDevice motor4(id4);
DynamixelDevice motor5(id5);

DynamixelDevice led(id);

void setup() {
  DxlMaster.begin(baudrate);

  motor1.init();
  motor2.init();
  motor3.init();
  motor4.init();
  motor5.init();

  motor1.write(operating_mode_reg, position_control_mode);
  motor2.write(operating_mode_reg, position_control_mode);
  motor3.write(operating_mode_reg, position_control_mode);
  motor4.write(operating_mode_reg, position_control_mode);
  motor5.write(operating_mode_reg, position_control_mode);

  delay(100);
  led.init();  

  motor1.write(torque_reg, 1);
  motor2.write(torque_reg, 1);
  motor3.write(torque_reg, 1);  
  motor4.write(torque_reg, 1);
  motor5.write(torque_reg, 1);  

  motor1.write(moving_speed, speed);
  motor2.write(moving_speed, speed);
  motor3.write(moving_speed, speed);
  motor4.write(moving_speed, speed);
  motor5.write(moving_speed, speed); 
  delay(1000);
}

void loop() {
firstMove();
secondMove();
}

void firstMove() 
{
// движение в начальное положение
motor1.write(goal_position, 4152);
motor2.write(goal_position, 9365);
motor3.write(goal_position, 11670);
motor4.write(goal_position, 8201);
motor5.write(goal_position, 7862);
delay(4000);
// наклон вперед
motor1.write(goal_position, 4152);
motor2.write(goal_position, 9996);
motor3.write(goal_position, 11409);
motor4.write(goal_position, 8201);
motor5.write(goal_position, 7862);
delay(2000);
// сжатие
motor1.write(goal_position, 4152);
motor2.write(goal_position, 9996);
motor3.write(goal_position, 11409);
motor4.write(goal_position, 8201);
motor5.write(goal_position, 6061);
delay(3000);
// светодиод загорается
led.write(26, 200);
// движение назад
motor1.write(goal_position, 4152);
motor2.write(goal_position, 9365);
motor3.write(goal_position, 11670);
motor4.write(goal_position, 8201);
motor5.write(goal_position, 6061);
delay(2000);
// поворот
motor1.write(goal_position, 8304);
motor2.write(goal_position, 9365);
motor3.write(goal_position, 11670);
motor4.write(goal_position, 8201);
motor5.write(goal_position, 6061);
delay(4000);
// наклон вперед
motor1.write(goal_position, 8304);
motor2.write(goal_position, 9896);
motor3.write(goal_position, 11409);
motor4.write(goal_position, 8201);
motor5.write(goal_position, 6061);
delay(1000);
// расжатие
motor1.write(goal_position, 8304);
motor2.write(goal_position, 9896);
motor3.write(goal_position, 11409);
motor4.write(goal_position, 8201);
motor5.write(goal_position, 7862);
// светодиод гаснет
led.write(26, 0);
delay(1000);
// движение назад
motor1.write(goal_position, 8304);
motor2.write(goal_position, 9365);
motor3.write(goal_position, 11670);
motor4.write(goal_position, 8201);
motor5.write(goal_position, 7862);
delay(2000);
}

void secondMove()
{
// возвращение в начальную позицию
motor1.write(goal_position, 4152);
motor2.write(goal_position, 9365);
motor3.write(goal_position, 11670);
motor4.write(goal_position, 8201);
motor5.write(goal_position, 7862);
delay(4000);
// опять поворот за кубиком
motor1.write(goal_position, 8304);
motor2.write(goal_position, 9365);
motor3.write(goal_position, 11670);
motor4.write(goal_position, 8201);
motor5.write(goal_position, 7862);
delay(4000);
// наклон
motor1.write(goal_position, 8304);
motor2.write(goal_position, 9896);
motor3.write(goal_position, 11409);
motor4.write(goal_position, 8201);
motor5.write(goal_position, 7862);
delay(1000);
// сжатие
motor1.write(goal_position, 8304);
motor2.write(goal_position, 9896);
motor3.write(goal_position, 11409);
motor4.write(goal_position, 8201);
motor5.write(goal_position, 6061);
delay(3000);

// светодиод загорается
led.write(26, 200);
// движение назад
motor1.write(goal_position, 8304);
motor2.write(goal_position, 9365);
motor3.write(goal_position, 11670);
motor4.write(goal_position, 8201);
motor5.write(goal_position, 6061);
delay(2000);

// поворот 
motor1.write(goal_position, 4152);
motor2.write(goal_position, 9365);
motor3.write(goal_position, 11670);
motor4.write(goal_position, 8201);
motor5.write(goal_position, 6061);
delay(4000);
// наклон вперед
motor1.write(goal_position, 4152);
motor2.write(goal_position, 9996);
motor3.write(goal_position, 11409);
motor4.write(goal_position, 8201);
motor5.write(goal_position, 6061);
delay(1000);
// расжатие
motor1.write(goal_position, 4152);
motor2.write(goal_position, 9996);
motor3.write(goal_position, 11409);
motor4.write(goal_position, 8201);
motor5.write(goal_position, 7862);
// светодиод гаснет
led.write(26, 0);
delay(3000);

// движение назад
motor1.write(goal_position, 4152);
motor2.write(goal_position, 9365);
motor3.write(goal_position, 11670);
motor4.write(goal_position, 8201);
motor5.write(goal_position, 7862);
delay(2000);
// поворот 
motor1.write(goal_position, 8304);
motor2.write(goal_position, 9365);
motor3.write(goal_position, 11670);
motor4.write(goal_position, 8201);
motor5.write(goal_position, 7862);
delay(4000);
}
