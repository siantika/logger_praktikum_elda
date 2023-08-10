#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

const String FIRST_MSG_ROW_0 = "** INSTRUKSI **";
const String FIRST_MSG_ROW_1 = "  RANGKAILAH !";

const String SECOND_MSG_ROW_0 = "** INFORMASI **";
const String SECOND_MSG_ROW_1 = "   ALAT SIAP!";

class Display
{
private:
    LiquidCrystal_I2C &lcd;
    void clear(void);

public:
    Display(LiquidCrystal_I2C &lcd);
    void init(void);
    void first_message(void);
    void second_message(void);
    void disp_measurements(float& volt, float& current, bool pos);
    void disp_custom(String msg_row_0, String msg_row_1);
};

#endif
