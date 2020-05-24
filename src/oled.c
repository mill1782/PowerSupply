#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include "oled.h"

uint16_t dispmem[34] = {
        0x080 + 0,
        0x220, 0x220, 0x220, 0x220, 0x220, 0x220, 0x220, 0x220,
        0x220, 0x220, 0x220, 0x220, 0x220, 0x220, 0x220, 0x220,
        0x080 + 64,
        0x220, 0x220, 0x220, 0x220, 0x220, 0x220, 0x220, 0x220,
        0x220, 0x220, 0x220, 0x220, 0x220, 0x220, 0x220, 0x220,
};
void spi_cmd(char b) {
    while((SPI2->SR & SPI_SR_TXE) == 0);
    SPI2->DR = b;
}

void nano_wait(unsigned int n) {
    asm(    "        mov r0,%0\n"
            "repeat: sub r0,#83\n"
            "        bgt repeat\n" : : "r"(n) : "r0", "cc");
}

void generic_lcd_startup(void) {
    nano_wait(100000000); // Give it 100ms to initialize
    spi_cmd(0x38);  // 0011 NF00 N=1, F=0: two lines
    spi_cmd(0x0c);  // 0000 1DCB: display on, no cursor, no blink
    spi_cmd(0x01);  // clear entire display
    nano_wait(6200000); // clear takes 6.2ms to complete
    spi_cmd(0x02);  // put the cursor in the home position
    spi_cmd(0x06);  // 0000 01IS: set display to increment
}

void setupPorts(void) {
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
    GPIOB->MODER |= 0x8A000000;
    GPIOB->BSRR = 1 << 12;
    GPIOB->BRR = (1 << 13) +
    			 (1 << 15);

    RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
    SPI2->CR1 |= SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE | SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0 | SPI_CR1_MSTR;
    SPI2->CR1 &= ~(SPI_CR1_CPOL | SPI_CR1_CPHA);
    SPI2->CR2 = SPI_CR2_DS_3 | SPI_CR2_DS_0 | SPI_CR2_SSOE | SPI_CR2_NSSP;
    SPI2->CR1 |= SPI_CR1_SPE;

    generic_lcd_startup();
}

void initOLED(void) {
    setupPorts();
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;
    DMA1_Channel5->CCR &= ~DMA_CCR_EN;
    DMA1_Channel5->CCR |= DMA_CCR_PSIZE_0;
    DMA1_Channel5->CPAR = (uint32_t) (&(SPI2->DR));
    DMA1_Channel5->CMAR = (uint32_t) dispmem;
    DMA1_Channel5->CCR |= DMA_CCR_MSIZE_0;
    DMA1_Channel5->CCR |= DMA_CCR_PSIZE_0;
    DMA1_Channel5->CCR |= DMA_CCR_DIR;
    DMA1_Channel5->CCR |= DMA_CCR_CIRC;
    DMA1_Channel5->CNDTR = 34;
    DMA1_Channel5->CCR |= DMA_CCR_MINC;
    DMA1_Channel5->CCR &= ~DMA_CCR_PL;
    SPI2->CR2 |= SPI_CR2_TXDMAEN;

    DMA1_Channel5->CCR |= DMA_CCR_EN;
}

void display1(const char *s) {
    spi_cmd(0x80);
    int x;
    for(x = 0; x < 16; x++)
        if (s[x])
            dispmem[x+1] = 0x200 + s[x];
        else
            break;
    for(; x < 16; x++) //Clear the remainder of the line
        dispmem[x+1] = 0x220;
}

void display2(const char *s) {
    spi_cmd(0x80);
    int x;
    for(x = 0; x < 16; x++)
        if (s[x])
            dispmem[x+18] = 0x200 + s[x];
        else
            break;
    for(; x < 16; x++) //Clear the remainder of the line
        dispmem[x+18] = 0x220;
}
