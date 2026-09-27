#include <avr/io.h>
#include <avr/interrupt.h>
#include "button.h"
#include "test.h"

#define LED_STATE_BUTTON TEST_LED_1
#define LED_ONE_CLICK TEST_LED_2
#define LED_DOUBLE_CLICK TEST_LED_3
#define LED_LONG_DOWN TEST_LED_4

typedef enum {
	failing,
	rising
} t_front;

typedef enum {
	wait_down,
	down_1,
	up_1,
	down_2,
	up_2,
	long_down,
} t_modes_button;

t_modes_button mode_button;
void probe_long();
void probe_click();

ISR (INT0_vect){
	/* Запрет прерывания INT0 */
	GICR &= ~(1 << INT0);
	add_new_task_with_delay(antidrebezg, DELAY_DREBEZG, 0);
}

void init_int0(t_front type_front){
	MCUCR &= ~((1 << ISC00)|(1 << ISC01));
	if (type_front == failing) {
		/* Конфигурация внешнего прерывания INT0 на срабатывание по спаду */
		MCUCR |= (1 << ISC01);
	} 
	else {
		/* Конфигурация внешнего прерывания INT0 на срабатывание по фронту */
		MCUCR |= (1 << ISC01) | (1 << ISC00);
	} 
	/* Сброс флага прерывания и разрешение прерывания INT0 */
	GIFR |= (1 << INTF0);
	GICR |= (1 << INT0);
}

void init_button(){
	/* Конфигурации порта кнопки на чтение и установка внутренней подтяжки */
	DIRECT_BUTTONS &= ~(1 << PIN_BUTTON);
	PORT_BUTTONS |= (1 << PIN_BUTTON);
	mode_button = wait_down;
	init_int0(failing);
}

void antidrebezg(){
	if (PIN_BUTTONS & (1 << PIN_BUTTON)){
		PORT_TEST_LEDS |= (1 << LED_STATE_BUTTON);
	}
	else {
		PORT_TEST_LEDS &= ~(1 << LED_STATE_BUTTON);
	}
	switch(mode_button) {
		case wait_down:
			mode_button = down_1;
			init_int0(rising);
			add_new_task_with_delay(probe_long, DELAY_LONG, 0);
			break;
		case down_1:
			mode_button = up_1;
			init_int0(failing);
			add_new_task_with_delay(probe_click, DELAY_ONE_CLICK, 0);
			break;
		case up_1:
			mode_button = down_2;
			init_int0(rising);
			//delay(probe_long, DELAY_LONG/PERIOD_TIMER, 0);
			break;
		case down_2:
			mode_button = wait_down;
			init_int0(failing);
			add_task(doubleclick);
			break;
		case long_down:
			init_int0(failing);
			mode_button = wait_down;
		default:
		;
	}
}

void probe_click(){
	if ((PIN_BUTTONS & (1 << PIN_BUTTON)) && (mode_button == up_1)){
		mode_button = wait_down;
		add_task(click);
	}
}

void probe_double(){
}

void probe_long(){
	if (!(PIN_BUTTONS & (1 << PIN_BUTTON)) && (mode_button == down_1)){
		mode_button = long_down;
		add_task(longdown);
	}
}

void click(){
	 PORT_TEST_LEDS ^= (1 << LED_ONE_CLICK);
}

void doubleclick(){
	PORT_TEST_LEDS ^= (1 << LED_DOUBLE_CLICK);
}

void longdown(){
	PORT_TEST_LEDS ^= (1 << LED_LONG_DOWN);
}

