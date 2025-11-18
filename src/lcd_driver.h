// Driver for LCD Display 16x2 Hitachi HD44780 4-bits Mode
// For ATmega328P Arduino Uno R3

#ifndef LCD_DRIVER_H
#define LCD_DRIVER_H

#include <stdint.h>

// Configures all control/data pins as output
// Must be called once in setup
void lcd_init(void);

// Sends a single-byte command to the LCD
// (Ex: 0x01 to clear screen)
void lcd_command(uint8_t cmd);

// Sends a character data (ASCII) to the LCD
void lcd_char(char data);

// Sends a string (ending in null) to the LCD
void lcd_print(char *str);

// Move the cursor to a position (Line, Column)
// Line 0 (first line) or 1 (second line)
// Column 0 to 15
void lcd_set_cursor(uint8_t line, uint8_t column);

#endif
