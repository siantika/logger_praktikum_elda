#include "CurrentSensor.h"

// Base class
CurrentSensor::CurrentSensor(uint8_t pin)
{
    this->_pin = pin;
}
CurrentSensor::~CurrentSensor()
{
    //pass
}

// DC sensor
CurrentSensorDc::CurrentSensorDc(uint8_t pin) : CurrentSensor(pin)
{
    this->_pin = pin;
    this->acs = new ACS712(ACS712_05B, this->_pin);
}

void CurrentSensorDc::calibrate()
{
    this->acs->calibrate();
}

float CurrentSensorDc::calculate()
{
    return this->acs->getCurrentDC();
}

CurrentSensorDc::~CurrentSensorDc()
{
    delete this->acs;
}


// AC sensor
CurrentSensorAc::CurrentSensorAc(uint8_t pin) : CurrentSensor(pin)
{
    this->_pin = pin;
    this->acs = new ACS712(ACS712_05B, this->_pin);
}

void CurrentSensorAc::calibrate()
{
    this->acs->calibrate();
}

float CurrentSensorAc::calculate()
{
    return this->acs->getCurrentAC();
}

CurrentSensorAc::~CurrentSensorAc()
{
    delete this->acs;
}