#include <DynamixelWorkbench.h>

#define DEVICE_NAME "3" 

#define BAUDRATE  1000000
#define DXL_ID1    1
#define DXL_ID2    2
#define DXL_ID3    3
#define DXL_ID4    4
#define DXL_ID5    5
#define DXL_ID6    6
#define RGB_ID     21

DynamixelWorkbench dxl_wb;

dynamixel::PortHandler *portHandler;
dynamixel::PacketHandler *packetHandler;

String error = "0";
int i;
bool flag = false;
bool flag2 = false;

void setup() 
{
  Serial.begin(57600);
  const char *log;
  dxl_wb.init(DEVICE_NAME, BAUDRATE, &log);
  for (i = 1; i <= 6; i++) {
    dxl_wb.ping(i, &log);
    dxl_wb.jointMode(i, 70, 1, &log);
  }
  //инициализируем обработчик порта
  portHandler = dynamixel::PortHandler::getPortHandler(DEVICE_NAME);
  //инициализируем обработчик пакета
  packetHandler = dynamixel::PacketHandler::getPacketHandler(1.0);
  //открываем порт
  portHandler->openPort();
  //устанавливаем скорость соединения
  portHandler->setBaudRate(BAUDRATE);

  Serial.println("Установка начального положения");
  dxl_wb.goalPosition(DXL_ID1, 501);
  dxl_wb.goalPosition(DXL_ID2, 462);
  dxl_wb.goalPosition(DXL_ID3, 468);
  dxl_wb.goalPosition(DXL_ID4, 749);
  dxl_wb.goalPosition(DXL_ID5, 511);
  dxl_wb.goalPosition(DXL_ID6, 511);
  delay(3000);
}

void loop() 
{
  packetHandler->write1ByteTxRx(portHandler, RGB_ID, 28, 0);
  packetHandler->write1ByteTxRx(portHandler, RGB_ID, 26, 200);
  Serial.println("Манипулятор готов к работе. Для начала работы введите команду start");
  
  while (Serial.available() == 0) {}
  String mode = Serial.readString();
  mode.trim();
  Serial.println(mode);
  error = "0";

  if (mode == "start") {
    packetHandler->write1ByteTxRx(portHandler, RGB_ID, 27, 200);
    packetHandler->write1ByteTxRx(portHandler, RGB_ID, 26, 50);
    firstMove();
    secondMove();
    Serial.println("ERROR");
    Serial.println("Введите что-нибудь");
    flag = false;
    flag2 = false;
    while (flag2 == false)
      crazy();
  } 

  else {
    packetHandler->write1ByteTxRx(portHandler, RGB_ID, 26, 0);
    packetHandler->write1ByteTxRx(portHandler, RGB_ID, 27, 200);
    while (error != "manual")
    ERR();
    packetHandler->write1ByteTxRx(portHandler, RGB_ID, 27, 0);
    error = "0";
    packetHandler->write1ByteTxRx(portHandler, RGB_ID, 28, 200);

    for (i = 1; i <= 6; i++)
    dxl_wb.jointMode(i, 70, 1);

    Serial.println("Переход в ручной режим");
    Serial.println("Возвращение в начальное положение");
    delay(3000);

    dxl_wb.goalPosition(DXL_ID1, 501);
    dxl_wb.goalPosition(DXL_ID2, 462);
    dxl_wb.goalPosition(DXL_ID3, 468);
    dxl_wb.goalPosition(DXL_ID4, 749);
    dxl_wb.goalPosition(DXL_ID5, 511);
    dxl_wb.goalPosition(DXL_ID6, 511);
    delay(3000);
  }
}  


void firstMove() 
{
// наклон вперед
dxl_wb.goalPosition(DXL_ID1, 501);
dxl_wb.goalPosition(DXL_ID2, 430);
dxl_wb.goalPosition(DXL_ID3, 549);
dxl_wb.goalPosition(DXL_ID4, 706);
dxl_wb.goalPosition(DXL_ID5, 511);
dxl_wb.goalPosition(DXL_ID6, 511);
delay(2000);

// сжатие
dxl_wb.goalPosition(DXL_ID1, 501);
dxl_wb.goalPosition(DXL_ID2, 420);
dxl_wb.goalPosition(DXL_ID3, 549);
dxl_wb.goalPosition(DXL_ID4, 706);
dxl_wb.goalPosition(DXL_ID5, 511);
dxl_wb.goalPosition(DXL_ID6, 680);
delay(2000);

// движение назад
dxl_wb.goalPosition(DXL_ID1, 501);
dxl_wb.goalPosition(DXL_ID2, 452);
dxl_wb.goalPosition(DXL_ID3, 468);
dxl_wb.goalPosition(DXL_ID4, 749);
dxl_wb.goalPosition(DXL_ID5, 511);
dxl_wb.goalPosition(DXL_ID6, 680);
delay(2000);

// поворот
dxl_wb.goalPosition(DXL_ID1, 162);
dxl_wb.goalPosition(DXL_ID2, 452);
dxl_wb.goalPosition(DXL_ID3, 468);
dxl_wb.goalPosition(DXL_ID4, 749);
dxl_wb.goalPosition(DXL_ID5, 511);
dxl_wb.goalPosition(DXL_ID6, 680);
delay(3000);

// наклон вперед
dxl_wb.goalPosition(DXL_ID1, 162);
dxl_wb.goalPosition(DXL_ID2, 420);
dxl_wb.goalPosition(DXL_ID3, 549);
dxl_wb.goalPosition(DXL_ID4, 706);
dxl_wb.goalPosition(DXL_ID5, 511);
dxl_wb.goalPosition(DXL_ID6, 680);
delay(2000);

// расжатие
dxl_wb.goalPosition(DXL_ID1, 162);
dxl_wb.goalPosition(DXL_ID2, 420);
dxl_wb.goalPosition(DXL_ID3, 549);
dxl_wb.goalPosition(DXL_ID4, 706);
dxl_wb.goalPosition(DXL_ID5, 511);
dxl_wb.goalPosition(DXL_ID6, 511);
delay(2000);

// движение назад
dxl_wb.goalPosition(DXL_ID1, 162);
dxl_wb.goalPosition(DXL_ID2, 452);
dxl_wb.goalPosition(DXL_ID3, 468);
dxl_wb.goalPosition(DXL_ID4, 749);
dxl_wb.goalPosition(DXL_ID5, 511);
dxl_wb.goalPosition(DXL_ID6, 511);
delay(2000);
}

void secondMove()
{
// возвращение в начальную позицию
  dxl_wb.goalPosition(DXL_ID1, 501);
  dxl_wb.goalPosition(DXL_ID2, 452);
  dxl_wb.goalPosition(DXL_ID3, 468);
  dxl_wb.goalPosition(DXL_ID4, 749);
  dxl_wb.goalPosition(DXL_ID5, 511);
  dxl_wb.goalPosition(DXL_ID6, 511);
  delay(4000);

// опять поворот за кубиком
  dxl_wb.goalPosition(DXL_ID1, 162);
  dxl_wb.goalPosition(DXL_ID2, 452);
  dxl_wb.goalPosition(DXL_ID3, 468);
  dxl_wb.goalPosition(DXL_ID4, 749);
  dxl_wb.goalPosition(DXL_ID5, 511);
  dxl_wb.goalPosition(DXL_ID6, 511);
  delay(3000);

// наклон
  dxl_wb.goalPosition(DXL_ID1, 162);
  dxl_wb.goalPosition(DXL_ID2, 420);
  dxl_wb.goalPosition(DXL_ID3, 549);
  dxl_wb.goalPosition(DXL_ID4, 706);
  dxl_wb.goalPosition(DXL_ID5, 511);
  dxl_wb.goalPosition(DXL_ID6, 511);
  delay(2000);

// сжатие
  dxl_wb.goalPosition(DXL_ID1, 162);
  dxl_wb.goalPosition(DXL_ID2, 420);
  dxl_wb.goalPosition(DXL_ID3, 549);
  dxl_wb.goalPosition(DXL_ID4, 706);
  dxl_wb.goalPosition(DXL_ID5, 511);
  dxl_wb.goalPosition(DXL_ID6, 700);
  delay(2000);

// движение назад
  dxl_wb.goalPosition(DXL_ID1, 162);
  dxl_wb.goalPosition(DXL_ID2, 452);
  dxl_wb.goalPosition(DXL_ID3, 468);
  dxl_wb.goalPosition(DXL_ID4, 749);
  dxl_wb.goalPosition(DXL_ID5, 511);
  dxl_wb.goalPosition(DXL_ID6, 700);
  delay(2000);

// поворот 
  dxl_wb.goalPosition(DXL_ID1, 400);
  dxl_wb.goalPosition(DXL_ID2, 452);
  dxl_wb.goalPosition(DXL_ID3, 468);
  dxl_wb.goalPosition(DXL_ID4, 749);
  dxl_wb.goalPosition(DXL_ID5, 511);
  dxl_wb.goalPosition(DXL_ID6, 700);
  delay(2000);

  packetHandler->write1ByteTxRx(portHandler, RGB_ID, 26, 0);
  for (i = 1; i <= 6; i++) 
  dxl_wb.jointMode(i, 120, 1);

  dxl_wb.goalPosition(DXL_ID1, 400);
  dxl_wb.goalPosition(DXL_ID2, 430);
  dxl_wb.goalPosition(DXL_ID3, 128);
  dxl_wb.goalPosition(DXL_ID4, 749);
  dxl_wb.goalPosition(DXL_ID5, 511);
  dxl_wb.goalPosition(DXL_ID6, 700);
  delay(1000);
}

void stop_crazy(){
    if(Serial.available()){
        error = Serial.readString();
        Serial.println(error);
        flag = !flag;
        flag2 = !flag2;
        packetHandler->write1ByteTxRx(portHandler, RGB_ID, 27, 0);
        packetHandler->write1ByteTxRx(portHandler, RGB_ID, 28, 200);
        Serial.println("Переход в ручной режим");
        Serial.println("Возвращение в начальное положение");
        for (i = 1; i <= 6; i++)
          dxl_wb.jointMode(i, 70, 1);
        delay(3000);

        dxl_wb.goalPosition(DXL_ID1, 501);
        dxl_wb.goalPosition(DXL_ID2, 452);
        dxl_wb.goalPosition(DXL_ID3, 468);
        dxl_wb.goalPosition(DXL_ID4, 749);
        dxl_wb.goalPosition(DXL_ID5, 511);
        dxl_wb.goalPosition(DXL_ID6, 511);
        delay(3000);
    }
}

void crazy() {
  while (flag != true) {
    dxl_wb.goalPosition(DXL_ID1, 487);
    dxl_wb.goalPosition(DXL_ID2, 556);
    dxl_wb.goalPosition(DXL_ID3, 300);
    dxl_wb.goalPosition(DXL_ID4, 749);
    dxl_wb.goalPosition(DXL_ID5, 511);
    dxl_wb.goalPosition(DXL_ID6, 300);
    delay(1000);
    stop_crazy();
    if (flag == true)
      break;

    dxl_wb.goalPosition(DXL_ID1, 487);
    dxl_wb.goalPosition(DXL_ID2, 556);
    dxl_wb.goalPosition(DXL_ID3, 387);
    dxl_wb.goalPosition(DXL_ID4, 749);
    dxl_wb.goalPosition(DXL_ID5, 375);
    dxl_wb.goalPosition(DXL_ID6, 200);
    delay(1000);
    stop_crazy();
    if (flag == true)
      break;

    for (i = 1; i <= 6; i++)
    dxl_wb.jointMode(i, 150, 1);
    stop_crazy();
    if (flag == true)
      break;

    dxl_wb.goalPosition(DXL_ID1, 687);
    dxl_wb.goalPosition(DXL_ID2, 431);
    dxl_wb.goalPosition(DXL_ID3, 287);
    dxl_wb.goalPosition(DXL_ID4, 749);
    dxl_wb.goalPosition(DXL_ID5, 749);
    dxl_wb.goalPosition(DXL_ID6, 511);
    delay(1000);
    stop_crazy();
    if (flag == true)
      break;

    dxl_wb.goalPosition(DXL_ID1, 562);
    dxl_wb.goalPosition(DXL_ID2, 431);
    dxl_wb.goalPosition(DXL_ID3, 387);
    dxl_wb.goalPosition(DXL_ID4, 562);
    dxl_wb.goalPosition(DXL_ID5, 511);
    dxl_wb.goalPosition(DXL_ID6, 600);
    delay(1000);
    stop_crazy();
    if (flag == true)
      break;

    for (i = 1; i <= 6; i++) 
    dxl_wb.jointMode(i, 120, 1);
    stop_crazy();
    if (flag == true)
      break;

    dxl_wb.goalPosition(DXL_ID1, 624);
    dxl_wb.goalPosition(DXL_ID2, 431);
    dxl_wb.goalPosition(DXL_ID3, 387);
    dxl_wb.goalPosition(DXL_ID4, 749);
    dxl_wb.goalPosition(DXL_ID5, 375);
    dxl_wb.goalPosition(DXL_ID6, 600);
    delay(1000);
    stop_crazy();
    if (flag == true)
      break;

    dxl_wb.goalPosition(DXL_ID1, 712);
    dxl_wb.goalPosition(DXL_ID2, 431);
    dxl_wb.goalPosition(DXL_ID3, 287);
    dxl_wb.goalPosition(DXL_ID4, 562);
    dxl_wb.goalPosition(DXL_ID5, 749);
    dxl_wb.goalPosition(DXL_ID6, 511);
    delay(1000);
    stop_crazy();
    if (flag == true)
      break;
  }
}
void ERR() 
{
  Serial.println("ERROR");
  Serial.println("Чтобы перейти в ручной режим, введите команду manual");
  while (Serial.available() == 0) {}
  error = Serial.readString();
  error.trim();
  Serial.println(error);
}

