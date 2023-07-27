#include "VoltageSensor.h"

VoltageSensor::VoltageSensor(uint8_t pin)
{
    this->_pin = pin;
}

// destructor
VoltageSensor::~VoltageSensor()
{
}

/* Derived class*/
// Class voltage sensor AC
VoltageSensorAc::VoltageSensorAc(uint8_t pin) : VoltageSensor(pin)
{
    // pass
}

// Private methods
int VoltageSensorAc::_read_analog()
{
    return analogRead(this->_pin);
}

void VoltageSensorAc::_filter_peek_adc(int *array_adc, int array_size)
{
    for (int i = 0; i < MAX_ITER; i++)
    {
        _read_adc = _read_analog();
        if (_read_analog() > ZERO_POINT_ADC)
        {
            array_adc[i] = _read_adc;
        }
        else
        {
            array_adc[i] = 0;
        }
        delay(1);
    }
}

int VoltageSensorAc::_find_max_adc(int *array_adc, int array_size)
{
    _max_val = 0;
    for (int i = 0; i < array_size; i++)
    {
        if (array_adc[i] > _max_val)
        {
            _max_val = _temp_data[i];
        }
        array_adc[i] = 0;
    }
    return _max_val;
}

// public methods
float VoltageSensorAc::calculate(void)
{
    _filter_peek_adc(_temp_data, MAX_ITER);
    _max_val = _find_max_adc(_temp_data, MAX_ITER);

    if (_max_val != 0)
    {
        v_max_adc = (float)_max_val;
        v_eff_adc = v_max_adc / sqrt(2);
        v_eff = (((v_eff_adc - 420.76) / -90.24) * -210.2) + 210.2;
    }
    else
    {
        v_eff = 0;
    }
    return (v_eff < BOTTOM_THRESHOLD_AC_SENSOR ? 0 : v_eff);
}

// Class voltage sensor DC
VoltageSensorDc::VoltageSensorDc(uint8_t pin) : VoltageSensor(pin)
{
    // pass
}

float VoltageSensorDc::calculate(void)
{
    int read_adc = analogRead(this->_pin);
    float high_voltage = ((0.0048 * read_adc + 0.08) * 1 / 0.0123) - CORRECTION_FACTOR;
    /* Filter negative value */
    return (high_voltage < BOTTOM_THRESHOLD_DC_SENSOR ? 0 : high_voltage);
}