#include "button_control.h"

void top_left(String value)
{
    print_debug("DEBUG","top_left");
    enable_ap();
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
}

void select(String value)
{
    print_debug("DEBUG","select");
}