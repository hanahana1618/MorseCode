//
//  main.c
//  MorseCode application which takes in a user-defined word and blinks the LEDs on the B^3.
//
//  Created by Ivette Prieto Castro on 10/25/17.
//  Copyright © 2017 FIU. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "McodeMod.h"


int main(int argc, const char * argv[]) {

    
    /* the empty string, follwed by 26 letter codes, followed by the 10 numeral codes, followed by the comma,
     period, and question mark.  */
    
    if (argc > 3) {
        printf("You have provided too many inputs. Closing program");
        return -1;
    }

    else if (argc < 3) {
        printf("You have provided less inputs than what the program requires. In order to run the program: './McodeM -w WORD'/n Closing program. ");
        return -1;
    }
        
    
    else if (argc == 3){
        if (strcmp(argv[1], "-w")) {
            //DEBUG
            printf("This shit works");


            //Check if this works at all
            unsigned long length = strlen(argv[2]);
            int i;
            FILE *fhandler;
            fhandler = fopen("/sys/class/leds/beaglebone:green:usr0/brightness", "w");
            
            FILE *fp;
            fp = fopen("/sys/class/leds/beaglebone:green:usr0/delay_off", "W");
            
            FILE *fh;
            fh = fopen("/sys/class/leds/beaglebone:green:usr0/delay_on", "w");
            
            FILE *ftrigger;
            ftrigger = fopen("/sys/class/leds/beaglebone:green:usr0/trigger", "w");
            
            //loop through every character in the word
            for (i = 0; i <= length; i++) {
                //send the current char to the mcodestring function to have its morse code equivalent
                char* morseValue = mcodestring(argv[2][i]);
                
                //send the Morse code string into the B^3 for it to be displayed using the LEDs
                
                
                
                
                int j;
                unsigned long length2 = strlen(morseValue);
                for (j = 0; j <= length2; j++ ) {
                    if (morseValue[j] == '.') {
                        //add code for one unit of time
                        fprintf(ftrigger, "none");
                        sleep(1);
                        fprintf(fhandler, "1");
                        
                    }
                    else if (morseValue[j] == '-') {
                        //add code for three units of time
                        //int counter = 0;
                        fprintf(ftrigger,"timer");
                        fprintf(fp, "500");
                        fprintf(fh, "500");
                        //keep the LEDs flashing like that for 3 seconds
                        sleep(3);
                        
                    }
                    usleep(1000);
                    //wait half a second in between 
                    
                    //printf("echo none > /sys/class/leds/beaglebone ")
                }
                
                fclose(fhandler);
                fclose(fp);
                fclose(fh);
                fclose(ftrigger);
                
                
            }
        }
    }
    
    
    
    
    return 0;
}



