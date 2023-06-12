#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>
#include <SD.h>
#include "DS3231.h"

class Logger
{
private:
    String get_date();
    String get_time();

public:
    uint8_t init(uint8_t pin_cs);
    void log(float &voltage_in, float &current_in, \
            float& voltage_out, float& current_out, String file_name);
};

#endif