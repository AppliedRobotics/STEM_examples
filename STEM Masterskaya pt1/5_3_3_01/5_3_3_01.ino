#include <Dynamixel2Arduino.h> // подключение библиотеки Dynamixel

// Последовательный порт DXL для платы STEM с OpenCM 9.04. (Если использовать DXL порт 
// на самой плате OpenCM 9.04, то нужно использовать Serial1, и из-за кода в драйвере, 
// необходимо перед dxl.begin() вызвать Serial1.setDxlMode(true).)
#define DXL_SERIAL   Serial3
#define DEBUG_SERIAL Serial // последовательный порт, подключаемый к компьютеру

#define DEGREE_COEFF 16383/360 // 0...16383 = 0...360 градусов для сервоприводов

const uint8_t DXL_DIR_PIN = 22; // номер информационного пина сервоприводов (28 для OpenCM 9.04)
const float DXL_PROTOCOL_VERSION = 2.0; // протокол передачи данных от OpenCM9.04 к сервоприводам

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN); // инициализация указателя на команды из библиотеки Dynamixel

void setup() {  // функция, внутри которой команды выполняются единожды

  DEBUG_SERIAL.begin(57600); // установка скорости обмена данными по последовательному порту компьютера
  dxl.begin(1000000); // установка скорости обмена данными по последовательному порту манипулятора
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION); // выбор протокола обмена данными
  
  dxl.torqueOff(1); // отключаем крутящий момент, когда изменяем EEPROM область в сервоприводе
  dxl.torqueOff(2);
  dxl.torqueOff(3);
  dxl.torqueOff(4);
  dxl.torqueOff(5);
  dxl.setOperatingMode(1, OP_POSITION); // установка режима работы сервопривода с номером 1 в качестве шарнира
  dxl.setOperatingMode(2, OP_POSITION);
  dxl.setOperatingMode(3, OP_POSITION);
  dxl.setOperatingMode(4, OP_POSITION);
  dxl.setOperatingMode(5, OP_POSITION); // установка режима работы сервопривода с номером 5 в качестве шарнира
  dxl.torqueOn(1); // включаем крутящий момент сервопривода для удержания целевого положения
  dxl.torqueOn(2);
  dxl.torqueOn(3);
  dxl.torqueOn(4);
  dxl.torqueOn(5);
}

void loop() { // функция, внутри которой команды выполняются многократно

  dxl.setGoalVelocity(1, 50); // задание целевой скорости 50 сервоприводу с номером 1
  dxl.setGoalPosition(1, 30*DEGREE_COEFF); // задание целевого положения 30 градусов сервоприводу с номером 1

  dxl.setGoalVelocity(2, 50); // задание целевой скорости 50 сервоприводу с номером 2
  dxl.setGoalPosition(2, 95*DEGREE_COEFF); // задание целевого положения -5 градусов от 100 сервоприводу с номером 2

  dxl.setGoalVelocity(3, 50); // задание целевой скорости 50 сервоприводу с номером 3
  dxl.setGoalPosition(3, 250*DEGREE_COEFF); // задание целевого положения +10 градусов от 240 сервоприводу с номером 3

  dxl.setGoalVelocity(4, 50); // задание целевой скорости 50 сервоприводу с номером 4
  dxl.setGoalPosition(4, 30*DEGREE_COEFF); // задание целевого положения +30 градусов сервоприводу с номером 4

  dxl.setGoalVelocity(5, 50); // задание целевой скорости 50 сервоприводу с номером 5
  dxl.setGoalPosition(5, 242*DEGREE_COEFF); // задание целевого положения +10 градусов сервоприводу с номером 5

  delay(5000); // задержка в 5 секунд, ожидание, пока сервоприводы займут нужное положение
  dxl.setGoalVelocity(1, 50); // задание целевой скорости 50 сервоприводу с номером 1
  dxl.setGoalPosition(1, 0); // задание целевого положения 0 градусов сервоприводу с номером 1

  dxl.setGoalVelocity(2, 50);  // задание целевой скорости 50 сервоприводу с номером 2
  dxl.setGoalPosition(2, 100*DEGREE_COEFF); // задание целевого положения 100 градусов сервоприводу с номером 2

  dxl.setGoalVelocity(3, 50); // задание целевой скорости 50 сервоприводу с номером 3
  dxl.setGoalPosition(3, 240*DEGREE_COEFF); // задание целевого положения 240 градусов сервоприводу с номером 3

  dxl.setGoalVelocity(4, 50); // задание целевой скорости 50 сервоприводу с номером 4
  dxl.setGoalPosition(4, 0); // задание целевого положения 0 градусов сервоприводу с номером 4

  dxl.setGoalVelocity(5, 50); // задание целевой скорости 50 сервоприводу с номером 5
  dxl.setGoalPosition(5, 232*DEGREE_COEFF); // задание целевого положения 232 градусов сервоприводу с номером 5

  delay(5000); // задержка в 5 секунд, ожидание, пока сервоприводы займут нужное положение
}
