#include "DxlMaster.h" // Добавление библиотеки
DynamixelMotor motor(1); // Создание объекта класса сервопривода с адресом 1
void setup() { 
  DxlMaster.begin(1000000); // Инициализация шины Dynamixel со скоростью 1000000 бод
  motor.enableTorque(); // Включение момента привода
  motor.jointMode(2000, 14000); // Включение режима сочленения с угловыми ограничениями
  motor.speed(100); // Задание максимальной скорости вращения привода
}
void loop() {
  motor.goalPosition(123); // Задание положения привода
}
