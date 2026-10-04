/*
 * main.h
 *
 * Created: 20.09.2026 11:08:08
 *  Author: Святослав
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define ATMEGA16_BOARD
#define EXIST_DISPLAY   1    /*  Если дисплей существует, тогда 1, если нет 0 */

#define LENGTH_TIMER_STRING  12 /* Длина строки, отображающей настройки таймера */

typedef enum {
	wait,
	setting,
	count,
} typemode;

typedef enum {
	False = 0,
	True = 1
} bool_t;


#endif /* MAIN_H_ */
