#include "DxlMaster2.h"  //указываем используемую библиотеку
const uint8_t id1 = 1;
const uint8_t id2 = 2;
const uint8_t id3 = 3;
const uint8_t id4 = 4;
const uint8_t COLOR_ID = 5;  //датчик цвета
const uint8_t RGB_ID = 21;   //rgb светодиод

const long unsigned int baudrate = 1000000;  // скорость обмена данными по последовательному порту манипулятора
int16_t speed = 100;                         //установка скорости вращения привода
int16_t operating_mode_reg = 11;             //режим работы
int16_t position_control_mode = 3;           //режим работы по положению
int16_t torque_reg = 64;                     //подача питания
int16_t moving_speed = 112;                  //скорость движения сервоприводов
int16_t goal_position = 116;                 //запись положения
// RGB данные
uint16_t R = 0;
uint16_t G = 0;
uint16_t B = 0;
//создание объектов класса сервопривода и датчиков
DynamixelMotor motor1(id1);
DynamixelMotor motor2(id2);
DynamixelMotor motor3(id3);
DynamixelMotor motor4(id4);
DynamixelDevice rgb(RGB_ID);
DynamixelDevice color_sensor(COLOR_ID);

DynamixelMotor motors[4] = { motor1, motor2, motor3, motor4 };//Объединяем для удобной работы

int positions[12][4] = {
  {8200, 8200, 8200, 8200},//базовое положение
  {11449, 4887, 6380, 8200},
  {11449, 4887, 4234, 8200},
  {11449, 4887, 4234, 4125},//установка следующих положений: первый кубик
  {11453, 4884, 4225, 8058},
  {7708, 8128, 8831, 7924},
  {7706, 8134, 8830, 4728},//второй кубик
  {7708, 8128, 8831, 7924},
  {9221, 3416, 7974, 8512},
  {9272, 3410, 7974, 4600},//третий кубик
  {9306, 3407, 7972, 8310},
  {12517, 3449, 8652, 8310},
};

void setup() {
  Serial.begin(57600);
  DxlMaster.begin(baudrate); 
  motor1.protocolVersion(1);
  motor2.protocolVersion(1);
  motor3.protocolVersion(1);
  motor4.protocolVersion(1);
  rgb.protocolVersion(1);
  color_sensor.protocolVersion(1);

  //поиск в шине и инициализация устройств
  motor1.init();
  motor2.init();
  motor3.init();
  motor4.init();
  rgb.init();
  color_sensor.init();
  delay(1000);

  for (uint8_t i = 0; i < 4; i++) {
    motors[i].write(operating_mode_reg, position_control_mode);  //Установка режима работы по положению
    motors[i].write(48, 16000);            //Установка максимального предела положения
    motors[i].write(52, 0);                //Установка минимального преледа положения
    motors[i].write(moving_speed, speed);  //Установка скорости работы сервопривода
    motors[i].write(torque_reg, 1);  //Включение момента на сервоприводе
  }
  delay(1000);
}
void loop() {
  for (int i = 0; i < 12; i++){//Цикл по строкам
    for (int j = 0; j < 4; j++){//Цикл по сервоприводам
      motors[j].write(goal_position, positions[i][j]);
    }
    delay(5000);
    color_sensor.write(42, 50);                                                                          //включение подсветки
    color_sensor.read(26, R);                                                                            //считывание с датчика цвета и запись в 26 регистр
    color_sensor.read(28, G);                                                                            //считывание с датчика цвета и запись в 28 регистр
    color_sensor.read(30, B);                                                                            //считывание с датчика цвета и запись в 230 регистр
    Serial.println("R: " + String(R / 257) + "   G: " + String(G / 257) + "    B: " + String(B / 257));  //вывод в монитор порта значений с датчика цвета
    rgb.write(26, G / 257);
    rgb.write(27, R / 257);
    rgb.write(28, B / 257);
    delay(1000);
  }
}
