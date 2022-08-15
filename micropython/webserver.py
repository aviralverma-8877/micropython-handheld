import socket, lcd, functions, json

class WebServer:
    def __init__(self):
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.s.bind(('', 80))
        self.s.listen(5)
        self.bkled_state = True

    def web_page(self):
        if self.bkled_state == True:
            gpio_state="ON"
        else:
            gpio_state="OFF"
        f = open("index.html","r")
        html = f.read()
        return html

    def stop_web_server(self):
        self.web_server_status = False

    def start_web_server(self):
        while True:
            conn, addr = self.s.accept()
            request = conn.recv(1024)
            request = str(request)
            led_on = request.find('/?led=on')
            led_off = request.find('/?led=off')
            server_off = request.find('/?server=off')
            print_into = request.find('/?welcome')
            if led_on == 6:
                self.bkled_state = True
                lcd.clear_display()
                lcd.turn_on_bkled()
                lcd.display("BKLED ON", 0)
            if led_off == 6:
                lcd.clear_display()
                lcd.turn_off_bkled()
                lcd.display("BKLED OFF", 0)
                self.bkled_state = False
            if server_off == 6:
                lcd.clear_display()
                lcd.display("Server Stopped...", 0)
                break
            if print_into == 6:
                f = open("config.json")
                config = json.load(f)
                ip_config = functions.do_connect(config["wifi"]["ssid"], config["wifi"]["pass"])
                functions.print_intro(ip_config)
            response = self.web_page()
            conn.send('HTTP/1.1 200 OK\n')
            conn.send('Content-Type: text/html\n')
            conn.send('Connection: close\n\n')
            conn.sendall(response)
            conn.close()