#include "button_control.h"

void top_left(String value)
{
    print_debug("DEBUG","top_left");
    clear_lcd();
    if(gps_recording)
    {
        TickerForGPS.detach();
        gps_recording = false;
        print_lcd("Record GPS",0);
        print_lcd("OFF",1);
    }
    else{
        File gps_record = SPIFFS.open("/track.txt", "w");
        if(gps_record){
            if(gps_record.println("")){
                print_lcd("track.txt", 3);
                print_lcd("Cleared", 4);
            }
            gps_record.close();
        }
        TickerForGPS.attach(5, get_gps_data);
        gps_recording = true;
        print_lcd("Record GPS",0);
        print_lcd("ON",1);        
    }
}

void top_right(String value)
{
    if(!ap_enabled)
    {
        ap_enabled = true;
        enable_ap();
        clear_lcd();
        print_lcd("AP Enabled",1);
        print_debug("DEBUG","top_right");
    }
    else
    {
        ap_enabled = false;
        disable_ap();
        clear_lcd();
        print_lcd("AP Disabled",1);
        print_debug("DEBUG","top_right");
    }
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