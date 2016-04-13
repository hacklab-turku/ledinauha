#!/usr/bin/python

import serial
import random
import time

ser = serial.Serial('/dev/ttyUSB0')

while 1:
    led=random.randrange(50)
    red=random.randrange(127)
    grn=random.randrange(127)
    blu=random.randrange(60)
    data=str(led)+' '+str(red)+' '+str(grn)+' '+str(blu)+'\n'
    ser.write(data)
    time.sleep(0.05)

ser.close()
