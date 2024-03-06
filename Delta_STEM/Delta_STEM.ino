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

#define vacuum_key 11
#define vacuum_pump 12

DynamixelWorkbench dxl_wb;

int f = 60;
int Rf = 90;
int Re = 168;
int e = 52;
float theta1, theta2, theta3, theta;
float y_1, y_2, y_3;
float x_1, x_2, x_3;
float m, n, k, v;


void coord(float a, float b)
{
  x_1 = a;
  y_1 = b;
  x_2 = a*cos(2.094) + b*sin(2.094);
  y_2 = b*cos(2.094) - a*sin(2.094);
  x_3 = a*cos(2.094) - b*sin(2.094);
  y_3 = b*cos(2.094) + a*sin(2.094);  
}

void find_angle(float x, float y, float z)
{
   float C1 = -0.5 * 0.57735 * f;
   y -= 0.5 * 0.57735 * e;
   float a = (x*x + y*y + z*z +Rf*Rf - Re*Re - C1*C1)/(2*z);
   float b = (C1-y)/z;
   float d = -(a+b*C1)*(a+b*C1)+Rf*(b*b*Rf+Rf);
   if(d < 0) 
      Serial.println("Error");
  
  float yj = (C1 - a*b - sqrt(d))/(b*b + 1); 
  float zj = a + b*yj;
  float angle = atan(-zj/(C1 - yj));
  theta = angle;
}



void full(float x0, float y0, float z0)
{
    coord(x0, y0);
    find_angle(x_1, y_1, z0);
    theta1 = theta;
    find_angle(x_2, y_2, z0);
    theta2 = theta;
    find_angle(x_3, y_3, z0); 
    theta3 = theta;
}

void set_pos( float p1 , float p2, float p3, int del)
// функция для задания угла поворота вала двигателя на манипуляторе в радианах
{
  dxl_wb.goalPosition(DXL_ID1,p1);
  dxl_wb.goalPosition(DXL_ID2,p2);
  dxl_wb.goalPosition(DXL_ID3,p3);
  delay(del);
}

void setup() 
{
  pinMode(vacuum_pump, OUTPUT);
  pinMode(vacuum_key, OUTPUT);
const char *log ;
Serial.begin(9600);
   
uint16_t model_number1 = 1;
uint16_t model_number2 = 2;
uint16_t model_number3 = 3;
dxl_wb.init(DEVICE_NAME, BAUDRATE, &log); 

dxl_wb.ping(DXL_ID1, &model_number1, &log);
dxl_wb.ping(DXL_ID2, &model_number2, &log);
dxl_wb.ping(DXL_ID3, &model_number3, &log);
dxl_wb.jointMode(DXL_ID1, 50, 0, &log);
dxl_wb.jointMode(DXL_ID2, 50, 0, &log);
dxl_wb.jointMode(DXL_ID3, 50, 0, &log);

}

void loop() {
 while (Serial.available() > 0 && Serial.read() == 'c') {
  m = Serial.parseInt();
  n = Serial.parseInt();
  k = Serial.parseInt();
  v = Serial.parseInt();
  Serial.print("X = " );
  Serial.println(m);
  Serial.print("Y = " );
  Serial.println(n);
  Serial.print("Z = " ); 
  Serial.println(k);
  if (k > 0)
  {
    k = 0;
    Serial.println("Z only negativ number");  
  }
  if (v == 1){
    Serial.println("Vacuum On" );
    digitalWrite(vacuum_pump, HIGH);
    digitalWrite(vacuum_key, HIGH);
  }
  else{
    Serial.println("Vacuum Off" );
    digitalWrite(vacuum_pump, LOW);
    digitalWrite(vacuum_key, LOW);
  }
  full(m, n, k);
  Serial.print("Angle #1: " );
  Serial.println(theta1);
  Serial.print("Angle #2: " );
  Serial.println(theta2);
  Serial.print("Angle #3: " );
  Serial.println(theta3);
  set_pos(theta1, theta2, theta3, 500);  
 
 }
}
