#include <stdint.h>
#include <stdlib.h>
#include "timer.h"

/* Внутреннее представление настройки текущего таймера. Используется всей программой, 
 * поэтому хранится в статической памяти */

uint16_t current_timer[LENGTH_BACKEND_TIMER];

char *timer_to_string(uint16_t *backend_timer){
	char *result = NULL;
	uint16_t current_symbol;
	uint16_t *buffer = malloc(LENGTH_BACKEND_TIMER*2);
	return result;
}

