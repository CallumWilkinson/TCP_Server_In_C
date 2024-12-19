#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// for close() and read()
#include <unistd.h>
// for socket functions
#include <sys/socket.h>
// for sockaddr_in
#include <netinet/in.h>
// for htons() and inet_ntoa()
#include <arpa/inet.h>

#define PORT 8080
//message to send to client can be up to 1kb long (1024 bytes) which is 1024 CHARACTERS LONG
#define BUFFER_SIZE 1024


int main()
{
    int server_fd;
    int client_fd;

    //create an instance of the predefined structure called sockaddres_in from netinet/in.h
    //used to store internet adresses
    //https://pubs.opengroup.org/onlinepubs/009695399/basedefs/netinet/in.h.html
    //a TCP socket is just an IP adress and a port number
    //address of the TCP socket (endpoint) on the server side
    struct sockaddr_in socket_address;
    //address of the TCP socket (endpoint) on the client side
    struct sockaddr_in client_address;
    //length of address
    socklen_t addr_len = sizeof(socket_address);

    //this is the message string
    const char *message = "Hello I am a server! =)";

    //string array to hold the DATA RECEIVED FROM THE CLIENT, message up to 1024 characters long text (1024 BYTES)
    //initialise it as blank
    char buffer[BUFFER_SIZE] = {0};





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
    socket_address.sin_family = AF_INET;
    //set socket's port to 8080
    //function just converts to network byte order itsnot that important
    socket_address.sin_port = htons(PORT);
    //sin_addr is the IP adress field of the socket
    //set socket's IP to local host
    socket_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    //bind the socket to the socket's address (assign a name to the socket)
    //you need to do this so that the TCP socket can receive connections
    int bind_status = bind(server_fd, (struct sockaddr *)&socket_address, addr_len);

    //if bind function returns negative 1 it will fail
    if (bind_status < 0)
    {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    //else it worked print bound to port 8080
    printf("Socket successfully bound to port %d.\n", PORT);




    //STEP 3: LISTEN FOR CONNECTIONS
    //set backlog to 5, so we can have 5 connections in the queue while server is handing other connections
    //5 is just a standard number for some reason
    //listen allows the socket to accept incomming requests using the accept() function
    int listen_status = listen(server_fd, 5);

    if(listen_status < 0)
    {
        //listen() returns -1 if failed, 0 if success
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    //else it worked
    printf("Server is listening for communication from the client...\n");





    //STEP 4: ACCEPT A CLIENT CONNECTION
    //accept returns an int which will be the CLIENT's FILE DESCRIPTOR
    //function takes in the server socket THAT IS CURRENTLY LISTENING for communication from the client
    //next takes in a pointer to the CLIENT's TCP SOCKET ADDRESS and a POINTER to the address length
    client_fd = accept(server_fd, (struct sockaddr *)&client_address, &addr_len);

    if(client_fd < 0)
    {
        //accept() returns -1 like other functions on failure and 0 on success
        perror("Failed to accept communication from client");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    //functions are just for formatting they are not that important
    printf("Connection accepted from %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));





    //STEP 5: SEND A MESSAGE TO THE CLIENT
    //send returns number of characters sent in the message, -1 if error
    //takes in server file desripter, the message, its size and a flag, i set the flag to 0 cos it doesnt seem important
    ssize_t num_bytes_sent = send(server_fd, message, strlen(message), 0);

    if (num_bytes_sent < 0)
    {
        perror("Failed to send message to client");
        close(server_fd);
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    printf("Messaged sent to client Successfully!\n");






    //STEP 6: RECEIVE A MESSAGE FROM THE CLIENT
    //read function from unistd.h to read from a file descriptor
    //returns -1 on error, on success returns num of bytes received
    //read() attempts to read the bytes received from the client file descriptor INTO THE BUFFER ARRAY
    ssize_t num_bytes_received = read(client_fd, buffer, BUFFER_SIZE);

    if(num_bytes_received < 0)
    {
        perror("Could not read message sent from the client");
        close(server_fd);
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    //print to the server's terminal what the client's message was
    printf("The Client said: %s\n", buffer);
    //send the message the client said back to the client so it also gets a confirmation that the sever received it's message
    //called "echoing the message"
    send(client_fd, buffer, num_bytes_received, 0);




    //STEP 7: CLOSE SOCKETS
    close(client_fd);
    close(server_fd);
    printf("Connection closed :)\n");


    return 0;
}
