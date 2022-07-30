import lcd, functions

def left_top():
    lcd.clear_display()
    lcd.display("Scanning...", 0)
    networks = functions.scan_network()
    j=0
    lcd.clear_display()
    for i in networks:
        lcd.display(str(i[0].decode("utf-8")), j)
        j = j+1
        if(j > 7):
            break

def right_top():
    lcd.clear_display()
    lcd.display("right_top", 0)

def left_bottom():
    lcd.clear_display()
    lcd.display("left_bottom", 0)

def right_bottom():
    lcd.clear_display()
    lcd.display("right_bottom", 0)

def select():
    lcd.clear_display()
    lcd.display("select", 0)