/*
 * adc1_config.h
 *
 *  Created on: Dec 5, 2025
 *      Author: Rubin Khadka
 */

#ifndef INC_ADC1_CONFIG_H_
#define INC_ADC1_CONFIG_H_

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NUM_CHANNELS 3

// Global variables
extern volatile uint16_t adc_buffer[NUM_CHANNELS];
extern volatile uint8_t adc_data_ready;

// Function Prototypes
void ADC1_Init(void);
void ADC1_DMA_Config(void);
void ADC1_StartConversion(void);
void DMA1_Channel1_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* INC_ADC1_CONFIG_H_ */
