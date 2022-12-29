// Подключение библиотеки
#include <DynamixelSDK.h>

//Версия протокола DXL
#define PROTOCOL_VERSION                1.0                 

//Базовые настройки
#define DXL_AX12                          1     //     ID привода   
#define BAUDRATE                          57600 //     Скорость обмена данными по шине DXL
#define DEVICENAME                        "3"   //     Адрес порта DXL
#define pos1                              0     //     Значение угла поворота 1
#define pos2                              1023  //     Значение угла поворота 2
#define _speed                            500   //     Cкорость вращения привода

//Создание экземпляра обьекта обработчика порта
dynamixel::PortHandler *portHandler;

//Создание экземпляр обьекта обработчика пакета
dynamixel::PacketHandler *packetHandler;

//Создание и инициализация переменных для хранения состояния
uint16_t _data = 0; // Текущий угол поворота вала
uint16_t _pos = 0;  // Значение положения для записи в регистр
                                                      
void setup() {
  // Инициализация порта EStop на вход
  pinMode(10,INPUT_PULLUP);
  //Инициализация вывода в последовательный порт
  Serial.begin(115200);
  //Инициализация обработчика порта
  portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME);
  //Инициализация обработчика пакета
  packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);
  //Открытие порта
  portHandler->openPort();
  //Установка скорости соединения шины DXL
  portHandler->setBaudRate(BAUDRATE);
  // Настройка работы привода в режиме joint
  packetHandler->write1ByteTxRx(portHandler,DXL_AX12, 24, 0);   // Отключение нагрузки
  packetHandler->write2ByteTxRx(portHandler,DXL_AX12, 6, 0);    // Запись максимального угла поворота по часовой стрелке
  packetHandler->write2ByteTxRx(portHandler,DXL_AX12, 8, 1023); // Запись максимального угла поворота ппротив часовой стрелки
  packetHandler->write1ByteTxRx(portHandler,DXL_AX12, 24, 1);   // Включение нагрузки
}

void loop() {
  // Условие запуска цикла при отжатой кнопке EStop
if (digitalRead(10) == false) {
  // Смена значения целевого положения
  if (_pos == pos1) _pos = pos2;
  else _pos = pos1;
  
  packetHandler->read2ByteTxRx(portHandler, DXL_AX12, 36, (uint16_t*)&_data); // Чтение регистра текущего положения
  packetHandler->write2ByteTxRx(portHandler,DXL_AX12, 32, _speed); // Запись значения скорости вращения
  packetHandler->write2ByteTxRx(portHandler,DXL_AX12, 30, _pos);   // Запись целевого положения привода
  Serial.println("Present Position is " + String(_data));            // Вывод текущего положения в последовательный порт
  delay(2000);                                                     // Задержка работы цикла
  }
else Serial.println("EStop pressed");                              // Вывод сообщения о нажатой кнопке EStop 
}
