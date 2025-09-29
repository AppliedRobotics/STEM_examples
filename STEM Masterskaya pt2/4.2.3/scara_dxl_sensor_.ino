#include "DxlMaster.h"

const uint8_t id1 = 1;
const uint8_t id2 = 2;
const uint8_t id3 = 3;
const uint8_t id4 = 4;
const uint8_t id = 5; // датчик цвета

const int baudrate = 1000000; // скорость обмена данными по последовательному порту манипулятора и датчика

int16_t speed = 80;         // скоростm вращения привода
int16_t goal_position = 30; // регистр записи положения
// создаем переменные для хранения RGB данные
uint16_t R = 0;
uint16_t G = 0;
uint16_t B = 0;
// создание экземпляров класса сервопривода и датчика
DynamixelMotor motor1(id1);
DynamixelMotor motor2(id2);
DynamixelMotor motor3(id3);
DynamixelMotor motor4(id4);
DynamixelDevice color_sensor(id);

void setup()
{
  DxlMaster.begin(baudrate);
  Serial.begin(57600);

  delay(100);
  // поиск в шине и инициализация устройств
  uint8_t status1 = motor1.init();
  uint8_t status2 = motor2.init();
  uint8_t status3 = motor3.init();
  uint8_t status4 = motor4.init();
  color_sensor.init();

  delay(3000);
  motor1.enableTorque(); // подача момента на сервоприводы
  motor2.enableTorque();
  motor3.enableTorque();
  motor4.enableTorque();

  motor1.jointMode(3, 1023); // режим работы по положению
  motor2.jointMode(3, 1023);
  motor3.jointMode(3, 1023);
  motor4.jointMode(3, 1023);

  motor1.speed(speed);
  motor2.speed(speed);
  motor3.speed(speed);
  motor4.speed(speed);
  delay(4000);
}
void loop()
{
  // базовое положение
  motor1.write(goal_position, 524);
  motor2.write(goal_position, 807);
  motor3.write(goal_position, 556);
  motor4.write(goal_position, 484);
  delay(4000);
  // красный
  motor1.write(goal_position, 502);
  motor2.write(goal_position, 816);
  motor3.write(goal_position, 532);
  motor4.write(goal_position, 193);
  delay(4000);
  color_sensor.write(42, 50); // задаем уровень освещенности у светодиода
  color_sensor.read(26, R);// считывание с датчика цвета и запись в переменную R
  color_sensor.read(28, G);// считывание с датчика цвета и запись в переменную G
  color_sensor.read(30, B);// считывание с датчика цвета и запись в переменную B
  Serial.println("R: " + String(R / 257) + "   G: " + String(G / 257) + "    B: " + String(B / 257)); // вывод в монитор порта значений с датчика цвета
  delay(1000);
  motor4.write(goal_position, 480); // поднимаем датчик
  delay(2000);
  // оранжевый
  motor1.write(goal_position, 476);
  motor2.write(goal_position, 762);
  motor3.write(goal_position, 528);
  motor4.write(goal_position, 258);
  delay(4000);
  color_sensor.read(26, R);
  color_sensor.read(28, G);
  color_sensor.read(30, B);
  Serial.println("R: " + String(R / 257) + "   G: " + String(G / 257) + "    B: " + String(B / 257)); // вывод в монитор порта значений с датчика цвета
  motor4.write(goal_position, 480); // поднимаем датчик
  delay(2000);
  // желтый
  motor1.write(goal_position, 557);
  motor2.write(goal_position, 547);
  motor3.write(goal_position, 551);
  motor4.write(goal_position, 225);
  delay(4000);
  color_sensor.read(26, R);
  color_sensor.read(28, G);
  color_sensor.read(30, B);
  Serial.println("R: " + String(R / 257) + "   G: " + String(G / 257) + "    B: " + String(B / 257)); // вывод в монитор порта значений с датчика цвета
  motor4.write(goal_position, 480); // поднимаем датчик
  delay(2000);
  // зеленый
  motor1.write(goal_position, 522);
  motor2.write(goal_position, 528);
  motor3.write(goal_position, 561);
  motor4.write(goal_position, 240);
  delay(4000);
  color_sensor.read(26, R);
  color_sensor.read(28, G);
  color_sensor.read(30, B);
  Serial.println("R: " + String(R / 257) + "   G: " + String(G / 257) + "    B: " + String(B / 257)); // вывод в монитор порта значений с датчика цвета
  motor4.write(goal_position, 480); // поднимаем датчик
  delay(2000);
  // голубой
  motor1.write(goal_position, 514);
  motor2.write(goal_position, 486);
  motor3.write(goal_position, 464);
  motor4.write(goal_position, 240);
  delay(4000);
  color_sensor.read(26, R);
  color_sensor.read(28, G);
  color_sensor.read(30, B);
  Serial.println("R: " + String(R / 257) + "   G: " + String(G / 257) + "    B: " + String(B / 257)); // вывод в монитор порта значений с датчика цвета
  motor4.write(goal_position, 480); // поднимаем датчик
  delay(2000);
  // синий
  motor1.write(goal_position, 498);
  motor2.write(goal_position, 453);
  motor3.write(goal_position, 368);
  motor4.write(goal_position, 253);
  delay(4000);
  color_sensor.read(26, R);
  color_sensor.read(28, G);
  color_sensor.read(30, B);
  Serial.println("R: " + String(R / 257) + "   G: " + String(G / 257) + "    B: " + String(B / 257)); // вывод в монитор порта значений с датчика цвета
  motor4.write(goal_position, 480); // поднимаем датчик
  delay(2000);
  // розовый
  motor1.write(goal_position, 518);
  motor2.write(goal_position, 346);
  motor3.write(goal_position, 394);
  motor4.write(goal_position, 239);
  delay(4000);
  color_sensor.read(26, R);
  color_sensor.read(28, G);
  color_sensor.read(30, B);
  Serial.println("R: " + String(R / 257) + "   G: " + String(G / 257) + "    B: " + String(B / 257)); // вывод в монитор порта значений с датчика цвета
  motor4.write(goal_position, 480); // поднимаем датчик
  delay(2000);
  delay(2000); // поднимаем датчик
  // белый
  motor1.write(goal_position, 538);
  motor2.write(goal_position, 206);
  motor3.write(goal_position, 491);
  motor4.write(goal_position, 239);
  delay(4000);
  color_sensor.read(26, R);
  color_sensor.read(28, G);
  color_sensor.read(30, B);
  Serial.println("R: " + String(R / 257) + "   G: " + String(G / 257) + "    B: " + String(B / 257)); // вывод в монитор порта значений с датчика цвета
  motor4.write(goal_position, 480); // поднимаем датчик
  delay(2000);
  delay(2000);
}