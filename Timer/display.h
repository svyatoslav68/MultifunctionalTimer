#ifndef DISPLAY_H
#define DISPLAY_H

#include "main.h"

#define NUMBER_STRING_ON_DISPLAY 2 

void init_display();
int8_t display_from_ROM(uint8_t number_page);
bool_t next_string();

#endif //DISPLAY_H
