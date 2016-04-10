#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

char message[] = "Hello there!"; 
char buf[sizeof(message)];

int main()
{
    int sock;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(9100); // или любой другой порт...
    //addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    string ip = "127.0.0.127";
    addr.sin_addr.s_addr = htonl(inet_addr(ip.c_str()));
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(2);
    }

    send(sock, message, sizeof(message), 0);
    recv(sock, buf, sizeof(message) + 9, 0);
    
    //printf(buf);
    cout << buf << "\n";
    
    
    //close(sock);
	//int shutdown (int socket, int how)
	//how: 
	// 0    Stop receiving data for this socket. If further data arrives, reject it.
	// 1    Stop trying to transmit data from this socket. Discard any data waiting to be sent. Stop looking for acknowledgement of data already sent; don’t retransmit it if it is lost.
	// 2    Stop both reception and transmission.
	shutdown (sock, 2);

    return 0;
}
