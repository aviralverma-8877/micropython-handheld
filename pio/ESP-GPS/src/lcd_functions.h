#ifndef lcd_function
    #define lcd_function
    #include "global_var.h"
    void print_lcd(String msg, int line);
    void clear_lcd();
    void toggle_bkled();
    void set_lcd_contrast(int value);
    void alert_lcd();
    void print_intro();
#endif