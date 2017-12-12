#define MAXPENDING 5

#ifndef __SOCKETCOMMUNICATE_H__
#define __SOCKETCOMMUNICATE_H__

int OpenSocket(int port);
int BindSocket(void);
int ListenSocket(void);
int AcceptSocket(void);
int RecvSocket(unsigned char* buffer, int buffersize);
int CloseSocket(void);

#endif //__SOCKETCOMMUNICATE_H__