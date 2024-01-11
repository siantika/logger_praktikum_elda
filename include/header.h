#ifndef HEADER_H
#define HEADER_H

/* Librarys*/
#include <Arduino.h>
#include "Display.h"
#include "VoltageSensor.h"
#include <LiquidCrystal_I2C.h>
#include "Logger.h"
#include "CurrentSensor.h"

#define CALIBRATED_CONST 0.00 // AC current only (input sensor)

/* Pins definition*/
#define PIN_BUTTON 2
#define PIN_INPUT_VOLTAGE_SENSOR A0
#define PIN_INPUT_CURRENT_SENSOR A1
#define PIN_OUTPUT_VOLTAGE_SENSOR A2
#define PIN_OUTPUT_CURRENT_SENSOR A6
#define PIN_INPUT_VOLTAGE_SENSOR A0
#define PIN_INPUT_CURRENT_SENSOR A1
#define PIN_OUTPUT_VOLTAGE_SENSOR A2
#define PIN_OUTPUT_CURRENT_SENSOR A6
#define PIN_CS_DATA_LOGGER 10
#define PIN_DEBUG 7

/* Variables*/
bool debug_mode_state;
volatile bool button_state = 1;
typedef struct data_collect
{
    float volt;
    float current;
} data_collect;
data_collect data_input;
data_collect data_output;

/* Global objects*/
LiquidCrystal_I2C lcd1(0x27, 16, 2);
LiquidCrystal_I2C lcd2(0x23, 16, 2);
Display disp1(lcd1); // untuk input
Display disp2(lcd2); // untuk output
Logger logger;

// Forward functions declarations
bool read_button_state(void);
void no_sd_card_handle(Display &disp1, Display &disp2);
void log_failed_handle(Display &disp1, Display &disp2);

#endif