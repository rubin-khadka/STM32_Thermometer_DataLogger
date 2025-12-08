/*
 * spi2_sd.h
 *
 *  Created on: Dec 8, 2025
 *      Author: Rubin Khadka
 */

#ifndef INC_SPI2_SD_H_
#define INC_SPI2_SD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "stdbool.h"

// TODO(Rubin) Check pin state here

#define SD_INIT_TIMEOUT_MS  1000
#define SD_CMD_TIMEOUT_MS   500
#define SD_DATA_TIMEOUT_MS  200
#define SD_BUSY_TIMEOUT_MS  3000

#define SD_BLOCK_SIZE       512
#define SD_CMD_BUFFER_SIZE  6

typedef enum {
    SD_OK = 0,
    SD_ERROR,
    SD_TIMEOUT,
    SS_NOT_READY,
    SD_INVALID_PARAM,
    SD_BUSY
} SD_Status_t;

typedef enum {
    SD_STATE_IDLE = 0,
    SD_STATE_INITIALIZING,
    SD_STATE_READING,
    SD_STATE_WRITING,
    SD_STATE_WAITING_TOKEN,
    SD_STATE_RECEIVING_DATA,
    SD_STATE_TRANSMITTING_DATA,
    SD_STATE_ERROR
} SD2_State_t;

typedef enum {
    SD_TYPE_UNKNOWN = 0,
    SD_TYPE_SDSC,
    SD_TYPE_SDHC,
    SD_TYPE_SDXC
} SD_Card_Type_t;

SD_Status_t SD2_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* INC_SPI2_SD_H_ */
