#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<cstring>
#include<assert.h>
#include<unistd.h>
#include<iostream>
#define MAXLINE 8192
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
        assert(close(clientfd)>=0);
    }
    freeaddrinfo(listp);
    if(!p) return -1;
    else return clientfd;
}

int send_text(char *ip_str,char *port_str,char *text)
{   
    
    int clinetfd = open_clientfd(ip_str,port_str);
    send(clinetfd,text,strlen(text),0);
    close(clinetfd);
    return 1;
}




