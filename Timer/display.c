#ifndef TEST
#include "lcd_lib_2.h"
#else
#include <stdio.h>
#include <string.h>
#endif
#include <stdint.h>
#include <stdlib.h>
#include "main.h"
#include "timer.h"
#include "EEPROM.h"
#include "display.h"

static int8_t current_cursor = 0; // Указатель на текущий таймер, на нем стоит указатель
static int8_t current_string = 0; // Номер строки на странице, на которой стоит указатель
static int8_t current_page = 0;   // Текущая страница

//int8_t display_string(const uint8_t number_display_string, uint8_t number, bool_t display_cursor=False);

static int8_t display_cursor();

#ifndef TEST

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
	//display_from_ROM();
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

#endif // TEST

inline static int8_t display_string(const uint16_t *source_words,  uint8_t *const destination_bytes, uint8_t number_display_string){
	int8_t result = -1;
	uint8_t i; 
	uint8_t *cursor_destination;
	for (i = 0, cursor_destination = destination_bytes; i < LENGTH_BACKEND_TIMER; ++i){
		uint16_t current_word = source_words[i];
		if (current_word == 0xffff) {
			*cursor_destination++ = '.';
			break;
		}
		else {
			if ((current_word & 0xf000) == 0xf000) {
				*cursor_destination++ = (uint8_t)(current_word & 0x00ff);
			}
			else {
				cursor_destination += int_to_allocated_str(current_word & 0x0fff, cursor_destination);
			}
		}
	}
	*cursor_destination = 0x00;
	result = cursor_destination - destination_bytes;
#ifndef TEST
	if (EXIST_DISPLAY) {
#if 1
		uint8_t current_xpos = 1;
		/* Создание C-строки, содержащей номер записи */
		uint8_t * string_for_number;
		string_for_number = int_to_str(current_cursor);
		/* Отображение номера записи */
		while (*string_for_number){
			LCD_Goto(current_xpos++, number_display_string);
			LCD_WriteData(*string_for_number++);
		}
		free(string_for_number);
		LCD_Goto(current_xpos++, number_display_string);
		LCD_WriteData(':');
		/* Отображение записи */
		uint8_t * pointer_symbol = destination_bytes;
		while (*pointer_symbol != '.'){
			//result++;
			LCD_Goto(current_xpos++, number_display_string);
			LCD_WriteData(*pointer_symbol++);
		}
#endif // if 1
	}
#else
    printf("%d: Длина строки = %d; Строка: %s\n", number_display_string, result, destination_bytes);
#endif // TEST
	return result;
}

void display_from_ROM(){//uint8_t number_page){
	/* Указатель на массив кодов для отображения на индикаторе создается внутри функции.
	 * Память под массив выделяется внутри функии. Объем выделяемой памяти определяется
	 * первым словом, читаемым из ПЗУ.
	 * Уничтожается массив кодов внутри функции.*/
	uint16_t record_from_rom[LENGTH_BACKEND_TIMER];
	//uint8_t i;
	for (uint8_t i = 0; i < NUMBER_STRING_ON_DISPLAY; ++i){
#ifdef TEST
        //printf("i = %d: ", i);
#endif
		if (read_record(current_page*NUMBER_STRING_ON_DISPLAY+i, record_from_rom) < 1){ 
			//--i;
			break;
		}
		else {
			uint8_t *buffer_display_string = (uint8_t *)malloc(record_from_rom[0] + 1);
			display_string(record_from_rom + 1, buffer_display_string, i);
			free(buffer_display_string);
		}
#ifdef TEST
        //printf("%s\n", buffer_display_string);
#endif
	}
	//return i;
}


