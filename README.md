# TCP_Server_In_C
This is a mini project where I made a TCP server in C using sys/socket.h - sockets for linux. I did this to practice C from recently learning some of it in Harvard CS50, and also to learn a bit more about networking

The server creates a TCP socket for communication with a the client, binds it to an IP address and PORT, listens for communications, accepts a connection from the client using the client's TCP socket address, sends a message to the client and echos it back to them.
