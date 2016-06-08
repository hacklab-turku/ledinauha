#Ledinauha
An Arduino project for controlling a WS2811 led strip from another device over serial interface

Arduino project is under `parempi-ledinauha`

`rainbow.py` is an example script which displays a scrolling rainbow. Usage: `python3 rainbow.py <serial port device> <baud rate>`

###Protocol
The Arduino will send one zero byte when it is ready, wait for this before you begin sending commands.
One command is 3*`N_LEDS` bytes long, where `N_LEDS` is the number of LEDs in your strip.

A byte with the high bit set signals the beginning of a new command. All values are in the range 0-127, so the high bit of any byte will never be set other than to signal the beginning of a new command.

A command consists of a series of R, G, and B values in the range 0-127, for each LED in the strip, starting from the first LED.

When one command has been successfully received and sent to the LED strip, the Arduino will send one zero byte to indicate that it is ready.
