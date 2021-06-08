/*
12.05.2021  hiwonder.h
*/
#ifndef hiwonder.h
#define hiwonder.h

#include "Arduino.h"

/*Координаты начальной/стартовой позиции*/
int hwr_Start_position [6] = {93, 93, 93, 93, 93, 93} ; // servo1,,,servo6
int sit_down_position [6] = {93, 93, 93, 48, 48, 93}; // Поза сидя. Сдвинуты 4,5 приводы (относительно 93)
int horse_position [6] = {93, 93, 0, 48, 48, 93};
int horse_mirror_position [6] = {45, 93, 180, 135, 135, 93};
int ready_to_catch [6] = {93, 93, 7, 10, 120, 93};
int catch_box [6] = {93, 93, 7, 10, 120, 93};


short DF [6] = {1, 1, 1, 1, 1, 1};


#endif
