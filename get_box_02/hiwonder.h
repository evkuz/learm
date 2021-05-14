/*
12.05.2021  hiwonder.h
*/
#ifndef hiwonder.h
#define hiwonder.h

#include "Arduino.h"

/*Координаты начальной/стартовой позиции*/
byte hwr_Start_position [6] = {90, 90, 90, 90, 90, 90} ; // servo1,,,servo6
byte sit_down_position [6] = {90, 90, 90, 45, 45, 90}; // Поза сидя. Сдвинуты 4,5 приводы (относительно 90)

short DF [6] = {1, 1, 1, 1, 1, 1};


#endif
