/* Copyright (C) 2023 Sean Kannanaika; - All Rights Reserved
 * You may use, distribute and modify this code under the fact
 * that code and knowledge should not be owned by anyone.  Have
 * at it viewers of my code. Do whatever the hell you want.
 */

//header file to include holding function prototypes

#ifndef NETWORK_H
#define NETWORK_H

int createSocket(void);
int connectToServer(char * ip_addr, int socket_connection, int port);
int sendData(char * message, int socket_connection);
void recvData(int socket_connection, char buffer[]);

#endif