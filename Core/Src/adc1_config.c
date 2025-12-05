/*
 * adc1_config.c
 *
 *  Created on: Dec 5, 2025
 *      Author: Rubin Khadka
 */

#include "adc1_config.h"
#include "main.h"

// Global variables
volatile uint16_t adc_buffer[NUM_CHANNELS];
volatile uint8_t adc_data_ready = 0;

/* Initialize ADC1 for temperature measurement */
void ADC1_Init(void)
{
  // Enable clocks
  RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
  RCC->AHBENR |= RCC_AHBENR_DMA1EN;

  // Power on ADC
  ADC1->CR2 |= ADC_CR2_ADON;

  // Configure Sampling times , 28.5 sampling cycles
  ADC1->SMPR2 &= ~(0x7 << 0);
  ADC1->SMPR2 |= (0x3 << 0);
  ADC1->SMPR2 &= ~(0x7 << 3);
  ADC1->SMPR2 |= (0x3 << 3);
  ADC1->SMPR2 &= ~(0x7 << 6);
  ADC1->SMPR2 |= (0x3 << 6);

  // Enable Scan Mode
  ADC1->CR1 |= ADC_CR1_SCAN;

  // Configure Sequence Length
  ADC1->SQR1 &= ~(0xF << 20);
  ADC1->SQR1 |= (0x2 << 20);

  // Configure Channel Sequence
  ADC1->SQR3 = 0;           // Clear entire register
  ADC1->SQR3 = (0 << 0) |   // SQ1 = Channel 0
      (1 << 5) |            // SQ2 = Channel 1
      (2 << 10);            // SQ3 = Channel 2

  // ADC calibration
  ADC1->CR2 |= ADC_CR2_RSTCAL;
  while(ADC1->CR2 & ADC_CR2_RSTCAL);

  ADC1->CR2 |= ADC_CR2_CAL;
  while(ADC1->CR2 & ADC_CR2_CAL);

  // Enable DMA for ADC
  ADC1->CR2 |= ADC_CR2_DMA;
  ADC1->CR2 &= ~ADC_CR2_CONT;   // Single conversion mode
  ADC1->CR2 &= ~ADC_CR2_ALIGN;  // Right alignment

  // Configure software trigger
  ADC1->CR2 &= ~(0x7 << 17);      // Clear EXTSEL bits
  ADC1->CR2 |= (0x7 << 17);       // EXTSEL[2:0] = 111 (Software trigger)
  ADC1->CR2 |= ADC_CR2_EXTTRIG;   // Enable external trigger

  ADC1_DMA_Config();

  // Clear buffer
  for(int i = 0; i < NUM_CHANNELS; i++)
  {
    adc_buffer[i] = 0;
  }
  adc_data_ready = 0;

  // Brief stabilization delay
  for(volatile uint32_t i = 0; i < 100000; i++);  // Approx 1ms delay
}

void ADC1_DMA_Config(void)
{
  // Disable DMA before configuration
  DMA1_Channel1->CCR &= ~DMA_CCR_EN;

  // Configure DMA Channel 1
  DMA1_Channel1->CPAR = (uint32_t) &(ADC1->DR);
  DMA1_Channel1->CMAR = (uint32_t) adc_buffer;
  DMA1_Channel1->CNDTR = 3;

  // Configure control register
  DMA1_Channel1->CCR = 0; // Reset the register first
  DMA1_Channel1->CCR = (0b01 << 12) |   // Medium priority
      (0b01 << 10) |                    // Memory: 16-bit
      (0b01 << 8) |                     // Peripheral: 16-bit
      (1 << 7) |                        // Memory increment: YES
      (0 << 6) |                        // Peripheral increment: NO
      (0 << 5) |                        // Circular mode: DISABLED
      (0 << 4) |                        // Direction: Peripheral to memory
      (0 << 3) |                        // TEIE = 0: No error interrupt
      (0 << 2) |                        // HTIE = 0: No half transfer interrupt
      (1 << 1) |                        // Transfer Complete Interrupt Enable
      (0 << 0);                         // Don't enable yet

  // Enable DMA interrupt in NVIC
  NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}

void ADC1_StartConversion(void)
{
  // Check if DMA is still enabled
  if(DMA1_Channel1->CCR & DMA_CCR_EN)
  {
    // DMA is still busy, disable it
    DMA1_Channel1->CCR &= ~DMA_CCR_EN;

    // Brief delay
    for(volatile uint32_t i = 0; i < 10; i++);

    // Clear interrupt flag
    DMA1->IFCR |= DMA_IFCR_CTCIF1;
  }

  for(int i = 0; i < NUM_CHANNELS; i++)
  {
    adc_buffer[i] = 0;
  }

  // Now configure DMA
  DMA1_Channel1->CNDTR  = 3;
  DMA1_Channel1->CMAR   = (uint32_t)adc_buffer;

  adc_data_ready = 0;

  // Enable DMA
  DMA1_Channel1->CCR |= DMA_CCR_EN;

  // Start ADC
  //ADC1->CR2 |= (0x01 << 22);
  ADC1->CR2 |= ADC_CR2_SWSTART;
}

void DMA1_Channel1_IRQHandler(void)
{
  // Only check Transfer Complete
  if(DMA1->ISR & DMA_ISR_TCIF1)
  {
    // CLEAR THE FLAG
    DMA1->IFCR |= DMA_IFCR_CTCIF1;

    // Signal main loop that data is ready
    adc_data_ready = 1;

  }
}

