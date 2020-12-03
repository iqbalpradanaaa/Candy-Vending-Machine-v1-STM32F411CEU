/*
 * seos.c
 *
 *  Created on: Dec 2, 2020
 *      Author: ACER
 */
#include "main.h"
#include "hardwareinit.h"
#include "seos.h"
#include "task.h"

TIM_HandleTypeDef htim3;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM3)
	{
		//Task_Init();
		B500();
		B1000();
		Task_Run();
		//Button();
	}
}

