#include "lcd_lib_2.h"
#include "main.h"
#include "display.h"

uint8_t current_cursor; // Указатель на текущий таймер, на нем стоит указатель
uint8_t current_string; // Номер строки на странице, на которой стоит указатель
uint8_t current_page;   // Текущая страница

static uint8_t buffer_display_string[LENGTH_TIMER_STRING+3];

void init_display(){
	current_cursor = 0;
	current_page = 0;
	current_string = 0;
	if (EXIST_DISPLAY) {
		LCD_Init();
	}
}

bool_t next_page(){
	if ((current_cursor + (NUMBER_STRING_ON_DISPLAY - current_string)) > MAX_NUMBER_RECORDS){
		return False;
	} 
	else {
		current_cursor += NUMBER_STRING_ON_DISPLAY - current_string;
		current_string = 0;
		++current_page;
	}
	return True;
}

bool_t next_string() {
	if (++current_string == NUMBER_STRING_ON_DISPLAY) {
		if (++current_cursor == MAX_NUMBER_RECORDS){
			init_display();
			return False;
		}
		current_string = 0;
		next_page();
	}
	return True;
}

uint8_t display_from_ROM(uint8_t number_from){
	uint8_t i;
	for (i = 0; i < NUMBER_STRING_ON_DISPLAY; ++i){
	}
	return i;
}
