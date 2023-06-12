#include <Arduino.h>
#include "Display.h"

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd (0x27, 16, 2);
Display disp1(lcd);


void setup() {
  
  disp1.init();
  

}

void loop() {
  
}

