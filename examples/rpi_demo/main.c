/**
 * Copyright (c) 2024 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// Copyright that was part of power management example used in this project
// functions that were originally part of it are all clearly marked in the comments

/*
* This file serves as an example to showcase functionality of context_lib library using Rasbperry Pi Pico 2W.
* For notes on development refer to setup.md file in this folder
*/
#include <stdio.h>
#include <inttypes.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/pio.h"
#include "hardware/timer.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include "hardware/powman.h"
#include "blink.pio.h"
#include "pico/sync.h"

#include "context_manager.h"
#include "context_lib_port.h"


/*
* Definitions
*/
// GPIO out pins for controlling LEDs.
#define MODULE_RED_PIN 13
#define MODULE_GREEN_PIN 12
#define MODULE_BLUE_PIN 11
#define BLUE1_PIN 18
#define GREEN1_PIN 19
#define BLUE2_PIN 20
#define GREEN2_PIN 21

// GPIO in pins for controlling buttons. uses external pullups
#define BUTTON0_PIN 0
#define BUTTON1_PIN 1
#define BUTTON2_PIN 2
#define BUTTON3_PIN 3
#define BUTTON4_PIN 4

// I2C module for reading and writing EEPROM
#define I2C_PORT i2c0
#define I2C_SDA 16
#define I2C_SCL 17

#define EEPROM_ADDR 0x50   // 24LC01B base address


/*
* Global variables
*/

// stop state to which MCU will go when changing mode
static powman_power_state off_state;
// run state to which MCU will go when changing mode
static powman_power_state on_state;

// index in led_array that determines which led is incremented
volatile uint32_t led_index;

uint32_t led_array[7];


// backup memory area
const Cl_memory_area_t eeprom = {31, (uint32_t *)0, (uint32_t *)127, CL_EEPROM_PICO};

// area that stores data from buttons
const Cl_memory_area_t buttons_ma = {32, led_array, led_array + 6, CL_CPU};

/*
* Functions
*/

/*
* Blink blue led on the RGB module once
*/
void control_blick_blue(void)
{
    sleep_ms(1000);
    gpio_put(MODULE_BLUE_PIN,true);
    sleep_ms(1000);
    gpio_put(MODULE_BLUE_PIN,false);
}

/*
* Blink red led on the RGB module once
*/
void control_blick_red(void)
{
    sleep_ms(1000);
    gpio_put(MODULE_RED_PIN,true);
    sleep_ms(1000);
    gpio_put(MODULE_RED_PIN,false);
}

/*
* Blink green led on the RGB module once
*/
void control_blick_green(void)
{
    sleep_ms(1000);
    gpio_put(MODULE_GREEN_PIN,true);
    sleep_ms(1000);
    gpio_put(MODULE_GREEN_PIN,false);
}

/*
* blink first blue led once
*/
void blick_blue1(void)
{
    sleep_ms(1000);
    gpio_put(BLUE1_PIN,true);
    sleep_ms(1000);
    gpio_put(BLUE1_PIN,false);
}

/*
* blink second blue led once
*/
void blick_blue2(void)
{
    sleep_ms(1000);
    gpio_put(BLUE2_PIN,true);
    sleep_ms(1000);
    gpio_put(BLUE2_PIN,false);
}

/*
* blink first green led once
*/
void blick_green1(void)
{
    sleep_ms(1000);
    gpio_put(GREEN1_PIN,true);
    sleep_ms(1000);
    gpio_put(GREEN1_PIN,false);
}

/*
* blink second green led once
*/
void blick_green2(void)
{
    sleep_ms(1000);
    gpio_put(GREEN2_PIN,true);
    sleep_ms(1000);
    gpio_put(GREEN2_PIN,false);
}

/*
* blink every led number of times specified in led_array[]
*/
void blink_all(void)
{
    uint32_t i;
    uint32_t index = 0;
    
    for (i = 0; i < led_array[index]; i++){
        control_blick_red();
    }
    index++;
    for (i = 0; i < led_array[index]; i++){
        control_blick_green();
    }
    index++;
    for (i = 0; i < led_array[index]; i++){
        control_blick_blue();
    }
    index++;
    for (i = 0; i < led_array[index]; i++){
        blick_blue1();
    }
    index++;
    for (i = 0; i < led_array[index]; i++){
        blick_blue2();
    }
    index++;
    for (i = 0; i < led_array[index]; i++){
        blick_green1();
    }
    index++;
    for (i = 0; i < led_array[index]; i++){
        blick_green2();
    }
    index++;
    return;
}

/*
* print values from led_array[]
*/
void print_led_array(void)
{
    printf("Leds will be blinked:\n");
    int i;
    for (i = 0; i < 7; i++){
        printf("%d\n",led_array[i]);
    }
}

int powman_example_off_until_gpio_low(int gpio);

/*
* interrupt handler for GPIO pins connected to buttons
* each button has different functionality necessary for right working of the application
*/
void gpio_callback(uint gpio, uint32_t events) {
    if (gpio == BUTTON0_PIN) {
        printf("Button 0 pressed: Increment value in led array\n");
        led_array[led_index] = (led_array[led_index] + 1) & 7;
    } else if (gpio == BUTTON1_PIN) {
        printf("Button 1 pressed: Increment array index\n");
        led_index = (led_index + 1) % 7;
    } else if (gpio == BUTTON2_PIN) {
        printf("Button 2 pressed: Save context and shut down controller\n");
        cl_save_mem_area(buttons_ma,eeprom,NULL);
        int rc = powman_example_off_until_gpio_low(BUTTON3_PIN);
        hard_assert(rc == PICO_OK);
        hard_assert(false); // should never get here!
    } else if (gpio == BUTTON3_PIN) {
        printf("Button 3 pressed: Show current configuration and blink leds\n");
        print_led_array();
        blink_all();
    } else if (gpio == BUTTON4_PIN) {
        printf("Button 4 pressed: Clear memory area\n");
        cl_clear_mem_area(eeprom,NULL);
    }
}

// initialize led pins
void app_rgb_init(void)
{
    gpio_init(MODULE_RED_PIN);
    gpio_init(MODULE_BLUE_PIN);
    gpio_init(MODULE_GREEN_PIN);
    gpio_init(BLUE1_PIN);
    gpio_init(GREEN1_PIN);
    gpio_init(BLUE2_PIN);
    gpio_init(GREEN2_PIN);

    gpio_set_dir(MODULE_RED_PIN, GPIO_OUT);
    gpio_set_dir(MODULE_BLUE_PIN, GPIO_OUT);
    gpio_set_dir(MODULE_GREEN_PIN, GPIO_OUT);
    gpio_set_dir(BLUE1_PIN, GPIO_OUT);
    gpio_set_dir(GREEN1_PIN, GPIO_OUT);
    gpio_set_dir(BLUE2_PIN, GPIO_OUT);
    gpio_set_dir(GREEN2_PIN, GPIO_OUT);

    gpio_put(MODULE_RED_PIN, false);
    gpio_put(MODULE_GREEN_PIN, false);
    gpio_put(MODULE_BLUE_PIN, false);
    gpio_put(BLUE1_PIN, false);
    gpio_put(BLUE2_PIN, false);
    gpio_put(GREEN1_PIN, false);
    gpio_put(GREEN2_PIN, false);
}


// initialize i2c
void app_i2c_init(void) {
    i2c_init(I2C_PORT, 100 * 1000);  // 100 kHz

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);

    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
}

// initialize button pins
void app_buttons_init(void)
{
    gpio_init(BUTTON0_PIN);
    gpio_set_dir(BUTTON0_PIN, GPIO_IN);
    gpio_disable_pulls(BUTTON0_PIN);

    gpio_init(BUTTON1_PIN);
    gpio_set_dir(BUTTON1_PIN, GPIO_IN);
    gpio_disable_pulls(BUTTON1_PIN);
    
    gpio_init(BUTTON2_PIN);
    gpio_set_dir(BUTTON2_PIN, GPIO_IN);
    gpio_disable_pulls(BUTTON2_PIN);

    gpio_init(BUTTON3_PIN);
    gpio_set_dir(BUTTON3_PIN, GPIO_IN);
    gpio_disable_pulls(BUTTON3_PIN);


    gpio_init(BUTTON4_PIN);
    gpio_set_dir(BUTTON4_PIN, GPIO_IN);
    gpio_disable_pulls(BUTTON4_PIN);


    // Register a single ISR for all GPIOs
    gpio_set_irq_enabled_with_callback(
        BUTTON0_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_callback
    );
    gpio_set_irq_enabled(BUTTON1_PIN, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(BUTTON2_PIN, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(BUTTON3_PIN, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(BUTTON4_PIN, GPIO_IRQ_EDGE_FALL, true);
}

/*
* initialize on and off state for shutting down controller
*
* One of the functions that were part of powman example
*/
void app_powman_init(void) {

    // Power states
    powman_power_state P1_7 = POWMAN_POWER_STATE_NONE;

    powman_power_state P0_0 = POWMAN_POWER_STATE_NONE;
    P0_0 = powman_power_state_with_domain_on(P0_0, POWMAN_POWER_DOMAIN_SWITCHED_CORE);
    P0_0 = powman_power_state_with_domain_on(P0_0, POWMAN_POWER_DOMAIN_XIP_CACHE);
    P0_0 = powman_power_state_with_domain_on(P0_0, POWMAN_POWER_DOMAIN_SRAM_BANK0);
    P0_0 = powman_power_state_with_domain_on(P0_0, POWMAN_POWER_DOMAIN_SRAM_BANK1);
    off_state = P1_7;
    on_state = P0_0;
}

// initialize whole app
void app_init(void)
{
    app_rgb_init();
    app_buttons_init();
    app_powman_init();
    app_i2c_init();
}


/*
* initialize turning power off process
*
* Was part of powman example
*/
static int powman_example_off(void) {
    control_blick_blue();
    // Get ready to power off
    stdio_flush();

    // Set power states
    bool valid_state = powman_configure_wakeup_state(off_state, on_state);
    if (!valid_state) {
        control_blick_red(); 
        return PICO_ERROR_INVALID_STATE;
    }
    control_blick_blue();

    // reboot to main
    powman_hw->boot[0] = 0;
    powman_hw->boot[1] = 0;
    powman_hw->boot[2] = 0;
    powman_hw->boot[3] = 0;

    control_blick_blue();
    // Switch to required power state
    int rc = powman_set_power_state(off_state);
    control_blick_blue();
    if (rc != PICO_OK) {
        control_blick_red();
        return rc;
    }

    control_blick_green();
    // Power down
    while (true) __wfi();
}

/*
* Go into low power mode
*
* Was part of powman example
*/
int powman_example_off_until_gpio_low(int gpio) {
    gpio_init(gpio);
    gpio_set_dir(gpio, false);
    if (!gpio_get(gpio)) {
        printf("Waiting for gpio %d to go low\n", gpio);
        while(!gpio_get(gpio)) {
            sleep_ms(100);
        }
    }
    printf("Powering off until GPIO %d goes low\n", gpio);
    powman_enable_gpio_wakeup(0, gpio, false, false);
    return powman_example_off();
}

// function for cl_layer 1 for writing data to backup memory
bool eeprom_write_byte(uint8_t data, uint8_t *mem_addr) {
    uint8_t addr = *mem_addr;          
    uint8_t buf[2] = { addr, data };

    int written = i2c_write_blocking(I2C_PORT, EEPROM_ADDR, buf, 2, false);
    if (written < 0) return false;

    sleep_ms(5); 
    return true;
}

// function for cl_layer 1 for reading data from backup memory
bool eeprom_read_byte(uint8_t *data_out, uint8_t *mem_addr) {
    uint8_t addr = *mem_addr;

    int ok = i2c_write_blocking(I2C_PORT, EEPROM_ADDR, &addr, 1, true);
    if (ok < 0) return false;

    int read = i2c_read_blocking(I2C_PORT, EEPROM_ADDR, data_out, 1, false);
    return read == 1;
}


int main() {
    stdio_init_all();
    app_init();
    int i;
    for (i = 0; i < 7; i++){
        led_array[i] = 0;
    }
    led_array[1] = 2;
    led_array[2] = 3;
    printf("Initialization ended! Waiting to boot console.\n");
    sleep_ms(15000);
    printf("After wait and successful library init\n");
    printf("Testing save array\n");
    cl_load_mem_area(buttons_ma,eeprom,NULL);
    sleep_ms(5000);
    
    while (1) tight_loop_contents();

}