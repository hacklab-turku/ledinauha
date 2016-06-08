#!/usr/bin/python3

import serial
import random
import time
import math
import colorsys
import sys

def hsv2rgb(h,s,v):
    return tuple(i * 127 for i in colorsys.hsv_to_rgb(h,s,v))

ser = serial.Serial(sys.argv[1], baudrate=int(sys.argv[2]))

ser.read(1)

while 1:
  data = []
  for i in range(50):
    now = time.time()/3
    
    color = hsv2rgb(now % 1 + i/50, 1, 1)
    
    red = int(color[0]) 
    green = int(color[1])
    blue = int(color[2])

    if i==0:  #this sets the high bit if the byte is the first in a new command
      red = (red&0b01111111)|0b10000000
    else:
      red = red&0b01111111
    green = green&0b01111111
    blue = blue&0b01111111
    
    data = [red, green, blue]
    ser.write(bytes(data))
    
  ser.flush()
  ser.read(1) #wait for ready signal from Arduino

ser.close()
