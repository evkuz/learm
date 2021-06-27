//#include "move_servos.h"

void move_servo_together (byte *pos, byte start_servo, byte end_servo) // address of position array and direction flag array, текущую позицию вычисляем
{
  byte s_pos, maxdt, counter;
  String message;
  get_all_servos("before"); //Получаем массив current_s[]
  get_curr_delta(pos);
  maxdt = get_max_delta(delta, start_servo, end_servo); // индекс в массиве delta, а не абсолютное значение/
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


  /*   message = "Current Max delta value is ";
message += String(delta[maxdt]);
Serial.println(message);
Serial.flush();
 */


  byte cycle_num =0;
while (maxdt != 100) // Перебираем дельты с наибольшим значением пока таковое не станет нулевым.
  {                    // см. get_max_delta()

     //Сначала проходим приводы 6-4, пауза 1сек. затем отдельно привод 1, и в конце приводы 3-2
    for (byte i=start_servo -1; i<= end_servo -1; i++) // ОБходим все приводы, но в обратном порядке
    {                                                // т.е. начинаем с 6-го и далее по убыванию номера привода.

        s_pos = servos[i].read();
        if (delta[i] !=0)
        {
            s_pos = s_pos + DF[i];
            servos[i].write(s_pos);
            delta[i] -= 1;
            delay(10);
        }

    }//for (byte i=start_servo -1; // вся текущая макс. дельта
    // Обошли все приводы. Определяем новое значение maxdt
    /*
        И вот тут засада, т.к. максимальное дельта может быть у привода не из списка start_servo - end_servo
*/
    maxdt = get_max_delta(delta, start_servo, end_servo);
    cycle_num++;

}//while (maxdt != 100)

// Посылаем текущие позиции после завершения движений.
get_all_servos("after");
/*
И вот тут надо бы сравнить, что пришло и что сейчас.
*/
// Сравниваем массивы
message += "Main Cycle worked "; message += String(cycle_num); message += " times";

//for (byte i=0; i<=serv_number -1; i++){ // ОБходим все приводы, проверяем совпадение позиции с заданной
//  if (current_s[i] != pos[i]){
//      message = "Позиция не совпадает с заданной, привод ";
//      message += String(i); message += "\n";
//      message += "Задано      "; message += String(pos[i]);
//      message += "Фактическая "; message += String(current_s[i]);
//      Serial.println(message);

//  }

//}



message = "Robot movement DONE!"; //message += String(numBytes); 
byte mystrlen = message.length();
while ( message.length() <=61){
    message += " ";//String(9);
    //byte a = 120;
}
Serial.println(message);
Serial.flush();

}//move_servo_together

//+++++++++++++++++++++++++++++++++++++++++++++++++
/*Возвращает индекс макисмального элемента в массиве delta*/
byte get_max_delta (byte *arr, byte start_servo, byte end_servo)
{
  int maxdelta, index;
  maxdelta=0;
  index=0;
  for (int i=start_servo-1; i<=end_servo-1; i++)
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
