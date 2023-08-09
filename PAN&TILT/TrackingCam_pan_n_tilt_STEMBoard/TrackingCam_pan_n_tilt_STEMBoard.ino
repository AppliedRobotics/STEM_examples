// Управление сервоприводами с помощью OpenCM9.04
#include <DynamixelWorkbench.h> // Подключение библиотеки
// выставление скорости передачи данных, ID Устройств
#define BAUDRATE  1000000
#define CAM_ID    51      // DXL адрес камеры
// Контроллер OpenCM управляет сервоприводами через шину 3 на плате STEM Board
#define DEVICE_NAME "3"
#define DXL_ID    1
#define DXL_ID2   2

bool result = false;  // переменная-флаг считывания данных по DXL
int32_t pos_data = 0; // текущее положение сервопривода
int step_angle = 2;   // шаг передвижения для камеры

int degree_coeff = 16383/360; // число условных единиц положения в 1 градусе

// Структура для считывания данных с камеры
struct TrackingCamBlobInfo_t
{
  uint8_t type;
  uint8_t dummy;
  uint16_t cx;
  uint16_t cy;
  uint32_t area;
  uint16_t left;
  uint16_t right;
  uint16_t top;
  uint16_t bottom;
};

// Объявление доп. параметров
DynamixelWorkbench dxl_wb;
unsigned long previousMillis = 0; 
int cx;
int cy;
int pos  = 180*degree_coeff; // начальное положение сервопривода посередине 0...360
int posY = 180*degree_coeff;

// Функция начальной установки
void setup()
{
  // Инициализация камеры и сервоприводов
  Serial.begin(57600);
  while (!dxl_wb.init(DEVICE_NAME, BAUDRATE))
  {}
  while (!dxl_wb.ping(CAM_ID))
  {}
  while (!dxl_wb.ping(DXL_ID))
  {}
  while (!dxl_wb.ping(DXL_ID2))
  {}
  dxl_wb.jointMode(DXL_ID);
  dxl_wb.jointMode(DXL_ID2);
  // Устанавливаем сервоприводы в стартовые позиции
  dxl_wb.goalPosition(DXL_ID, pos);
  dxl_wb.goalPosition(DXL_ID2, posY);

  delay(5000);
}

// Функция бесконечного цикла
void loop()
{
  //Вывод положений сервоприводов в консоль
  for (int i=1; i<=2; i++)
  {
    result = dxl_wb.itemRead(i, "Present_Position", &pos_data); // Считываем позицию по DXL
    Serial.print("pos" + String(i) + " = " + String(pos_data/degree_coeff) + "; ");
    Serial.println();
  }
  
  // Блок работы с данными камеры:
  int max_n = 5;
  int n = 0;
  TrackingCamBlobInfo_t blob[10];
  for (int i = 0; i < max_n; i++)
  {
    uint32_t resp[16];
    if (!dxl_wb.readRegister(CAM_ID, 16 + i * 16, 16, resp))
      break;
      
    int idx = 0;
    blob[i].type = resp[idx++];
    if (blob[i].type == 0xFF)
      break;
    blob[i].dummy = resp[idx++];
    blob[i].cx = resp[idx] + (resp[idx + 1] << 8);
    idx += 2;
    cx = blob[i].cx;
    blob[i].cy = resp[idx] + (resp[idx + 1] << 8);
    idx += 2;
    cy = blob[i].cy;
    blob[i].area = (resp[idx] + (resp[idx + 1] << 8)) * 4;
    idx += 2;
    blob[i].left = resp[idx] + (resp[idx + 1] << 8);
    idx += 2;
    blob[i].right = resp[idx] + (resp[idx + 1] << 8);
    idx += 2;
    blob[i].top = resp[idx] + (resp[idx + 1] << 8);
    idx += 2;
    blob[i].bottom = resp[idx] + (resp[idx + 1] << 8);
    idx += 2;
    n++;
  }
  //Вывод данных камеры в консоль
  Serial.println("n = " + String(n));
  for (int i = 0; i < n; i++)
    Serial.print( String(blob[i].type) + " " + String(blob[i].cx) + " " + String(blob[i].cy) + " " +
                  String(blob[i].area) + " " + String(blob[i].left) + " " + String(blob[i].right) + " " +
                  String(blob[i].top) + " " + String(blob[i].bottom) + "\n");

  // Блок управления сервоприводами:
  if (n > 0) { // двигаемся, если камера видит объект
    
    if (cy < 70)// мин значение координаты У камеры для начала движения
    {
      dxl_wb.goalPosition(DXL_ID2, posY);// команда для движения вала сервопривода ID2 в координату posY
      posY = posY - step_angle*degree_coeff;// изменение координаты смещения вала привода
    }    
    else if (cy > 130)// макс значание координаты У камеры для начала движения
    {
      dxl_wb.goalPosition(DXL_ID2, posY);
      posY = posY + step_angle*degree_coeff;
    }  
    posY = constrain(posY, 90*degree_coeff, 270*degree_coeff); // ограничиваем углы поворота
  
    if (cx < 150)// мин значание координаты Х камеры для начала движения
    {
      dxl_wb.goalPosition(DXL_ID, pos);// команда для движения вала сервопривода ID1 в координату pos
      pos = pos + step_angle*degree_coeff;
    }    
    else if (cx > 200)// макс значание координаты Х камеры для начала движения
    {
      dxl_wb.goalPosition(DXL_ID, pos);
      pos = pos - step_angle*degree_coeff;
    }  
    pos = constrain(pos, 90*degree_coeff, 270*degree_coeff); // ограничиваем углы поворота
  
    while (millis() - previousMillis < 33)
    {};
    previousMillis = millis();
  }
}
