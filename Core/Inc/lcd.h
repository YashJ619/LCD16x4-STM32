/*
 * lcd.h
 *
 *  Created on: Mar 30, 2023
 *      Author: Yash
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "stm32f1xx_hal.h"

#define LCD_PIN_RS				GPIO_PIN_9
#define LCD_PIN_EN				GPIO_PIN_8
#define LCD_PIN_D0				GPIO_PIN_7
#define LCD_PIN_D1				GPIO_PIN_6
#define LCD_PIN_D2				GPIO_PIN_5
#define LCD_PIN_D3				GPIO_PIN_4
#define LCD_PIN_D4				GPIO_PIN_3
#define LCD_PIN_D5				GPIO_PIN_15
#define LCD_PIN_D6				GPIO_PIN_12
#define LCD_PIN_D7				GPIO_PIN_11

#define LCD_PORT_CTRL			GPIOB
#define LCD_PORT_D0_4			GPIOB
#define LCD_PORT_D5_7			GPIOA

#define CMD_FUNTIONSET			0x38U//
#define CMD_DISPLAYMODE	    	0x08U//
#define	CMD_DISPLAYCLEAR    	0x01U//
#define CMD_ENTRYMODE			0x04U//
#define CMD_RETURNHOME      	0x02U//
#define CMD_DISPLAY_SHIFT   	0x10U//
#define CMD_CGRAM_ADDR      	0x40U//
#define CMD_DDRAM_ADDR      	0x80U//

#define DISPLAY_ON	    		  0x04U//
#define DISPLAY_OFF	    		~(0x04U)//
#define CURSOR_ON     			  0x02U//
#define CURSOR_OFF     			~(0x02U)//
#define BLINK_ON      			  0x01U//
#define BLINK_OFF      			~(0x01U)//

#define ENTRYMODE_INC	   		  0x02U//
#define ENTRYMODE_DEC 		    ~(0x02U)//
#define ENTRYMODE_FLIP_ON         0x01U//
#define ENTRYMODE_FLIP_OFF      ~(0x01U)//

void lcd_gpio_init(void);
void lcd_init(void);
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_clear(void);
void lcd_send_data(uint8_t data);
void lcd_send_cmd(uint8_t cmd);
void write_8bit(uint8_t value);
void lcd_print(char *str);
void lcd_enable(void);
void lcd_oncursor(void);

#endif /* INC_LCD_H_ */
