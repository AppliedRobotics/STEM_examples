#include <DynamixelWorkbench.h>

#define DEVICE_NAME "3" 

#define BAUDRATE  1000000
#define DXL_ID1    1
#define DXL_ID2    2
#define DXL_ID3    3
#define DXL_ID4    4
#define DXL_ID5    5
#define DXL_ID6    6

#define MOD_ID 23

DynamixelWorkbench dxl_wb;

dynamixel::PortHandler *portHandler;
dynamixel::PacketHandler *packetHandler;

int i;
uint8_t data = 0;

void setup() {
  Serial.begin(115200);
  const char *log;
  dxl_wb.init(DEVICE_NAME, BAUDRATE, &log);
  
  for (i = 1; i <= 6; i++) {
    dxl_wb.ping(i, &log);
    dxl_wb.jointMode(i, 50, 1, &log);
  }

  //инициализируем обработчик порта
  portHandler = dynamixel::PortHandler::getPortHandler(DEVICE_NAME);
  //инициализируем обработчик пакета
  packetHandler = dynamixel::PacketHandler::getPacketHandler(1.0);
  //открываем порт
  portHandler->openPort();
  //устанавливаем скорость соединения
  portHandler->setBaudRate(BAUDRATE);

  delay(3000);
}

void loop() {

  dxl_wb.goalPosition(1, 8192);
  dxl_wb.goalPosition(2, 8192);
  dxl_wb.goalPosition(3, 8192);
  dxl_wb.goalPosition(4, 8192);
  dxl_wb.goalPosition(5, 8192);
  dxl_wb.goalPosition(6, 9000);
  delay(3000);

  button();

  dxl_wb.goalPosition(1, 8192);
  dxl_wb.goalPosition(2, 9800);
  dxl_wb.goalPosition(3, 9471);
  dxl_wb.goalPosition(4, 6049);
  dxl_wb.goalPosition(5, 8354);
  dxl_wb.goalPosition(6, 9000);
  delay(3000);

  button();
  
  dxl_wb.goalPosition(1, 8192);
  dxl_wb.goalPosition(2, 9800);
  dxl_wb.goalPosition(3, 9471);
  dxl_wb.goalPosition(4, 6049);
  dxl_wb.goalPosition(5, 8354);
  dxl_wb.goalPosition(6, 5600);
  delay(5000);

  button();

  dxl_wb.goalPosition(1, 8192);
  dxl_wb.goalPosition(2, 8800);
  dxl_wb.goalPosition(3, 9471);
  dxl_wb.goalPosition(4, 6049);
  dxl_wb.goalPosition(5, 8354);
  dxl_wb.goalPosition(6, 5600);
  delay(2000);

  button();

  dxl_wb.goalPosition(1, 4188);
  dxl_wb.goalPosition(2, 8310);
  dxl_wb.goalPosition(3, 12466);
  dxl_wb.goalPosition(4, 8312);
  dxl_wb.goalPosition(5, 16113);
  dxl_wb.goalPosition(6, 5600);
  delay(1000);

  button();

  dxl_wb.goalPosition(1, 8192);
  dxl_wb.goalPosition(2, 8192);
  dxl_wb.goalPosition(3, 16383);
  dxl_wb.goalPosition(4, 8192);
  dxl_wb.goalPosition(5, 16383);
  dxl_wb.goalPosition(6, 5600);
  delay(1000);

  button();

  dxl_wb.goalPosition(1, 8192);
  dxl_wb.goalPosition(2, 6584);
  dxl_wb.goalPosition(3, 15104);
  dxl_wb.goalPosition(4, 10335);
  dxl_wb.goalPosition(5, 16221);
  dxl_wb.goalPosition(6, 5600);
  delay(3000);

  button();

  dxl_wb.goalPosition(1, 8192);
  dxl_wb.goalPosition(2, 6584);
  dxl_wb.goalPosition(3, 15104);
  dxl_wb.goalPosition(4, 10335);
  dxl_wb.goalPosition(5, 16221);
  dxl_wb.goalPosition(6, 9000);
  delay(2000);

  button();

  dxl_wb.goalPosition(1, 8192);
  dxl_wb.goalPosition(2, 7584);
  dxl_wb.goalPosition(3, 15104);
  dxl_wb.goalPosition(4, 10335);
  dxl_wb.goalPosition(5, 16221);
  dxl_wb.goalPosition(6, 9000);
  delay(1000);

  button();

  dxl_wb.goalPosition(1, 4177);
  dxl_wb.goalPosition(2, 8310);
  dxl_wb.goalPosition(3, 12466);
  dxl_wb.goalPosition(4, 8312);
  dxl_wb.goalPosition(5, 16113);
  dxl_wb.goalPosition(6, 9000);
  delay(1000);

  button();

}

void button() {
  packetHandler->read1ByteTxRx(portHandler, MOD_ID, 27, (uint8_t*)&data);
  Serial.println(data);
  delay(100);
  if (data == 1){
  for (i = 1; i <= 6; i++) 
  dxl_wb.jointMode(i, 0, 1);
  while (data == 1) {
  packetHandler->read1ByteTxRx(portHandler, MOD_ID, 27, (uint8_t*)&data);
  Serial.println(data);
  delay(500);

    if (data == 0) {
      for (i = 1; i <= 6; i++) 
      dxl_wb.jointMode(i, 50, 1);
      break;
    }
  }}
  }

