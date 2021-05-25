/*
25.05.2021  hiwonder_byte.h
*/
#ifndef hiwonder.h
#define hiwonder.h

#include "Arduino.h"

/*Координаты начальной/стартовой позиции*/
byte hwr_Start_position [6] = {93, 93, 93, 93, 93, 93} ; // servo1,,,servo6
byte sit_down_position [6] = {93, 93, 93, 48, 48, 93}; // Поза сидя. Сдвинуты 4,5 приводы (относительно 93)
byte horse_position [6] = {93, 93, 0, 48, 48, 93};
byte horse_mirror_position [6] = {45, 93, 180, 135, 135, 93};
byte ready_to_catch [6] = {93, 93, 7, 10, 120, 93};
byte catch_box [6] = {93, 93, 7, 10, 120, 93};


short DF [6] = {1, 1, 1, 1, 1, 1};


#endif
