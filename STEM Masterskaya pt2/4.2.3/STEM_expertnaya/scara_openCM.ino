#include <DynamixelSDK.h> //Подключение библиотеки Dynamixel
#define DEVICENAME "3"  // Порт подключения Dynamixel
#define BAUDRATE 1000000 // Скорость обмена данными по последовательному порту манипулятора и датчиков
#define PROTOCOL_VERSION 1.0
#define COLOR_ID 5 //датчик цвета
#define RGB_ID 21 //RGB
// Конфигурация для управления сервоприводами
#define jointN 4 //инициализация для массива
#define pages 10

// Создаем экземпляры обработчиков
dynamixel::PortHandler *portHandler;
dynamixel::PacketHandler *packetHandler;

//создаем переменные для хранения RGB данные
uint16_t R = 0;
uint16_t G = 0;
uint16_t B = 0;

//Задаем массив позиций сервоприводов
int buf[pages + 1][jointN + 1] = { //Инициализация двумерного массива, его размер задается 4+1=5, так как в программировании нумерация начинается с 0, но нулевой элемент мы использовать не будем
    {0, 8200, 8200, 8200, 8200}, //задаем иначальное положение
    {0, 11449, 4887, 4234, 4125},//первый кубик
    {0, 11453, 4884, 4225, 8058},
    {0, 7708, 8128, 8831, 7924},
    {0, 7706, 8134, 8830, 4728},//второй кубик
    {0, 7708, 8128, 8831, 7924},
    {0, 9221, 3416, 7974, 8512},
    {0, 9272, 3410, 7974, 4600}, //третий кубик
    {0, 9306, 3407, 7972, 8310},
    {0, 12517, 3449, 8652, 8310}, 
};

void setup() {
  Serial.begin(57600); //Установка скорости обмена данными по последовательному порту компьютера
  portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME); // Инициализация обработчиков
  packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);  // Создаем обработчик пакетов для протоколов
  
  portHandler->openPort();//открытие порта обработчика
  portHandler->setBaudRate(BAUDRATE);//установка скорости обмена данными по порту манипулятора
  uint8_t dxl_error = 0;
  //packetHandler->write1ByteTxRx(portHandler, 4, 3, 5, &dxl_error); //для переустановки ID светодиода

  // Настройка сервоприводов для дальнейшей работы
  for (int i = 1; i <= jointN; i++) { //цикл с изменением i от 1 до 6 с шагом 1
    packetHandler->write1ByteTxRx(portHandler, i, 64, 0, &dxl_error); //отключение крутящий момент
    packetHandler->write1ByteTxRx(portHandler, i, 11, 3, &dxl_error); //режим управления положением
    packetHandler->write1ByteTxRx(portHandler, i, 64, 1, &dxl_error); //включаем крутящий момент
    packetHandler->write4ByteTxRx(portHandler, i, 112, 50, &dxl_error); //скорость 
    packetHandler->write2ByteTxRx(portHandler, i, 80, 100, &dxl_error);  //D - составляющая ПИД
    packetHandler->write2ByteTxRx(portHandler, i, 82, 100, &dxl_error);  //I - составляюшая ПИД
    packetHandler->write2ByteTxRx(portHandler, i, 84, 50, &dxl_error);   //P - составляющая ПИД
  }
}

void loop() {
   // Управление сервоприводами
  for (int j = 0; j < pages; j++) {
    for (int i = 1; i <= jointN; i++) {
      uint8_t dxl_error = 0;
      packetHandler->write4ByteTxRx(portHandler, i, 116, buf[j][i], &dxl_error); //положение цели
      packetHandler->write1ByteTxRx(portHandler, COLOR_ID, 42, 50); // включение подсветки датчика цвета
      RED();
      GREEN();
      BLUE();
      Serial.println("R: " + String(R / 257) + " G: " + String(G / 257) + " B: " + String(B / 257));//запись rgb параметров в монитор порта
      packetHandler->write1ByteTxRx(portHandler, RGB_ID, 27, R / 257);//запись в 27 регистр для красного цвета
      packetHandler->write1ByteTxRx(portHandler, RGB_ID, 26, G / 257);//запись в 26 регистр для зеленого цвета
      packetHandler->write1ByteTxRx(portHandler, RGB_ID, 28, B / 257);//запись в 28 регистр для красного цвета
      delay(1500);
    }
  }
}
// Функции чтения RGB значений
void RED() {
  packetHandler->read2ByteTxRx(portHandler, COLOR_ID, 26, (uint16_t *)&R); //функция чтения красного цвета
}
void GREEN() {
  packetHandler->read2ByteTxRx(portHandler, COLOR_ID, 28, (uint16_t *)&G); //функция чтения зеленого цвета
}
void BLUE() {
  packetHandler->read2ByteTxRx(portHandler, COLOR_ID, 30, (uint16_t *)&B); //функция чтения синего цвета
}