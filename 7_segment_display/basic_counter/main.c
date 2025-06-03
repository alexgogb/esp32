/*
 * Author: Alejandro González Blanco (alexgogb)
 *
*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define RESET_DISPLAY 10

int gpio_pins[] = {GPIO_NUM_4, GPIO_NUM_5, GPIO_NUM_6, GPIO_NUM_7, GPIO_NUM_10, GPIO_NUM_11, GPIO_NUM_18, GPIO_NUM_19};

// ABCDEFGP. P = DP. Binary literals (0b) just in C23.
int instructions[] = {
    0xFC, // 0 (0b11111100)
    0x60, // 1 (0b01100000)
    0xDA, // 2 (0b11011010)
    0xF2, // 3 (0b11110010)
    0x66, // 4 (0b01100110)
    0xB6, // 5 (0b10110110)
    0xBE, // 6 (0b10111110)
    0xE0, // 7 (0b11100000)
    0xFE, // 8 (0b11111110)
    0xE6, // 9 (0b11100110)
    0x00  // Reset (0b00000000)
};

void initial_config() {
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << 4) | (1ULL << 5) | (1ULL << 6) | (1ULL << 7) | (1ULL << 10) | (1ULL << 11) | (1ULL << 18) | (1ULL << 19),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&io_conf);
}

void set_display(int number) {
    int instruction = instructions[number];
    for (int i = 0; i <= 7; i++) {
        int level = (instruction >> (7-i)) & 0x01;
        gpio_set_level(gpio_pins[i], level);
    }
}

void app_main(void) {
    initial_config();
    
    while (1) {
        for (int i = 0; i < 10; i++) {
            set_display(i);
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
        set_display(RESET_DISPLAY);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}