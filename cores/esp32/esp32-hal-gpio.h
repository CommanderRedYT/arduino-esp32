/*
 Arduino.h - Main include file for the Arduino SDK
 Copyright (c) 2005-2013 Arduino Team.  All right reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef MAIN_ESP32_HAL_GPIO_H_
#define MAIN_ESP32_HAL_GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "soc/soc_caps.h"

#if (CONFIG_IDF_TARGET_ESP32S2 || CONFIG_IDF_TARGET_ESP32S3)
#define NUM_OUPUT_PINS  45
#define PIN_DAC1        17
#define PIN_DAC2        18
#else
#define NUM_OUPUT_PINS  34
#define PIN_DAC1        25
#define PIN_DAC2        26
#endif

#define LOW               0x0
#define HIGH              0x1

//GPIO FUNCTIONS
#define INPUT             0x01
#define OUTPUT            0x02
#define PULLUP            0x04
#define INPUT_PULLUP      0x05
#define PULLDOWN          0x08
#define INPUT_PULLDOWN    0x09
#define OPEN_DRAIN        0x10
#define OUTPUT_OPEN_DRAIN 0x12
#define SPECIAL           0xF0
#define FUNCTION_1        0x00
#define FUNCTION_2        0x20
#define FUNCTION_3        0x40
#define FUNCTION_4        0x60
#define FUNCTION_5        0x80
#define FUNCTION_6        0xA0
#define ANALOG            0xC0

//Interrupt Modes
#define DISABLED  0x00
#define RISING    0x01
#define FALLING   0x02
#define CHANGE    0x03
#define ONLOW     0x04
#define ONHIGH    0x05
#define ONLOW_WE  0x0C
#define ONHIGH_WE 0x0D

typedef struct {
    uint8_t reg;      /*!< GPIO register offset from DR_REG_IO_MUX_BASE */
    int8_t rtc;       /*!< RTC GPIO number (-1 if not RTC GPIO pin) */
    int8_t adc;       /*!< ADC Channel number (-1 if not ADC pin) */
    int8_t touch;     /*!< Touch Channel number (-1 if not Touch pin) */
} esp32_gpioMux_t;

extern const esp32_gpioMux_t esp32_gpioMux[SOC_GPIO_PIN_COUNT];
extern const int8_t esp32_adc2gpio[20];

#define digitalPinIsValid(pin)          ((pin) < SOC_GPIO_PIN_COUNT && esp32_gpioMux[(pin)].reg)
#define digitalPinCanOutput(pin)        ((pin) < NUM_OUPUT_PINS && esp32_gpioMux[(pin)].reg)
#define digitalPinToRtcPin(pin)         (((pin) < SOC_GPIO_PIN_COUNT)?esp32_gpioMux[(pin)].rtc:-1)
#define digitalPinToAnalogChannel(pin)  (((pin) < SOC_GPIO_PIN_COUNT)?esp32_gpioMux[(pin)].adc:-1)
#define digitalPinToTouchChannel(pin)   (((pin) < SOC_GPIO_PIN_COUNT)?esp32_gpioMux[(pin)].touch:-1)
#define digitalPinToDacChannel(pin)     (((pin) == PIN_DAC1)?0:((pin) == PIN_DAC2)?1:-1)

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t val);
int digitalRead(uint8_t pin);

#ifdef __cplusplus
}
#endif

#endif /* MAIN_ESP32_HAL_GPIO_H_ */
