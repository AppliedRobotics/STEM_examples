#include <Dynamixel2Arduino.h>  // подключение библиотеки Dynamixel

// Последовательный порт DXL для платы STEM с OpenCM 9.04. (Если использовать DXL порт на самой плате OpenCM 9.04, то нужно использовать Serial1, и из-за кода в драйвере, необходимо перед dxl.begin() вызвать Serial1.setDxlMode(true).)
#define DXL_SERIAL   Serial3
#define DEBUG_SERIAL Serial // последовательный порт, подключаемый к компьютеру

const uint8_t DXL_DIR_PIN = 22; // номер информационного пина сервоприводов (28 для OpenCM 9.04)
const float DXL_PROTOCOL_VERSION = 2.0; // протокол передачи данных от OpenCM9.04 к сервоприводам

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN); // инициализация указателя на команды из библиотеки Dynamixel

float pi = 3.14159265; // задание константы Пи
float rad2ticks = 2*pi / 16383; // перевод из радиан (0...360 градусов) в условные угловые единицы (0...16383)
float degree_coeff = 16383.0 / 360; // количество условных угловых единиц на 1 градус поворота

#define jointN 5  // задание количества сервоприводов

int pos = 0; // инициализация переменной для начального положения сервопривода
bool input_coords = true;  // флаг для печати строки ввода координат в последовательный порт
int start_pos[jointN+1];   // инициализация одномерного массива для положений, размер его задается 5+1=6, 
int cur_pos[jointN+1];   // т.к. нулевой элемент мы использовать не будем, так как начнем с первого

int i = 0;   // счетчик цикла
int alphas[jointN+1]; // массив целевых угловых позиций 1-5 сервоприводов (в условных единицах)

float X; // желаемое положение схвата по оси X (в метрах)
float Y; // желаемое положение схвата по оси Y (в метрах)
float Z; // желаемое положение схвата по оси Z (в метрах)
float x; // положение по оси X относительно 2 и 3 звеньев (в метрах)
float y; // положение по оси Y относительно 2 и 3 звеньев (в метрах)
float z; // положение по оси Z относительно 2 и 3 звеньев (в метрах)
float xf; // расчетное положение по оси X относительно 2 и 3 звеньев (в метрах)
float yf; // расчетное положение по оси Y относительно 2 и 3 звеньев (в метрах)
float zf; // расчетное положение по оси Z относительно 2 и 3 звеньев (в метрах)

float d; // вспомогательная расчетная величина - расстояние от основания манипулятора до схвата
float betta_d; // вспомогательная расчетная величина - угол между осью X и d
float gamma_d; // вспомогательная расчетная величина - угол между звеном 2 и d
float alpha1;     // целевая угловая позиция 1 сервопривода (в радианах)
float alpha2;     // целевая угловая позиция 2 сервопривода (в радианах)
float alpha3;     // целевая угловая позиция 3 сервопривода (в радианах)
float alpha4;     // целевая угловая позиция 4 сервопривода (в радианах)
float alpha5;     // целевая угловая позиция 5 сервопривода (в радианах)


float l1 = 0.05;  // длина условного 1 звена (в метрах)
float l2 = 0.14;  // длина условного 2 звена (в метрах)
float l3 = 0.14;  // длина условного 3 звена (в метрах)
float l4 = 0.07;  // длина условного 4 звена (в метрах)
float l5 = 0.02;  // длина условного 5 звена (в метрах)


void setup() {
  
  DEBUG_SERIAL.begin(57600); // установка скорости обмена данными по последовательному порту компьютера
  dxl.begin(1000000);        // установка скорости обмена данными по последовательному порту манипулятора
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);  // выбор протокола обмена данными

  for (i=1; i<=jointN; i++)  // цикл с изменением i от 1 до 5 с шагом 1
  {
    dxl.torqueOff(i); // отключаем момент, когда изменяем EEPROM область в сервоприводе
    dxl.setOperatingMode(i, OP_POSITION); // установка режима работы сервопривода с номером i в качестве шарнира
  }
  delay(5000);
  for (i=1; i<=jointN; i++)
  {
    start_pos[i] = int(180 * degree_coeff); // установка начальных положений по центру диапазона 0...360 градусов
    dxl.torqueOn(i);  // включаем момент сервопривода для удержания целевого положения
  }
  move_servos(40, start_pos); // перемещаем манипулятор в стартовую позицию
  delay(2000);  
}

void loop() {
  
  if (input_coords) {
    DEBUG_SERIAL.println("Введите координаты цели x,y,z в сантиметрах через пробел:");
    input_coords = false;
  }

  if (DEBUG_SERIAL.available()) {
    //  X = 0.15; //>=l4
    //  Y = 0.0;  //0.0       ///// ЗДЕСЬ НЕОБХОДИМО ЗАДАВАТЬ ТРЕБУЕМОЕ ПОЛОЖЕНИЕ МАНИПУЛЯТОРА
    //  Z = 0.07;             ///// (ИЛИ В SERIAL ПОРТЕ)
    parse_input(DEBUG_SERIAL.readString()); // cчитываем из Serial порта координаты X,Y,Z
  
    // Переходим в систему координат относительно 2 и 3 звеньев:
    alpha1 = atan(Y / X); // угол поворота 1-го звена альфа 1
    z = Z - l1 + l5;  // учитываем длины вертикальных звеньев для целевой координаты Z
    x = max(l4, X - l4); // пересчет целевой координаты X
    
    DEBUG_SERIAL.print("x = "); DEBUG_SERIAL.println(x); // строки для отладки
    DEBUG_SERIAL.print("y = "); DEBUG_SERIAL.println(y);
    DEBUG_SERIAL.print("z = "); DEBUG_SERIAL.println(z);
    DEBUG_SERIAL.print("alpha1 = "); DEBUG_SERIAL.println(alpha1);
    
    d = sqrt(x*x + z*z);  // вычисление вспомогательного коэффициента d
    // Прежде чем найти нужные углы, найдем побочные betta_d и gamma_d:
    gamma_d = acos((l2*l2 + d*d - l3*l3)/(2*l2*d));
    betta_d = atan(z / x);
    alpha2 = pi/2 - gamma_d - betta_d; // вычисление угла альфа 2
    
    alpha3 = pi - acos((l2*l2 + l3*l3 - d*d)/(2*l2*l3)); // вычисление угла альфа 3
    alpha3 = alpha3 - (pi/2 - alpha2); // пересчет в целевое положение 3 сервопривода (учитывается альфа 2)
    
    xf = cos(alpha1)*(l2*sin(alpha2) + l3*sin(pi-alpha3-alpha2));
    yf = sin(alpha1)*(l2*sin(alpha2) + l3*sin(pi-alpha3-alpha2));
    zf = l2*cos(alpha2) - l3*cos(pi-alpha3-alpha2);
    DEBUG_SERIAL.print("xf = "); DEBUG_SERIAL.println(xf); // строки для отладки
    DEBUG_SERIAL.print("yf = "); DEBUG_SERIAL.println(yf);
    DEBUG_SERIAL.print("zf = "); DEBUG_SERIAL.println(zf);
    delay(1000);
    
    alpha4 = 0; // углы альфа4 и альфа5 принимаются нулевыми
    alpha5 = 0; // фактически, если разобраться, альфа - это угол отклонения следующего звена от предыдущего
  
    alphas[1] = start_pos[1] + int(alpha1/rad2ticks); // пересчет в целевое положение 1 сервопривода
    alphas[2] = start_pos[2] + int(alpha2/rad2ticks); // пересчет в целевое положение 2 сервопривода
    alphas[3] = start_pos[3] + int(alpha3/rad2ticks); // пересчет в целевое положение 3 сервопривода
    alphas[4] = start_pos[4] + int(alpha4/rad2ticks); // пересчет в целевое положение 4 сервопривода
    alphas[5] = start_pos[5] + int(alpha5/rad2ticks); // пересчет в целевое положение 5 сервопривода

    move_servos(40, alphas); // перемещаем манипулятор в целевую позицию

    delay(1000);
    input_coords = true;
  }
}

// Разделяет строку по пробелам на числа float.
void parse_input(String str) {
  int separator = str.indexOf(' '); // ищем первый пробел в строке:
  X = str.substring(0, separator).toInt()/100.0; // переводим строку из сантиметров в метры
  int separator2 = str.indexOf(' ', separator+1); // ищем второй пробел
  Y = str.substring(separator+1, separator2).toInt()/100.0;
  Z = str.substring(separator2).toInt()/100.0;
}

// Устанавливает целевые положения и пошагово перемещает сервоприводы.
void move_servos(int delay_ms, int* pos) {

  int diff = 100*degree_coeff; // разница позиций
  int dir; // направление движения
  int step_degree = 3; // шаг в градусах

  while (diff/degree_coeff > step_degree) { // выполняется пока разница позиций больше шага
    for (i=1; i<=jointN; i++)
    {
      cur_pos[i] = dxl.getPresentPosition(i); // получение текущей позиции сервопривода с номером i
      if (abs(cur_pos[i] - pos[i]) > 0.7*step_degree*degree_coeff) { // двигаем сервопривод, если он еще далеко от цели
        dir = (pos[i]-cur_pos[i])<0 ? -1 : 1;     // считаем направление (если <0, то dir=-1)
        dxl.setGoalPosition(i, cur_pos[i] + int(step_degree*dir*degree_coeff)); // делаем шаг
      }
      else
        dxl.setGoalPosition(i, pos[i]);
    }
    delay(delay_ms); // задержка выполнения

    diff = 0;
    for (i=1; i<=jointN; i++)
      diff = max(diff, abs(cur_pos[i] - pos[i])); // нахождение максимальной разницы позиций
  }
  
}
