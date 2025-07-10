/*
 * keypad.c
 *
 *  Created on: Aug 9, 2024
 *      Author: abhaysoni512
 */
#include "keypad.h"

// Define keypad connections
#define ROWS 4
#define COLS 4

// Define row and column GPIO pins
const uint16_t rowPins[ROWS] = {GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11};
const uint16_t colPins[COLS] = {GPIO_PIN_6, GPIO_PIN_7, GPIO_PIN_8, GPIO_PIN_9};

// Define keypad matrix
const char keypad[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Function to initialize keypad GPIOs
void Keypad_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Enable GPIO clocks
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    // Initialize row pins as outputs
    for (int i = 0; i < ROWS; i++) {
        GPIO_InitStruct.Pin = rowPins[i];
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        HAL_GPIO_WritePin(GPIOA, rowPins[i], GPIO_PIN_SET); // Set rows high initially
    }

    // Initialize column pins as inputs with pull-ups
    for (int i = 0; i < COLS; i++) {
        GPIO_InitStruct.Pin = colPins[i];
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    }
}

// Function to get the key pressed on the keypad
char Keypad_GetKey(void) {
    for (int row = 0; row < ROWS; row++) {
        // Set current row low
        HAL_GPIO_WritePin(GPIOA, rowPins[row], GPIO_PIN_RESET);

        for (int col = 0; col < COLS; col++) {
            // Check if column pin is low
            if (HAL_GPIO_ReadPin(GPIOC, colPins[col]) == GPIO_PIN_RESET) {
                // Wait for key release
                while (HAL_GPIO_ReadPin(GPIOC, colPins[col]) == GPIO_PIN_RESET);

                // Return the corresponding key
                return keypad[row][col];
            }
        }

        // Set current row high again
        HAL_GPIO_WritePin(GPIOA, rowPins[row], GPIO_PIN_SET);
    }

    // No key pressed
    return 0;
}


