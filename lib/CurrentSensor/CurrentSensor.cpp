#include "CurrentSensor.h"

// Base class
CurrentSensor::CurrentSensor(uint8_t pin)
{
    this->_pin = pin;
}
CurrentSensor::~CurrentSensor()
{
    // pass
}

// DC sensor
CurrentSensorDc::CurrentSensorDc(uint8_t pin) : CurrentSensor(pin)
{
    this->_pin = pin;
    this->acs = new ACS712(this->_pin, V_REF, MAX_ADC, ACS712_5_V_REF);
}

void CurrentSensorDc::calibrate()
{
    // pass
}

float CurrentSensorDc::calculate()
{
    return (this->acs->mA_DC()) / 100000.0;
}

CurrentSensorDc::~CurrentSensorDc()
{
    delete this->acs;
}

// AC sensor
CurrentSensorAc::CurrentSensorAc(uint8_t pin) : CurrentSensor(pin)
{
    this->_pin = pin;
    this->acs = new ACS712(this->_pin, V_REF, MAX_ADC, ACS712_5_V_REF);
}

void CurrentSensorAc::calibrate()
{
    // pass
}

float CurrentSensorAc::calculate()
{
    float average = 0;
    for (uint8_t i = 0; i < 100; i++)
    {
        average += this->acs->mA_AC();
    }
    /* in Ampere unit*/
    return (average / 100000.0) - CALIBRATED_CONST_CURRENT;
}

CurrentSensorAc::~CurrentSensorAc()
{
    delete this->acs;
}