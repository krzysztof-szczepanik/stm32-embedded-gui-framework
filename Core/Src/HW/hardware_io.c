/**
 ******************************************************************************
 * @file     hardware_io.c
 * @brief    Implementation of the ADC and GPIO low‑level access interface.
 * 
 * @details  This module configures ADC and GPIO hardware and provides simple
 *           functions for reading ADC channels and GPIO input states through
 *           low‑level register access.
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

#include "hardware_io.h"

void configure_adc_registers(void) {
	// Enable clocks:
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; // GPIOC clock
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;  // ADC1 clock

    // Configure PC1 and PC2 as analog pins:
    GPIOC->MODER |= (3U << (1 * 2)) | (3U << (2 * 2));    // set as GPIO_ANALOG
    GPIOC->PUPDR &= ~((3U << (1 * 2)) | (3U << (2 * 2))); // disable pull-up/down

    // Basic ADC configuration:
    ADC1->CR1 = 0; // reset control register 1
    ADC1->CR2 = 0; // reset control register 2

    // Set sample time for channels 11 and 12:
    ADC1->SMPR1 |= (7U << ((11 - 10) * 3)) | (7U << ((12 - 10) * 3));

    // Convert only 1 channel at a time:
    ADC1->SQR1 &= ~ADC_SQR1_L;

    // Enable ADC:
    ADC1->CR2 |= ADC_CR2_ADON;

    // Short stabilization delay:
    for (volatile int i = 0; i < 10000; ++i);
}

void configure_gpio_registers(void) {
    // Enable clock for GPIOC:
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    // Set PC3 as input:
    GPIOC->MODER &= ~(3U << (3 * 2));

    // Disable pull-down, enable pull-up:
    GPIOC->PUPDR &= ~(3U << (3 * 2)); // clear pull-up/pull-down
    GPIOC->PUPDR |=  (1U << (3 * 2)); // pull-up
}

uint16_t read_adc(uint8_t channel) {
    // Select ADC channel:
    ADC1->SQR3 = channel & 0x1F;

    // Clear end-of-conversion flag:
    ADC1->SR &= ~ADC_SR_EOC;

    // Start conversion:
    ADC1->CR2 |= ADC_CR2_SWSTART;

    // Wait for conversion to complete:
    while (!(ADC1->SR & ADC_SR_EOC));

    // Return conversion result:
    return ADC1->DR;
}

uint8_t read_gpio_pin(GPIO_TypeDef *port, uint16_t pin) {
    return (port->IDR & pin) ? 1 : 0;
}