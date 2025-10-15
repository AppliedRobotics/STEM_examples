#include "DxlMaster.h"

const uint8_t id1 = 1;
const uint8_t id2 = 2;
const uint8_t id3 = 3;
const uint8_t id4 = 4;
const uint8_t id5 = 5;
const uint8_t id6 = 6;
const uint8_t id = 21;
const long unsigned int baudrate = 1000000;

int16_t speed = 70;
int16_t goal_position = 30;

String error = "0";
bool flag = false;
bool flag2 = false;

DynamixelMotor motor1(id1);
DynamixelMotor motor2(id2);
DynamixelMotor motor3(id3);
DynamixelMotor motor4(id4);
DynamixelMotor motor5(id5);
DynamixelMotor motor6(id6);
DynamixelDevice rgb(id);

void setup() {
  Serial.begin(57600);

  DxlMaster.begin(baudrate);
  motor1.init();
  motor2.init();
  motor3.init();
  motor4.init();
  motor5.init();
  motor6.init();
  delay(100);
  rgb.init();  

  motor1.enableTorque();
  motor2.enableTorque();
  motor3.enableTorque();  
  motor4.enableTorque();
  motor5.enableTorque();  
  motor6.enableTorque();  

  motor1.jointMode(3, 1020);
  motor1.speed(speed);
  motor2.jointMode(3, 1020);
  motor2.speed(speed);
  motor3.jointMode(3, 1020);
  motor3.speed(speed);
  motor4.jointMode(3, 1020);
  motor4.speed(speed);    
  motor5.jointMode(3, 1020);
  motor5.speed(speed);  
  motor6.jointMode(3, 1020);
  motor6.speed(speed);  
  delay(500);

  Serial.println("Установка начального положения");
  motor1.write(goal_position, 501);
  motor2.write(goal_position, 462);
  motor3.write(goal_position, 468);
  motor4.write(goal_position, 749);
  motor5.write(goal_position, 511);
  motor6.write(goal_position, 511);
  delay(3000);
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
    rgb.write(26, 50);
    rgb.write(27, 200); 
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
    rgb.write(28, 200);
    error = "0";

    motor1.speed(speed);
    motor2.speed(speed);
    motor3.speed(speed);
    motor4.speed(speed);
    motor5.speed(speed);
    motor6.speed(speed);

    Serial.println("Переход в ручной режим");
    Serial.println("Возвращение в начальное положение");
    delay(3000);

    motor1.write(goal_position, 501);
    motor2.write(goal_position, 462);
    motor3.write(goal_position, 468);
    motor4.write(goal_position, 749);
    motor5.write(goal_position, 511);
    motor6.write(goal_position, 511);
    delay(3000);
  }
}

void firstMove() 
{
// наклон вперед
  motor1.write(goal_position, 501);
  motor2.write(goal_position, 420);
  motor3.write(goal_position, 549);
  motor4.write(goal_position, 706);
  motor5.write(goal_position, 511);
  motor6.write(goal_position, 511);
  delay(2000);
// сжатие
  motor1.write(goal_position, 501);
  motor2.write(goal_position, 420);
  motor3.write(goal_position, 549);
  motor4.write(goal_position, 706);
  motor5.write(goal_position, 511);
  motor6.write(goal_position, 680);
  delay(2000);
// движение назад
  motor1.write(goal_position, 501);
  motor2.write(goal_position, 452);
  motor3.write(goal_position, 468);
  motor4.write(goal_position, 749);
  motor5.write(goal_position, 511);
  motor6.write(goal_position, 680);
  delay(2000);
// поворот
  motor1.write(goal_position, 162);
  motor2.write(goal_position, 452);
  motor3.write(goal_position, 468);
  motor4.write(goal_position, 749);
  motor5.write(goal_position, 511);
  motor6.write(goal_position, 680);
  delay(3000);
// наклон вперед
  motor1.write(goal_position, 162);
  motor2.write(goal_position, 420);
  motor3.write(goal_position, 549);
  motor4.write(goal_position, 706);
  motor5.write(goal_position, 511);
  motor6.write(goal_position, 680);
  delay(2000);
// расжатие
  motor1.write(goal_position, 162);
  motor2.write(goal_position, 420);
  motor3.write(goal_position, 549);
  motor4.write(goal_position, 706);
  motor5.write(goal_position, 511);
  motor6.write(goal_position, 511);
  delay(2000);
// движение назад
  motor1.write(goal_position, 162);
  motor2.write(goal_position, 452);
  motor3.write(goal_position, 468);
  motor4.write(goal_position, 749);
  motor5.write(goal_position, 511);
  motor6.write(goal_position, 511);
  delay(2000);
}

void secondMove()
{
// возвращение в начальную позицию
  motor1.write(goal_position, 501);
  motor2.write(goal_position, 452);
  motor3.write(goal_position, 468);
  motor4.write(goal_position, 749);
  motor5.write(goal_position, 511);
  motor6.write(goal_position, 511);
  delay(4000);
// опять поворот за кубиком
  motor1.write(goal_position, 162);
  motor2.write(goal_position, 452);
  motor3.write(goal_position, 468);
  motor4.write(goal_position, 749);
  motor5.write(goal_position, 511);
  motor6.write(goal_position, 511);
  delay(3000);
// наклон
  motor1.write(goal_position, 162);
  motor2.write(goal_position, 420);
  motor3.write(goal_position, 549);
  motor4.write(goal_position, 706);
  motor5.write(goal_position, 511);
  motor6.write(goal_position, 511);
  delay(2000);
// сжатие
  motor1.write(goal_position, 162);
  motor2.write(goal_position, 420);
  motor3.write(goal_position, 549);
  motor4.write(goal_position, 706);
  motor5.write(goal_position, 511);
  motor6.write(goal_position, 700);
  delay(2000);
// движение назад
  motor1.write(goal_position, 162);
  motor2.write(goal_position, 452);
  motor3.write(goal_position, 468);
  motor4.write(goal_position, 749);
  motor5.write(goal_position, 511);
  motor6.write(goal_position, 700);
  delay(2000);
// поворот 
  motor1.write(goal_position, 400);
  motor2.write(goal_position, 452);
  motor3.write(goal_position, 468);
  motor4.write(goal_position, 749);
  motor5.write(goal_position, 511);
  motor6.write(goal_position, 700);
  delay(2000);

  rgb.write(26, 0);
  rgb.write(27, 200);
  motor1.speed(120);
  motor2.speed(120);
  motor3.speed(120);
  motor4.speed(120);
  motor5.speed(120);
  motor6.speed(120); 

  motor1.write(goal_position, 400);
  motor2.write(goal_position, 430);
  motor3.write(goal_position, 128);
  motor4.write(goal_position, 749);
  motor5.write(goal_position, 511);
  motor6.write(goal_position, 700);
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
    motor1.speed(speed);
    motor2.speed(speed);
    motor3.speed(speed);
    motor4.speed(speed);
    motor5.speed(speed);
    motor6.speed(speed); 
    delay(3000);
    
    motor1.write(goal_position, 501);
    motor2.write(goal_position, 452);
    motor3.write(goal_position, 468);
    motor4.write(goal_position, 749);
    motor5.write(goal_position, 511);
    motor6.write(goal_position, 511);
    delay(3000);
  }
}

void crazy() {
  while (flag != true) {
  motor1.write(goal_position, 487);
  motor2.write(goal_position, 556);
  motor3.write(goal_position, 300);
  motor4.write(goal_position, 749);
  motor5.write(goal_position, 511);
  motor6.write(goal_position, 300);
  delay(1000);
  stop_crazy();
  if (flag == true)
    break;

  motor1.write(goal_position, 487);
  motor2.write(goal_position, 556);
  motor3.write(goal_position, 387);
  motor4.write(goal_position, 749);
  motor5.write(goal_position, 375);
  motor6.write(goal_position, 200);
  delay(1000);
  stop_crazy();
  if (flag == true)
    break;

  motor1.speed(150);
  motor2.speed(150);
  motor3.speed(150);
  motor4.speed(150);
  motor5.speed(150);
  motor6.speed(150); 
  stop_crazy();
  if (flag == true)
    break;

  motor1.write(goal_position, 687);
  motor2.write(goal_position, 431);
  motor3.write(goal_position, 287);
  motor4.write(goal_position, 749);
  motor5.write(goal_position, 749);
  motor6.write(goal_position, 511);
  delay(1000);
  stop_crazy();
  if (flag == true)
    break;

  motor1.write(goal_position, 562);
  motor2.write(goal_position, 431);
  motor3.write(goal_position, 387);
  motor4.write(goal_position, 562);
  motor5.write(goal_position, 511);
  motor6.write(goal_position, 600);
  delay(1000);
  stop_crazy();
  if (flag == true)
    break;

  motor1.speed(120);
  motor2.speed(120);
  motor3.speed(120);
  motor4.speed(120);
  motor5.speed(120);
  motor6.speed(120); 
  stop_crazy();
  if (flag == true)
    break;

  motor1.write(goal_position, 624);
  motor2.write(goal_position, 431);
  motor3.write(goal_position, 387);
  motor4.write(goal_position, 749);
  motor5.write(goal_position, 375);
  motor6.write(goal_position, 600);
  delay(1000);
  stop_crazy();
  if (flag == true)
    break;

  motor1.write(goal_position, 712);
  motor2.write(goal_position, 431);
  motor3.write(goal_position, 287);
  motor4.write(goal_position, 562);
  motor5.write(goal_position, 749);
  motor6.write(goal_position, 511);
  delay(1000);
  stop_crazy();
  if (flag == true)
    break;
  }
}

void ERR() {
  Serial.println("ERROR");
  Serial.println("Чтобы перейти в ручной режим, введите команду manual");
  while (Serial.available() == 0) {}
  error = Serial.readString();
  error.trim();
  Serial.println(error);
}

