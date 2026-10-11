#include <stdlib.h>
#include "lcd_lib_2.h"
#include "main.h"
#include "EEPROM.h"
#include "display.h"

int8_t current_cursor; // Указатель на текущий таймер, на нем стоит указатель
int8_t current_string; // Номер строки на странице, на которой стоит указатель
int8_t current_page;   // Текущая страница

static char buffer_display_string[LENGTH_TIMER_STRING+3];
//int8_t display_string(const uint8_t number_display_string, uint8_t number, bool_t display_cursor=False);

static int8_t display_from_ROM();
static int8_t display_cursor();

char * int_to_str(const uint8_t number){
	int8_t result = 0;
	char * str;
	char * point_str;
	if (!(number < 10)) {
		str = (number < 100)?(char *)malloc(3):(char *)malloc(4);
		point_str = str;
		uint16_t exponent = 1;
		while(number/exponent){
			*point_str++ = (number%(10*exponent))/exponent + '0';
			exponent*=10;
			++result;
		}
		*point_str =0;
		char tmp;
		for (uint8_t i = 0; i < result/2; ++i) {
			tmp = *(str+i);
			*(str+i) = *(str+result-i-1);
			*(str+result-i-1)=tmp;
		}
	}
	else {
		str = (char *)malloc(2);
		point_str = str;
		*point_str++ = '0' + number;
		point_str = 0;
	}
	return str;
}

inline void init_display(){
	current_cursor = 0;
	current_page = 0;
	current_string = 0;
	if (EXIST_DISPLAY) {
		LCD_Init();
		LCD_Goto(0, current_string);
		LCD_WriteData('>');
		display_from_ROM();
	}
}

int8_t next_page(){
	if ((current_cursor + (NUMBER_STRING_ON_DISPLAY - current_string)) > MAX_NUMBER_RECORDS){
		return 0;
	} 
	else {
		current_cursor += NUMBER_STRING_ON_DISPLAY - current_string;
		current_string = 0;
		++current_page;
		display_from_ROM();
		display_cursor();
	}
	return 1;
}

static int8_t display_cursor(){
	/* Отображение в нулевой позиции символа курсора */
	if ((current_string > -1) && (EXIST_DISPLAY)) {
		LCD_Goto(0, current_string);
		LCD_WriteData('>');
		return current_string;
	}
	return -1;
}

int8_t next_string() {
	if (++current_string == NUMBER_STRING_ON_DISPLAY) {
		if (++current_cursor == MAX_NUMBER_RECORDS){
			init_display();
			return 0;
		}
		current_string = 0;
		next_page();
	}
	else {
		display_cursor();
	}
	return 1;
}


inline static int8_t display_string(const uint8_t number_display_string, const uint8_t number){
	int8_t result = -1;
	if (EXIST_DISPLAY) {
		uint8_t current_xpos = 1;
		/* Создание C-строки, содержащей номер записи */
		char * string_for_number;
		string_for_number = int_to_str(number);
		/* Отображение номера записи */
		while (*string_for_number){
			LCD_Goto(current_xpos++, number_display_string);
			LCD_WriteData(*string_for_number++);
		}
		free(string_for_number);
		LCD_Goto(current_xpos++, number_display_string);
		LCD_WriteData(':');
		/* Отображение записи */
		char * pointer_symbol = buffer_display_string;
		while (pointer_symbol){
			result++;
			LCD_Goto(current_xpos++, number_display_string);
			LCD_WriteData(*pointer_symbol++);
		}
	}
	return result;
}

static int8_t display_from_ROM(){//uint8_t number_page){
	uint8_t i;
	for (i = 0; i < NUMBER_STRING_ON_DISPLAY; ++i){
		if (read_record(LENGTH_TIMER_STRING*(current_page*NUMBER_STRING_ON_DISPLAY+i), buffer_display_string) == -1){
			--i;
			break;
		}
		else {
			display_string(i, LENGTH_TIMER_STRING*(current_page*NUMBER_STRING_ON_DISPLAY+i));
		}
	}
	return i;
}


