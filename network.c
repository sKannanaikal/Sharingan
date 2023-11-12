/* Copyright (C) 2023 Sean Kannanaika; - All Rights Reserved
 * You may use, distribute and modify this code under the fact
 * that code and knowledge should not be owned by anyone.  Have
 * at it viewers of my code. Do whatever the hell you want.
 */


//necessary libraries to include
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/*
@return int socket handle
This function creates and returns a socket handle
*/
int createSocket(void){
    int socket_connection;
    socket_connection = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_connection == -1){
        return -1;
    }

    return socket_connection;

}

/*
@param ip address a socket handle and a port
@return int success(0) or failure(-1)
Given a socket handle along with an ip and a port will connect
to designated destination via socket
*/
int connectToServer(char * ip_addr, int socket_connection, int port){
    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr(ip_addr);
    server.sin_family = AF_INET;
    server.sin_port = htons (port);

    if(connect(socket_connection, (struct sockaddr *) &server, sizeof(server)) < 0){
        return -1;
    }

    return 0;
}

/*
@param key to send and a socket connection
Using a socket connection will send the desired key character
to the server
*/
int sendData(char * key, int socket_connection){
    if(send(socket_connection, key, strlen(key), 0) < 0){
        return -1;
    }

    return 0;
}

/*
@param socket connection and a buffer to hold server response
Using a socket connection will attempt to store information
sent to it into the paramterized buffer
*/
void recvData(int socket_connection, char buffer[]){
    if(recv(socket_connection, buffer, 2000, 0) < 0){
        return;
    }
    
}