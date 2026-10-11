TARGET=timer
DEST_DIR=./debug
OBJECT_DIR=./build
SRC_DIR=.
HEADERS_DIR=.

# Программы и настройки для прошивки
FTPROG	  = avrdude
# HARDPROG      = 2ftbb
HARDPROG      = avrftdi

DEV_FOR_AVRDUDE = m16
MCU = atmega16a

# Программы  настройки для компиляции и сборки
CC            = avr-gcc
LINK          = avr-gcc
OBJCOPY		  = avr-objcopy
CFLAGS        = -mmcu=$(MCU) -Os -Wall -ggdb -W -D_REENTRANT -std=gnu99 -D F_CPU=16000000UL#-pthread $(DEFINES)
LDFLAGS        = -mmcu=$(MCU) -Wl,-Os #-pthread

SOURCES=main.c \
		button.c \
	   	display.c \
		EEPROM.c \
		encoder.c \
		functions.c \
		RTOS.c \
		timer_queue.c \
		timer_task_manager.c \
		lcd_lib_2.c

OBJS=$(SOURCES:%.c=$(OBJECT_DIR)/%.o)

all:$(DEST_DIR)/$(TARGET)

$(DEST_DIR)/$(TARGET):$(OBJS)
	$(LINK.o) $^ -o$@.elf 
	$(OBJCOPY) -O binary $@.elf $@.bin
	$(OBJCOPY) -j .text -j .data -O ihex $@.elf $@.hex
	$(OBJCOPY) -j .eeprom -O ihex $@.elf $@.eep

$(OBJECT_DIR)/%.o:$(SRC_DIR)/%.c
	$(COMPILE.c) -I $(HEADERS_DIR) $< -o $@ 

.PHONY: clean
clean:
	rm -rf *.o $(OBJECT_DIR)/*.o $(DEST_DIR)/$(TARGET).*
