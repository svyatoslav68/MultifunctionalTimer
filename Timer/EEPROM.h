#ifndef EEPROM_H
#define EEPROM_H

#define MAX_NUMBER_RECORDS 10

int8_t read_record(const uint8_t number, const uint16_t * buffer);

#endif // EEPROM_H
