#include <avr/eeprom.h>
#include <stdlib.h>
#include <stdint.h>
#include "main.h"
#include "timer.h"
#include "EEPROM.h"

uint16_t  records_in_ROM[MAX_NUMBER_RECORDS][LENGTH_BACKEND_TIMER] EEMEM;// = {"25+20-*2.","15+5-10+5-."};//
/* Текущее количество сохраненных таймеров */
uint8_t array_timers_size = 2;	

//int8_t  int_to_allocated_str(const uint16_t number, uint8_t *point_result);
																	    
uint8_t * int_to_str(const uint16_t number){
	/* Функция преобразует число в массив символов. Число должно быть < 4096. 
	 * Функция возвращает указатель на получившийся массив. Если что-то не так, 
	 * возвращается NULL 
	 * Функция выделяет память под массив. Кто-то должен её освобождать. */
	if(number > 4095)
		return NULL;
	//int8_t result = 0;
	uint8_t * str;
	//uint8_t * point_str;
	if (!(number < 10)) {
		str = (number < 100)?(uint8_t *)malloc(2):((number < 1000)?(uint8_t *)malloc(3):(uint8_t *)malloc(4));
	}
	else {
		str = (uint8_t *)malloc(1);
	}
	int_to_allocated_str(number, str);
	return str;
}

int8_t  int_to_allocated_str(const uint16_t number, uint8_t *point_result){
	/* Функция размещает результат преобразования числа в строку в памяти,
	 * на которую указывает point_result 
	 * Функция не выделяет память. Память должна быть уже кем-то выделена 
	 * Функция возвращает количество байт, необходимых для размещения числа
	 * или -1, если преобразовываемое число > 4095 */
	if(number > 4095)
		return -1;
	uint8_t * point_str = point_result;
	int8_t result = 0;
	if (!(number < 10)) {
		uint16_t exponent = 1;
		while(number/exponent){
			*point_str++ = (number%(10*exponent))/exponent + '0';
			exponent*=10;
			++result;
		}
		// *point_str =0; // Результат не является строкой, оканчивающейся на \0.
		uint8_t tmp;
		for (uint8_t i = 0; i < result/2; ++i) {
			tmp = *(point_result+i);
			*(point_result+i) = *(point_result+result-i-1);
			*(point_result+result-i-1)=tmp;
		}
	}
	else {
		*point_str = '0' + number;
		return ++result;
	}
}

uint8_t read_record(const uint8_t number, const uint16_t * buffer){
	/* Функция читает настройки таймера number, сохраняет их в буфере buffer,
	 * Память для buffer не выделяется в функции.
	 * Функция возвращает 1, если успешно прочитано и 0, если не успешно */
	if (number < array_timers_size){
		eeprom_read_block((void *)buffer, records_in_ROM + 2*LENGTH_BACKEND_TIMER*number, 2*LENGTH_BACKEND_TIMER);
		return number;
	}
	else {
		return -1;
	}
}
