#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "EEPROM.h"
#include "display.h"

#define NUMBER_TEST_1 3
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
    //scan_array(fp_input, string_timer);
	//read_record(1, string_timer);
    display_from_ROM();
    //print_array(stdout, string_timer);
}
