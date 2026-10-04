#include <stdlib.h>
#include "lcd_lib_2.h"
#include "main.h"
#include "EEPROM.h"
#include "display.h"

uint8_t current_cursor; // Указатель на текущий таймер, на нем стоит указатель
uint8_t current_string; // Номер строки на странице, на которой стоит указатель
uint8_t current_page;   // Текущая страница

static char buffer_display_string[LENGTH_TIMER_STRING+3];
//int8_t display_string(const uint8_t number_display_string, uint8_t number, bool_t display_cursor=False);

int8_t int_to_str(uint8_t number, char * str){
	int8_t result = 0;
	char * point_str = str;
	if (!(number < 10)) {
		uint16_t exponent = 1;
		while(number/exponent){
			*point_str++ = (number%(10*exponent))/exponent + '0';
			exponent*=10;
			++result;
		}
		char tmp;
		for (uint8_t i = 0; i < result/2; ++i) {
			tmp = *(str+i);
			*(str+i) = *(str+result-i-1);
			*(str+result-i-1)=tmp;
		}
	}
	else {
		*str = '0' + number;
		++result;
	}
	return result;
}

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


int8_t display_string(const uint8_t number_display_string, uint8_t number, bool_t display_cursor){
	int8_t result = -1;
	if (EXIST_DISPLAY) {
		uint8_t current_xpos = 0;
		LCD_Goto(current_xpos++, number_display_string);
		if (display_cursor)
			LCD_WriteData('>');
		else
			LCD_WriteData(' ');
		LCD_Goto(current_xpos++, number_display_string);
		char * string_for_number;
		if (LENGTH_TIMER_STRING > 9){
			if (LENGTH_TIMER_STRING > 99){
				string_for_number = (char *)malloc(4);
			}
			else {
			string_for_number = (char *)malloc(3);
			}
		}
		else {
			string_for_number = (char *)malloc(4);
		}
		//uint8_t length_number = 
		int_to_str(number, string_for_number);
		// ????????????????????????????
		while (*string_for_number)
			LCD_WriteData(*string_for_number++);
		// ????????????????????????????
		char * pointer_symbol = buffer_display_string;
		while (pointer_symbol){
			result++;
			LCD_Goto(current_xpos++, number_display_string);
			LCD_WriteData(*pointer_symbol++);
		}
		free(string_for_number);
	}
	return result;
}

int8_t display_from_ROM(uint8_t number_page){
	uint8_t i;
	for (i = 0; i < NUMBER_STRING_ON_DISPLAY; ++i){
		if (read_record(LENGTH_TIMER_STRING*(number_page*NUMBER_STRING_ON_DISPLAY+i), buffer_display_string) == -1){
			--i;
			break;
		}
		else {
			display_string(i, LENGTH_TIMER_STRING*(number_page*NUMBER_STRING_ON_DISPLAY+i), False);
		}
	}
	return i;
}


