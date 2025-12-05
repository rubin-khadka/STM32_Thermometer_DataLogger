/*
 * seven_segment.h
 *
 *  Created on: Dec 5, 2025
 *      Author: Rubin Khadka
 */

#ifndef INC_SEVEN_SEGMENT_H_
#define INC_SEVEN_SEGMENT_H_

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Structure to hold the temperature data */
typedef struct
{
  uint8_t digit1;  // Handles negative
  uint8_t digit2;  // digit (0-9)
  uint8_t digit3;  // Decimal point + digit
  uint8_t digit4;  // digit (0-9)
}DisplayDigits_t;

/* Function Prototypes */
void Temperature_To_Digit(float temperature, DisplayDigits_t *digits);
void Update_Display(const DisplayDigits_t *digits);

#ifdef __cplusplus
}
#endif

#endif /* INC_SEVEN_SEGMENT_H_ */
