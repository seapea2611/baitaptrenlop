#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#define MAX 1024
int main() {
    int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(9000);

    int ret = connect(client, (struct sockaddr *)&addr, sizeof(addr));
    if (ret == -1)
    {
        perror("connect() failed");
        return 1;
    }
    char tenMT[MAX];
    printf("Nhap ten may tinh: ");
    fgets(tenMT, MAX, stdin);
    tenMT[strcspn(tenMT,"\n")] = 0;

    int so_o_dia;
    printf("\nNhap so o dia: ");
    scanf("%d", &so_o_dia);
    getchar();

    char buff[(so_o_dia + 1) * (MAX + 8)];
    char buffer[MAX];
    char diskName[MAX];
    char diskSize[MAX];
    strcat(buff,tenMT);
    // char str[20];
    // sprintf(str, "\nSo o dia: %d", so_o_dia);
    // strcat(buff,str);
    
    int i = 0;
    for(i = 0; i < so_o_dia; i++) {
        printf("\nNhap ten o dia so %d: ", i+1);
        fgets(diskName, MAX, stdin);
        diskName[strcspn(diskName,"\n")] = 0;

        printf("\nNhap kick co o dia so %d: ", i+1);
        fgets(diskSize, MAX, stdin);
        diskSize[strcspn(diskSize,"\n")] = 0;
        
        sprintf(buffer, "\n%s - %sGB", diskName,diskSize);
        strcat(buff,buffer);
    }
    printf("%s", buff);
    if(send(client, buff, strlen(buff),0) == -1) {
        perror("send failed");
        return 1;
    }
    printf("success");
    close(client);
    return 0;
}