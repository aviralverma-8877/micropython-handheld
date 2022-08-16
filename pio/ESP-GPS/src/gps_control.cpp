#include "gps_control.h"

void process_nmea(String value)
{
    clear_lcd();
    print_lcd("GPS Data",0);
    print_debug("DEBUG",value);
    for(char r:value)
    {
        if(gps.encode(r))
            displayGPSInfo();
    }
}

void displayGPSInfo()
{
    if (gps.location.isValid())
    {
        print_lcd("Location:", 1);
        print_lcd(String(gps.location.lat()), 2);
        print_lcd(String(gps.location.lng()), 3);
    }

    if (gps.date.isValid())
    {
        String date_val = String(gps.date.day())+"/"+String(gps.date.month())+"/"+String(gps.date.year());
        print_lcd("Date:", 4);
        print_lcd(date_val, 5);
    }

    if (gps.time.isValid())
    {
        String time_val = String(gps.time.hour())+":"+String(gps.time.minute())+":"+String(gps.time.second());
        if (gps.time.hour() < 10)
            if (gps.time.minute() < 10)
                if (gps.time.second() < 10)
                {
                    String time_val = String(gps.time.hour())+":"+String(gps.time.minute())+":"+String(gps.time.second());
                    print_lcd("Time:", 6);
                    print_lcd(time_val, 7);
                }
    }
}