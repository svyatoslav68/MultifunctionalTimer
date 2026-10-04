#include <avr/eeprom.h>
#include <stdint.h>
#include "main.h"
#include "EEPROM.h"

char  records_in_ROM[MAX_NUMBER_RECORDS][LENGTH_TIMER_STRING] EEMEM = {"25+20-*2.","15+5-10+5-5+5-."};//
uint8_t array_timers_size = 2;	
																	    
int8_t read_record(const uint8_t number, const char * buffer){
	if (number < array_timers_size){
		eeprom_read_block((void *)buffer, records_in_ROM + LENGTH_TIMER_STRING*number, LENGTH_TIMER_STRING);
		return number;
	}
	else {
		return -1;
	}
}
