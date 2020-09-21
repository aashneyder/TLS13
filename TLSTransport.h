//
// Created by therbl on 9/21/20.
//

#ifndef TLS13_TLSTRANSPORT_H
#define TLS13_TLSTRANSPORT_H

#include <stdio.h> //standard io
#include <string.h> //string operations
#include <unistd.h> //mobility
#include <stdlib.h> //std library
#include <sys/ipc.h> //inter-process communication
#include <sys/types.h> //types; mobility
#include <sys/msg.h> //MQ
#include <time.h> //time
#include <sys/stat.h> //?
#include <fcntl.h> //system calls ( e.g. open() )

#define MSGMAX 1024

struct msgbuf {
    long mtype;
    char mtext[MSGMAX];
};

void send(struct msgbuf *buf);
void receive(struct msgbuf *buf);
void connect();


#endif //TLS13_TLSTRANSPORT_H
