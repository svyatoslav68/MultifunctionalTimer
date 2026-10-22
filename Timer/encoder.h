/*
 * encoder.h
 * Project: ProbaManager
 * Заголовочный файл для обработки энкодера
 * Created: 03.07.2026 12:50:41
 *  Author: Svyatoslav
 */ 


#ifndef ENCODER_H_
#define ENCODER_H_

#define DDR_ENCODER DDRD
#define PORT_ENCODER PORTD
#define PIN_ENCODER PIND

#define ENCODER_CHANNEL_A PORTD1
#define ENCODER_CHANNEL_B PORTD0

#define NUMBER_RIGHT_VALUE 5
//#define NUMBER_FOR_END_ROTATION 20

void init_encoder();
void enable_encoder();
void disable_encoder();
void reading_encoder();



#endif /* ENCODER_H_ */
