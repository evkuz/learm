#include <Servo.h>
#include "hiwonder.h"

#include <stdlib.h>

Servo servo1, servo2, servo3, servo4, servo5, servo6;

Servo servos [6] = {servo1, servo2, servo3,servo4,servo5,servo6};

int S4_pos, S5_pos;
int *s1, *s2, *s3, *s4, *s5, *s6;
byte current_s [6];
byte delta [6];
//String message, number;//, s_pos;
char *s_pos;

#define GET_1_S1_OPEN 60
#define GET_1_S1_CLOSE 30

#define GET_1_S2 90 // всегда в этой позиции
#define GET_1_S3 5  // самый низ
#define GET_1_S4 15
#define GET_1_S5 15
/*
Список позиций
get_1 - взять в точке 1

*/


void setup() {
  Serial.begin(115200);
  // put Learm to initial pozition
  servo1.attach(2);
  servo2.attach(3);
  servo3.attach(4);
  servo4.attach(5);
  servo5.attach(6);
  servo6.attach(7);

  start_pozition();
  get_curr_delta(hwr_Start_position);

  
}
//++++++++++++++++++++++++ loop 
void loop() {
  //start_pozition();
  start_position ();

  delay(1000);
  //S4_pos = servo4.read();
  //S5_pos = servo5.read();

  //sit_position(sit_down_position); // Print out array values passed by pointer

  //sit_down_pozition (S4_pos,S5_pos);
  //get_all_servos();

  //move_servo(sit_down_position);

  move_servo_together(sit_down_position);
  //delay(2500);
  //horse_stand();
  delay(1000);

 // S4_pos = servo4.read();
  ///S5_pos = servo5.read();
  /*Кривой вариант
   * message = "Servo 4 ";
  itoa(S4_pos, s_pos, 15);  
  message += s_pos;
  Serial.println(message);
*/
 // message = "Servo 4 ";
  // Так тоже можно
  //number = String (S4_pos);
  //message += number;

  // И так можно
 // message += String (S4_pos);
 // Serial.println(message);
  
 //  print_servos_2_serial();
  //horse_drink(S4_pos, S5_pos);
  
 // servo2.write(180);
 // delay(2000);
//  servo2.write(0);
//  delay(2000);
//  S4_pos = servo4.read();
 // S5_pos = servo5.read();
 // stand_up_pozition(S4_pos, S5_pos);
 // delay(2500);
 // clamp(servo1.read());
 clamp_open();
 delay(1000);
 servo5.write(servo5.read() +10);
 clamp_catch();
 delay(1000);
}//loop
//++++++++++++++++++++++++++++++++++ start 
// А вообще, на будущее, надо чтобы сначала считывала текущую позицию и 
// и на основании этого вычисляла количество шагов, чтобы было плавное 
// позиционирование в начальную позицию.
void start_pozition()
{
  servo1.write(90);
  delay(10);
  servo2.write(90);
  delay(10);
  servo3.write(90);
  delay(10);
  servo4.write(90);
  delay(10);
  servo5.write(90);
  delay(10);
  servo6.write(90);
  delay(10);
  
}//start_pozition


//+++++++++++++++++++++++++++ start_position with header

void start_position ()
{
  servo1.write(hwr_Start_position[0]);
  delay(10);
  servo2.write(hwr_Start_position[1]);
  delay(10);
  servo3.write(hwr_Start_position[2]);
  delay(10);
  servo4.write(hwr_Start_position[3]);
  delay(10);
  servo5.write(hwr_Start_position[4]);
  delay(10);
  servo6.write(hwr_Start_position[5]);
  delay(10);


}// start_posotion
//+++++++++++++++++++++++++++ sit_down
//Присаживаем. Предположительно из начальной позиции
void sit_down_pozition(int s4_pos, int s5_pos)
{
  int i;
  

  for (int i = 0; i <= 44; i++) {
    s5_pos -= 1; 
    s4_pos -= 1;
    servo5.write(s5_pos);
    delay(15);
    servo4.write(s4_pos);
    delay(15);
    
  }

}//sit_down_pozition
//+++++++++++++++++++++++++++++++++++

void sit_position(byte *pos)
{
String message;
  
  get_all_servos(); //Получили текущие значения приводов.
                    // Целевые значения в массиве 

  for (int i=0; i <= 5; i++)
  {
   message += "Servo ";
   message += String(i+1); message += " ";
   message += String(pos[i]); message +=", ";
  }

}//sit_position

//+++++++++++++++++++++++++++++++++++
  /* Прибавляем градус по 1-у 45 раз.
  Предполагается, что встаем из сидячего положения 
  */
void stand_up_pozition(int s4_pos, int s5_pos)
{
  int i;
  

  for (int i = 0; i <= 44; i++) {
    s5_pos += 1; 
    s4_pos += 1;
    servo5.write(s5_pos);
    delay(15);
    servo4.write(s4_pos);
    delay(15);
  }

}//stand_up_pozition

//++++++++++++++++++++++
/* Клацаем захватом
*/
void clamp (int clamp_angle)
{
  int clamp_cur;
  servo1.write(45);
  delay(1500);
  servo1.write(180);
  delay(1500);
}//clamp

//+++++++++++++++++++++++++++++++
void clamp_open(void)
{
  servo1.write(45);
//  delay(1500);

  }

//++++++++++++++++++++++++++++++
void clamp_catch(void)
{
    servo1.write(180);
  }  
//+++++++++++++++++++++++++++++++
/* Принимаем позу шахматного коня 
*/
void horse_stand(void)
{
  int i;
  int s3_pos;

  s3_pos=servo3.read();
  for (int i = 0; i <= 89; i++) {
  
  servo3.write(s3_pos -i);
  delay(10);
  }//for
  delay(1500);
  //++++++++ go back
 /* s3_pos=servo3.read();
   for (int i = 0; i <= 89; i++) {
  
  servo3.write(s3_pos +i);
  delay(10);
  }//for
   delay(1500);
 //++++++++++++++++++ More angulation
 
   s3_pos=servo3.read();
   for (int i = 0; i <= 89; i++) {
  
  servo3.write(s3_pos +i);
  delay(10);
  }//for
*/
} // horse_stand

//+++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++
/*
Получить значения углов для всех приводов
*/
void get_all_servos(void)
{
    String message;
/* current_s[0] = servo1.read();
 current_s[1] = servo2.read();
 current_s[2] = servo3.read();
 current_s[3] = servo4.read();
 current_s[4] = servo5.read();
 current_s[5] = servo6.read();
 */
    for (int i=0; i<=5; i++)
    {

      current_s[i] = servos[i].read();
 /*     message = "Current servo ";
      message += String(i); message += " position ";
      message += String(current_s[i]); //servos[i].read()
      Serial.println(message);
*/
    }
}

//+++++++++++++++++++++++++++++++++++
/* 
  Задаем значения приращения угла и направление для всех приводов для текущей и целевой позиции
*/
void get_curr_delta (byte *pos)
{

  for (int i=0; i<=5; i++)
  {
    if (current_s[i] > pos[i])
      {
       delta[i] = current_s[i] - pos[i];
       DF[i] = -1;
      }
    else
      {
        delta[i] = pos[i] - current_s[i];
       DF[i] = 1;
      }

  }//for


}







/* Определяем текущую позицию и ПЛАВНО переходим в позицию get_1

*/
void get_1_box_position(void)
{
  get_all_servos();
  int s5_delta;
  int df ;  // direction_flag

  if (*s5 > GET_1_S5) // Текущая позиция больше, чем целевая
  {
    s5_delta = *s5 - GET_1_S5;
    DF[4] = -1; // Т.е. идем в обратном направлении
   }
  else               // Текущая позиция меньше, чем целевая, идем в прямом направлениии
  { s5_delta = GET_1_S5 - *s5;
    DF[4]=1;
    }
  
}//get_1_box_position

//++++++++++++++++
void horse_drink(int s4_pos, int s5_pos)
{
  int i;
  

  for (int i = 0; i <= 89; i++) {
    s5_pos += 1; 
  //  s4_pos += 1;
    servo5.write(s5_pos);
    delay(15);
 //   servo4.write(s4_pos);
 //   delay(15);
    
  }
 // delay(1000);
  

}//horse_drink


//+++++++++++++++++++++++++
/*

Каждый серво отрабатывает свою позицию отдельно, что не есть гуд.
Нут плавного движения, когда одновременно 2 серво двигаются.
*/
void move_servo (byte *pos) // address of position array and direction flag array, текущую позицию вычисляем
{
  int s_pos;

  get_all_servos();
  get_curr_delta(pos);


  
  for (int i=0; i<=5; i++)
  {
    s_pos = current_s[i];

    for (int j=0; j<=delta[i] -1; j++)
    {
     s_pos = s_pos + 1*DF[i];
     servos[i].write(s_pos);
     delay(15);
    }
    
    }
  
}
//+++++++++++++++++++++++++++++++++++

/*
Алгоритм :
Берем самое большое delta и задаем как счетчик цикла внешнего
А внутри перебираем все приводы - каждый со своей дельтой.
Берем снова самое большое и т.д.


*/
void move_servo_together (byte *pos) // address of position array and direction flag array, текущую позицию вычисляем
{
  int s_pos, maxdt;
  String message;
  get_all_servos();
  get_curr_delta(pos);
  maxdt = get_max_delta(delta); // индекс в массиве delta
  message = "Servo index with max delta is ";
  message += String(maxdt);
  Serial.println(message);

  message = "Max delta value is ";
  message += String(delta[maxdt]);

  Serial.println(message);

for (int dt=0; dt <= (delta[maxdt] -1); dt++)
{
    message = "Current Max delta value is ";
    message += String(delta[maxdt]);
    Serial.println(message);

  for (int i=0; i<=5; i++) // ОБходим все приводы
  {
    s_pos = servos[i].read();
    message = "Current servo ";
    message += String(i); message += " position ";
    message += String(servos[i].read());
    message += " and delta is "; message += String(delta[i]);
    Serial.println(message);

// Почему-то заканчивает на 23...

    if (delta[i] !=0)
    {
      s_pos = s_pos + DF[i];
      servos[i].write(s_pos);
      delta[i] -= 1;
     // delay(15);
      message = "changed position, delta is ";
      message += String(DF[i]);
      Serial.println("changed position");

    }
    
  }//for int i=0
}  //int dt=0;
}//move_servo_together

//++++++++++++++++++++
/*Возвращает индекс макисмального элемента в массиве delta*/
byte get_max_delta (byte *arr)
{
  int maxdelta, index;
  maxdelta=0;
  index=0;
  for (int i=0; i<=5; i++)
  {
    if (arr[i] > maxdelta)
    {
      maxdelta = arr[i];
      index = i;
    }

  }//for

return index;
} //get_max_delta
//++++++++++++++++++++++++++
void print_servos_2_serial()
{
  String message;
  get_all_servos();

  message = "";
  for (int i=0; i <= 5; i++)
  {
   message += "Servo ";
   message += String(i+1); message += " ";
   message += String(current_s[i]); message +=", ";
  }

  Serial.println(message);
}//print_servos_2_serial
