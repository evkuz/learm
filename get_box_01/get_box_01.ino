#include <Servo.h>


Servo servo1, servo2, servo3,servo4,servo5,servo6;

int S4_pos, S5_pos;
int *s1, *s2, *s3, *s4, *s5, *s6;

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
  // put Learm to initial pozition
  servo1.attach(2);
  servo2.attach(3);
  servo3.attach(4);
  servo4.attach(5);
  servo5.attach(6);
  servo6.attach(7);

  start_pozition();
  
}
//++++++++++++++++++++++++ loop 
void loop() {
  // put your main code here, to run repeatedly:
  
  start_pozition();
  delay(1000);
  S4_pos = servo4.read();
  S5_pos = servo5.read();
  sit_down_pozition (S4_pos,S5_pos);
  delay(2500);
  horse_stand();
  delay(2000);

  S4_pos = servo4.read();
  S5_pos = servo5.read();
  
  horse_drink(S4_pos, S5_pos);
  
 // servo2.write(180);
 // delay(2000);
//  servo2.write(0);
//  delay(2000);
  S4_pos = servo4.read();
  S5_pos = servo5.read();
 // stand_up_pozition(S4_pos, S5_pos);
 // delay(2500);
 // clamp(servo1.read());
 clamp_open();
 delay(1500);
 servo5.write(servo5.read() +10);
 clamp_catch();
 delay(1500);
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

}//sit_down_pozition(
//+++++++++++++++++++++++++++++++++++
  /* Прибавляем градус по 1 45 раз.
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
 *s1 = servo1.read();
 *s2 = servo2.read();
 *s3 = servo3.read();
 *s4 = servo4.read();
 *s5 = servo5.read();
 *s6 = servo6.read();
}

//+++++++++++++++++++++++++++++++++++

/* Определяем текущую позицию и ПЛАВНО переходим в позицию get_1

*/
void get_1_box_position(void)
{
  get_all_servos();
  int s5_delta;

  if (*s5 > GET_1_S5)
  {
    s5_delta = *s5 - GET_1_S5;
   }
  else
  { s5_delta = GET_1_S5 - *s5;
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

/*void move_sero (Servo srv, *srv_ptr, int delta, int direction)
{
  int fin;
  fin = *srv_ptr + delta;
  for (int i=0; i<=fin; i++)
  {
    
    }
  
  }

*/
