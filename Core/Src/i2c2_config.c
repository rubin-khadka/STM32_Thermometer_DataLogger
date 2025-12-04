/*
 * i2c2_config.c
 *
 *  Created on: Nov 30, 2025
 *      Author: Rubin Khadka
 */

#include "i2c2.h"
#include "main.h"

void I2C2_Init(void)
{
  // Enable I2C2 clock
  RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;

  // Disable I2C2
  I2C2->CR1 &= ~I2C_CR1_PE;

//  while(I2C2->CR1 & I2C_CR1_PE);

  // Reset I2C2 Peripheral
  I2C2->CR1 |= I2C_CR1_SWRST;   // Assert software reset
  I2C2->CR1 &= ~I2C_CR1_SWRST;  // Release software reset

  // Set Peripheral Clock Frequency (36 MHz)
  I2C2->CR2 = (0x24 << 0);

  // Configure CCR for Standard Mode 100KHz with 36MHz peripheral clock
  I2C2->CCR = (0xA0 << 0);

  // Configure TRISE
  I2C2->TRISE = (0x25 << 0);

  // Configure Own Address Register so that there is no conflict
  //I2C2->OAR1 = 0x4000;  // Bit14=1, ADDMODE=0 (7-bit)

  I2C2->CR |= I2C_CR2_ITBUFEN;    // Buffer Interrupt Enable
  I2C2->CR |= I2C_CR2_ITEVTEN;    // Event Interrupt Enable

  I2C2->CR1 |= I2C_CR1_ACK;
  // Enable I2C2
  I2C2->CR1 |= I2C_CR1_PE;

  HAL_Delay(100);
}


