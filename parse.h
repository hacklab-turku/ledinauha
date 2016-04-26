/*
simple parse script
translates
<LEDNumber> <R> <G> <B>\n
in to an array
*/

#ifndef PARSE_H
#define PARSE_H 

#include "Arduino.h"
#define N_LEDS 50
#define SEPARATOR ' '
#define ENDOFLINE '\n'

volatile char led[N_LEDS][4];


int rawParse(char c);
void cmdParse(char c);

#endif
