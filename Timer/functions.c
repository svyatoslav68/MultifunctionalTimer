/*
 * functions.c
 *
 * Created: 26.09.2026 12:03:51
 *  Author: svjat
 */ 

#include <avr/io.h>
#include "functions.h"
#include "test.h"
#include "timer_queue.h"
#include "timer_task_manager.h"

void led_1_on(){
	//PORT_TEST_LEDS |= (1 << TEST_LED_1);
	add_new_task_with_delay(led_1_off, 5000, 0);
}

void led_1_off(){
	//PORT_TEST_LEDS &= ~(1 << TEST_LED_1);
	add_new_task_with_delay(led_1_on, 5000, 0);	
}