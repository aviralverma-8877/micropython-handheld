import lcd, functions, json
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
    f = open("config.json")
    config = json.load(f)
    ip_config = functions.do_connect(config["wifi"]["ssid"], config["wifi"]["pass"])
    functions.print_intro(ip_config)

def select():
    lcd.clear_display()
    lcd.display("Connecting to", 0)
    lcd.display("GPS",1)
    lcd.get_gps()
