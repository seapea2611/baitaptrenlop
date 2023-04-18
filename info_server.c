#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listener == -1)
    {
        perror("socket() failed");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(9000);

    if (bind(listener, (struct sockaddr *)&addr, sizeof(addr)))
    {
        perror("bind() failed");
        return 1;        
    }

    if (listen(listener, 5))
    {
        perror("listen() failed");
        return 1;
    }

    printf("Khoi tao thanh cong!!!\n");

    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);

    int client = accept(listener, 
        (struct sockaddr *)&client_addr, 
        &client_addr_len);

    printf("Accepted socket %d from IP: %s:%d\n", 
        client,
        inet_ntoa(client_addr.sin_addr),
        ntohs(client_addr.sin_port));

    char buff[10000];
    int ret;
    while(1) {
    ret = recv(client, buff, sizeof(buff), 0);
        buff[ret] = '\0';
        if (ret <= 0) {
            return 0;
        }
        printf("%s", buff);
}
        // int pos = 0;
        // char name[64];
        // strcpy(name ,buff);
        // pos = strlen(name) + 1;
        // int num = (ret - pos) / 3;

        // for (int i = 0; i < count; i++)
        // {
        //     /* code */
        //     char drive_letter = buff[pos];

        // }
        
    close(client);
    close(listener);
    return 0;
    
}