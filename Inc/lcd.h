/*
 * lcd.h
 *
 *  Created on: Dec 7, 2024
 *      Author: dell
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

void LCD_STROBE(void);
void lcd_write_cmd(unsigned char);
void lcd_write_data(unsigned char);
void lcd_clear(void);
void lcd_puts(const char * s);
void lcd_putch(char c);
void lcd_goto(int row);
void lcd_init(void);


#endif /* INC_LCD_H_ */
