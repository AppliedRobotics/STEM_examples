#include <DynamixelWorkbench.h>

#if defined(__OPENCM904__)
  #define DEVICE_NAME "3" //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#elif defined(__OPENCR__)
  #define DEVICE_NAME ""
#endif   

#define BAUDRATE  1000000
#define DXL_ID1    1
#define DXL_ID2    2
#define DXL_ID3    3
#define DXL_ID4    4
#define DXL_ID5    5

DynamixelWorkbench dxl_wb;

void setup() {
  // put your setup code here, to run once:
  const char *log;
uint16_t model_number1 = 1;
uint16_t model_number2 = 2;
uint16_t model_number3 = 3;
uint16_t model_number4 = 4;
uint16_t model_number5 = 5;

  dxl_wb.init(DEVICE_NAME, BAUDRATE, &log);
  
dxl_wb.ping(DXL_ID1, &model_number1, &log);
dxl_wb.ping(DXL_ID2, &model_number2, &log);
dxl_wb.ping(DXL_ID3, &model_number3, &log);
dxl_wb.ping(DXL_ID4, &model_number4, &log);
dxl_wb.ping(DXL_ID5, &model_number5, &log);
dxl_wb.jointMode(DXL_ID1, 20, 1, &log);
dxl_wb.jointMode(DXL_ID2, 20, 1, &log);
dxl_wb.jointMode(DXL_ID3, 20, 1, &log);
dxl_wb.jointMode(DXL_ID4, 20, 1, &log);
dxl_wb.jointMode(DXL_ID5, 20, 1, &log);
}

void loop() {
dxl_wb.goalPosition(1, 4304);
dxl_wb.goalPosition(2, 9365);
dxl_wb.goalPosition(3, 11670);
dxl_wb.goalPosition(4, 8201);
dxl_wb.goalPosition(5, 7862);
delay(4000);
dxl_wb.goalPosition(1, 4404);
dxl_wb.goalPosition(2, 9896);
dxl_wb.goalPosition(3, 11409);
dxl_wb.goalPosition(4, 8201);
dxl_wb.goalPosition(5, 7862);
delay(1000);
dxl_wb.goalPosition(1, 4404);
dxl_wb.goalPosition(2, 9896);
dxl_wb.goalPosition(3, 11409);
dxl_wb.goalPosition(4, 8201);
dxl_wb.goalPosition(5, 6861);
delay(1000);
dxl_wb.goalPosition(1, 4304);
dxl_wb.goalPosition(2, 9365);
dxl_wb.goalPosition(3, 11670);
dxl_wb.goalPosition(4, 8201);
dxl_wb.goalPosition(5, 6861);
delay(1000);
dxl_wb.goalPosition(1, 8304);
dxl_wb.goalPosition(2, 9365);
dxl_wb.goalPosition(3, 11670);
dxl_wb.goalPosition(4, 8201);
dxl_wb.goalPosition(5, 6861);
delay(4000);
dxl_wb.goalPosition(1, 8304);
dxl_wb.goalPosition(2, 9896);
dxl_wb.goalPosition(3, 11409);
dxl_wb.goalPosition(4, 8201);
dxl_wb.goalPosition(5, 6861);
delay(1000);
dxl_wb.goalPosition(1, 8304);
dxl_wb.goalPosition(2, 9896);
dxl_wb.goalPosition(3, 11409);
dxl_wb.goalPosition(4, 8201);
dxl_wb.goalPosition(5, 7862);
delay(1000);
dxl_wb.goalPosition(1, 8304);
dxl_wb.goalPosition(2, 9365);
dxl_wb.goalPosition(3, 11670);
dxl_wb.goalPosition(4, 8201);
dxl_wb.goalPosition(5, 7862);
delay(4000);
}  
