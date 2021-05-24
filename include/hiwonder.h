/*
12.05.2021  hiwonder.h
*/
#ifndef hiwonder.h
#define hiwonder.h

#include "Arduino.h"

/*Координаты начальной/стартовой позиции*/
int hwr_Start_position [6] = {90, 90, 90, 90, 90, 90} ; // servo1,,,servo6
int sit_down_position [6] = {90, 90, 90, 48, 48, 90}; // Поза сидя. Сдвинуты 4,5 приводы (относительно 90)
int horse_position [6] = {90, 90, 0, 48, 48, 90};
int horse_mirror_position [6] = {45, 90, 180, 135, 135, 90};
int ready_to_catch [6] = {90, 90, 7, 10, 120, 90};


short DF [6] = {1, 1, 1, 1, 1, 1};


#endif
