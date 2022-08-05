import lcd, functions
from webserver import WebServer

web_server = WebServer()
bkled = True

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
    lcd.display("web server", 0)
    lcd.display("Started...", 1)
    web_server.start_web_server()

def left_bottom():
    global bkled
    lcd.clear_display()
    if bkled:
        lcd.turn_off_bkled()
        lcd.display("BKLED OFF", 0)
        bkled = False
    else:
        lcd.turn_on_bkled()
        lcd.display("BKLED ON", 0)
        bkled = True

def right_bottom():
    lcd.clear_display()
    lcd.display("right_bottom", 0)

def select():
    lcd.clear_display()
    lcd.display("select", 0)