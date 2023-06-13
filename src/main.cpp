#include <Arduino.h>
#include "Display.h"
#include "VoltageSensor.h"
#include <LiquidCrystal_I2C.h>
#include "Logger.h"
#include "CurrentSensor.h"

#define PIN_BUTTON 2

volatile bool button_state = 1;

LiquidCrystal_I2C lcd1(0x27, 16, 2);
LiquidCrystal_I2C lcd2(0x23, 16, 2);
Display disp1(lcd1); // untuk input
Display disp2(lcd2); // untuk output
Logger logger;

typedef struct data_collect
{
  float volt;
  float current;
} data_collect;

data_collect data_input;
data_collect data_output;

// Forward functions declarations
bool read_button_state(void);

void setup()
{
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  Serial.begin(115200);
  disp1.init();
  disp2.init();
  delay(2000);

  disp1.first_message();
  disp2.first_message();

  // Wait users to finish the circuit.
  while (button_state != 0)
  {
    button_state = read_button_state();
  }

  // Tell users that the device is ready
  disp1.second_message();
  disp2.second_message();
  delay(500);

  // Waiting users to touch the button for confirmation.
  button_state = 1;
  while (button_state != 0)
  {
    button_state = read_button_state();
  }

  disp1.disp_custom(F("** INFORMASI **"), F("Collecting ..."));
  disp2.disp_custom(F("** INFORMASI **"), F("Collecting ..."));

  VoltageSensorAc *input_voltage_sensor = new VoltageSensorAc(A3);
  VoltageSensorDc *output_voltage_sensor = new VoltageSensorDc((A7));
  CurrentSensorDc *output_current_sensor = new CurrentSensorDc(A1);
  CurrentSensorAc *input_current_sensor = new CurrentSensorAc(A0);

  // Calibrate current-sensors (To get nice values)
  input_current_sensor->calibrate();
  output_current_sensor->calibrate();

  // Capture data from sensors
  data_input.current = input_current_sensor->calculate();
  data_input.volt = input_voltage_sensor->calculate();
  data_output.volt = output_voltage_sensor->calculate();
  data_output.current = output_current_sensor->calculate();

  // Dealocate memory used by objetcs
  delete input_current_sensor;
  delete output_current_sensor;
  delete input_voltage_sensor;
  delete output_voltage_sensor;

  // Log captured data once to SD card.
  bool status = logger.log(data_input.volt, data_input.current, data_output.volt,
                           data_output.current, "sensor.txt");

  // Display captured data on LCDs
  disp1.disp_measurements(data_input.volt, data_input.current, 0);
  disp2.disp_measurements(data_output.volt, data_output.current, 1);
}

void loop()
{
  // pass
}

/* Functions*/

bool read_button_state(void)
{
  return digitalRead(PIN_BUTTON);
}