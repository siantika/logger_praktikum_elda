#ifndef VOLTAGE_SENSOR_H
#define VOLTAGE_SENSOR_H
#include <Arduino.h>

#define CORRECTION_FACTOR 0.0
#define CORRECTION_FACTOR 0.0
#define MAX_ITER 100
#define ZERO_POINT_ADC 511
#define BOTTOM_THRESHOLD_DC_SENSOR 10
#define BOTTOM_THRESHOLD_AC_SENSOR 100

class VoltageSensor
{
protected:
    uint8_t _pin;

public:
    VoltageSensor(uint8_t pin);
    virtual float calculate(void) = 0;
    virtual ~VoltageSensor();
};

class VoltageSensorAc : VoltageSensor
{
private:
    int _max_val;
    int _read_adc;
    int _temp_data[MAX_ITER];
    float v_max_adc;
    float v_eff_adc;
    float v_eff;
    int _read_analog();
    void _filter_peek_adc(int *array_adc, int array_size);
    int _find_max_adc(int *array_adc, int array_size);

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
