#include "DxlMaster.h" // Добавление библиотеки
DynamixelDevice device(1); // Создание объекта управления с адресом id = 1
void setup() {
  DxlMaster.begin(1000000); // Инициализация шины со скоростью 1000000 бод
  device.init(); // Поиск в сети и инициализация устройства
  device.write(DYN_ADDRESS_ENABLE_TORQUE, 1);  // Включение момента
  uint16_t zero_limit = 0;
  device.write(DYN_ADDRESS_CW_LIMIT, zero_limit); // Очистка ограничения вращения по часовой стрелке
  device.write(DYN_ADDRESS_CCW_LIMIT, zero_limit); // Очистка ограничения вращения против часовой стрелки
}
void loop() {
  int16_t speed = 1000;
  device.write(DYN_ADDRESS_GOAL_SPEED, speed); // Установка скорости
}
