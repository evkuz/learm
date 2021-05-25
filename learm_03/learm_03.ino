/*
 * learm_03.ino
 * Двигаемся дальше. Добавляем фиксированные команды.
 * Т.е. из начального положения - взять предмет и переместить.
 * Обнаружилась проблема с парсером строки, приходящей из ПК.
 * Перехожу к следующему проекту, чтобы этот сохранился.
 *
 * learm_02.ino
 * Настриваем прием, парсинг и выполнение команд от serial порта. [сделано 24.05.2021]
 * 
 * learm_01.ino
 * Готовая база для развития проекта
 * Роботу надо сообщать углы (конечное положение)+ для приводов, далее он сам передвигает ПЛАВНО двигатели в нужную позицию
*/

#include <Servo.h>
#include "/home/evkuz/lit/learm/include/hiwonder.h"

#include <stdlib.h>
#include "/home/evkuz/lit/learm/include/Parser.h"

#include "AsyncStream.h"  // асинхронное чтение сериал
AsyncStream<50> serial(&Serial, ';');   // указываем обработчик и стоп символ


#define serv_number 6 // Количество приводов под управлением

Servo servo1, servo2, servo3,servo4,servo5,servo6;
Servo servos [6] = {servo1, servo2, servo3,servo4,servo5,servo6};

int S4_pos, S5_pos;
int *s1, *s2, *s3, *s4, *s5, *s6;
byte current_s [6]; // Текущее значение угла для соответстующего привода 0-180
byte target_pos[6];
byte delta [6];     // Разница (между текущим и целевым положением) в угле для соответствующего привода 0 - 180
//String message, number;//, s_pos;
char *s_pos;

int inByte; // Данные, полученные по serial

//++++++++++++++++++++++++ setup
void setup() {
  Serial.begin(115200);
  while (!Serial) {

      ; // wait for serial port to connect. Needed for native USB port only

    }
// attach servos to correspondent pin
  for (int i=0; i<= serv_number -1; i++)  { servos[i].attach(i+2), 500, 2500; }
  move_servo_together(hwr_Start_position);
  delay(1000);
  //get_all_servos();
  //delay(10000);
  //delay(1500);

}
//++++++++++++++++++++++++ loop 
void loop() {

int inByte;
parse_command();
/*
    if (Serial.available() > 0) {

        // get incoming byte:

        inByte = Serial.read();
        Serial.print("NANO received: ");
        Serial.println(inByte, DEC);


   // clamp();
    delay(1500);
    }
    */

/*  move_servo_together(sit_down_position);
  delay(1500);

  move_servo_together(hwr_Start_position);
  delay(1500);
*/


}//loop
//+++++++++++++++++++++++++++++++++++ to_fix_position(byte *pos)
/*
void to_fix_position (*pos)
Перейти в позицию из набора фиксированных.
параметр - указатель на массив значений углов приводов.
*/
void to_fix_position(int *pos) { for (int i=0; i<= serv_number -1; i++) { servos[i].write(pos[i]); delay(15); }
}

//++++++++++++++++++++++++++++++++++ start 
// А вообще, на будущее, надо чтобы сначала считывала текущую позицию и 
// и на основании этого вычисляла количество шагов, чтобы было плавное 
// позиционирование в начальную позицию.
void start_pozition() { to_fix_position(hwr_Start_position); }//start_pozition
//+++++++++++++++++++++++++++ sit_down
//Присаживаем. Предположительно из начальной позиции
// Пример плавного передвижения. Два привода двигаются одновременно.
void sit_down_pozition(int s4_pos, int s5_pos)
{
  int i;

  for (int i = 0; i <= 44; i++) {
    s5_pos -= 1;  s4_pos -= 1;
    servo5.write(s5_pos); delay(15);
    servo4.write(s4_pos); delay(15);
    
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
void clamp () //int clamp_angle
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
/*  s3_pos=servo3.read();
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
  } // horse_stand()
//++++++++++++++++++++++++++++++++++++++++++++++++
/*
Получить значения углов для всех приводов
*/
void get_all_servos(void)
{
    String message;
    message = "From robot after get_all_servo  :  ";
    for (int i=0; i<=serv_number - 1; i++)
    {

      current_s[i] = servos[i].read(); //Current servo
        //  message += String(i); message += " position ";
      message += String(current_s[i]);  message += ", ";
    //
    }
    Serial.println(message);
}//get_all_servos()

//+++++++++++++++++++++++++++++++++++
/*
  Задаем значения приращения угла и направление для всех приводов для текущей и целевой позиции
*/
void get_curr_delta (int *pos)
{

  for (int i=0; i<=serv_number -1; i++)
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


}//get_curr_delta

//+++++++++++++++++++++++++++++++++++ move_servo_together (byte *pos)

/*
Алгоритм :
Берем самое большое delta и задаем как счетчик цикла внешнего
А внутри перебираем все приводы - каждый со своей дельтой.
Берем снова самое большое и т.д.
*/
void move_servo_together (int *pos) // address of position array and direction flag array, текущую позицию вычисляем
{
  byte s_pos, maxdt, counter;
  String message;
  get_all_servos();
  get_curr_delta(pos);
  maxdt = get_max_delta(delta); // индекс в массиве delta, а не абсолютное значение/
/*  message = "Servo index with max delta is ";
  message += String(maxdt);
  Serial.println(message);

  message = "Max delta value is ";
  message += String(delta[maxdt]);

  Serial.println(message);

  message = "Delta values are : ";
  for (byte i=0; i<= serv_number -1; i++){ message += String(DF[i]); message += ", ";}
  Serial.println(message);
*/
while (maxdt != 100) // Перебираем дельты с наибольшим значением пока таковое не станет нулевым.
{
    counter = delta[maxdt];
  for (byte dt=0; dt <= counter  -1; dt++) //Берем дельту по индексу из массива
   {
/*     message = "Current Max delta value is ";
     message += String(delta[maxdt]);
     Serial.println(message);
*/
     for (byte i=0; i<=serv_number -1; i++) // ОБходим все приводы
       {
        s_pos = servos[i].read();
    if (delta[i] !=0)
    {
      s_pos = s_pos + DF[i];
      servos[i].write(s_pos);
      delta[i] -= 1;
      delay(10);
    }
    }//for int i=0 // все приводы

  }//for int dt=0; // вся текущая макс. дельта
    // Обошли все приводы. Определяем новое значение maxdt
    maxdt = get_max_delta(delta);

}//while (maxdt != 100)

// Посылаем текущие позиции после завершения движений.
get_all_servos();
/*
И вот тут надо бы сравнить, что пришло и что сейчас.
*/

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

  if (maxdelta==0)
  { // Перебрали все дельты и все теперь равны 0
    index = 100;
  }

  return index;
} //get_max_delta
//++++++++++++++++++++++++++
void parse_command ()
{
    String message;
    if (serial.available()) {
      Parser data(serial.buf, ',');  // отдаём парсеру
      int ints[6];           // массив для численных данных, у нас 6 приводов
      data.parseInts(ints);   // парсим в него

      message = "Robot just got data : ";
      for (int i=0; i<=5; i++)
      {          message += String(ints[i]); message += ", ";

      }
      Serial.println(message);

      move_servo_together(ints);
      /*Now send current servo data to PC*/
     // get_all_servos();

    }//if (serial.available())


 /*
    switch (data) {

    case 0x55:
        clamp();
        break;
    default:
        message = "Wrong data !!!";
        Serial.println(message);
       
    }
*/

}//parse_command

//+++++++++++++++++++++++++++++
