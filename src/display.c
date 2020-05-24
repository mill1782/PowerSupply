#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include "display.h"

void setupGPIO(){
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	GPIOB->MODER |= (1 << (2 * DISP_CATHODE_1)) +
					(1 << (2 * DISP_CATHODE_2)) +
					(1 << (2 * DISP_CATHODE_3)) +
					(1 << (2 * DISP_SRCLK)) +
					(1 << (2 * DISP_RCLK)) +
					(1 << (2 * DISP_VOLT_SRL)) +
					(1 << (2 * DISP_CURRENT_SRL));
}


