#include <sim800l.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> // UNIX standard function definitions
#include <fcntl.h> // file control definitions
#include <errno.h> // error number definitions
#include <Serialcommunicate.h> // POISX terminal control definitions
#include <time.h>
#include <sys/wait.h>
#include <stdlib.h>

int sim800l;

int main (void)
{
    int pipefd[2];
    pid_t cpid;
    char buf;
    int n,i = 0,k=0;
    unsigned char buff[255];
    unsigned char recvdata[255];
    n = OpenSocket(4567);
    if(BindSocket() < 0)
        perror("fail to bind");

    pipe(pipefd); // create the pipe
    cpid = fork(); // duplicate the current process
    if (cpid == 0) // if I am the child then
    {   while(1)
        {
            while (read(pipefd[0], &buf, 1) > 0) // read while EOF
            {
                write(1, &buf, 1);
            }
            write(1, "\n", 1);
        }
    }
    else if (cpid > 0) // if I am the parent then
    {
    while (1)
        {
            if(ListenSocket() < 0)
                perror("fail to listen");
            if(AcceptSocket() < 0)
                perror("fail to accept");
            bzero(buff, sizeof(buff));
            while(RecvSocket(buff,strlen(buff) >= 0))
            {
                fflush(stdout);
                write(pipefd[1], &buff, strlen(buff)); 
                recvdata[i] = buff[0];
                i++;
            }
            bzero(recvdata, sizeof(recvdata));
            i = 0;
        }
    } 
}