#ifndef DISPLAY_H
#define DISPLAY_H

#include "main.h"

#define NUMBER_STRING_ON_DISPLAY 2 
#define MAX_NUMBER_RECORDS 10

void init_display();
uint8_t display_from_ROM(uint8_t number_from);
bool_t next_string();

#endif //DISPLAY_H
