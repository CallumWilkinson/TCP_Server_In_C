#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// for close()
#include <unistd.h>
// for socket functions
#include <sys/socket.h>
// for sockaddr_in
#include <netinet/in.h>
// for htons() and inet_ntoa()
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024


int main()
{
    int server_fd;
    int client_fd;
    //create an instance of the predefined structure called sockaddres_in from netinet/in.h
    //used to store internet adresses
    //https://pubs.opengroup.org/onlinepubs/009695399/basedefs/netinet/in.h.html
    struct sockaddr_in address;
    //length of address
    socklen_t addr_len = sizeof(address);







    //STEP 1 CREATE A SOCKET
    //create a server file descriptor using IPV4 and TCP for connection
    //the socket function returns a file descriptor that refers to an endpoint for communication
    //AF_INET = IPV4
    //SOCK_STREAM = TCP
    //0 just means use the default
    server_fd = socket(AF_INET, SOCK_STREAM, 0);


    //socket function returns -1 if error
    if (server_fd == -1)
    {
        perror("Could not create socket");

        //exit the calling process
        exit(EXIT_FAILURE);
    }

    //else it worked
    printf("Socket successfully created.\n");









    //STEP 2: BIND SOCKET TO IP/PORT
    //set the socket'S adress to IPV4
    address.sin_family = AF_INET;
    //set socket's port to 8080
    address.sin_port = htons(PORT);
    //sin_addr is the IP adress field of the socket
    //set socket's IP to local host
    address.sin_addr.s_addr = inet_addr("127.0.0.1");


    //bind the socket to the socket's address (assign a name to the socket)
    //you need to do this so that the TCP socket can receive connections
    int bind_status = bind(server_fd, (struct sockaddr *)&address, addr_len);

    //if bind function returns negative 1 it will fail
    if (bind_status < 0)
    {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    //else it worked print bound to port 8080
    printf("Socket successfully bound to port %d.\n", PORT);








    //STEP 3: listen for connections
    int listen_status = listen(server_fd, );









    //STEP 4: accept a client connection

    //STEP 5: communicate with the client

    //STEP 6: close sockets

    return 0;
}
