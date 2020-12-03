/*
 * task.c
 *
 *  Created on: Nov 28, 2020
 *      Author: ACER
 */
#include "task.h"
#include "stm32f4xx_hal.h"
#include "hardwareinit.h"
#include "main.h"
#include "i2c-lcd.h"

UART_HandleTypeDef huart1;

#define delay       100   // 200ms
#define delay2		300   // 600ms
#define BTN500      HAL_GPIO_ReadPin(BTN1_GPIO_Port, BTN1_Pin)==GPIO_PIN_RESET
#define BTN1000     HAL_GPIO_ReadPin(BTN2_GPIO_Port, BTN2_Pin)==GPIO_PIN_RESET
#define LDBTN_ON    HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_RESET)
#define LDBTN_OFF   HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_SET)

#define LD500_ON    HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET)
#define LD500_OFF   HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET)

#define LD1000_ON   HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET)
#define LD1000_OFF  HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET)

#define LDSCS_ON    HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_SET)
#define LDSCS_OFF   HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_RESET)

enum tampil {t1, t2, t3, t4} tampilan;
enum state {s0, s1, s2, s3, s4} stateku;
unsigned int timedelay = 0;
unsigned int timedelay2 = 0;
unsigned char bouncing = 0xFF;
unsigned char bouncing2 = 0xFF;
int t_500 = 0;
int t_1000= 0;

void B500 (void)
{
	if (BTN500)
	{
		bouncing = (bouncing<<1);
		//LD500_ON;
	}
	else
		bouncing = (bouncing<<1)|1;
	if (bouncing==0x03)
	{
		t_500=1;
		LD500_ON;
	}

}

void B1000 (void)
{
	if (BTN1000)
	{
		bouncing2 = (bouncing2<<1);
		//LD1000_ON;
	}
	else
		bouncing2 = (bouncing2<<1)|1;
	if (bouncing2==0x03)
	{
		t_1000=1;
		LD1000_ON;
	}
}

void Task_Init (void)
{
	stateku=s0;
	tampilan=t1;
}

void Task_Run (void)
{
	switch (stateku)
	{
		case s0 :
		{
			LD500_OFF;
			LD1000_OFF;
			LDBTN_OFF;
			timedelay=0;
			timedelay2=0;

			lcd_put_cur(0,3);
			lcd_send_string("CANDY  MACHINE");
			lcd_put_cur(1,0);
			lcd_send_string("---Masukkan  Uang---");
			lcd_put_cur(2,0);
			lcd_send_string("H. Permen = Rp 1500");
			lcd_put_cur(3,0);
			lcd_send_string("Uang Anda = Rp ");

			if(t_500==1)
			{
				stateku = s1;
				LDBTN_ON;
				LD500_ON;
				t_500 = 0;
				lcd_clear();
				HAL_UART_Transmit(&huart1,(uint8_t*)"\n\rUang Anda    = Rp  500",25,10);
			}

			if(t_1000==1)
			{
				stateku = s2;
				LDBTN_ON;
				LD1000_ON;
				t_1000 = 0;
				lcd_clear;
				HAL_UART_Transmit(&huart1,(uint8_t*)"\n\rUang Anda    = Rp 1000",25,10);
			}
			break;
		}

		case s1 :
		{
			LD500_OFF;
			LDBTN_OFF;

			lcd_put_cur(0,3);
			lcd_send_string("CANDY  MACHINE");
			lcd_put_cur(1,0);
			lcd_send_string("---Masukkan  Uang---");
			lcd_put_cur(2,0);
			lcd_send_string("H. Permen = Rp 1500");
			lcd_put_cur(3,0);
			lcd_send_string("Uang Anda = Rp  500");

			if(t_500==1)
			{
				stateku = s2;
				LDBTN_ON;
				LD500_ON;
				t_500 = 0;
				lcd_clear();
				HAL_UART_Transmit(&huart1,(uint8_t*)"\n\rUang Anda    = Rp 1000",25,10);
			}

			if(t_1000==1)
			{
				stateku = s3;
				tampilan = t1;
				LDBTN_ON;
				LD1000_ON;
				t_1000 = 0;
				lcd_clear();
				HAL_UART_Transmit(&huart1,(uint8_t*)"\n\rUang Anda    = Rp 1500",25,10);
				HAL_UART_Transmit(&huart1,(uint8_t*)"\n\r---------------PROSES---------------",38,10);
			}

			break;
		}

		case s2 :
		{
			LD500_OFF;
			LD1000_OFF;
			LDBTN_OFF;

			lcd_put_cur(0,3);
			lcd_send_string("CANDY  MACHINE");
			lcd_put_cur(1,0);
			lcd_send_string("---Masukkan  Uang---");
			lcd_put_cur(2,0);
			lcd_send_string("H. Permen = Rp 1500");
			lcd_put_cur(3,0);
			lcd_send_string("Uang Anda = Rp 1000");

			if(t_500==1)
			{
				stateku = s3;
				tampilan = t1;
				LDBTN_ON;
				LD500_ON;
				t_500 = 0;
				lcd_clear();
				HAL_UART_Transmit(&huart1,(uint8_t*)"\n\rUang Anda    = Rp 1500",25,10);
				HAL_UART_Transmit(&huart1,(uint8_t*)"\n\r---------------PROSES---------------",38,10);
			}

			if(t_1000==1)
			{
				stateku = s4;
				tampilan = t3;
				LDBTN_ON;
				LD1000_ON;
				t_1000 = 0;
				lcd_clear();
				HAL_UART_Transmit(&huart1,(uint8_t*)"\n\rUang Anda    = Rp 2000",25,10);
				HAL_UART_Transmit(&huart1,(uint8_t*)"\n\r---------------PROSES---------------",38,10);
			}
			break;
		}

		case s3 :
		{
			LDBTN_OFF;
			LD500_OFF;
			LD1000_OFF;

			switch (tampilan)
			{
				case t1 :
				{
					lcd_put_cur(0,3);
					lcd_send_string("CANDY  MACHINE");
					lcd_put_cur(1,0);
					lcd_send_string("(((((((Proses)))))))");
					lcd_put_cur(2,0);
					lcd_send_string("H. Permen = Rp 1500");
					lcd_put_cur(3,0);
					lcd_send_string("Uang Anda = Rp 1500");

					if (++timedelay==delay)
					{
						lcd_clear();
						tampilan = t2;
						HAL_UART_Transmit(&huart1,(uint8_t*)"\n\rPembelian Berhasil :)",23,10);
						HAL_UART_Transmit(&huart1,(uint8_t*)"\n\rTerima Kasih",15,10);
					}
					break;
				}
				case t2 :
				{
					LDSCS_ON;

					lcd_put_cur(1,1);
					lcd_send_string("Pembelian Berhasil");
					lcd_put_cur(2,0);
					lcd_send_string("Selamat Menikmati :)");

					if (++timedelay2==delay2)
					{
						LDSCS_OFF;
						lcd_clear();
						stateku = s0;
						HAL_UART_Transmit(&huart1,(uint8_t*)"\n\r\n\r----------Masukkan  Uang------------",40,10);
						HAL_UART_Transmit(&huart1,(uint8_t*)"\n\rHarga Permen = Rp 1500",25,10);
						HAL_UART_Transmit(&huart1,(uint8_t*)"\n\rUang Anda    = Rp  -  ",25,10);
					}
					break;
				}
			}
			break;
		}

		case s4 :
		{
			LDBTN_OFF;
			LD1000_OFF;


			switch (tampilan)
			{
				case t3:
				{
					lcd_put_cur(0,3);
				    lcd_send_string("CANDY  MACHINE");
				    lcd_put_cur(1,0);
				    lcd_send_string("(((((((Proses)))))))");
					lcd_put_cur(2,0);
					lcd_send_string("H. Permen = Rp 1500");
					lcd_put_cur(3,0);
					lcd_send_string("Uang Anda = Rp 2000");

					if (++timedelay==delay)
					{
						lcd_clear();
						tampilan = t4;
						HAL_UART_Transmit(&huart1,(uint8_t*)"\n\rSilahkan ambil uang kembali (Rp 500)",38,10);
					}
					break;
				}
				case t4:
				{
					LD500_ON;
					lcd_put_cur(0,3);
					lcd_send_string("Silahkan ambil");
					lcd_put_cur(1,4);
					lcd_send_string("Uang Kembali");
					lcd_put_cur(3,0);
					lcd_send_string("-------Rp 500-------");

					if(t_500==1)
					{
						LD500_OFF;
					    stateku = s3;
					    tampilan = t1;
					    timedelay = 0;
					    timedelay2 = 0;
						t_500 = 0;
						lcd_clear();
						HAL_UART_Transmit(&huart1,(uint8_t*)"\n\rUang kembali (Rp 500) telah diambil",37,10);
						HAL_UART_Transmit(&huart1,(uint8_t*)"\n\r---------------PROSES---------------",38,10);
					}
					break;
				}
			}
			break;
		}

	}
}
