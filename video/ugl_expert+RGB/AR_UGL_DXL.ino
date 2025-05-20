#include "DxlMaster.h"

const uint8_t id1 = 1;
const uint8_t id2 = 2;
const uint8_t id3 = 3;
const uint8_t id4 = 4;
const uint8_t id5 = 5;
const uint8_t id6 = 6;

const uint8_t id = 21;
const long unsigned int baudrate = 1000000;

int16_t speed = 100;
int16_t operating_mode_reg = 11;
int16_t position_control_mode = 3;
int16_t torque_reg = 64;
int16_t moving_speed = 112;
int16_t goal_position = 116;

String error = "0";
bool flag = false;
bool flag2 = false;

DynamixelDevice motor1(id1);
DynamixelDevice motor2(id2);
DynamixelDevice motor3(id3);
DynamixelDevice motor4(id4);
DynamixelDevice motor5(id5);
DynamixelDevice motor6(id6);

DynamixelDevice rgb(id);

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
  rgb.init();  

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

  delay(1000);

  Serial.println("Установка начального положения");
  motor1.write(goal_position, 8192);
  motor2.write(goal_position, 7400);
  motor3.write(goal_position, 7500);
  motor4.write(goal_position, 12000);
  motor5.write(goal_position, 8192);
  motor6.write(goal_position, 8192);
  delay(4000);
}

void loop() {
  rgb.write(28, 0);
  rgb.write(26, 200);
  Serial.println("Манипулятор готов к работе. Для начала работы введите команду start");

  while (Serial.available() == 0) {}
  String mode = Serial.readString();
  mode.trim();
  Serial.println(mode);
  error = "0";

  if (mode == "start") {

    rgb.write(26, 100);
    rgb.write(27, 200);
    delay(100);
    firstMove();
    secondMove();
    Serial.println("ERROR");
    Serial.println("Введите что-нибудь");
    flag = false;
    flag2 = false;
    while (flag2 == false)
      crazy();
  } 

  else {
    rgb.write(26, 0);
    rgb.write(27, 200);
    while (error != "manual")
    ERR();
    rgb.write(27, 0);
    error = "0";

    rgb.write(28, 200);

  Serial.println("Переход в ручной режим");
  Serial.println("Возвращение в начальное положение");
  delay(5000);

  motor1.write(goal_position, 8192);
  motor2.write(goal_position, 7400);
  motor3.write(goal_position, 7500);
  motor4.write(goal_position, 12000);
  motor5.write(goal_position, 8192);
  motor6.write(goal_position, 8192);
  delay(3000);
  }
}

void firstMove() 
{
// наклон вперед
  motor1.write(goal_position, 8192);
  motor2.write(goal_position, 7020);
  motor3.write(goal_position, 8800);
  motor4.write(goal_position, 11300);
  motor5.write(goal_position, 8192);
  motor6.write(goal_position, 8192);
  delay(2000);
// сжатие
  motor1.write(goal_position, 8192);
  motor2.write(goal_position, 7020);
  motor3.write(goal_position, 8800);
  motor4.write(goal_position, 11300);
  motor5.write(goal_position, 8192);
  motor6.write(goal_position, 6000);
  delay(2000);
// движение назад
  motor1.write(goal_position, 8192);
  motor2.write(goal_position, 7400);
  motor3.write(goal_position, 7500);
  motor4.write(goal_position, 12000);
  motor5.write(goal_position, 8192);
  motor6.write(goal_position, 6000);
  delay(2000);
// поворот
  motor1.write(goal_position, 4200);
  motor2.write(goal_position, 7400);
  motor3.write(goal_position, 7500);
  motor4.write(goal_position, 12000);
  motor5.write(goal_position, 8192);
  motor6.write(goal_position, 6000);
  delay(3000);
// наклон вперед
  motor1.write(goal_position, 4200);
  motor2.write(goal_position, 7020);
  motor3.write(goal_position, 8800);
  motor4.write(goal_position, 11300);
  motor5.write(goal_position, 8192);
  motor6.write(goal_position, 6000);
  delay(2000);
// расжатие
  motor1.write(goal_position, 4200);
  motor2.write(goal_position, 7020);
  motor3.write(goal_position, 8800);
  motor4.write(goal_position, 11300);
  motor5.write(goal_position, 8192);
  motor6.write(goal_position, 8192);
  delay(2000);
// движение назад
  motor1.write(goal_position, 4200);
  motor2.write(goal_position, 7400);
  motor3.write(goal_position, 7500);
  motor4.write(goal_position, 12000);
  motor5.write(goal_position, 8192);
  motor6.write(goal_position, 8192);
  delay(2000);
}

void secondMove()
{
// возвращение в начальную позицию
  motor1.write(goal_position, 8192);
  motor2.write(goal_position, 7400);
  motor3.write(goal_position, 7500);
  motor4.write(goal_position, 12000);
  motor5.write(goal_position, 8192);
  motor6.write(goal_position, 8192);
  delay(3000);
// опять поворот за кубиком
  motor1.write(goal_position, 4200);
  motor2.write(goal_position, 7400);
  motor3.write(goal_position, 7500);
  motor4.write(goal_position, 12000);
  motor5.write(goal_position, 8192);
  motor6.write(goal_position, 8192);
  delay(3000);
// наклон
  motor1.write(goal_position, 4200);
  motor2.write(goal_position, 7020);
  motor3.write(goal_position, 8800);
  motor4.write(goal_position, 11300);
  motor5.write(goal_position, 8192);
  motor6.write(goal_position, 8192);
  delay(2000);
// сжатие
  motor1.write(goal_position, 4200);
  motor2.write(goal_position, 7020);
  motor3.write(goal_position, 8800);
  motor4.write(goal_position, 11300);
  motor5.write(goal_position, 8192);
  motor6.write(goal_position, 6000);
  delay(2000);

// движение назад
  motor1.write(goal_position, 4200);
  motor2.write(goal_position, 7400);
  motor3.write(goal_position, 7500);
  motor4.write(goal_position, 12000);
  motor5.write(goal_position, 8192);
  motor6.write(goal_position, 6000);
  delay(2000);

// поворот 
  motor1.write(goal_position, 6400);
  motor2.write(goal_position, 7400);
  motor3.write(goal_position, 7500);
  motor4.write(goal_position, 12000);
  motor5.write(goal_position, 8192);
  motor6.write(goal_position, 6000);
  delay(2000);

  rgb.write(26, 0);
  rgb.write(27, 200);
  speed = 200;

  motor1.write(moving_speed, speed);
  motor2.write(moving_speed, speed);
  motor3.write(moving_speed, speed);
  motor4.write(moving_speed, speed);
  motor5.write(moving_speed, speed); 
  motor6.write(moving_speed, speed); 

  motor1.write(goal_position, 6400);
  motor2.write(goal_position, 7020);
  motor3.write(goal_position, 1000);
  motor4.write(goal_position, 12000);
  motor5.write(goal_position, 8192);
  motor6.write(goal_position, 6000);
  delay(1000);

}

void stop_crazy(){

    if(Serial.available()){
        error = Serial.readString();
        Serial.println(error);
        flag = !flag;
        flag2 = !flag2;
        rgb.write(27, 0);
        rgb.write(28, 200);

        Serial.println("Переход в ручной режим");
        Serial.println("Возвращение в начальное положение");
        speed = 100;

        motor1.write(moving_speed, speed);
        motor2.write(moving_speed, speed);
        motor3.write(moving_speed, speed);
        motor4.write(moving_speed, speed);
        motor5.write(moving_speed, speed); 
        motor6.write(moving_speed, speed);
        delay(3000);
        
        motor1.write(goal_position, 8192);
        motor2.write(goal_position, 7400);
        motor3.write(goal_position, 7500);
        motor4.write(goal_position, 12000);
        motor5.write(goal_position, 8192);
        motor6.write(goal_position, 8192);
        delay(3000);
    }
}

void crazy() {
  while (flag != true) {
  motor1.write(goal_position, 7800);
  motor2.write(goal_position, 8900);
  motor3.write(goal_position, 2600);
  motor4.write(goal_position, 12000);
  motor5.write(goal_position, 8192);
  motor6.write(goal_position, 6000);
  delay(1000);
  stop_crazy();
  if (flag == true)
    break;

  motor1.write(goal_position, 7800);
  motor2.write(goal_position, 8900);
  motor3.write(goal_position, 4600);
  motor4.write(goal_position, 12000);
  motor5.write(goal_position, 6000);
  motor6.write(goal_position, 6000);
  delay(1000);
    stop_crazy();
  if (flag == true)
    break;

  speed = 230;

  motor1.write(moving_speed, speed);
  motor2.write(moving_speed, speed);
  motor3.write(moving_speed, speed);
  motor4.write(moving_speed, speed);
  motor5.write(moving_speed, speed); 
  motor6.write(moving_speed, speed);

    stop_crazy();
  if (flag == true)
    break;

  motor1.write(goal_position, 11000);
  motor2.write(goal_position, 6900);
  motor3.write(goal_position, 4600);
  motor4.write(goal_position, 12000);
  motor5.write(goal_position, 12000);
  motor6.write(goal_position, 8192);
  delay(1000);

    stop_crazy();
  if (flag == true)
    break;

  motor1.write(goal_position, 9000);
  motor2.write(goal_position, 6900);
  motor3.write(goal_position, 4600);
  motor4.write(goal_position, 9000);
  motor5.write(goal_position, 8192);
  motor6.write(goal_position, 6000);
  delay(1000);

    stop_crazy();
  if (flag == true)
    break;

  speed = 250;

  motor1.write(moving_speed, speed);
  motor2.write(moving_speed, speed);
  motor3.write(moving_speed, speed);
  motor4.write(moving_speed, speed);
  motor5.write(moving_speed, speed); 
  motor6.write(moving_speed, speed);

    stop_crazy();
  if (flag == true)
    break;

  motor1.write(goal_position, 10000);
  motor2.write(goal_position, 6900);
  motor3.write(goal_position, 4600);
  motor4.write(goal_position, 12000);
  motor5.write(goal_position, 6000);
  motor6.write(goal_position, 6000);
  delay(1000);

    stop_crazy();
  if (flag == true)
    break;

  motor1.write(goal_position, 13000);
  motor2.write(goal_position, 6900);
  motor3.write(goal_position, 4600);
  motor4.write(goal_position, 9000);
  motor5.write(goal_position, 12000);
  motor6.write(goal_position, 8192);
  delay(1000);

    stop_crazy();
  if (flag == true)
    break;
  }
}

void ERR() 
{
  Serial.println("ERROR");
  Serial.println("Чтобы перейти в ручной режим, введите команду manual");
  while (Serial.available() == 0) {}
  error = Serial.readString();
  error.trim();
  Serial.println(error);
}
