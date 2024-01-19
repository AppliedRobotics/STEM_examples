#include <Dynamixel2Arduino.h>  // подключение библиотеки Dynamixel

// Последовательный порт DXL для платы STEM с OpenCM 9.04. (Если использовать DXL порт 
// на самой плате OpenCM 9.04, то нужно использовать Serial1, и из-за кода в драйвере, необходимо перед dxl.begin() вызвать Serial1.setDxlMode(true).)
#define DXL_SERIAL   Serial3
#define DEBUG_SERIAL Serial // последовательный порт, подключаемый к компьютеру

#define DEGREE_COEFF 16383/360 // 0...16383 = 0...360 градусов для сервоприводов

const uint8_t DXL_DIR_PIN = 22; // номер информационного пина сервоприводов (28 для OpenCM 9.04)
const float DXL_PROTOCOL_VERSION = 2.0; // протокол передачи данных от OpenCM9.04 к сервоприводам

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN); // инициализация указателя на команды из библиотеки Dynamixel

#define jointN 5 // инициализация константы, обозначающей количество сервоприводов (и, соответственно, элементов массива)
int pos = 0; // инициализация переменной для положения сервопривода
int i = 0; // инициализация переменной счетчика циклов
int buf[jointN+1]; // инициализация одномерного массива, размер его задается 5+1=6, так как в программировании нумерация элементов начинается с 0, но нулевой элемент мы использовать не будем, так как начнем с первого

void setup() {  // функция, внутри которой команды выполняются единожды

  DEBUG_SERIAL.begin(57600); // установка скорости обмена данными по последовательному порту компьютера
  dxl.begin(1000000); // установка скорости обмена данными по последовательному порту манипулятора
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);  // выбор протокола обмена данными
  
  for (i=1; i<=jointN; i++) {   // цикл с изменением счетчика цикла i от 1 до 5 с шагом 1 (для перебора всех 5 сервоприводов)
    dxl.torqueOff(i); // отключаем крутящий момент, когда изменяем EEPROM область в сервоприводе
    dxl.setOperatingMode(i, OP_POSITION); // установка режима работы сервопривода с номером i в качестве шарнира
    dxl.torqueOn(i); // включаем крутящий момент сервопривода для удержания целевого положения
  }
}

void loop() { // функция, внутри которой команды выполняются многократно

  for (i=1; i<=jointN; i++) {
    pos = dxl.getPresentPosition(i);  // получение текущей позиции сервопривода с номером i и запись в переменную pos
    buf[i] = pos;  // запись переменной значения pos в i-тый элемент массива buf
  }

  for (i=1; i<=jointN; i++) {
    dxl.setGoalVelocity(i, 50); // задание целевой скорости 50 сервоприводу с номером i
    dxl.setGoalPosition(i, buf[i]-20*DEGREE_COEFF); // задание целевого положения -20 градусов от текущего сервоприводу с номером i
  }
  delay(5000); // задержка в 5 секунд, ожидание, пока сервоприводы займут нужное положение


  for (i=1; i<=jointN; i++) {
    dxl.setGoalVelocity(i, 50); // задание целевой скорости 50 сервоприводу с номером i
    dxl.setGoalPosition(i, buf[i]); // задание начального целевого положения, т.е. +20 градусов от последнего сервоприводу с номером i
  }
  delay(5000); // задержка в 5 секунд, ожидание, пока сервоприводы займут нужное положение
  
}
