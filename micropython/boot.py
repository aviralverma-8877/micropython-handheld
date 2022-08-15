import webrepl, functions, json
from button_control import left_top, right_top, left_bottom, right_bottom
from functions import gps_data
import machine

machine.freq()          # get the current frequency of the CPU
machine.freq(160000000) # set the CPU frequency to 160 MHz

webrepl.start()
f = open("config.json")
config = json.load(f)
ip_config = functions.do_connect(config["wifi"]["ssid"], config["wifi"]["pass"])
functions.init_uart()
functions.print_intro(ip_config)

#webserver.start_web_server()