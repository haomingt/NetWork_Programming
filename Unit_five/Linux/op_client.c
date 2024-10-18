#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
int main(int argc, char *argv[])
{
    int sock;
    char message[BUF_SIZE];
    int str_len;
    struct sockaddr_in serv_adr;

    if (argc != 3)
    {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        error_handling("socket() error");
    }

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
    {
        error_handling("connect() error");
    }
    else
    {
        puts("Connected........");
    }

    while (1)
    {
        int times;
        fputs("请输入运算数字的个数(0 to quit): ", stdout);
        
        scanf("%d", &times);
        if (times == 0)
            break;
        char times_str[BUF_SIZE];
        sprintf(times_str, "%d", times);
        if(write(sock, times_str, BUF_SIZE - 1) == -1) {
            error_handling("write() error");
        }
        for (int i = 0; i < times;i ++) {
            int num;
            char num_str[BUF_SIZE];
            printf("请输入第%d个数字", i + 1);
            scanf("%d", &num);
            sprintf(num_str, "%d", num);
            if (write(sock, num_str, BUF_SIZE - 1) == -1)
            {
                error_handling("write() error");
            }
        }
        printf("请输入运算符：");
        char op;
        scanf("%c", &op);
        if (write(sock, op, BUF_SIZE - 1) == -1)
        {
            error_handling("write() error");
        }
        char rev[BUF_SIZE];
        if(read(sock,&rev,BUF_SIZE - 1) == -1) {
            error_handling("read() error");
        }
        printf("最后运算的结果为：%s", rev);
    }
    close(sock);
    return 0;
}