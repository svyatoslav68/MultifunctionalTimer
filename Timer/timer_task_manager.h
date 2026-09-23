#ifndef CTRL_TIMER_H
#define CTRL_TIMER_H

//#include <stdint.h>

#define  DELAY_TIMER_MS (10UL/1000000UL) /* Время задержки, генерируемой таймером в сотых долях мс */
#define  DIVIDER_0 8UL      			 /* Предделитель для таймера-счетчика 0 */
#if DIVIDER_0 == 1024UL
#define CLOCK_SELECT_BITS_TIMER0 ((1 << CS02) | (1 << CS00))
#elif DIVIDER_0 == 256UL
#define CLOCK_SELECT_BITS_TIMER0 (1 << CS02)
#elif DIVIDER_0 == 64UL
#define CLOCK_SELECT_BITS_TIMER0 ((1 << CS01) | (1 << CS00))
#elif DIVIDER_0 == 8UL
#define CLOCK_SELECT_BITS_TIMER0 (1 << CS01)
#endif

#define VALUE_OCR0 ((F_CPU*DELAY_TIMER_MS)/DIVIDER_0)
// #define VALUE_TCNT0 (256UL-F_CPU/(DIVIDER_0*DELAY_TIMER_MS*10))


struct queue_node_t; 
struct queue_t;

void init_timer_queue();
void start_timer0();
void stop_timer0();
//void add_timer_task(type_queue_node task);
void init_test_timer_queue(void);
void add_new_task_with_delay(const TPTR task, const uint16_t delay, const uint16_t tiks);

#endif // CTRL_TIMER_H
