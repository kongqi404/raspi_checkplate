#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<cstring>
#include<unistd.h>
#include<pthread.h>
#include<netoperator.h>
#include<cstdio>
#define MAXLINE 8192
#define LISTENQ 1024

//listen port
char client_port_str[MAXLINE]="9918";
char buf[MAXLINE];
int open_clientfd(char *ip_str,char *port_str)
{
    int clientfd;
    addrinfo hints, *listp, *p;
    memset(&hints,0,sizeof(addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV | AI_ADDRCONFIG;
    getaddrinfo(ip_str,port_str,&hints,&listp);
    for(p=listp;p;p=p->ai_next)
    {
        if((clientfd=socket(p->ai_family,p->ai_socktype,p->ai_protocol))<0) continue;
        if(connect(clientfd,p->ai_addr,p->ai_addrlen)!= -1) break;
        close(clientfd);
    }
    freeaddrinfo(listp);
    if(!p) return -1;
    else return clientfd;
}

// send text to client
int send_text(char *ip_str,char *port_str,char *text)
{   
    
    int clinetfd = open_clientfd(ip_str,port_str);
    send(clinetfd,text,strlen(text),0);
    close(clinetfd);
    return 1;
}



int open_listenfd(char *port)
{
    addrinfo hints,*listp,*p;
    int listenfd,optval = 1;
    memset(&hints,0,sizeof(addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG | AI_NUMERICSERV;
    getaddrinfo(NULL,port,&hints,&listp);

    for(p=listp;p;p=p->ai_next)
    {
        if((listenfd=socket(p->ai_family,p->ai_socktype,p->ai_protocol))<0) continue;
        setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,(const void *)&optval,sizeof(int));
        if(bind(listenfd,p->ai_addr,p->ai_addrlen)==0) break;
        close(listenfd);
    }
    freeaddrinfo(listp);
    if(!p) return -1;
    if(listen(listenfd,LISTENQ)<0)
    {
        close(listenfd);
        return -1;
    }
    return listenfd;
}



void *open_listen_service(void *args)
{
    int listenfd,connfd;
    socklen_t clientlen;
    sockaddr_storage clientaddr;
    char client_ip_str[MAXLINE];
    //client_port_str[MAXLINE];
    //char buf[MAXLINE];
    //client_port_str=port_server;
    listenfd = open_listenfd(client_port_str);
    while(1)
    {
        clientlen = sizeof(sockaddr_storage);
        connfd = accept(listenfd,(sockaddr *)&clientaddr,&clientlen);
        getnameinfo((sockaddr *)&clientaddr,clientlen,client_ip_str,MAXLINE,client_port_str,MAXLINE,0);
        fprintf(stdout,"connect to (%s %s)\n",client_ip_str,client_port_str);
        while(recv(connfd,buf,sizeof(buf),0)>0)
        {
            
        }
        close(connfd);
    }
    close(listenfd);
}

void get_buf(char *buffer)
{
    memcpy(buffer,buf,sizeof(buf));
}