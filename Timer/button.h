#pragma once

/*
*/

#define DIRECT_BUTTONS DDRD
#define PORT_BUTTONS PORTD
#define PIN_BUTTONS PIND
#define PIN_BUTTON PORTD2
#define DELAY_DREBEZG (200/1000000) /* 200 мкс */
#define DELAY_ONE_CLICK (500/1000) /* 500 мс */
#define DELAY_LONG (800/1000) /* 800 мс */

void init_button();
void click();
void doubleclick();
void longdown();


