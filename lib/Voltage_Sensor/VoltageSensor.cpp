#include "VoltageSensor.h"

VoltageSensor::VoltageSensor(uint8_t pin)
{
    this->_pin = pin;
}

/* Derived class*/
// Class voltage sensor AC
VoltageSensorAc::VoltageSensorAc(uint8_t pin) : VoltageSensor(pin)
{
    // pass
}

float VoltageSensorAc::calculate(void)
{
    int read_adc;
    read_adc = analogRead(this->_pin);
    float high_voltage = ((0.0048 * ADC + 0.08) * 1 / 0.0123) - CORRECTION_FACTOR;
    return high_voltage;
}

// Class voltage sensor DC
VoltageSensorDc::VoltageSensorDc(uint8_t pin) : VoltageSensor(pin)
{
    // pass
}

float VoltageSensorDc::calculate(void)
{
    int read_adc;
    read_adc = analogRead(this->_pin);
    float high_voltage = ((0.0048 * ADC + 0.08) * 1 / 0.0123) - CORRECTION_FACTOR;
    return high_voltage;
}