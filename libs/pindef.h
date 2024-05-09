/*
 * This file contains all pins used by the libraries.
 * This is a poor substitute for something like a zephyr 
 * device tree or a Kconfig, but it will have to do.
 */

#define NRF_CE_PIN 10
#define NRF_CSN_PIN 9

#define LEFT_MOTOR_PIN P0_29
#define RIGHT_MOTOR_PIN P0_30

#define PUMP_PIN P0_21

#define SENSE_TEMP_PIN P0_30
#define SENSE_COND_PIN P0_29
#define SENSE_FLUO_PIN P0_28
#define SENSE_TURB_PIN P0_3
