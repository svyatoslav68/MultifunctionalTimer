#ifndef EEPROM_H
#define EEPROM_H

#define MAX_NUMBER_RECORDS 10

/* Формат хранения таймера в ПЗУ.
 * Для хранения одного таймера резервируется 32 байта, т. е. 16 слов.
 * В первом слове хранится длина текствого представления таймера.
 * Текстовое представление используется для отображения на дисплее.
 * Далее следует 15 слов предназначенных для хранени таймера. */

uint8_t * int_to_str(const uint16_t number);
int8_t  int_to_allocated_str(const uint16_t number, uint8_t *point_result);
uint8_t read_record(const uint8_t number, const uint16_t * buffer);

#endif // EEPROM_H
