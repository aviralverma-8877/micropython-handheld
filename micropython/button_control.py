import lcd, functions, json
from webserver import WebServer

web_server = WebServer()

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
    lcd.clear_display()
    lcd.flip_bkled()
    lcd.display("BKLED Flip", 0)

def right_bottom():
    f = open("config.json")
    config = json.load(f)
    ip_config = functions.do_connect(config["wifi"]["ssid"], config["wifi"]["pass"])
    functions.print_intro(ip_config)
