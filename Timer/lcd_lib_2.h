//***************************************************************************
//  File........: lcd_lib.h
//
//  Author(s)...: Pashgan    chipenable.ru
//
//  Target(s)...: ATMega...
//
//  Compiler....: IAR, CodeVision, GNU GCC
//
//  Description.: Драйвер знакосинтезирующего жк дисплея
//
//  Data........: 20.07.13  
//
//***************************************************************************
#ifndef LCD_LIB_H
#define LCD_LIB_H

#include "main.h"
#include "compilers_4.h"

//здесь я определил виртуальный порт

//шина данных LCD
#ifdef ARDUINO 
#define LCD_PORT  LCD_DATA, C, _REAL
#define LCD_DATA_0  C, 0, _NONE
#define LCD_DATA_1  C, 1, _NONE
#define LCD_DATA_2  C, 2, _NONE
#define LCD_DATA_3  C, 3, _NONE
#define LCD_DATA_4  C, 4, _HI
#define LCD_DATA_5  C, 5, _HI
#define LCD_DATA_6  C, 6, _HI
#define LCD_DATA_7  C, 7, _HI
#else
#define LCD_PORT  LCD_DATA, A, _REAL
#define LCD_DATA_0  A, 0, _NONE
#define LCD_DATA_1  A, 1, _NONE
#define LCD_DATA_2  A, 2, _NONE
#define LCD_DATA_3  A, 3, _NONE
#define LCD_DATA_4  A, 4, _HI
#define LCD_DATA_5  A, 5, _HI
#define LCD_DATA_6  A, 6, _HI
#define LCD_DATA_7  A, 7, _HI
#endif

//управляющие выводы LCD
#define LCD_RS  B, 2, _HI
#define LCD_RW  B, 1, _HI
#define LCD_EN  B, 0, _HI  

/*____________________________________________________________________*/

//глобальные настройки драйвера
#define LCD_CHECK_FL_BF             1
#define LCD_BUS_4_8_BIT             0

//настройки инициализации дисплея
#define LCD_ONE_TWO_LINE            1
#define LCD_FONT58_FONT511          0
#define LCD_DEC_INC_DDRAM           1
#define LCD_SHIFT_RIGHT_LEFT        0
#define LCD_DISPLAY_OFF_ON          1
#define LCD_CURSOR_OFF_ON           1
#define LCD_CURSOR_BLINK_OFF_ON     0
#define LCD_CURSOR_DISPLAY_SHIFT    0

/*_____________________макро функции________________________________*/

//команды
#define LCD_CLEAR_DISPLAY  0x01
#define LCD_RETURN_HOME    0x02

//очистка дисплея
#define LCD_Clear() do{LCD_WriteCom(LCD_CLEAR_DISPLAY); _delay_ms(2);}while(0)   

//возврат курсора в начальное положение
#define LCD_ReturnHome()  do{LCD_WriteCom(LCD_RETURN_HOME);}while(0)

//позиционирование курсора
#define LCD_Goto(x, y)    LCD_WriteCom(((((y)& 1)*0x40)+((x)& 15))|128)  

/*___________________пользовательские функции_______________________*/

void LCD_Init(void);                                  //инициализация портов и жкд по умолчанию
void LCD_WriteCom(uint8_t data);                      //посылает команду жкд
void LCD_WriteData(char data);                        //выводит символ на жкд
void LCD_SendStr(char *str);                          //выводит строку из ОЗУ

#ifdef __GNUC__
   void LCD_SendStrFl(char *str);                           //выводит строку из флэш памяти     
   void LCD_SetUserChar(uint8_t const *sym, uint8_t adr);   //загрузить пользовательский символ
#else
   void LCD_SendStrFl(char __flash *str);                   //выводит строку из флэш памяти
   void LCD_SetUserChar(uint8_t __flash *sym, uint8_t adr); //загрузить пользовательский символ
#endif

#endif
