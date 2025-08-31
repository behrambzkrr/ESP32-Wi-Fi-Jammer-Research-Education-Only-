import network
import time

sta = network.WLAN(network.STA_IF)
sta.active(True)

while True:
    nets = sta.scan()
    print("Ağlar:")
    for net in nets:
        ssid = net[0].decode('utf-8')
        bssid = ':'.join('{:02x}'.format(b) for b in net[1])
        print("SSID:", ssid, "BSSID:", bssid, "RSSI:", net[3])
    time.sleep(10)