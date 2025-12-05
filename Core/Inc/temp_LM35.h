/*
 * temp_LM35.h
 *
 *  Created on: Dec 5, 2025
 *      Author: Rubin Khadka
 */

#ifndef INC_TEMP_LM35_H_
#define INC_TEMP_LM35_H_

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NUM_SENSORS 3

// Global temperature buffer
extern float temperature_buffer[NUM_SENSORS];

// Function Prototypes
uint8_t Temp_Values_Ready(void);
void Temp_Update_All(void);
float Temp_Get_Average_Celsius(void);
void Temp_Reset_All(void);

#ifdef __cplusplus
}
#endif

#endif /* INC_TEMP_LM35_H_ */
