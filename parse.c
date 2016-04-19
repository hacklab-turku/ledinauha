/*
simple parse script
translates
<LEDNumber> <R> <G> <B>\n
in to an array
*/
#include "Arduino.h"
#include <stdlib.h>
#include "parse.h"

void rawParse(char c)
{
    static char command[4];
    static char charcounter = 0;
    
    command[charcounter] = c;
    charcounter++;
    
    if(charcounter == 4) {
        charcounter = 0;
        for(int i = 0; i < 4; i++) {
            led[command[0]-128][i] = command[i+1];
        }
    }
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
