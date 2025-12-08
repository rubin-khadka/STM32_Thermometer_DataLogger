/*
 * spi2_sd.c
 *
 *  Created on: Dec 8, 2025
 *      Author: Rubin Khadka
 */

#include "spi2_sd.h"
#include "main.h"
#include "string.h"

#define SD_CMD0_GO_IDLE_STATE        0
#define SD_CMD8_SEND_IF_COND         8
#define SD_CMD16_SET_BLOCKLEN        16
#define SD_CMD17_READ_SINGLE_BLOCK   17
#define SD_CMD24_WRITE_SINGLE_BLOCK  24
#define SD_CMD55_APP_CMD             55
#define SD_ACMD41_SD_SEND_OP_COND    41
#define SD_CMD58_READ_OCR            58

#define SD_TOKEN_START_BLOCK         0xFE
#define SD_TOKEN_START_BLOCK_MULTI   0xFC
#define SD_TOKEN_STOP_TRAN           0xFD

#define SD_CS(x) (x==1 ? (HAL_GPIO_WritePin(SD_CS_GPIO_Port, SD_CS_Pin, GPIO_PIN_SET)):\
                         (HAL_GPIO_WritePin(SD_CS_GPIO_Port, SD_CS_Pin, GPIO_PIN_RESET)))
//
//static void SD_Transmit_Byte(uint8_t data)
//{
//    // Using blocking transmit for command phase
//    HAL_SPI_Transmit(&hspi2, &data, 1, HAL_MAX_DELAY);
//}
//
