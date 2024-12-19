# TCP_Server_In_C
This is a mini project where I made a TCP server in C using sys/socket.h - sockets for linux. I did this to practice writing C off the back of learning C in Harvard CS50x, and also to learn a bit more about networking. Also I wanted to practise actually using and reading documentation instead of relying on ChatGPT so much lol.

The server creates a TCP socket for communication with a the client, binds it to an IP address and PORT, listens for communications, accepts a connection from the client using the client's TCP socket address, sends a message to the client and echos it back to them.
