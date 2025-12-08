# STM32 Multi-Sensor Temperature Monitor & Logger

## Project Overview
A embedded system built around the STM32F103C8T6 microcontroller that monitors three separate temperature points, processes the data in real-time, and provides both immediate visual feedback and long-term data storage.

### Core Capabilities
This system extends the single-sensor [STM32 Digital Thermomerter](https://github.com/rubin-khadka/STM32_Digital_Thermometer). This version introduces:
- Multi-Point Sensing: 3x LM35 sensors on `ADC1_IN0–IN2`
- Zero-CPU Sampling: ADC in scan + single conversion mode + DMA normal buffer with interrupt-based processing
- Persistent Logging: FAT32-formatted microSD via SPI2 using FATfs library
- Real-Time Display: 4-digit 7-segment display with multiplexing driven by 2 daisy-chained 74HC595 shift registers

### Hardware Components

| Component              | Specification                          | Purpose                                  |
|------------------------|----------------------------------------|------------------------------------------|
| **Microcontroller**    | STM32F103C8T6 <br> [STM32 Blue Pill Essential Circuits](https://github.com/rubin-khadka/STM32_Thermometer_DataLogger/blob/main/Docs/stm32%20blue%20pil%20circuit.png)              | Main processing unit (72 MHz Cortex-M3)  |
| **Temperature Sensors**| 3 × LM35 (10 mV/°C, ±0.5°C accuracy)   | Analog temperature acquisition           |
| **Display**            | 4-digit Common-Cathode 7-Segment       | Real-time temperature readout            |
| **Shift Registers**    | 2 × 74HC595 (daisy-chained)  | GPIO expansion & display driving         |
| **Storage**            | MicroSD Card Module (SPI interface)    | Persistent CSV logging (FAT32 support)   |

### System Configuration
#### Clock Configuration 
- System Clock: 72 MHz (HSE 8 MHz → PLL ×9) <br>
    [STM32 Clock Configuration](https://github.com/rubin-khadka/STM32_Thermometer_DataLogger/blob/main/Media/Clock_configuration.png)

#### [ADC1 with DMA Configuration](https://github.com/rubin-khadka/STM32_Thermometer_DataLogger/blob/main/Core/Src/adc1_config.c) (Multi-Channel Acquisition)
| Parameter         | Value                                       |
|-------------------|---------------------------------------------|
| **Clock Source**  | 12 MHz                                      |
| **Resolution**    | 12-bit                                      |
| **Mode**          | Scan + Single Conversion + DMA              |
| **DMA Mode**      | Normal Buffer + Transfer Complete Interrupt |
| **Sampling Time** | 28.5 cycles / channel                       |
| **Channels**      | `PA0 → IN0`, `PA1 → IN1`, `PA2 → IN2`       |
| **Data Alignment**| Right-aligned                               |

*Direct register manipulation for fine-grained control over ADC timing and triggering*

#### SPI1 Configuration (74HC595 Shift Register)
| Parameter           | Value                                      |
|-------------------|--------------------------------------------|
| **Mode**          | Master, Full-Duplex                        |
| **Baud Rate**     | 9 Mbps                   |
| **Clock Polarity**| Low (CPOL = 0)                             |
| **Clock Phase**   | First Edge (CPHA = 0)                      |
| **Data Size**    | 16-bit                                |
| **First Bit**     | MSB                                        |

#### SPI2 Configuration (SD Card Module)
