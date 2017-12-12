#include "socketcommunicate.h"

#include <stdio.h>          /* for printf() and fprintf() */
#include <sys/socket.h>     /* for socket(),connect(),send() and recv() */
#include <stdlib.h>         /* for atoi() and exit() */
#include <string.h>         /* for memset() */
#include <unistd.h>         /* for close() */
#include <sys/types.h> 
#include <netinet/in.h>

/*value*/
static int socketfd, clntfd;
socklen_t clntLen;
static struct sockaddr_in serv_addr, cli_addr;  
    

/*function*/
/////////////////////////////////////////////////////////////////////
//open socket
int OpenSocket(int port)
{
        socketfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

        memset(&serv_addr, 0, sizeof(serv_addr));       
        serv_addr.sin_family = AF_INET;                
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
        serv_addr.sin_port = htons(port); 

        return socketfd;
}

// Bind to the local address
int BindSocket(void)
{
    return bind(socketfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
}

//Listen to all client connect
int ListenSocket(void)
{
        return listen(socketfd, MAXPENDING);
}

//accept conection
int AcceptSocket(void)
{
        clntLen = sizeof(cli_addr);
        clntfd = accept(socketfd, (struct sockaddr *) &cli_addr, &clntLen);
        return clntfd;
}

//reciever from client
int RecvSocket(unsigned char* buffer, int buffersize)
{
        // xoa buffer
        bzero(buffer,buffersize);
        return recv(clntfd,buffer,buffersize,0); 
}

//close socket
int CloseSocket(void)
{
        return close(socketfd);
}