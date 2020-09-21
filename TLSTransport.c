//
// Created by therbl on 9/21/20.
//

#include "TLSTransport.h"

void send(struct msgbuf *buf){
    int key = 443;
    int msq_id = msgget(key, 0);
#ifdef CLIENT_MODE
    #ifdef DEBUG_MODE
        int target_output = open ("client_transport.log", O_CREAT | O_APPEND, 0600);
        close(1);
        dup2(target_output, 1);
#endif //DEBUG_MODE
        if (msq_id == -1) perror("msgq find error");
        if(msgsnd(msq_id, &buf, MSGMAX, 0) < 0) perror("client msg snd error");
#ifdef DEBUG_MODE
        else {
            struct msqid_ds msq_buf;
            msgctl(msq_id, IPC_STAT, &msq_buf);
            printf("New msg send by client PID %ld: %s\n at %s", msq_buf.msg_lspid, buf->mtext, ctime(&msq_buf.msg_stime));
        }
#endif //DEBUG_MODE
#endif //CLIENT_MODE
#ifdef SERVER_MODE
    #ifdef DEBUG_MODE
        int target_output = open ("server_transport.log", O_CREAT | O_APPEND, 0600);
        close(1);
        dup2(target_output, 1);
#endif //DEBUG_MODE
        if(msgsnd(msq_id, &buf, MSGMAX, IPC_NOWAIT) < 0) perror("server msg snd error");
#ifdef DEBUG_MODE
        else {
            struct msqid_ds msq_buf;
            msgctl(msq_id, IPC_STAT, &msq_buf);
            printf("New msg send by server to PID %ld: %s\n at %s", buf->mtype, buf->mtext, ctime(&msq_buf.msg_stime));
        }
#endif //DEBUG_MODE
#endif //SERVER_MODE
}
void receive(struct msgbuf *buf){
    int key = 443;
#ifdef CLIENT_MODE
    int msq_id = msgget(key, 0);
        __pid_t pid = getpid();
#ifdef DEBUG_MODE
        int target_output = open ("client_transport.log", O_CREAT | O_APPEND, 0600);
        close(1);
        dup2(target_output, 1);
#endif //DEBUG_MODE
        if(msgrcv(msq_id, &buf, MSGMAX, pid, IPC_NOWAIT) < 0) perror("client msg rcv error");
#ifdef DEBUG_MODE
        else {
            struct msqid_ds msq_buf;
            msgctl(msq_id, IPC_STAT, &msq_buf);
            printf("Msg recieved by client PID %ld: %s\n at %s", pid, buf->mtext, ctime(&msq_buf.msg_rtime));
        }
#endif //DEBUG_MODE
#endif //CLIENT_MODE
#ifdef SERVER_MODE
    int msq_id = msgget(key, O_CREAT|0660);
#ifdef DEBUG_MODE
        int target_output = open ("server_transport.log", O_CREAT | O_APPEND, 0600);
        close(1);
        dup2(target_output, 1);
#endif //DEBUG_MODE
        if(msgrcv(msq_id, &buf, MSGMAX, 0, 0) < 0) perror("server msg rcv error"); /* if there is no message in the queue, receive will wait for one */
#ifdef DEBUG_MODE
        else {
            struct msqid_ds msq_buf;
            msgctl(msq_id, IPC_STAT, &msq_buf);
            printf("Msg recieved by server from client with PID %ld: %s\n at %s", buf->mtype, buf->mtext, ctime(&msq_buf.msg_rtime));
        }
#endif //DEBUG_MODE
#endif //SERVER_MODE
}
void connect(){
    // что должен делать?
    //по логике вещей, должен отвечать за создание очереди сообщений и подключение к ней. если не очень нужен, можем пока убрать.
}