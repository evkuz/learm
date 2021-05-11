#include <Servo.h>


Servo servo1, servo2, servo3,servo4,servo5,servo6;

int S4_pos, S5_pos;

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
  servo2.write(180);
  delay(2000);
  servo2.write(0);
  delay(2000);
  S4_pos = servo4.read();
  S5_pos = servo5.read();
  stand_up_pozition(S4_pos, S5_pos);
  delay(2500);
  clamp(servo1.read());
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
/*
  clamp_cur = clamp_angle;
  if (clamp_cur <60)
    {
      servo1.write(60);
      delay(1500);
      servo1.write(180);
      }
   else {
         servo3.write(180); 
         delay(1500);   
   }
*/  
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
  s3_pos=servo3.read();
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


  

  }
