#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "lcd_driver.h"

int main(void) {
  // Initializes the driver
  lcd_init();
  // Print test
  lcd_print("Hello World!");

  // Cursor test
  lcd_set_cursor(1, 2); // Line 1 (The bottom), Collum 2
  lcd_print("Driver v1.0");

  // Loop test
  while (1) {
    // Let's do a simple blink string effect at the bottom line
    _delay_ms(1000);

    lcd_set_cursor(1, 2);
    lcd_print("                ");

    _delay_ms(500);

    lcd_set_cursor(1, 2);
    lcd_print("Driver v1.0");
  }

  return 0;
}
