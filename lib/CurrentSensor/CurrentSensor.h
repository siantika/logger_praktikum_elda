#ifndef CURRENT_SENSOR_H
#define CURRENT_SENSOR_H

#include <Arduino.h>
#include <ACS712.h>

class CurrentSensor
{
protected:
    uint8_t _pin;

public:
    CurrentSensor(uint8_t pin);
    virtual ~CurrentSensor();
    virtual void calibrate() = 0;
    virtual float calculate() = 0;
};

class CurrentSensorDc : CurrentSensor
{
private:
    ACS712 *acs;

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
