/*
 * spi_config.h
 *
 *  Created on: Dec 4, 2025
 *      Author: Rubin Khadka
 */

#ifndef INC_SPI1_CONFIG_H_
#define INC_SPI1_CONFIG_H_

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Macros */
#define LATCH(x) (x==1 ? (HAL_GPIO_WritePin(SPI_SS_GPIO_Port, SPI_SS_Pin, GPIO_PIN_SET)):\
                         (HAL_GPIO_WritePin(SPI_SS_GPIO_Port, SPI_SS_Pin, GPIO_PIN_RESET)))

/* Function Prototypes */
void SPI1_init(void);
void SPI1_Transmit16(uint16_t data);

#ifdef __cplusplus
}
#endif

#endif /* INC_SPI1_CONFIG_H_ */
