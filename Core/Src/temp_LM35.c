/*
 * temp_LM35.c
 *
 *  Created on: Dec 5, 2025
 *      Author: Rubin Khadka
 */

#include "temp_LM35.h"
#include "adc1_config.h"

// Configuration
#define VREF_VOLTAGE        3.3f
#define ADC_RESOLUTION      4096.0f

// Global Variables
float temperature_buffer[NUM_SENSORS] = { 0 };

static float Celsius_To_Fahrenheit(float celsius)
{
  return ((celsius * 9.0f / 5.0f) + 32.0f);
}

uint8_t Temp_Values_Ready(void)
{
  return adc_data_ready;
}

/* Update temperature buffer from ADC */
void Temp_Update_All(void)
{
  if(!adc_data_ready)
    return;

  for(int i = 0; i < NUM_SENSORS; i++)
  {
    float voltage = (adc_buffer[i] * VREF_VOLTAGE) / ADC_RESOLUTION;
    temperature_buffer[i] = (voltage - 1.65f) * 100.0f;
  }
}

/* Calculate average temperature */
float Temp_Get_Average_Celsius(void)
{
  float sum = 0.0f;

  for(int i = 0; i < NUM_SENSORS; i++)
  {
    sum += temperature_buffer[i];
  }

  return sum / NUM_SENSORS;
}

void Temp_Get_All_Fahrenheit(float *fahrenheit_buffer)
{
  for(int i = 0; i < NUM_SENSORS; i++)
  {
    fahrenheit_buffer[i] = Celsius_To_Fahrenheit(temperature_buffer[i]);
  }
}

/* Reset all temperatures to zero */
void Temp_Reset_All(void)
{
  for(int i = 0; i < NUM_SENSORS; i++)
  {
    temperature_buffer[i] = 0.0f;
  }
}

