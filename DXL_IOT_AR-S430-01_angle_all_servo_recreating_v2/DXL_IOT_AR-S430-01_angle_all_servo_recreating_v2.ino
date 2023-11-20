// Воспроизведение записанных позиций

// https://github.com/AppliedRobotics/dxlmaster2
#include "DxlMaster2.h"  // подключение библиотеки Dynamixel

#define BAUDRATE  1000000   // скорость передачи данных
#define DEBUG_SERIAL Serial // последовательный порт, подключаемый к компьютеру
#define jointN 6           // инициализация константы, обозначающей количество сервоприводов
#define num_pages 9        // задание количества строк массива
int i = 0;                 // задание переменной-счетчика i
int j = 0;                 // задание переменной-счетчика j

const float DXL_PROTOCOL_VERSION = 2.0; // протокол передачи данных от DXL IOT к сервоприводам

// Массив для доступа ко всем сервоприводам с адресом DXL в скобках
DynamixelMotor motors[] = {
  DynamixelMotor(1), DynamixelMotor(2), DynamixelMotor(3),
  DynamixelMotor(4), DynamixelMotor(5), DynamixelMotor(6)
};

uint16_t pos; // текущая позиция сервопривода
int buf[num_pages][jointN]={             // инициализация двумерного массива размером 9 на 6
  {8192, 8192, 8192, 11000, 8192, 8192, },
  
{8192, 7400, 8000, 11000, 8192, 8192, },
{8192, 7400, 8000, 11000, 8192, 6000, },
{8192, 7400, 6700, 12000, 8192, 6000, },
{4200, 7400, 6700, 12000, 8192, 6000, },
{4200, 7400, 8000, 11000, 8192, 6000, },
{4200, 7400, 8000, 11000, 8192, 8192, },
{4200, 7400, 6700, 12000, 8192, 8192, },
{8192, 7400, 6700, 12000, 8192, 8192, },
};

// Задание ПИД уставок:
#define P_Gain_Pos_addr 84
#define I_Gain_Pos_addr 82
#define D_Gain_Pos_addr 80
#define param_len 2
#define TIMEOUT 10
uint16_t P_Pos_param = 50;     // 640
uint16_t I_Pos_param = 0;       // 0
uint16_t D_Pos_param = 400;    // 4000


void setup() {
  
  DxlMaster.begin(BAUDRATE);    // установка скорости обмена данными по последовательному порту манипулятора

  for (i=0; i<jointN; i++)      // цикл с изменением i от 0 до jointN-1 с шагом 1
    motors[i].protocolVersion(DXL_PROTOCOL_VERSION); // выбор протокола обмена данными

  for (i=0; i<jointN; i++)     // цикл для перебора всех сервоприводов
  {
    motors[i].enableTorque(0);  // отключаем крутящий момент, когда изменяем EEPROM область в сервоприводе
    motors[i].write(DYN2_ADDR_OPERATION_MODE, (uint8_t)3); // установка режима работы сервопривода в качестве шарнира = 3
    motors[i].write(DYN2_ADDR_PROFILE_VELOCITY, (uint16_t)100); // установка скорости передвижения сервопривода
    // установка параметров ПИД регулятора по номеру регистра:
    motors[i].write(P_Gain_Pos_addr, (uint16_t)P_Pos_param);
    motors[i].write(I_Gain_Pos_addr, (uint16_t)I_Pos_param);
    motors[i].write(D_Gain_Pos_addr, (uint16_t)D_Pos_param);
  }
  delay(3000);
}

void loop() {
  for (i=0; i<num_pages; i++)  // цикл с изменением i от 0 до num_pages-1 с шагом 1
  {
    for(j=0; j<jointN; j++)  // цикл с изменением j от 0 до jointN-1 с шагом 1
    {
        motors[j].enableTorque(1);
        motors[j].goalPosition(buf[i][j]);  // задание целевого положения сервоприводу, получаемого из элемента ([i],[j])
        delay(50);
    }

    delay(3000);
  }
}
