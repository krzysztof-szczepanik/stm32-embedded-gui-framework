/**
 ******************************************************************************
 * @file     hardware_io.h
 * @brief    ADC and GPIO low‑level access interface.
 * 
 * @details  This module provides simple functions for configuring ADC and GPIO
 *           registers and reading their values directly through low‑level
 *           register access.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 Krzysztof Szczepanik.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#ifndef HARDWARE_IO_H
#define HARDWARE_IO_H

#include <stdint.h>
#include "stm32f4xx_hal.h"

/**
 * @brief  Configure ADC registers and pins for analog input.
 * 
 * @note   Configures PC1 and PC2 as analog inputs for ADC1, sets sample time,
 *         enables ADC and does short stabilization delay.
 */
void configure_adc_registers(void);

/**
 * @brief  Configure GPIO registers for input pins.
 * 
 * @note   Enables clock for GPIOC and sets PC3 as input with pull-up.
 */
void configure_gpio_registers(void);

/**
 * @brief   Read a value from the ADC.
 * 
 * @param   channel ADC channel number (11 = PC1, 12 = PC2)
 * @return  12-bit ADC conversion result
 */
uint16_t read_adc(uint8_t channel);

/**
 * @brief   Read the state of a GPIO pin.
 * 
 * @param   port GPIO port
 * @param   pin GPIO pin mask
 * @return  1 if pin is HIGH (not pressed), 0 if LOW (pressed)
 */
uint8_t read_gpio_pin(GPIO_TypeDef *port, uint16_t pin);

#endif /* HARDWARE_IO_H */