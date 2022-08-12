import network, lcd, time
from machine import UART

def scan_network():
    sta_if = network.WLAN(network.STA_IF)
    networks = sta_if.scan()
    return networks

def do_connect(uname, password):
    sta_if = network.WLAN(network.STA_IF)
    ap_if = network.WLAN(network.AP_IF)
    if not sta_if.isconnected():
        print('connecting to network...')
        sta_if.active(True)
        sta_if.connect(uname, password)
        retry = 10
        while not sta_if.isconnected():
            retry = retry-1
            time.sleep(0.5)
            if(retry == 0):
                break
        if (sta_if.isconnected()):
            ap_if.active(False)
        else:
            ap_if.active(True)
    return sta_if.ifconfig()

def init_uart():
    uart = UART(0, baudrate=115200)
    uart.init()

def gps_data(time, status, latitud, latitudHemisphere, longitud, longitudMeridiano, speedKnots, trackAngle, date, magneticVariation, magneticVariationOrientation):
    lcd.clear_display()
    lcd.display("Time : "+time, 0)
    lcd.display("status : "+status, 1)
    lcd.display("Latitud : "+latitud, 2)
    lcd.display("Longitud : "+longitud, 3)
    lcd.display("Date : "+date, 4)
    lcd.display("Speed : "+speedKnots, 5)

def print_intro(ip_config):
    print("\n")
    lcd.set_contrast(5)
    lcd.clear_display()
    lcd.display("Hello World", 0)
    lcd.display("We are running", 1)
    lcd.display("Micropython!!", 2)
    lcd.display("Use WebREPL", 3)
    lcd.display("Connect to:", 4)
    lcd.display(ip_config[0], 5)
    lcd.display(ip_config[3], 6)
    lcd.alert()
    print("\n")
