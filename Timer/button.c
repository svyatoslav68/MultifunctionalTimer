#include <avr/io.h>
#include <avr/interrupt.h>
#include "button.h"


ISR (INT0_vect){
	/* Запрет прерывания INT0 */
	GICR &= ~(1 << INT0);
	add_new_task_with_delay(antidrebezg, DELAY_DREBEZG/PERIOD_TIMER, 0);
}

void init_button(){
	/* Конфигурации порта кнопки на чтение и установка внутренней подтяжки */
	DIRECT_BUTTONS &= ~(1 << PIN_BUTTON);
	PORT_BUTTONS |= (1 << PIN_BUTTON);
	/* Конфигурация внешнего прерывания INT0 на срабатывание по спаду */
	MCUCR &= ~((1 << ISC00)|(1 << ISC01));
	MCUCR |= (1 << ISC01);
	/* Сброс флага прерывания и разрешение прерывания INT0 */
	GIFR |= (1 << INTF0);
	GICR |= (1 << INT0);
}

void antidrebezg(){
	switch(mode) {
		case wait:
			mode = down_1;
			add_new_task_with_delay(probe_long, DELAY_LONG/PERIOD_TIMER, 0);
			break;
		case down_1:
			mode = up_1;
			add_new_task_with_delay(probe_long, DELAY_ONE_CLICK/PERIOD_TIMER, 0);
			break;
		case up_1:
			mode = down_2;
			add_new_task_with_delay(probe_long, DELAY_LONG/PERIOD_TIMER, 0);
			break;
		case down_2:
			mode = wait;
			add_task(longdown);
			break;
		case up_2:
			mode = wait;
		default:
		;
	}
}

void probe_click(){
}

void probe_double(){
}

void probe_long(){
}

void click(){
}

void doubleclick(){
}

void longdown(){
}

