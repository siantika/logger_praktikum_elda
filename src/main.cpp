#include <Arduino.h>
#include "Display.h"

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd1(0x27, 16, 2);
LiquidCrystal_I2C lcd2 (0x23, 16, 2);
Display disp1(lcd1); // untuk input
Display disp2(lcd2); // untuk output


typedef struct data_collect
{
  float volt;
  float current;
} data_collect;

data_collect data_input;
data_collect data_output;

void setup()
{
  data_input.current = (float) 0.09;
  data_input.volt = (float) 220.3;
  data_output.current = (float) 1.89;
  data_output.volt = (float) 112.3;

  disp1.init();
  disp2.init();
  delay(2000);
  disp1.first_message();
  disp2.first_message();
  delay(2000);
  disp1.second_message();
  disp2.second_message();
  delay(2000);
  disp1.disp_measurements(data_input.volt, data_input.current, 0);
  disp2.disp_measurements(data_output.volt, data_output.current, 1);
}

void loop()
{
}
