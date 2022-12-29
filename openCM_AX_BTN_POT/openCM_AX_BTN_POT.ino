// Подключение библиотеки
#include <DynamixelSDK.h>

//Версия протокола DXL
#define PROTOCOL_VERSION                1.0                 

//Базовые настройки
#define DXL_AX12                          1     //     ID привода   
#define DXL_BTN                           3     //     ID кнопки
#define DXL_POT                           19    //     ID потенциометра
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
uint8_t  _data1 = 0; // Состояние кнопки
uint16_t _data2 = 0; // Значение потенциометра
uint16_t _data3 = 0; // Текущий угол поворота вала
uint16_t _data4 = 0; // Текущая скорость поворота вала
uint16_t _pos = 0;   // Значение положения для записи в регистр
                                                      
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
  packetHandler->read1ByteTxRx(portHandler,DXL_BTN, 27, (uint8_t*)&_data1);          // Считывание состояния кнопки
  packetHandler->read2ByteTxRx(portHandler,DXL_POT, 26, (uint16_t*)&_data2);         // Считывание значения потенциометра
  if (_data1 == 1) _pos = pos2;
  else _pos = pos1;
  packetHandler->read2ByteTxRx(portHandler, DXL_AX12, 36, (uint16_t*)&_data3); // Чтение регистра текущего положения
  packetHandler->read2ByteTxRx(portHandler, DXL_AX12, 38, (uint16_t*)&_data4); // Чтение регистра текущей скорости
  packetHandler->write2ByteTxRx(portHandler,DXL_AX12, 32, map(_data2,0,1023,1,1023)); // Запись значения скорости вращения
  packetHandler->write2ByteTxRx(portHandler,DXL_AX12, 30, _pos);   // Запись целевого положения привода
  Serial.println("Present Position is "+String(_data3));           // Вывод текущего положения в последовательный порт
  Serial.println("Present Speed is "+String(map(_data2,0,1023,1,1023)));              // Вывод текущего положения в последовательный порт
  }
else Serial.println("EStop pressed");                              // Вывод сообщения о нажатой кнопке EStop 
}
