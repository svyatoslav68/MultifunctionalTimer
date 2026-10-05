#pragma once

/*
 * button.h
 * Project: MultifunctionalTimer
 * Created: 24.09.2026 12:18:45
 *  Author: Святослав
*/

#include "timer_task_manager.h" 

#define DIRECT_BUTTONS DDRD
#define PORT_BUTTONS PORTD
#define PIN_BUTTONS PIND
#define PIN_BUTTON PORTD2
#define DELAY_DREBEZG (2*MSEC_IN_MKSEC/DELAY_TIMER_MKS) /* 2 мс */
#define DELAY_ONE_CLICK (400*MSEC_IN_MKSEC/DELAY_TIMER_MKS) /* 400 мс */
#define DELAY_LONG (800*MSEC_IN_MKSEC/DELAY_TIMER_MKS) /* 800 мс */


void antidrebezg();
void init_button();
void click();
void doubleclick();
void longdown();


