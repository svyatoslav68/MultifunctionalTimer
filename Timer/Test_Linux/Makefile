TARGET=test
DEST_DIR=./
OBJECT_DIR=./build
TEST_DIR=./test
SRC_DIR=..
HEADERS_DIR=..

SOURCES=EEPROM.c display.c test.c
OBJS=$(SOURCES:%.c=$(OBJECT_DIR)/%.o)

all:$(DEST_DIR)/$(TARGET)

$(DEST_DIR)/$(TARGET):$(OBJS)
	$(LINK.o) $^ -o$@ 

$(OBJECT_DIR)/test.o:./test.c
	$(COMPILE.c) -D TEST -I $(HEADERS_DIR) $< -o $@

$(OBJECT_DIR)/%.o:$(SRC_DIR)/%.c
	$(COMPILE.c) -D TEST -I $(HEADERS_DIR) $< -o $@ 

.PHONY: runtest
runtest:
	./test

.PHONY: clean
clean:
	rm -rf *.o $(OBJECT_DIR)/*.o $(DEST_DIR)/$(TARGET) $(DEST_DIR)/test

