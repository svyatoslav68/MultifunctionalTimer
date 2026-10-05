/*
 * Timer.c
 *
 * Created: 20.09.2026 10:35:11
 * Author : Святослав
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "main.h"
#include "RTOS.h"
#include "button.h"
#include "timer_queue.h"
#include "timer_task_manager.h"
#include "test.h"
#include "functions.h"

typemode  mode;

void init() {
	sei();
}

void init_test() {
	DIRECT_TEST_LEDS |= (1 << TEST_LED_1)|(1 << TEST_LED_2)|(1 << TEST_LED_3)|(1 << TEST_LED_4);
	DIRECT_TEST_PINS |= (1 << TEST_PIN_1)|(1 << TEST_PIN_2)|(1 << TEST_PIN_3)|(1 << TEST_PIN_4);
}

int main(void)
{
	init_button();
	init_task_queue();
	init_test();
	init();
	init_timer_queue();
	start_timer0();

	PORT_TEST_LEDS &= ~(1 << TEST_LED_1);
	add_new_task_with_delay(led_1_on, 5000, 0);
	mode = wait;
    while (1) {
		task_manager();
    }
}

