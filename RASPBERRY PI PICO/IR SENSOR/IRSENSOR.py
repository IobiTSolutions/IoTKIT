from machine import Pin
import utime as time

led = Pin(25, Pin.OUT)
sensor = Pin(28, Pin.IN)

while True:
    time.sleep(1)
    print(sensor.value())
    if sensor.value()==0:
        led.value(1)
    else:
        led.value(0)
    
   