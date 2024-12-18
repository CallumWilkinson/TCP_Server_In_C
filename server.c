#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

//in this project i should bind to port 127.0.0.1 (local host) and NOT 0.0.0.0
//run server on port above 1024, stick to port 8080


//link with ws2_32.lib
//dunno what this means but whatever
#pragma comment(lib, "ws2_32.lib")

#define port 8080
#define BUFFER_SIZE 1024

int main()
{
    WSADATA wsadata;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int addrLen = sizeof(clientAddr);
    char buffer[BUFFER_SIZE];
    
}