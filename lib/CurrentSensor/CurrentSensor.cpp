#include "CurrentSensor.h"

// Base class
CurrentSensor::CurrentSensor(uint8_t pin)
{
    this->_pin = pin;
}

void CurrentSensor::add_list_float(float data)
{
}

CurrentSensor::~CurrentSensor()
{
    // pass
}

// DC sensor
CurrentSensorDc::CurrentSensorDc(uint8_t pin) : CurrentSensor(pin)
{
    this->_pin = pin;
    this->acs = new ACS712(this->_pin, V_REF, MAX_ADC, ACS712_5_SENSITIVITY);
}

void CurrentSensorDc::calibrate()
{
    // pass
}

float CurrentSensorDc::calculate()
{
    /* Finding the highest current*/
    float selected_amps = 0.0;
    for (uint8_t i = 0; i < 100; i++)
    {
        float amps = CurrentSensorDc::calculateCurrentDcOnce();
        if (amps > selected_amps)
        {
            selected_amps = amps;
        }
    }

    return (selected_amps > DC_CURRENT_THRESHOLD ? selected_amps : 0.00); // average and converts to amps
}

// private function
float CurrentSensorDc::calculateCurrentDcOnce()
{
    float amps_pp = ((analogRead(this->_pin) / 1024.0 * 5.0) - V_OFFSET_ACS712) / ACS712_5_SENSITIVITY;
    return amps_pp / 2.0 * 0.707; // in RMS
}

CurrentSensorDc::~CurrentSensorDc()
{
    delete this->acs;
}

// AC sensor
CurrentSensorAc::CurrentSensorAc(uint8_t pin) : CurrentSensor(pin)
{
    this->_pin = pin;
    this->acs = new ACS712(this->_pin, V_REF, MAX_ADC, ACS712_5_SENSITIVITY);
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