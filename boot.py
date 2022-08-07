import webrepl, lcd, time, functions
from button_control import left_top, right_top, left_bottom, right_bottom, select

webrepl.start()
ip_config = functions.do_connect('Airtel_B403', 'airtelb403')
functions.init_uart()
functions.print_intro(ip_config)

#webserver.start_web_server()