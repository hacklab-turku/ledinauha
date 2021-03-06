/*
simple parse script
translates
<LEDNumber> <R> <G> <B>\n
in to an array
*/
#include "Arduino.h"
#include <stdlib.h>
#include "parse.h"

//volatile char ledsRefresh=0;

int rawParse(char c)
{
    static char rawCommand[4];
    static char rawCharcounter = 0;

    if (c&0x80) {
      rawCharcounter = 0;
    }
    
    rawCommand[rawCharcounter] = c;
    
    rawCharcounter++;
    
    if(rawCharcounter == 4) {
        rawCharcounter = 0;
        for(int i = 0; i < 3; i++) {
            led[rawCommand[0]&0x7f][i] = rawCommand[i+1];
        }
        led[rawCommand[0]&0x7f][3] = 1;
        return 1;
    }
    return 0;
}
    

void cmdParse(char c)
{
    static char command[20];
    static char charcounter = 0;
    char values[4] = {0,0,0,0};
    char parsecounter = 0;
    
    //add text to buffer until string ends
    command[charcounter] = c;
    charcounter ++;
    
    if(command[charcounter-1]==ENDOFLINE)    //start parsing the string
    {
        for(int i = 0; i < 4; i ++) //temprorarily store values in an array
        {
            while(command[parsecounter] != SEPARATOR && command[parsecounter] != ENDOFLINE)  //spaces seperate the values
            {
                values[i] *= 10;  //previous vaules were tens or hundreds
                values[i] += command[parsecounter]-0x30;
                parsecounter ++;  //go to next character
            }
            parsecounter ++;  //skip over the separator
        }
        //parse complete, dump values to the main array to the corresponding position
        for(int i = 0; i < 3; i ++)
            led[values[0]][i]=values[i+1];
        charcounter=0;
    }
}
