#include <DynamixelWorkbench.h> //Подключение библиотеки Dynamixel
#define DEVICE_NAME "3"         // Порт Dynamixel
#define BAUDRATE 1000000        // Скорость обмена данными по последовательному порту манипулятора и датчиков
#define PROTOCOL_VERSION 1.0
#define DXL_ID1 1
#define DXL_ID2 2
#define DXL_ID3 3
#define DXL_ID4 4
#define COLOR_ID 5 // датчик цвета
// Создаем экземпляры обработчиков
dynamixel::PortHandler *portHandler;
dynamixel::PacketHandler *packetHandler;
DynamixelWorkbench dxl_wb;
// создаем переменные для хранения RGB данных
uint16_t R = 0;
uint16_t G = 0;
uint16_t B = 0;

void setup()
{
  const char *log;
  uint16_t model_number1 = 1;
  uint16_t model_number2 = 2;
  uint16_t model_number3 = 3;
  uint16_t model_number4 = 4;

  dxl_wb.init(DEVICE_NAME, BAUDRATE, &log);

  dxl_wb.ping(DXL_ID1, &model_number1, &log);
  dxl_wb.ping(DXL_ID2, &model_number2, &log);
  dxl_wb.ping(DXL_ID3, &model_number3, &log);
  dxl_wb.ping(DXL_ID4, &model_number4, &log);

  dxl_wb.jointMode(DXL_ID1, 80, 1, &log); // установка скорости сервоприводов
  dxl_wb.jointMode(DXL_ID2, 80, 1, &log);
  dxl_wb.jointMode(DXL_ID3, 80, 1, &log);
  dxl_wb.jointMode(DXL_ID4, 80, 1, &log);

  // инициализируем обработчик порта
  portHandler = dynamixel::PortHandler::getPortHandler(DEVICE_NAME);
  // инициализируем обработчик пакета
  packetHandler = dynamixel::PacketHandler::getPacketHandler(1.0);

  // открываем порт
  portHandler->openPort();
  // устанавливаем скорость соединения
  portHandler->setBaudRate(BAUDRATE);
}

void loop()
{
  // базовое положение
  dxl_wb.goalPosition(1, 524);
  dxl_wb.goalPosition(2, 807);
  dxl_wb.goalPosition(3, 556);
  dxl_wb.goalPosition(4, 484);
  delay(4000);
  RED();
  GREEN();
  BLUE();
  Serial.println("R: " + String(R / 257) + " G: " + String(G / 257) + " B: " + String(B / 257)); // запись rgb параметров в монитор порта
  delay(2000);
  // красный
  dxl_wb.goalPosition(1, 502);
  dxl_wb.goalPosition(2, 816);
  dxl_wb.goalPosition(3, 532);
  dxl_wb.goalPosition(4, 193);
  delay(4000);
  packetHandler-> (portHandler, COLOR_ID, 42, 50); // включение подсветки датчика цвета
  RED();
  GREEN();
  BLUE();
  Serial.println("R: " + String(R / 257) + " G: " + String(G / 257) + " B: " + String(B / 257)); // запись rgb параметров в монитор порта
  dxl_wb.goalPosition(4, 480); // поднимаем датчик
  delay(2000);
  // оранжевый
  dxl_wb.goalPosition(1, 476);
  dxl_wb.goalPosition(2, 762);
  dxl_wb.goalPosition(3, 528);
  dxl_wb.goalPosition(4, 258);
  delay(4000);
  RED();
  GREEN();
  BLUE();
  Serial.println("R: " + String(R / 257) + " G: " + String(G / 257) + " B: " + String(B / 257)); // запись rgb параметров в монитор порта
  dxl_wb.goalPosition(4, 480); // поднимаем датчик
  delay(2000);
  // желтый
  dxl_wb.goalPosition(1, 557);
  dxl_wb.goalPosition(2, 547);
  dxl_wb.goalPosition(3, 551);
  dxl_wb.goalPosition(4, 225);
  delay(4000);
  RED();
  GREEN();
  BLUE();
  Serial.println("R: " + String(R / 257) + " G: " + String(G / 257) + " B: " + String(B / 257)); // запись rgb параметров в монитор порта
  dxl_wb.goalPosition(4, 480);// поднимаем датчик
  delay(2000); 
  // зеленый
  dxl_wb.goalPosition(1, 522);
  dxl_wb.goalPosition(2, 528);
  dxl_wb.goalPosition(3, 561);
  dxl_wb.goalPosition(4, 240);
  delay(4000);
  RED();
  GREEN();
  BLUE();
  Serial.println("R: " + String(R / 257) + " G: " + String(G / 257) + " B: " + String(B / 257)); // запись rgb параметров в монитор порта
  dxl_wb.goalPosition(4, 480);// поднимаем датчик
  delay(2000); 
  // голубой
  dxl_wb.goalPosition(1, 514);
  dxl_wb.goalPosition(2, 486);
  dxl_wb.goalPosition(3, 464);
  dxl_wb.goalPosition(4, 240);
  delay(4000);
  RED();
  GREEN();
  BLUE();
  Serial.println("R: " + String(R / 257) + " G: " + String(G / 257) + " B: " + String(B / 257)); // запись rgb параметров в монитор порта
  dxl_wb.goalPosition(4, 480);// поднимаем датчик
  delay(2000); 
  // синий
  dxl_wb.goalPosition(1, 498);
  dxl_wb.goalPosition(2, 453);
  dxl_wb.goalPosition(3, 368);
  dxl_wb.goalPosition(4, 253);
  delay(4000);
  RED();
  GREEN();
  BLUE();
  Serial.println("R: " + String(R / 257) + " G: " + String(G / 257) + " B: " + String(B / 257)); // запись rgb параметров в монитор порта
  dxl_wb.goalPosition(4, 480);// поднимаем датчик
  delay(2000); 
  // розовый
  dxl_wb.goalPosition(1, 518);
  dxl_wb.goalPosition(2, 346);
  dxl_wb.goalPosition(3, 394);
  dxl_wb.goalPosition(4, 239);
  delay(4000);
  RED();
  GREEN();
  BLUE();
  Serial.println("R: " + String(R / 257) + " G: " + String(G / 257) + " B: " + String(B / 257)); // запись rgb параметров в монитор порта
  dxl_wb.goalPosition(4, 480);// поднимаем датчик
  delay(2000); 
  // белый
  dxl_wb.goalPosition(1, 538);
  dxl_wb.goalPosition(2, 206);
  dxl_wb.goalPosition(3, 491);
  dxl_wb.goalPosition(4, 239);
  delay(4000);
  RED();
  GREEN();
  BLUE();
  Serial.println("R: " + String(R / 257) + " G: " + String(G / 257) + " B: " + String(B / 257)); // запись rgb параметров в монитор порта
  dxl_wb.goalPosition(4, 480);// поднимаем датчик
  delay(2000); 
}
void RED()
{
  packetHandler->read2ByteTxRx(portHandler, COLOR_ID, 26, (uint16_t *)&R); // функция чтения красного цвета
}
void GREEN()
{
  packetHandler->read2ByteTxRx(portHandler, COLOR_ID, 28, (uint16_t *)&G); // функция чтения зеленого цвета
}
void BLUE()
{
  packetHandler->read2ByteTxRx(portHandler, COLOR_ID, 30, (uint16_t *)&B); // функция чтения синего цвета
}
