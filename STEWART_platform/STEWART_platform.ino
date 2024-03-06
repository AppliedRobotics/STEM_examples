#include <DynamixelWorkbench.h>
#include <math.h>

#if defined(__OPENCM904__)
  #define DEVICE_NAME "3" //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#elif defined(__OPENCR__)
  #define DEVICE_NAME ""
#endif  

#define BAUDRATE  1000000
#define DXL_ID1  1
#define DXL_ID2  2
#define DXL_ID3  3
#define DXL_ID4  4
#define DXL_ID5  5
#define DXL_ID6  6
DynamixelWorkbench dxl_wb;

float s = 211;
float a = 35;
float b = 100;
float p = 110;
float fi_b = 0.61;
float fi_p = 0.13;
float bx, by, px, py;
float R[3][3];

float alfa1 = 0;
float beta1 = 0;
float gama1 = 0; 
float x1;
float y_1;
float z1;

float angle0, angle1, angle2, angle3, angle4, angle5, angle6;

void set_pos( float p1 , float p2, float p3, float p4, float p5, float p6, int del)
{
  dxl_wb.goalPosition(DXL_ID1,p1);
  dxl_wb.goalPosition(DXL_ID2,p2);
  dxl_wb.goalPosition(DXL_ID3,p3);
  dxl_wb.goalPosition(DXL_ID4,p4);
  dxl_wb.goalPosition(DXL_ID5,p5);
  dxl_wb.goalPosition(DXL_ID6,p6);
  delay(del);
}


void matrix(float alfa, float beta, float gama)
{
  R[0][0] = cos(alfa)*cos(beta);
  R[1][0] = -sin(alfa)*cos(gama) + cos(alfa)*sin(beta)*sin(gama);
  R[2][0] = sin(alfa)*sin(gama) + cos(alfa)*sin(beta)*cos(gama);
  R[0][1] = sin(alfa)*cos(beta);
  R[1][1] = cos(alfa)*cos(gama) + sin(alfa)*sin(beta)*sin(gama);
  R[2][1] = -cos(alfa)*sin(gama) + sin(alfa)*sin(beta)*cos(gama);
  R[0][2] = -sin(beta);
  R[1][2] = cos(beta)*sin(gama);
  R[2][2] = cos(beta)*cos(gama);
 
}

void angle(float fi_b, float fi_p, float x, float y, float z)
{
 
  bx = b*cos(fi_b);
  by = b*sin(fi_b); 
  px = p*cos(fi_p);
  py = p*sin(fi_p); 
  float A = R[0][0]*px + R[1][0]*py;
  float B = R[0][1]*px + R[1][1]*py;
  float C = R[0][2]*px + R[1][2]*py ;
  A = A - bx + x;
  B = B - by + y;
  C = C + z;
  float l = sqrt(A*A + B*B + C*C);
  float L = l*l - s*s + a*a;
  float M = 2*a*l;
  float N = 2*a*(cos(fi_b)*(px - bx) + sin(fi_b)*(py - by));
  angle0 = -(asin(L/(sqrt(M*M + N*N))) - atan(N/M));
}
int32_t get_data = 0;
bool result;
void setup() 
{
  const char *log ;
  Serial.begin(9600);
  while(!Serial);
  uint16_t model_number = 0;
  dxl_wb.init(DEVICE_NAME, BAUDRATE, &log);
  for (int cnt = 1; cnt < 7; cnt++)
  {
    dxl_wb.ping( cnt, &model_number);
    dxl_wb.jointMode(cnt, 30, 0);
    dxl_wb.itemWrite(cnt, "Position_P_Gain", uint16_t(350));
    dxl_wb.itemWrite(cnt, "Position_I_Gain", uint16_t(0));
    dxl_wb.itemWrite(cnt, "Position_D_Gain", uint16_t(600)); 
  } 

}

void loop()
{
 if (Serial.available() > 0 && Serial.read() == 'c') {
  x1 = Serial.parseInt();
  y_1 = Serial.parseInt();
  z1 = Serial.parseInt();
  alfa1 = Serial.parseInt();
  beta1 = Serial.parseInt();
  gama1 = Serial.parseInt();
Serial.print("X = " );
Serial.println(x1);
Serial.print("Y = " );
Serial.println(y_1);
Serial.print("Z = " ); 
Serial.println(z1);
Serial.print("Alfa = " ); 
Serial.println(alfa1);
Serial.print("Beta = " ); 
Serial.println(beta1);
Serial.print("Gamma = " ); 
Serial.println(gama1);
alfa1 = alfa1*3.14/180;
beta1 = beta1*3.14/180; 
gama1 = gama1*3.14/180;
matrix(alfa1, beta1, gama1);

 angle(0.61, 0.13, x1, y_1, z1);
   angle1 = angle0;

  angle(1.48, 1.95, x1, y_1, z1);
   angle2 = -angle0;


  angle(2.7, 2.22, x1, y_1, z1);
   angle3 = angle0;


  angle(3.58, 4.04, x1, y_1, z1);
   angle4 = -angle0;


  angle(4.8, 4.31, x1, y_1, z1);
   angle5 = angle0;


  angle(5.6, 6.13, x1, y_1, z1);
   angle6 = -angle0;
Serial.print("Angle #1: " );
Serial.println(angle1);
Serial.print("Angle #2: " );
Serial.println(angle2);
Serial.print("Angle #3: " );
Serial.println(angle3);
Serial.print("Angle #4: " );
Serial.println(angle4);
Serial.print("Angle #5: " );
Serial.println(angle5);
Serial.print("Angle #6: " );
Serial.println(angle6);
 set_pos(angle1, angle2, angle3, angle4, angle5, angle6, 50);
}
}
