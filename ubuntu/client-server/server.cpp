#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int tryConnect(string ip);

int main() {
	/*int a = 127, b = 0, c = 0, d = 0;
	for (a = 127; a < 256; a++) {
		for (b = 0; b < 256; b++) {
			for (c = 0; c < 256; c++) {
				for (d = 1; d < 256; d++) {
					string ip = to_string(a) + "." + to_string(b) + "." + to_string(c) + "." + to_string(d);
					try {
						tryConnect(ip);
					} catch(exception e) {
						cout << ip << "fail\n";
					}
				}
			}
		}
	}*/
	tryConnect("127.0.0.127");
	return 0;
}

int tryConnect(string ip)
{
	cout << "got ip " << ip << "\n";
    int sock, listener;
    struct sockaddr_in addr;
    char buf[1024];
    int bytes_read;

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }
    
    addr.sin_family = AF_INET;
    //addr.sin_port = htons(3425);
    addr.sin_port = htons(9100);
    //addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_addr.s_addr = htonl(inet_addr(ip.c_str()));
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        //exit(2);
        return 2;
    }

    listen(listener, 1);
    cout << "start listen " << ip << "\n";
    while(1)
    {
        sock = accept(listener, 0, 0);
        if(sock < 0)
        {
            perror("accept");
            exit(3);
        }

        while(1)
        {
            bytes_read = recv(sock, buf, 1024, 0);
            if(bytes_read <= 0) break;
            cout << buf << "\n";
            string msg = string(buf) + " - AGA - ";
            cout << "will send " << msg << "\n";
            send(sock, /*buf*/msg.c_str(), bytes_read + 9, 0);
            
        }
    
        //close(sock);
        //int shutdown (int socket, int how)
        //how: 
        // 0    Stop receiving data for this socket. If further data arrives, reject it.
		// 1    Stop trying to transmit data from this socket. Discard any data waiting to be sent. Stop looking for acknowledgement of data already sent; don’t retransmit it if it is lost.
		// 2    Stop both reception and transmission.
        shutdown (sock, 2);
    }
    
    return 0;
}
