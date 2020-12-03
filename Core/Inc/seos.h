/*
 * seos.h
 *
 *  Created on: Dec 2, 2020
 *      Author: ACER
 */

#ifndef INC_SEOS_H_
#define INC_SEOS_H_
#include <stdint.h>

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void MX_TIM3_Init(uint32_t Periode);

#endif /* INC_SEOS_H_ */
