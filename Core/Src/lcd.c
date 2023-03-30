/*
 * lcd.c
 *
 *  Created on: Mar 30, 2023
 *      Author: Yash
 */

#include "lcd.h"

uint8_t _displayset = 0;
uint8_t _entryset = 0;
uint8_t _shiftset = 0;

void lcd_gpio_init(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	GPIO_InitTypeDef GPIOx = {0};

	HAL_GPIO_WritePin(LCD_PORT_CTRL, LCD_PIN_RS | LCD_PIN_EN, GPIO_PIN_RESET);

	GPIOx.Pin = LCD_PIN_RS | LCD_PIN_EN;
	GPIOx.Mode = GPIO_MODE_OUTPUT_PP;
	GPIOx.Pull = GPIO_NOPULL;
	GPIOx.Speed = GPIO_SPEED_FREQ_HIGH;

	HAL_GPIO_Init(LCD_PORT_CTRL, &GPIOx);

	HAL_GPIO_WritePin(LCD_PORT_D0_4, LCD_PIN_D0 | LCD_PIN_D1 | LCD_PIN_D2 | LCD_PIN_D3 | LCD_PIN_D4, GPIO_PIN_RESET);

	GPIOx.Pin = LCD_PIN_D0 | LCD_PIN_D1 | LCD_PIN_D2 | LCD_PIN_D3 | LCD_PIN_D4;
	GPIOx.Mode = GPIO_MODE_OUTPUT_PP;
	GPIOx.Pull = GPIO_NOPULL;
	GPIOx.Speed = GPIO_SPEED_FREQ_HIGH;

	HAL_GPIO_Init(LCD_PORT_D0_4, &GPIOx);

	HAL_GPIO_WritePin(LCD_PORT_D5_7, LCD_PIN_D5 | LCD_PIN_D6 | LCD_PIN_D7, GPIO_PIN_RESET);

	GPIOx.Pin = LCD_PIN_D5 | LCD_PIN_D6 | LCD_PIN_D7;
	GPIOx.Mode = GPIO_MODE_OUTPUT_PP;
	GPIOx.Pull = GPIO_NOPULL;
	GPIOx.Speed = GPIO_SPEED_FREQ_HIGH;

	HAL_GPIO_Init(LCD_PORT_D5_7, &GPIOx);

}

void lcd_init()
{
	HAL_Delay(10);
	lcd_send_cmd(CMD_FUNTIONSET);
	HAL_Delay(5);

	lcd_send_cmd(CMD_FUNTIONSET);
	HAL_Delay(1);

	lcd_send_cmd(CMD_FUNTIONSET);

	lcd_send_cmd(CMD_FUNTIONSET);

	_displayset |= (CMD_DISPLAYMODE | DISPLAY_ON);
	lcd_send_cmd(_displayset);
	HAL_Delay(1);

	lcd_send_cmd(CMD_DISPLAYCLEAR);
	HAL_Delay(3);

	_entryset |= (CMD_ENTRYMODE | ENTRYMODE_INC);
	lcd_send_cmd(_entryset);
	HAL_Delay(1);
}


void lcd_enable()
{
	HAL_GPIO_WritePin(LCD_PORT_CTRL, LCD_PIN_EN, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(LCD_PORT_CTRL, LCD_PIN_EN, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(LCD_PORT_CTRL, LCD_PIN_EN, GPIO_PIN_RESET);
	HAL_Delay(1);
}

void write_8bit(uint8_t value)
{
	HAL_GPIO_WritePin(LCD_PORT_D5_7, LCD_PIN_D7, (value >> 7) & 0x1);
	HAL_GPIO_WritePin(LCD_PORT_D5_7, LCD_PIN_D6, (value >> 6) & 0x1);
	HAL_GPIO_WritePin(LCD_PORT_D5_7, LCD_PIN_D5, (value >> 5) & 0x1);
	HAL_GPIO_WritePin(LCD_PORT_D0_4, LCD_PIN_D4, (value >> 4) & 0x1);
	HAL_GPIO_WritePin(LCD_PORT_D0_4, LCD_PIN_D3, (value >> 3) & 0x1);
	HAL_GPIO_WritePin(LCD_PORT_D0_4, LCD_PIN_D2, (value >> 2) & 0x1);
	HAL_GPIO_WritePin(LCD_PORT_D0_4, LCD_PIN_D1, (value >> 1) & 0x1);
	HAL_GPIO_WritePin(LCD_PORT_D0_4, LCD_PIN_D0, (value >> 0) & 0x1);

	lcd_enable();
}

void lcd_send_cmd(uint8_t cmd)
{
	HAL_GPIO_WritePin(LCD_PORT_CTRL, LCD_PIN_RS, GPIO_PIN_RESET);
	write_8bit(cmd);
}

void lcd_clear()
{
	lcd_send_cmd(CMD_DISPLAYCLEAR);
	HAL_Delay(3);
}


void lcd_send_data(uint8_t data)
{
	HAL_GPIO_WritePin(LCD_PORT_CTRL, LCD_PIN_RS, GPIO_PIN_SET);
	write_8bit(data);
}

void lcd_oncursor()
{
	_displayset |= (CMD_DISPLAYMODE | CURSOR_ON);
	lcd_send_cmd(_displayset);
}

void lcd_print(char *str)
{
	do
	{
		lcd_send_data((uint8_t)*str);
		str++;
	}while(*str != '\0');
}


void lcd_set_cursor(uint8_t row, uint8_t col)
{
	col--;
	switch(row)
	{
	case 1:
		lcd_send_cmd(col |= 0x80);
		break;
	case 2:
		lcd_send_cmd(col |= 0xC0);
		break;
	case 3:
		lcd_send_cmd(col |= 0x90);
		break;
	case 4:
		lcd_send_cmd(col |= 0xD0);
		break;
	default:
		break;
	}
}
