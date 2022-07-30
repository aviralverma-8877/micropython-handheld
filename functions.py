import network

def scan_network():
    sta_if = network.WLAN(network.STA_IF)
    networks = sta_if.scan()
    return networks