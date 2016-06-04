#!/usr/bin/env python3

import serial
import sys
import signal
import colorsys
import time
import math
import pytweening
import random
import requests
import json

###
#USAGE: python3 animation.py <serial port device file> <baud rate>
###

ser = serial.Serial(sys.argv[1], baudrate=int(sys.argv[2]))
ser.read(1)

N_LEDS = 50

def clamp(x, min, max):
    if x<min: return min
    elif x>max: return max
    else: return x

class Fade:
    def __init__(self, numLeds):
        self.introStartTime = 0
        self.introDuration = 5
        self.outroStartTime = 0
        self.outroDuration = 7

        self.on = False

        self.numLeds = numLeds
        self.shuffledIndices = list(range(numLeds))
        random.shuffle(self.shuffledIndices)

    def getFade(self, index):
        if (self.on):
            return pytweening.easeInOutBounce(clamp((time.time()-(self.introStartTime+self.shuffledIndices[index]*0.02))/self.introDuration, 0, 1))
        else:
            return pytweening.easeInOutBounce(clamp(1-(time.time()-(self.outroStartTime+self.shuffledIndices[index]*0.02))/self.outroDuration, 0, 1))

    def startIntro(self):
        if (not self.on):
            self.on = True
            self.introStartTime = time.time()
    
    def startOutro(self):
        if (self.on):
            self.on = False
            self.outroStartTime = time.time()

introOutroFade = Fade(N_LEDS)

def plasmaPattern(x):
    x = x%1
    return (
            max(clamp(-6*x+2, 0, 1), clamp(6*x-4, 0, 1)),
            min(clamp(6*x, 0, 1), clamp(-6*x+4, 0, 1)),
            min(clamp(6*x-2, 0, 1), clamp(-6*x+6, 0, 1)))

def backgroundPattern(index, time):
    return plasmaPattern((math.sin(math.sqrt(math.pow((index-25)-math.cos(time/3)*25, 2)*0.6+math.pow(math.sin(time/5)*25, 2))/5)+math.sin(math.cos(index*0.25)+math.sin(time/7)*5)*0.3)*0.5-0.5) #it works

leds = [(0,0,0)]*N_LEDS

lastCheck = 0
while True:
    for i in range(N_LEDS):
        fade = introOutroFade.getFade(i)
        backgroundColor = backgroundPattern(i, time.time())

        leds[i] = (
                backgroundColor[0]*fade,
                backgroundColor[1]*fade,
                backgroundColor[2]*fade)
    
    ledData = [int(x*127)&0b01111111 for x in list(sum(leds, ()))] #flattens the led list into an RGBRGB... list and converts from 0..1 floats to 0..127 integers
    ser.write(bytes([ledData[0] | 0b10000000]+ledData[1:])) #this sets the first byte to have the high bit set and sends to serial port
    ser.flush()
    ser.read(1) #wait for response
    
    now = time.time()
    if now-lastCheck > 2:
        lastCheck = now

        pirStatus = requests.get(url="http://10.0.1.2/pi_api/pir/", params={"a":"getStatus"})
        pirTimestamp = int(json.loads(pirStatus.text)["timestamp"])

        if (pirTimestamp > now-20):
            introOutroFade.startIntro()
        else:
            introOutroFade.startOutro()
