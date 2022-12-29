// Подключение библиотеки
#include <DynamixelSDK.h>

//Версия протокола DXL
#define PROTOCOL_VERSION                1.0                 

//Базовые настройки
#define DXL_LED                           9     //     ID светодиода
#define BAUDRATE                          57600 //     Скорость обмена данными по шине DXL
#define DEVICENAME                        "3"   //     Адрес порта DXL

//Создание экземпляра обьекта обработчика порта
dynamixel::PortHandler *portHandler;

//Создание экземпляр обьекта обработчика пакета
dynamixel::PacketHandler *packetHandler;

                                                      
void setup() {
  //Инициализация вывода в последовательный порт
  Serial.begin(115200);
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
  packetHandler->write1ByteTxRx(portHandler,DXL_LED, 26, 255); // Включение светодиода
  delay(1000);                                                 // Пауза 1 секунда
  packetHandler->write1ByteTxRx(portHandler,DXL_LED, 26, 0);   // Выключение светодиода
  delay(1000);                                                 // Пауза 1 секунда
  }
else Serial.println("EStop pressed");                          // Вывод сообщения о нажатой кнопке EStop 

}
