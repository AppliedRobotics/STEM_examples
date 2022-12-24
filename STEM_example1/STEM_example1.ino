#include <DynamixelWorkbench.h> // подключение библиотеки для работы с приводами

#if defined(__OPENCM904__)
  #define DEVICE_NAME "3" // Номер порта USART для работы с приводами 
#endif   

#define BAUDRATE  1000000 // Скорость передачи данных на приводы 

int PRES_POS1 = 512; // Переменная для хранения значения энкодера 1 привода
int PRES_POS2 = 512; // Переменная для хранения значения энкодера 2 привода
int PRES_POS3 = 512; // Переменная для хранения значения энкодера 3 привода
int PRES_POS4 = 797; // Переменная для хранения значения энкодера 4 привода
int PRES_POS5 = 512; // Переменная для хранения значения энкодера 5 привода
int PRES_POS6 = 460; // Переменная для хранения значения энкодера 6 привода

DynamixelWorkbench servo; // Объявление структуры servo для работы с приводами

void setup() 
{
  const char *log; // переменная для хранения журнала ошибок
  uint16_t model_number = 0; // номер модели привода для инициализации

 servo.init(DEVICE_NAME, BAUDRATE, &log); // инифиализация структуры servo
 for (int i = 0; i <= 6; i++) // цикл для опроса и установки режима работы приводов
  {
    servo.ping(i, &model_number, &log); // опрос привода
    servo.jointMode(i, 0, 0, &log); // установка режима работы joint(управление по положению)
  }

 servo.goalPosition(1, PRES_POS1); // установка начальной позиции 1 привода
 servo.goalPosition(2, PRES_POS2); // установка начальной позиции 2 привода
 servo.goalPosition(3, PRES_POS3); // установка начальной позиции 3 привода
 servo.goalPosition(4, PRES_POS4); // установка начальной позиции 4 привода
 servo.goalPosition(5, PRES_POS5); // установка начальной позиции 5 привода
 servo.goalPosition(6, PRES_POS6); // установка начальной позиции 6 привода
 delay(1000); // задержка перед началом цикла 
 
}

void loop() 
{
 int vel = 10; // коэффицент скорости перемещения манипулятора 
 posz(100,1,vel); posy(60,0,vel);  posx(60,1,vel); //! подъём на безопасную высоту и перемещение на точку 1
 posz(30,0,vel);  grip(250,1,vel);                 //0 перемещение на рабочую высоту и захват объекта
 posz(30,1,vel);  posy(120,1,vel);                 //! подъём на безопасную высоту и перемещение на точку 2
 posz(30,0,vel);  grip(250,0,vel);                 //0 перемещение на рабочую высоту и отпускание объекта
 posz(30,1,vel);  posx(60,0,vel);  posy(60,0,vel);  posz(100,0,vel); //! перемещение в стартовую позицию
 delay(1000);                                      //0 пауза 1 секунда
 posz(100,1,vel); posy(60,1,vel);  posx(60,1,vel); //! подъём на безопасную высоту и перемещение на точку 2
 posz(30,0,vel);  grip(250,1,vel);                 //0 перемещение на рабочую высоту и захват объекта
 posz(30,1,vel);  posy(120,0,vel);                 //! подъём на безопасную высоту и перемещение на точку 1
 posz(30,0,vel);  grip(250,0,vel);                 //0 перемещение на рабочую высоту и отпускание объекта
 posz(30,1,vel);  posx(60,0,vel);  posy(60,1,vel);  posz(100,0,vel); //! перемещение в стартовую позицию
 delay(1000);                                      // пауза 1 секунда
}









void posx(int _angle, bool _dir, int _speed) // Функция управления координатой X
  {
    if (_dir == true)
    {
      for (int count = 0; count < _angle; count++)
        {
          PRES_POS2= PRES_POS2 + 2;
          PRES_POS3= PRES_POS3 - 2;
          PRES_POS4--;
          servo.goalPosition(2,PRES_POS2);
          servo.goalPosition(3,PRES_POS3);
          servo.goalPosition(4,PRES_POS4);
          delay(_speed);
        }
    }
    else
    {
      for (int count = _angle; count > 0; count--)
        {
          PRES_POS2= PRES_POS2 - 2;
          PRES_POS3= PRES_POS3 + 2;
          PRES_POS4++;
          servo.goalPosition(2,PRES_POS2);
          servo.goalPosition(3,PRES_POS3);
          servo.goalPosition(4,PRES_POS4);
          delay(_speed);
        }
    }
  }

void posy(int _angle, bool _dir, int _speed) // Функция управления координатой Y
  {
    if (_dir == true)
    {
      for (int count = 0; count < _angle; count++)
        {
          PRES_POS1++;
          PRES_POS5++;
          servo.goalPosition(1,PRES_POS1);
          servo.goalPosition(5,PRES_POS5);
          delay(_speed);
        }
    }
    else
    {
      for (int count = _angle; count > 0; count--)
        {
          PRES_POS1--;
          PRES_POS5--;
          servo.goalPosition(1,PRES_POS1);
          servo.goalPosition(5,PRES_POS5);
          delay(_speed);
        }
    }
  }

void posz(int _angle, int _dir, int _speed) // Функция управления координатой Z
  {
    if (_dir == 0)
    {
      for (int count = 0; count < _angle; count++)
        {
          PRES_POS3++;
          PRES_POS4--;
          servo.goalPosition(3,PRES_POS3);
          servo.goalPosition(4,PRES_POS4);
          delay(_speed);
        }
    }
    if (_dir == 2)
    {
      for (int count = 0; count < _angle; count++)
        {
          PRES_POS3++;
          PRES_POS4++;
          servo.goalPosition(3,PRES_POS3);
          servo.goalPosition(4,PRES_POS4);
          delay(_speed);
        }
    }
    if (_dir == 1)
    {
      for (int count = _angle; count > 0; count--)
        {
          PRES_POS3--;
          PRES_POS4++;
          servo.goalPosition(3,PRES_POS3);
          servo.goalPosition(4,PRES_POS4);
          delay(_speed);
        }
    }
  }

void grip(int _angle, bool _dir, int _speed) // Функция управления схватом
  {
    if (_dir == true)
    {
      for (int count = 0; count < _angle; count++)
        {
          PRES_POS6++;
          servo.goalPosition(6,PRES_POS6);
          delay(_speed);
        }
    }
    if (_dir == false)
    {
      for (int count = _angle; count > 0; count--)
        {
          PRES_POS6--;
          servo.goalPosition(6,PRES_POS6);
          delay(_speed);
        }
    }
  }
