import socket, lcd

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
            print('Got a connection from %s' % str(addr))
            request = conn.recv(1024)
            request = str(request)
            print('Content = %s' % request)
            led_on = request.find('/?led=on')
            led_off = request.find('/?led=off')
            server_off = request.find('/?server=off')
            if led_on == 6:
                self.bkled_state = True
                lcd.clear_display()
                lcd.turn_on_bkled()
                lcd.display("BKLED ON", 0)
                print('BKLED ON')
            if led_off == 6:
                lcd.clear_display()
                lcd.turn_off_bkled()
                lcd.display("BKLED OFF", 0)
                self.bkled_state = False
                print('BKLED OFF')
            if server_off == 6:
                lcd.clear_display()
                lcd.display("Server Stopped...", 0)
                break
            response = self.web_page()
            conn.send('HTTP/1.1 200 OK\n')
            conn.send('Content-Type: text/html\n')
            conn.send('Connection: close\n\n')
            conn.sendall(response)
            conn.close()