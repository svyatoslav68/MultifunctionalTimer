#ifndef DISPLAY_H
#define DISPLAY_H

#define NUMBER_STRING_ON_DISPLAY 2 

#include "main.h"
#ifndef TEST

void init_display();
int8_t next_page();
int8_t next_string();
void display_from_ROM();

#else
int8_t display_string(const uint16_t *source_words,  uint8_t *const destination_bytes, uint8_t number_display_string);
#endif // TEST

#endif //DISPLAY_H
