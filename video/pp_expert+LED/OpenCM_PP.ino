#include <DynamixelWorkbench.h>

#define DEVICE_NAME "3" 

#define BAUDRATE  1000000
#define DXL_ID1    1
#define DXL_ID2    2
#define DXL_ID3    3
#define DXL_ID4    4
#define DXL_ID5    5
#define LED_ID     9

DynamixelWorkbench dxl_wb;

//создаём экземпляр обработчика порта
dynamixel::PortHandler *portHandler;
//создаём экземпляр обработчика пакета
dynamixel::PacketHandler *packetHandler;

uint8_t data = 0;

void setup() 
{
const char *log;
dxl_wb.init(DEVICE_NAME, BAUDRATE, &log);
delay(500);
dxl_wb.ping(DXL_ID1, &log);
dxl_wb.ping(DXL_ID2, &log);
dxl_wb.ping(DXL_ID3, &log);
dxl_wb.ping(DXL_ID4, &log);
dxl_wb.ping(DXL_ID5, &log);
delay(500);
dxl_wb.jointMode(DXL_ID1, 80, 1, &log);
dxl_wb.jointMode(DXL_ID2, 80, 1, &log);
dxl_wb.jointMode(DXL_ID3, 80, 1, &log);
dxl_wb.jointMode(DXL_ID4, 80, 1, &log);
dxl_wb.jointMode(DXL_ID5, 80, 1, &log);
delay(500);

//инициализируем обработчик порта
portHandler = dynamixel::PortHandler::getPortHandler(DEVICE_NAME);
//инициализируем обработчик пакета
packetHandler = dynamixel::PacketHandler::getPacketHandler(1.0);
//открываем порт
portHandler->openPort();
//устанавливаем скорость соединения
portHandler->setBaudRate(BAUDRATE);
}

void loop() 
{
firstMove();
secondMove();
}  

void firstMove() 
{
// // движение в начальное положение
dxl_wb.goalPosition(DXL_ID1, 4152);
dxl_wb.goalPosition(DXL_ID2, 9365);
dxl_wb.goalPosition(DXL_ID3, 11670);
dxl_wb.goalPosition(DXL_ID4, 8201);
dxl_wb.goalPosition(DXL_ID5, 7862);
delay(4000);
// наклон вперед
dxl_wb.goalPosition(DXL_ID1, 4152);
dxl_wb.goalPosition(DXL_ID2, 9996);
dxl_wb.goalPosition(DXL_ID3, 11409);
dxl_wb.goalPosition(DXL_ID4, 8201);
dxl_wb.goalPosition(DXL_ID5, 7862);
delay(1000);
// сжатие
dxl_wb.goalPosition(DXL_ID1, 4152);
dxl_wb.goalPosition(DXL_ID2, 9996);
dxl_wb.goalPosition(DXL_ID3, 11409);
dxl_wb.goalPosition(DXL_ID4, 8201);
dxl_wb.goalPosition(DXL_ID5, 6061);
delay(3000);

// светодиод загорается
packetHandler->write1ByteTxRx(portHandler, LED_ID, 26, 250);

// движение назад
dxl_wb.goalPosition(DXL_ID1, 4152);
dxl_wb.goalPosition(DXL_ID2, 9365);
dxl_wb.goalPosition(DXL_ID3, 11670);
dxl_wb.goalPosition(DXL_ID4, 8201);
dxl_wb.goalPosition(DXL_ID5, 6061);
delay(2000);
// поворот
dxl_wb.goalPosition(DXL_ID1, 8304);
dxl_wb.goalPosition(DXL_ID2, 9365);
dxl_wb.goalPosition(DXL_ID3, 11670);
dxl_wb.goalPosition(DXL_ID4, 8201);
dxl_wb.goalPosition(DXL_ID5, 6061);
delay(4000);
// наклон вперед
dxl_wb.goalPosition(DXL_ID1, 8304);
dxl_wb.goalPosition(DXL_ID2, 9896);
dxl_wb.goalPosition(DXL_ID3, 11409);
dxl_wb.goalPosition(DXL_ID4, 8201);
dxl_wb.goalPosition(DXL_ID5, 6061);
delay(1000);
// расжатие
dxl_wb.goalPosition(DXL_ID1, 8304);
dxl_wb.goalPosition(DXL_ID2, 9896);
dxl_wb.goalPosition(DXL_ID3, 11409);
dxl_wb.goalPosition(DXL_ID4, 8201);
dxl_wb.goalPosition(DXL_ID5, 7862);

// светодиод гаснет
packetHandler->write1ByteTxRx(portHandler, LED_ID, 26, 0);

delay(1000);
// движение назад
dxl_wb.goalPosition(DXL_ID1, 8304);
dxl_wb.goalPosition(DXL_ID2, 9365);
dxl_wb.goalPosition(DXL_ID3, 11670);
dxl_wb.goalPosition(DXL_ID4, 8201);
dxl_wb.goalPosition(DXL_ID5, 7862);
delay(2000);
}

void secondMove()
{
// возвращение в начальную позицию
dxl_wb.goalPosition(DXL_ID1, 4152);
dxl_wb.goalPosition(DXL_ID2, 9365);
dxl_wb.goalPosition(DXL_ID3, 11670);
dxl_wb.goalPosition(DXL_ID4, 8201);
dxl_wb.goalPosition(DXL_ID5, 7862);
delay(4000);
// опять поворот за кубиком
dxl_wb.goalPosition(DXL_ID1, 8304);
dxl_wb.goalPosition(DXL_ID2, 9365);
dxl_wb.goalPosition(DXL_ID3, 11670);
dxl_wb.goalPosition(DXL_ID4, 8201);
dxl_wb.goalPosition(DXL_ID5, 7862);
delay(4000);
// наклон
dxl_wb.goalPosition(DXL_ID1, 8304);
dxl_wb.goalPosition(DXL_ID2, 9896);
dxl_wb.goalPosition(DXL_ID3, 11409);
dxl_wb.goalPosition(DXL_ID4, 8201);
dxl_wb.goalPosition(DXL_ID5, 7862);
delay(1000);
// сжатие
dxl_wb.goalPosition(DXL_ID1, 8304);
dxl_wb.goalPosition(DXL_ID2, 9896);
dxl_wb.goalPosition(DXL_ID3, 11409);
dxl_wb.goalPosition(DXL_ID4, 8201);
dxl_wb.goalPosition(DXL_ID5, 6061);
delay(3000);

// светодиод загорается
packetHandler->write1ByteTxRx(portHandler, LED_ID, 26, 250);

// движение назад
dxl_wb.goalPosition(DXL_ID1, 8304);
dxl_wb.goalPosition(DXL_ID2, 9365);
dxl_wb.goalPosition(DXL_ID3, 11670);
dxl_wb.goalPosition(DXL_ID4, 8201);
dxl_wb.goalPosition(DXL_ID5, 6061);
delay(2000);

// поворот 
dxl_wb.goalPosition(DXL_ID1, 4152);
dxl_wb.goalPosition(DXL_ID2, 9365);
dxl_wb.goalPosition(DXL_ID3, 11670);
dxl_wb.goalPosition(DXL_ID4, 8201);
dxl_wb.goalPosition(DXL_ID5, 6061);
delay(4000);
// наклон вперед
dxl_wb.goalPosition(DXL_ID1, 4152);
dxl_wb.goalPosition(DXL_ID2, 9996);
dxl_wb.goalPosition(DXL_ID3, 11409);
dxl_wb.goalPosition(DXL_ID4, 8201);
dxl_wb.goalPosition(DXL_ID5, 6061);
delay(1000);
// расжатие
dxl_wb.goalPosition(DXL_ID1, 4152);
dxl_wb.goalPosition(DXL_ID2, 9996);
dxl_wb.goalPosition(DXL_ID3, 11409);
dxl_wb.goalPosition(DXL_ID4, 8201);
dxl_wb.goalPosition(DXL_ID5, 7862);

// светодиод гаснет
packetHandler->write1ByteTxRx(portHandler, LED_ID, 26, 0);

delay(3000);
// движение назад
dxl_wb.goalPosition(DXL_ID1, 4152);
dxl_wb.goalPosition(DXL_ID2, 9365);
dxl_wb.goalPosition(DXL_ID3, 11670);
dxl_wb.goalPosition(DXL_ID4, 8201);
dxl_wb.goalPosition(DXL_ID5, 7862);
delay(2000);
// поворот 
dxl_wb.goalPosition(DXL_ID1, 8304);
dxl_wb.goalPosition(DXL_ID2, 9365);
dxl_wb.goalPosition(DXL_ID3, 11670);
dxl_wb.goalPosition(DXL_ID4, 8201);
dxl_wb.goalPosition(DXL_ID5, 7862);
delay(4000);
}