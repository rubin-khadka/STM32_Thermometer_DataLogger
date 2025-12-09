/*
 * spi1_config.c
 *
 *  Created on: Dec 4, 2025
 *      Author: Rubin Khadka
 */

#include "spi1_config.h"
#include "main.h"

void SPI1_init(void)
{
  // Enable Peripheral Clock
  RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

  // Disable SPI to configure it
  SPI1->CR1 &= ~SPI_CR1_SPE;

  // Reset Control Registers
  SPI1->CR1 = 0;
  SPI1->CR2 = 0;

  // Select Master Mode
  SPI1->CR1 |= SPI_CR1_MSTR;

  // Select Baud Rate
  SPI1->CR1 |= (0x1 << 3);

  // Software NSS Management
  SPI1->CR1 |= SPI_CR1_SSM;
  SPI1->CR1 |= SPI_CR1_SSI;

  // Data Format Mode
  SPI1->CR1 |= SPI_CR1_DFF;

  // MSB First
  SPI1->CR1 &= ~SPI_CR1_LSBFIRST;

  // Mode 1: CPOL=0, CPHA=1
  SPI1->CR1 &= ~SPI_CR1_CPOL;
  SPI1->CR1 &= ~SPI_CR1_CPHA;

  // Enable SPI
  SPI1->CR1 |= SPI_CR1_SPE;

  // Dummy read to clear status flags
  (void) SPI1->SR;
  (void) SPI1->DR;

  // Wait for SPI to be ready
  while(SPI1->SR & SPI_SR_BSY);
}

void SPI1_Transmit16(uint16_t data)
{
  // Wait until TX buffer is empty
  while(!(SPI1->SR & SPI_SR_TXE));

  // Write 16-bit data to Data Register
  SPI1->DR = data;

  // Wait for transmission to complete
  while(SPI1->SR & SPI_SR_BSY);

  // Clear RX buffer
  if(SPI1->SR & SPI_SR_RXNE) {
    (void)SPI1->DR;
  }
}
