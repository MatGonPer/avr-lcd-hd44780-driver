#include "lcd_driver.h"

#include <avr/io.h>
#include <util/delay.h>

// 16Mhz Arduino Uno R3
#define F_CPU 16000000UL

// Controll Pins mapped to PORTB (Arduino Uno R3 Digital Pins PB0-PB7)
#define LCD_CTRL_PORT PORTB
#define LCD_CTRL_DDR  DDRB
#define LCD_RS_PIN    PB0 // PIN 8 = RS
#define LCD_E_PIN     PB1 // PIN 9 = E

// Data Pins mapped to PORTD (Arduino Uno R3 Digital Pins PD0-PD7)
#define LCD_DATA_PORT PORTD
#define LCD_DATA_DDR  DDRD
#define LCD_D4_PIN    PD4 // PIN 4 = D4
#define LCD_D5_PIN    PD5 // PIN 5 = D5
#define LCD_D6_PIN    PD6 // PIN 6 = D6
#define LCD_D7_PIN    PD7 // PIN 7 = D7

static void lcd_pulse_enable(void) {
  LCD_CTRL_PORT |= (1 << LCD_E_PIN); 
  _delay_us(1);
  LCD_CTRL_PORT &= ~(1 << LCD_E_PIN);
  _delay_us(100);
}

static void lcd_send_4bits(uint8_t data) {
  LCD_DATA_PORT &= ~( (1 << LCD_D4_PIN) | (1 << LCD_D5_PIN) | (1 << LCD_D6_PIN) | (1 << LCD_D7_PIN));

  if (data & (1 << 0)) LCD_DATA_PORT |= (1 << LCD_D4_PIN);
  if (data & (1 << 1)) LCD_DATA_PORT |= (1 << LCD_D5_PIN);
  if (data & (1 << 2)) LCD_DATA_PORT |= (1 << LCD_D6_PIN);
  if (data & (1 << 3)) LCD_DATA_PORT |= (1 << LCD_D7_PIN);

  lcd_pulse_enable();
}

static void lcd_send_byte(uint8_t data, uint8_t mode) {
  if (mode)
    LCD_CTRL_PORT |= (1 << LCD_RS_PIN);
  else
    LCD_CTRL_PORT &= ~(1 << LCD_RS_PIN);

  lcd_send_4bits(data >> 4);
  lcd_send_4bits(data & 0x0F);
}

void lcd_command(uint8_t cmd) {
  lcd_send_byte(cmd, 0);
}

void lcd_char(char data) {
  lcd_send_byte(data, 1);
}

void lcd_print(char *str) {
  while (*str) {
    lcd_char(*str++);
  }
}

void lcd_set_cursor(uint8_t line, uint8_t column) {
  uint8_t addr;
  if (line == 0)
    addr = 0x00 + column;
  else
    addr = 0x40 + column;

  lcd_command(0x80 | addr);
}

void lcd_init(void) {
  LCD_CTRL_DDR |= (1 << LCD_RS_PIN) | (1 << LCD_E_PIN);
  LCD_DATA_DDR |= (1 << LCD_D4_PIN) | (1 << LCD_D5_PIN) | (1 << LCD_D6_PIN) | (1 << LCD_D7_PIN);

  _delay_ms(50);
  lcd_send_4bits(0x03); _delay_ms(5);
  lcd_send_4bits(0x03); _delay_us(100);
  lcd_send_4bits(0x03); _delay_us(100);
  lcd_send_4bits(0x02); _delay_us(100);

  lcd_command(0x28);
  lcd_command(0x0C);
  lcd_command(0x06);
  lcd_command(0x01);
  _delay_ms(2);
}
