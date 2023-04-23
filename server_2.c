#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

#define MAX_CLIENT 10

int main()
{
    // Thiết lập thông tin địa chỉ cho socket
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(9000);

    // Tạo socket
    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server == -1)
    {
        perror("socket() failed");
        exit(EXIT_FAILURE);
    }

    // Gán địa chỉ cho socket
    if (bind(server, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("bind() failed");
        exit(EXIT_FAILURE);
    }

    // Lắng nghe kết nối
    if (listen(server, MAX_CLIENT) == -1)
    {
        perror("listen() failed");
        exit(EXIT_FAILURE);
    }

    // Chấp nhận kết nối từ client
    struct sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(client_addr));
    socklen_t client_addr_len = sizeof(client_addr);
    int client = accept(server, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client == -1)
    {
        perror("accept() failed");
        exit(EXIT_FAILURE);
    }
    printf("Connection from %s %d port [tcp/*] succeeded!\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    // Nhận dữ liệu từ client
   int count = 0;
char buf[1024];
int bytes_received = recv(client, buf, sizeof(buf), 0);
if (bytes_received == -1)
{
    perror("recv() failed");
    exit(EXIT_FAILURE);
}

buf[bytes_received] = '\0'; // kết thúc chuỗi nhận được

char *pos = buf;
while ((pos = strstr(pos, "0123456789")) != NULL)
{
    count++;
    pos++; // di chuyển vị trí tìm thấy chuỗi để tìm tiếp
}

printf("\nSố lần xuất hiện chuỗi '0123456789' là: %d\n", count);
    close(client);
    close(server);
    return 0;
}