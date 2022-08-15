import time, json
delay = 0.5
def display(message, line):
    data = {
        "m":message,
        "l":line
    }
    print(json.dumps(data))
    time.sleep(delay)

def clear_display():
    data = {
        "c":0
    }
    print(json.dumps(data))
    time.sleep(delay)

def flip_bkled():
    data = {
        "c":1
    }
    print(json.dumps(data))
    time.sleep(delay)

def set_contrast(value):
    data = {
        "c":2,
        "v":value
    }
    print(json.dumps(data))
    time.sleep(delay)

def alert():
    data = {
        "c":3
    }
    print(json.dumps(data))
    time.sleep(delay)