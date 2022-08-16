#include "button_control.h"

void top_left(String value)
{
    print_debug("DEBUG","top_left");
    clear_lcd();
    if(gps_recording)
    {
        TickerForGPS.detach();
        gps_recording = false;
        print_lcd("Auto GPS",0);
        print_lcd("OFF",1);
    }
    else{
        TickerForGPS.attach(5, get_gps_data);
        gps_recording = true;
        print_lcd("Auto GPS",0);
        print_lcd("ON",1);        
    }
}

void top_right(String value)
{
    enable_ap();
    clear_lcd();
    print_lcd("AP Enabled",1);
    print_debug("DEBUG","top_right");
}

void bottom_left(String value)
{
    print_debug("DEBUG","bottom_left");
    toggle_bkled();
}

void bottom_right(String value)
{
    print_debug("DEBUG","bottom_right");
    print_intro();
}

void select(String value)
{
    print_debug("DEBUG","select");
    get_gps_data();
}