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
    this->lcd.print("** PRAKTIKUM **");
    this->lcd.setCursor(0, 1);
    this->lcd.print("  ELDA MODUL 1");
}

void Display::first_message(void)
{
    clear();
    this->lcd.setCursor(0, 0);
    this->lcd.print(FIRST_MSG_ROW_0);
    this->lcd.setCursor(0, 1);
    this->lcd.print(FIRST_MSG_ROW_1);
}

void Display::second_message(void)
{
    clear();
    this->lcd.setCursor(0, 0);
    this->lcd.print(SECOND_MSG_ROW_0);
    this->lcd.setCursor(0, 1);
    this->lcd.print(SECOND_MSG_ROW_1);
}

void Display::disp_measurements(float &volt, float &current, bool pos, bool debug_mode = false)
{
    clear();
    if (pos == 0)
    {
        this->lcd.setCursor(0, 0);
        if (debug_mode) {this->lcd.print(F("DEBUG INPUT:"));}
        else {this->lcd.print(F("NILAI INPUT:"));}
    }
    else
    {
        this->lcd.setCursor(0, 0);
        if (debug_mode) {this->lcd.print(F("DEBUG OUTPUT:"));}
        else {this->lcd.print(F("NILAI OUTPUT:"));}
    }
    this->lcd.setCursor(0, 1);
    String msg_display = String(volt) + "V | " + String(current) + "A";
    this->lcd.print(msg_display);
}

void Display::disp_custom(String msg_row_0, String msg_row_1)
{
    this->lcd.clear();
    this->lcd.setCursor(0,0);
    this->lcd.print(msg_row_0);
    this->lcd.setCursor(0,1);
    this->lcd.print(msg_row_1);
}
