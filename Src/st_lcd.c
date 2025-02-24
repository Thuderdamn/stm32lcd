/*
 * st_lcd.c
 *
 *  Created on: Dec 7, 2024
 *      Author: dell
 */
#include "main.h"
#include "lcd.h"
#include "stm32f4xx_hal.h"


#define LCD_EN GPIO_PIN_13
#define LCD_RS GPIO_PIN_14
#define LCD_D0 GPIO_PIN_2
#define LCD_D1 GPIO_PIN_3
#define LCD_D2 GPIO_PIN_4
#define LCD_D3 GPIO_PIN_5
#define LCD_D4 GPIO_PIN_6
#define LCD_D5 GPIO_PIN_7
#define LCD_D6 GPIO_PIN_8
#define LCD_D7 GPIO_PIN_9

void LCD_STROBE()
{
HAL_GPIO_WritePin(GPIOC,LCD_EN,GPIO_PIN_SET);
HAL_Delay(1);
HAL_GPIO_WritePin(GPIOC,LCD_EN,GPIO_PIN_RESET);
HAL_Delay(1);
}

void lcd_write_cmd(unsigned char c)
{
	GPIOB->ODR = c;  // Directly send the 8-bit command/data to the GPIO data lines
	    HAL_GPIO_WritePin(GPIOC, LCD_RS, GPIO_PIN_RESET);  // RS = 0 for command
	    LCD_STROBE();     // Pulse the Enable pin to latch the command

	    HAL_Delay(5);  // Small delay to ensure the LCD processes the command
}

void lcd_write_data(unsigned char c)
{
unsigned int d;
d = c;
GPIOB->ODR = (d << 2); // Output to GPIOA
HAL_GPIO_WritePin(GPIOC,LCD_RS,GPIO_PIN_SET); // Set RS HIGH
LCD_STROBE();
}

void lcd_clear(void)
{
lcd_write_cmd(0x1);
HAL_Delay(5);
}
//
// Display text message on LCD
//
void lcd_puts(const char * s)
{
while(*s)
lcd_write_data(*s++);
}
//
// Display single character on LCD

//
// Position the cursor at column, row
//
void lcd_goto( int row)
{
uint16_t address;
if(row == 0)address = 0;
if(row == 1)address = 0x0100;

lcd_write_cmd(address);
}
//
// Initialize the LCD
//
void lcd_init(void)
	{
	    // Step 1: Clear GPIOB
	    GPIOB->ODR = 0;        // Clear all GPIOB pins (initial state)
	    HAL_Delay(50);         // Wait for LCD to power up

	    // Step 2: Initialize 8-bit mode (command 0x38)
	    GPIOB->ODR = 0x00E0;     // Set the data lines to 0x38 (binary 0011 1000)
	    HAL_GPIO_WritePin(GPIOB, LCD_RS, GPIO_PIN_RESET);  // RS = 0 (Command mode)
	    LCD_STROBE();          // Pulse the Enable pin to latch the data
	    HAL_Delay(5);          // Wait for the command to be processed

	    // Step 3: Turn on the display (command 0x0F)
	    lcd_write_cmd(0x003C);   // Display ON, Cursor ON, Blink ON
	    HAL_Delay(5);          // Wait for the command to be processed

	    // Step 4: Clear the display (command 0x01)
	    lcd_write_cmd(0x0004);   // Clear the display
	    HAL_Delay(5);          // Wait for the display to clear

	    // Step 5: Set cursor to move right (command 0x06)
	    lcd_write_cmd(0x0050);   // Set cursor to move right after each character
	    HAL_Delay(5);          // Wait for the command to be processed

	}

