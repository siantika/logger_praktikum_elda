#include "Display.h"

Display::Display(LiquidCrystal_I2C &lcd) : lcd(lcd)
{
}

// private methods
void Display::clear(void)
{
    lcd.clear();
}

// public method
void Display::init(void)
{
    this->lcd.init();
    this->lcd.backlight();
    this->lcd.setCursor(0, 0);
    this->lcd.print("***---INIT---***");
    this->lcd.setCursor(0, 1);
    this->lcd.print("PRAK ELDAYA M.1");
}

void Display::first_message(void)
{
    clear();
    this->lcd.setCursor(0, 0);
    this->lcd.print(FIRST_MSG_ROW_0);
}