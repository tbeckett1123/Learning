/* Name: 	Timothy Beckett
 * Lab:		9
 * Number:	4
 * Description: Client
 */

#include "csapp.h"

int main(int argc, char *argv[])
{
    int clientfd; //file descriptor to communicate with the server
    char *host, *port;
    size_t n;
    char buffer[MAXLINE]; //MAXLINE = 8192 defined in csapp.h

    if (argc != 3)
    {
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
        exit(0);
    }

    host = argv[1];  // getting host from command line
    port = argv[2];  // getting port from command line
    clientfd = Open_clientfd(host, port); // opening connection to host

    printf("Please enter the message: "); // getting a message from the user
    bzero(buffer,MAXLINE);                // resetting the buffer
    Fgets(buffer,MAXLINE,stdin);          // getting the message from the user

                                           // I must have deleted it, but it was not there
                                           // It took me way to long to relize this was missing
    write(clientfd,buffer,strlen(buffer)); // Sending message to the server

    bzero(buffer,MAXLINE);         // waiting for the message from the server.
    read(clientfd,buffer,MAXLINE); // the message will be stored in buffer variable.

    printf("Message from Server:"); // displaying the message in buffer on the console
    Fputs(buffer,stdout);

    // Adding second message to and from the server per the TODO insturctions
    // original comment
    // * /*TODO
    // * 1. Add a code to send new messages to the server
    // * (you can ask the user to provide a new message in the terminal)
    // * 2. Wait for the confirmation message (using Rio_readlineb function)
    // * from the server and display it.
    // * */

    printf("Please enter the message: "); // getting a message from the user
    bzero(buffer,MAXLINE);                // resetting the buffer
    Fgets(buffer,MAXLINE,stdin);          // getting the message from the user

    write(clientfd,buffer,strlen(buffer)); // sending message to the server.

    bzero(buffer,MAXLINE);         // waiting for the message from the server.
    read(clientfd,buffer,MAXLINE); // the message will be stored in buffer variable.

    printf("Second message from Server:"); // displaying the message in buffer on the console
    Fputs(buffer,stdout);

    Close(clientfd);
    return 0;
}