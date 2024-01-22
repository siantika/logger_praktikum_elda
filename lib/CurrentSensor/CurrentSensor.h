#ifndef CURRENT_SENSOR_H
#define CURRENT_SENSOR_H

#include <Arduino.h>
#include "ACS712.h"
#define V_REF 5.0
#define ACS712_5_SENSITIVITY 185 // see datahseet
#define V_OFFSET_ACS712 2.5      // ACS_712 (in volt)
#define MAX_ADC 1023
#define CALIBRATED_CONST_CURRENT 0.135 //  current only (input sensor)
#define DC_CURRENT_THRESHOLD 0.05      // self calibrated
#define AC_CURRENT_THRESHOLD 0.02      // self calibrated
class CurrentSensor
{
protected:
    uint8_t _pin;

public:
    CurrentSensor(uint8_t pin);
    virtual ~CurrentSensor();
    virtual void calibrate() = 0;
    virtual float calculate() = 0;
    void add_list_float(float data);
};

class CurrentSensorDc : CurrentSensor
{
private:
    ACS712 *acs;
    float calculateCurrentDcOnce();

public:
    CurrentSensorDc(uint8_t pin);
    ~CurrentSensorDc();
    void calibrate() override;
    float calculate() override;
};

class CurrentSensorAc : CurrentSensor
{
private:
    ACS712 *acs;

public:
    CurrentSensorAc(uint8_t pin);
    ~CurrentSensorAc();
    void calibrate() override;
    float calculate() override;
};

#endif
