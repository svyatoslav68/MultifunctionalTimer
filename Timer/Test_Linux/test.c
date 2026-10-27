#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "timer.h"
#include "EEPROM.h"
#include "display.h"

extern uint16_t  records_in_ROM[MAX_NUMBER_RECORDS][LENGTH_BACKEND_TIMER];

#define NUMBER_TEST_1 2
#define NUMBER_TEST_2 4
#define NUMBER_TEST_3 3

int scan_array(FILE *fp, uint16_t * array){
    for(int i = 0; i < LENGTH_TIMER_STRING; ++i){
        fscanf(fp,"%x",array +i); 
        //printf("%d: word = %x, ", i, *(array + i));
        if (*(array+i) == 0xffff)
            break;
    }
}

int print_array(FILE *fp, uint16_t *array){
    for(int i = 0; i < LENGTH_TIMER_STRING; ++i){
        fprintf(fp, "0x%04hx ", *(array + i));
    }
    fprintf(fp, "\n");
}

int main(int argc, char ** argv){
	FILE *fp_input;
	FILE *fp_output;
	const char *name_file_input_data = "input.data";
	if ((fp_input = fopen(name_file_input_data, "r")) == NULL) {
		printf("Ошибка при открытии файла %s\n", name_file_input_data);
		exit(1);
	}
	const char *name_file_output_data = "output.data";
	if ((fp_output = fopen(name_file_output_data, "r")) == NULL) {
		printf("Ошибка при открытии файла %s\n", name_file_output_data);
		exit(1);
	}
	uint16_t string_timer[LENGTH_TIMER_STRING];
    scan_array(fp_input, *records_in_ROM);
    scan_array(fp_input, *records_in_ROM + LENGTH_BACKEND_TIMER);
	//read_record(1, string_timer);
    /*print_array(stdout, *records_in_ROM);
    print_array(stdout, *records_in_ROM + LENGTH_BACKEND_TIMER);*/
	uint16_t record_from_rom[LENGTH_BACKEND_TIMER];
	for (uint8_t i = 0; i < NUMBER_TEST_1; ++i){
		if (read_record(i, record_from_rom) < 1){ 
			break;
		}
		else {
			uint8_t *buffer_display_string = (uint8_t *)malloc(record_from_rom[0] + 1);
			uint16_t length_string_from_file;
			fscanf(fp_output, "%d", &length_string_from_file);
			uint8_t *string_from_file = (uint8_t *)malloc(length_string_from_file + 1);	
			fscanf(fp_output, "%s", string_from_file);
			printf("length = %u, string_from_file = %s\n", length_string_from_file, string_from_file);
			if((length_string_from_file == display_string(record_from_rom + 1, buffer_display_string, i)) && !strncmp(string_from_file, buffer_display_string, length_string_from_file)){
					printf("Test %d.%d Ok!\n", 1, i);
			}
			else{
					printf("Test %d.%d Fail!!!\n", 1, i);
			}
			free(string_from_file);
			free(buffer_display_string);
		}
	}
}
