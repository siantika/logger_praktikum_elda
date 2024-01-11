#include "Logger.h"

// private
String Logger::get_date()
{
    DS3231 rtc(A4, A5);
    rtc.begin();
    return rtc.getDateStr();
}

String Logger::get_time()
{
    DS3231 rtc(A4, A5);
    rtc.begin();
    return rtc.getTimeStr();
}

uint8_t Logger::init(uint8_t pin_cs)
{
    // returns 
    // operation status (bool) : 0 = Works || 1 = Error
    uint8_t opt = !SD.begin(pin_cs);
    return opt;
}

bool Logger::log(float &voltage_in, float &current_in,
                 float &voltage_out, float &current_out, String file_name)
{
    bool opt_success = 0;

    File dataFile = SD.open(file_name, FILE_WRITE);
    if (dataFile)
    {
        dataFile.print(F("DATE,\t"));
        dataFile.print(F("TIME,\t"));
        dataFile.print(F("VOLTAGE IN(V),\t"));
        dataFile.print(F("CURRENT IN(A),\t"));
        dataFile.print(F("VOLTAGE OUT(V),\t"));
        dataFile.println(F("CURRENT OUT(A),"));
        dataFile.print(get_date());
        dataFile.print(",\t");
        dataFile.print(get_time());
        dataFile.print(",\t");
        dataFile.print(String(voltage_in));
        dataFile.print(",\t");
        dataFile.print(String(current_in));
        dataFile.print(",\t");
        dataFile.print(String(voltage_out));
        dataFile.print(",\t");
        dataFile.println(String(current_out));
        dataFile.close();

        opt_success = 0;
    }
    else
    {
        opt_success = 1;// error occured
    }
    return opt_success;
}
