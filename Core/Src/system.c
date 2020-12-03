/*
 * system.c
 *
 *  Created on: Dec 2, 2020
 *      Author: ACER
 */
#include "main.h"
#include "hardwareinit.h"
#include "system.h"
#include "i2c-lcd.h"

TIM_HandleTypeDef htim3;
UART_HandleTypeDef huart1;

void system (void)
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_I2C1_Init();
	MX_TIM3_Init(2);
	MX_USART1_UART_Init();

	lcd_init();
	lcd_put_cur(1,3);
	lcd_send_string ("CANDY  MACHINE");
	lcd_put_cur(2, 1);
	lcd_send_string("3D4EA | 1110181004");
	HAL_Delay(2500);
	lcd_clear ();
	lcd_put_cur(1,3);
	lcd_send_string ("SELAMAT DATANG");
	HAL_Delay(1000);
	lcd_put_cur(2, 3);
	lcd_send_string ("SELAMAT BELANJA");
	HAL_Delay(2000);
	lcd_clear();

	HAL_UART_Transmit(&huart1,(uint8_t*)"\n\r((Tugas Teori Sistem Embedded 2020))",38,10);
	HAL_UART_Transmit(&huart1,(uint8_t*)"\n\r----------Candy  Machine------------",38,10);
	HAL_UART_Transmit(&huart1,(uint8_t*)"\n\r--------3D4EA---1110181004----------",38,10);
	HAL_UART_Transmit(&huart1,(uint8_t*)"\n\r----------Masukkan  Uang------------",38,10);
	HAL_UART_Transmit(&huart1,(uint8_t*)"\n\rHarga Permen = Rp.1500",25,10);
	HAL_UART_Transmit(&huart1,(uint8_t*)"\n\rUang Anda    = Rp. -  ",25,10);

	HAL_TIM_Base_Start_IT(&htim3);
}
