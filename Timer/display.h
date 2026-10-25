#ifndef DISPLAY_H
#define DISPLAY_H

#define NUMBER_STRING_ON_DISPLAY 2 

#ifndef TEST
#include "main.h"


void init_display();
int8_t next_page();
int8_t next_string();

#endif // TEST

void display_from_ROM();

#endif //DISPLAY_H
