#ifndef VOLTAGE_SENSOR_H
#define VOLTAGE_SENSOR_H

#define CORRECTION_FACTOR 21.0

#include <Arduino.h>

class VoltageSensor
{
protected:
    uint8_t _pin;

public:
    VoltageSensor(uint8_t pin);
    virtual float calculate(void) = 0;
};

class VoltageSensorAc : VoltageSensor
{
public:
    VoltageSensorAc(uint8_t pin);
    float calculate(void) override;
};

class VoltageSensorDc : VoltageSensor
{
public:
    VoltageSensorDc(uint8_t pin);
    float calculate(void) override;
};

#endif
