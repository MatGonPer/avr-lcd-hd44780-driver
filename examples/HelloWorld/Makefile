MCU       = atmega328p
F_CPU 		= 16000000UL
TARGET    = main

CC        = avr-gcc
OBJCOPY   = avr-objcopy
AVRDUDE   = avrdude
SIZE      = avr-size

DETECTED_PORT := $(shell ls /dev/ttyACM* /dev/ttyUSB* 2>/dev/null | head -n 1)

ifdef DETECTED_PORT
    PORT ?= $(DETECTED_PORT)
else
    PORT ?= COM3
endif

BAUD      = 115200
PROGRAMMER= arduino
DUDEFLAGS = -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUD) -D

LIB_DIR = ../../src

SRCS = main.c $(LIB_DIR)/lcd_driver.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -Os -Wall -mmcu=$(MCU) -DF_CPU=$(F_CPU) -I$(LIB_DIR)
LDFLAGS = -mmcu=$(MCU)

all: $(TARGET).hex

$(TARGET).elf: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: $(LIB_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@
	@echo "--------------------------------------"
	@echo "Build Completo!"
	@echo "Tamanho do Firmware:"
	@$(SIZE) --format=avr --mcu=$(MCU) $(TARGET).elf
	@echo "--------------------------------------"

upload: $(TARGET).hex
	@echo "Tentando upload na porta: $(PORT)"
	$(AVRDUDE) $(DUDEFLAGS) -U flash:w:$(TARGET).hex:i

clean:
	rm -f $(TARGET).elf $(TARGET).hex $(OBJS)

.PHONY: all upload clean
