// Управление сервоприводами через Arduino Uno
#include <Dynamixel2Arduino.h>  // Подключение библиотеки DXL
#include "TrackingCamDxlUart.h" // Подключение библиотеки для камеры через DXL/UART

// Выставление скорости передачи данных, ID устройств
#define BAUDRATE  1000000
#define DXL_ID    1
#define DXL_ID2   2
#define CAM_ID    51

// Используем Dynamixel Shield:
#include <SoftwareSerial.h>
SoftwareSerial soft_serial(7, 8); // DYNAMIXEL Shield UART RX/TX
#define DXL_SERIAL   Serial
#define DEBUG_SERIAL soft_serial
const int DXL_DIR_PIN = 2; // Номер информационного пина DYNAMIXEL Shield

const float DXL_PROTOCOL_VERSION = 1.0; // Протокол передачи данных от Arduino Uno к сервоприводам

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN); // Создаем объект DXL шины

// Включаем пространство имен для работы с таблицей управления сервоприводов
using namespace ControlTableItem;

int32_t pos_data = 0; // Текущее положение сервопривода
int step_angle = 2;   // Шаг передвижения для камеры

int degree_coeff = 16383/360; // Число условных единиц положения в 1 градусе

TrackingCamDxlUart camera;    // Создаем объект камеры

unsigned long previousMillis = 0;
int cx;
int cy;
int pos = 180*degree_coeff; // Начальное положение сервопривода посередине 0...360
int posY = 180*degree_coeff;

// Функция начальной установки
void setup()
{
  // Установка одинаковой скорости обмена данными с сервоприводами, камерой
  DEBUG_SERIAL.begin(BAUDRATE);
  dxl.begin(BAUDRATE);
  camera.init(51, 1, BAUDRATE, 30);
  
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION); // Установка протокола обмена данными
  while (dxl.ping(DXL_ID) != true)
  {}
  while (dxl.ping(DXL_ID2) != true)
  {}
  // Установка режима работы сервоприводов в качестве шарниров
  dxl.setOperatingMode(DXL_ID, OP_POSITION);
  dxl.setOperatingMode(DXL_ID2, OP_POSITION);

  // Ограничиваем скорость сервоприводов в режиме шарнира
  dxl.writeControlTableItem(PROFILE_VELOCITY, DXL_ID, 30);
  dxl.writeControlTableItem(PROFILE_VELOCITY, DXL_ID2, 30);

  dxl.torqueOn(DXL_ID);  // Включаем момент
  dxl.torqueOn(DXL_ID2);
  // Устанавливаем сервоприводы в стартовые позиции
  dxl.setGoalPosition(DXL_ID, pos);
  dxl.setGoalPosition(DXL_ID2, posY);

  delay(5000);
}

// Функция бесконечного цикла
void loop()
{
  // Вывод положений сервоприводов в консоль
  for (int i=1; i<=2; i++)
  {
    pos_data = dxl.getPresentPosition(i);
    DEBUG_SERIAL.print("pos " + String(i) + " = " + String(pos_data/degree_coeff) + "; ");
    DEBUG_SERIAL.println();
  }
  
  int max_n = 5; // ограничиваем число объектов для камеры
  uint8_t n = camera.readBlobs(max_n); // считываем данные первых max_n объектов
  
  // Вывод данных камеры в консоль
  DEBUG_SERIAL.println("n = " + String(n));
  for (int i = 0; i < n; i++)
    DEBUG_SERIAL.println( String(camera.blob[i].type) + " " + String(camera.blob[i].cx) + " " +
                          String(camera.blob[i].cy) + " " + String(camera.blob[i].area) + " " +
                          String(camera.blob[i].left) + " " + String(camera.blob[i].right) + " " +
                          String(camera.blob[i].top) + " " + String(camera.blob[i].bottom) + "\n");

  // Блок работы сервоприводов
  if (n > 0) { // Если камера видит объекты

    cx = camera.blob[0].cx;
    cy = camera.blob[0].cy;
  
    if (cy < 110)// Мин значение координаты У камеры для начала движения
    {
      dxl.setGoalPosition(DXL_ID2, posY); // Команда для движения вала сервопривода ID2 в координату posY
      posY = posY - step_angle*degree_coeff; // Изменение координаты смещения вала привода
    }    
    else if (cy > 160)// Макс значание координаты У камеры для начала движения
    {
      dxl.setGoalPosition(DXL_ID2, posY);
      posY = posY + step_angle*degree_coeff;
    }
    posY = constrain(posY, 90*degree_coeff, 270*degree_coeff); // Ограничиваем углы поворота
  
    if (cx < 140)// Мин значание координаты Х камеры для начала движения
    {
      dxl.setGoalPosition(DXL_ID, pos); // Команда для движения вала сервопривода ID1 в координату pos
      pos = pos + step_angle*degree_coeff;
    }    
    else if (cx > 170)// Макс значание координаты Х камеры для начала движения
    {
      dxl.setGoalPosition(DXL_ID, pos);
      pos = pos - step_angle*degree_coeff;
    }  
    pos = constrain(pos, 90*degree_coeff, 270*degree_coeff); // Ограничиваем углы поворота

    // Ждем следующего фрейма
    while (millis() - previousMillis < 33)
    {};
    previousMillis = millis();
  }
}
