import time
delay = 0.1
def display(message, line):
    data = {
        "m":message,
        "l":line
    }
    print(data)
    time.sleep(delay)

def clear_display():
    data = {
        "c":0
    }
    print(data)
    time.sleep(delay)

def turn_off_bkled():
    data = {
        "c":1
    }
    print(data)
    time.sleep(delay)

def turn_on_bkled():
    data = {
        "c":2
    }
    print(data)
    time.sleep(delay)

def set_contrast(value):
    data = {
        "c":3,
        "v":value
    }
    print(data)
    time.sleep(delay)

def alert():
    data = {
        "c":4
    }
    print(data)
    time.sleep(delay)

def get_gps():
    time.sleep(delay)
    data = {
        "c":5
    }
    print(data)
    time.sleep(delay)