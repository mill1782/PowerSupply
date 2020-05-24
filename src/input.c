#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include "input.h"

void setupGPIO(){
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	GPIOB->MODER |= (1 << (2 * VOLTAGE_IN)) +
					(1 << (2 * CURRENT_IN)) +
					(1 << (2 * CURRENT_LIMIT_IN)) +
					(1 << (2 * VOLTAGE_SNS_IN));
}
