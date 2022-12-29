// Подключение библиотеки
#include <DynamixelSDK.h>

//Версия протокола DXL
#define PROTOCOL_VERSION                1.0                 

//Базовые настройки
#define DXL_TMP                           22    //     ID датчика температуры
#define BAUDRATE                          57600 //     Скорость обмена данными по шине DXL
#define DEVICENAME                        "3"   //     Адрес порта DXL


//Создание и инициализация переменных для хранения состояния
uint8_t _data1 = 0; // Целое часть значения параметра влажности 
uint8_t _data2 = 0; // Десятичная часть значения параметра влажности 
uint8_t  _data3 = 0; // Целое часть значения параметра температуры
uint8_t _data4 = 0; // Десятичная часть значения параметра температуры

//Создание экземпляра обьекта обработчика порта
dynamixel::PortHandler *portHandler;

//Создание экземпляр обьекта обработчика пакета
dynamixel::PacketHandler *packetHandler;

                                                      
void setup() {
  // Инициализация порта EStop на вход
  pinMode(10,INPUT_PULLUP);
  //Инициализация обработчика порта
  portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME);
  //Инициализация обработчика пакета
  packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);
  //Открытие порта
  portHandler->openPort();
  //Установка скорости соединения шины DXL
  portHandler->setBaudRate(BAUDRATE);

}

void loop() {
 // Условие запуска цикла при отжатой кнопке EStop
if (digitalRead(10) == false) {
  // Считывание значений параметров температуры и влажности
  packetHandler->read1ByteTxRx(portHandler, DXL_TMP, 24, (uint8_t*)&_data1); 
  packetHandler->read1ByteTxRx(portHandler, DXL_TMP, 26, (uint8_t*)&_data2); 
  packetHandler->read1ByteTxRx(portHandler, DXL_TMP, 28, (uint8_t*)&_data3); 
  packetHandler->read1ByteTxRx(portHandler, DXL_TMP, 30, (uint8_t*)&_data4); 
  Serial.println("Humidity is " + String(_data1) + "." + String(_data2) + "%");
  Serial.println("Temperature is " + String(_data3) + "." + String(_data4) + "°C");
  delay(1000);                                                 // Пауза 1 секунда
  }
else Serial.println("EStop pressed");                          // Вывод сообщения о нажатой кнопке EStop 

}
