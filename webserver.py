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

        html = """<html><head> <title>ESP Web Server</title> <meta name="viewport" content="width=device-width, initial-scale=1">
        <link rel="icon" href="data:,"> <style>html{font-family: Helvetica; display:inline-block; margin: 0px auto; text-align: center;}
        h1{color: #0F3376; padding: 2vh;}p{font-size: 1.5rem;}.button{display: inline-block; background-color: #e7bd3b; border: none; 
        border-radius: 4px; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}
        .button2{background-color: #4286f4;}.button3{background-color: #42adf5;}</style></head><body> <h1>ESP Web Server</h1> 
        <p>GPIO state: <strong>""" + gpio_state + """</strong></p>
        <p><a href="/?led=on"><button class="button">ON</button></a></p>
        <p><a href="/?led=off"><button class="button button2">OFF</button></a></p>
        <p><a href="/?server=off"><button class="button button3">Stop</button></a></p></body></html>"""
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