#include <Arduino.h>
#include "Display.h"
#include "VoltageSensor.h"
#include <LiquidCrystal_I2C.h>
#include "Logger.h"

#define PIN_BUTTON 2

volatile int button_state = 1;

LiquidCrystal_I2C lcd1(0x27, 16, 2);
LiquidCrystal_I2C lcd2(0x23, 16, 2);
Display disp1(lcd1); // untuk input
Display disp2(lcd2); // untuk output

Logger logger;
VoltageSensorDc voltage_sensor_dc(A7);

typedef struct data_collect
{
  float volt;
  float current;
} data_collect;

data_collect data_input;
data_collect data_output;

// Forward declarations
bool read_button_state(void);

void setup()
{
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  Serial.begin(115200);
  Serial.println(logger.init(10));
  data_input.current = (float)0.09;
  data_input.volt = (float)220.3;
  data_output.current = (float)1.89;
  data_output.volt = (float)112.3;

  disp1.init();
  disp2.init();
  delay(2000);
  disp1.first_message();
  disp2.first_message();
  
  // waiting button state
  while (button_state != 0)
  {
    button_state = read_button_state();
  }

  disp1.second_message();
  disp2.second_message();

  delay(500);

    // waiting button state
    button_state = 1; // reset to untouch
  while (button_state != 0)
  {
    button_state = read_button_state();
  }

  disp1.disp_custom(F("** INFORMASI **"), F("Collecting ..."));
  disp2.disp_custom(F("** INFORMASI **"), F("Collecting ..."));

  delay(3000);


  // for (;;)
  // {
  //   disp1.disp_custom("OUTPUT: ", String(voltage_sensor_dc.calculate()));
  //   delay(250);
  // }

  logger.log(data_input.volt, data_input.current, data_output.volt,
             data_output.current, "sensor.txt");
  delay(2000);
  disp1.disp_measurements(data_input.volt, data_input.current, 0);
  disp2.disp_measurements(data_output.volt, data_output.current, 1);

}

void loop()
{
  // pass
}

// Functions  
bool read_button_state(void)
{
  return digitalRead(PIN_BUTTON);
}