/* Copyright (C) 2023 Sean Kannanaika; - All Rights Reserved
 * You may use, distribute and modify this code under the fact
 * that code and knowledge should not be owned by anyone.  Have
 * at it viewers of my code. Do whatever the hell you want.
 */

//header file to include holding function prototypes

#ifndef KEYLOG_H
#define KEYLOG_H


void detectKeyboard(char * fileNameBuffer);
int logKeyStroke(char * LOGFILE, char * key);
char * mapButtonRelease(int event_code, int shiftHeld, int capsLock);

#endif