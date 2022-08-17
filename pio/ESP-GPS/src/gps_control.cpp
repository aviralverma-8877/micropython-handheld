#include "gps_control.h"

void process_nmea(DynamicJsonDocument value)
{
    clear_lcd();
    print_lcd("GPS Data",0);
    if (value.containsKey("lat"))
    {
        if (value.containsKey("lng"))
        {
            print_lcd("Location:", 1);
            print_lcd("Lat : "+String(value["lat"]), 2);
            print_lcd("Lng : "+String(value["lng"]), 3);
        }
    }

    if (value.containsKey("day"))
    {
        if (value.containsKey("month"))
        {
            if (value.containsKey("year"))
            {
                String date_val = String(value["day"])+"/"+String(value["month"])+"/"+String(value["year"]);
                print_lcd("Date:", 4);
                print_lcd(date_val, 5);
            }
        }
    }


    if (value.containsKey("hour"))
    {
        if (value.containsKey("minute"))
        {
            if (value.containsKey("second"))
            {
                print_lcd("Time:", 6);
                String time_val = String(value["hour"])+":"+String(value["minute"])+":"+String(value["second"]);
                print_lcd(time_val, 7);
            }
        }
    }
}