/*
 * learm_04.ino
 *
 * Данные передаем/принимаем в двоичном виде.
 *
 *
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
#include "/home/evkuz/0_arduino/include/hiwonder_byte.h"
//lit/learm/

// /home/evkuz/lit/learm/
/// //../include/hiwonder_byte.h
#include <stdlib.h>


#define serv_number 6 // Количество приводов под управлением
#define sBufSize 64   // Размер буфера компорта в плате NANO - 64 байта.

Servo servo1, servo2, servo3,servo4,servo5,servo6;
Servo servos [6] = {servo1, servo2, servo3,servo4,servo5,servo6};


int *s1, *s2, *s3, *s4, *s5, *s6;
byte current_s [6]; // Текущее значение угла для соответстующего привода 0-180
byte readed_pos[6];
byte delta [6];     // Разница (между текущим и целевым положением) в угле для соответствующего привода 0 - 180
//String message, number;//, s_pos;
char *s_pos;

int inByte; // Данные, полученные по serial
byte ints[64];

//++++++++++++++++++++++++ setup
void setup() {
  Serial.begin(115200);
  Serial.setTimeout(1000);
  while (!Serial) {

      ; // wait for serial port to connect. Needed for native USB port only

    }
// attach servos to correspondent pin
  for (int i=0; i<= serv_number -1; i++)  { servos[i].attach(i+2), 500, 2500; }
<<<<<<< HEAD
  move_servo_together(hwr_Start_position);
  delay(1000);

=======
  for (byte i=0; i<= 63; i++){
      ints[i] = 93;
  }
>>>>>>> 840c33de2b572b42a54e53395fb1a85157287b93
}
//++++++++++++++++++++++++ loop 
void loop() {

int inByte;
parse_command();
<<<<<<< HEAD



=======

/*
    if (Serial.available() > 0) {

        // get incoming byte:

        inByte = Serial.read();
        Serial.print("NANO received: ");
        Serial.println(inByte, DEC);
        Serial.flush();

    }
*/
>>>>>>> 840c33de2b572b42a54e53395fb1a85157287b93
}//loop
//+++++++++++++++++++++++++++++++++++ to_fix_position(byte *pos)
/*
void to_fix_position (*pos)
Перейти в позицию из набора фиксированных.
параметр - указатель на массив значений углов приводов.
*/
void to_fix_position(byte *pos) { for (int i=0; i<= serv_number -1; i++) { servos[i].write(pos[i]); delay(15); }
}

//++++++++++++++++++++++++++++++++++ start 
// А вообще, на будущее, надо чтобы сначала считывала текущую позицию и 
// и на основании этого вычисляла количество шагов, чтобы было плавное 
// позиционирование в начальную позицию.
void start_pozition() { to_fix_position(hwr_Start_position); }//start_pozition
//+++++++++++++++++++++++++++++++++++
/*
Получить значения углов для всех приводов
параметр when означает - ДО начала движения и В КОНЦЕ движения
*/
void get_all_servos(String when)
{
    String message;
    message = "From robot "; message += when; message += " get_all_servo  :  ";
    for (int i=0; i<=serv_number - 1; i++)
    {

      current_s[i] = servos[i].read(); //Current servo
      //readed_pos[i] = current_s[i];
        //  message += String(i); message += " position ";
      message += String(current_s[i]);  message += ", ";
    //
    }
  //  Serial.println(message);
  //  Serial.flush();
}//get_all_servos()

//+++++++++++++++++++++++++++++++++++
/*
  Задаем значения приращения угла и направление для всех приводов для текущей и целевой позиции
*/
void get_curr_delta (byte *pos)
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
void move_servo_together (byte *pos, byte numBytes) // address of position array and direction flag array, текущую позицию вычисляем
{
  byte s_pos, maxdt, counter;
  String message;
  get_all_servos("before"); //Получаем массив current_s[]
  get_curr_delta(pos);
  maxdt = get_max_delta(delta); // индекс в массиве delta, а не абсолютное значение/
/*  message = "Servo index with max delta is ";
  message += String(maxdt);
  Serial.println(message);
  Serial.flush();

  message = "Max delta value is ";
  message += String(delta[maxdt]);

  Serial.println(message);
  Serial.flush();
  message = "Delta values are : ";
  for (byte i=0; i<= serv_number -1; i++){ message += String(DF[i]); message += ", ";}
  Serial.println(message);
  Serial.flush();
*/
while (maxdt != 100) // Перебираем дельты с наибольшим значением пока таковое не станет нулевым.
{                    // см. get_max_delta()
    counter = delta[maxdt];
  for (byte dt=0; dt <= counter  -1; dt++) //Берем дельту по индексу из массива
   {
/*     message = "Current Max delta value is ";
     message += String(delta[maxdt]);
     Serial.println(message);
     Serial.flush();
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
get_all_servos("after");
/*
И вот тут надо бы сравнить, что пришло и что сейчас.
*/
// Сравниваем массивы

for (byte i=0; i<=serv_number -1; i++){ // ОБходим все приводы
  if (current_s[i] != pos[i]){
      message = "Позиция не совпадает с заданной, привод ";
      message += String(i); message += "\n";
      message +=  "Задано      "; message += String(pos[i]);
      message += "Фактическая "; message += String(current_s[i]);
      Serial.println(message);

  }

}



message = "Robot got "; message += String(numBytes); message += " bytes and movement DONE!";
//byte mystrlen = message.length();
while ( message.length() <=61){
    message += " ";//String(9);
    //byte a = 120;
}
Serial.println(message);
//Serial.flush();

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

    static byte prevAm = 0;
    static uint32_t tmr = 0;
    byte am = Serial.available();
    if (am != prevAm){
        prevAm = am;
        tmr = millis();
    }
    if ((am & millis() - tmr >10) || am >60){
        uint32_t us = micros();


    }

    if (Serial.available()) {
      //byte ints[64];           // массив для численных данных, у нас 6 приводов
      byte numReaded;
      
      numReaded=Serial.readBytes(ints, 64);

      message = "Robot just got data : ";
      for (int i=0; i<=63; i++)
      {          message += String(ints[i]); message += ", ";

      }
      message.remove(message.length()-2);
    //  Serial.println(message);
      // Serial.flush();

      move_servo_together(ints, numReaded);
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
        Serial.flush();
    }
*/
}//parse_command

//+++++++++++++++++++++++++++++
