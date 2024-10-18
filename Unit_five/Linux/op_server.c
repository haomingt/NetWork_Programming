#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 200
void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
int strtoint(char str[BUF_SIZE], int len)
{
    int ans = 0;
    for (int i = 0; i < 0; i++)
    {
        ans = ans * 10 + (str[i] - '0');
    }
    return ans;
}
int calculate(int nums[BUF_SIZE], int len, char op)
{
    if (len == 0)
    {
        error_handling("服务器运算数组为空");
    }
    int ans = nums[0];
    if (op == '+')
    {
        for (int i = 1; i < len; i++)
        {
            ans += nums[i];
        }
    }
    else if (op == '-')
    {
        for (int i = 1; i < len; i++)
        {
            ans -= nums[i];
        }
    }
    else if (op == '/')
    {
        for (int i = 1; i < len; i++)
        {
            ans /= nums[i];
        }
    }
    else if (op == '*')
    {
        for (int i = 1; i < len; i++)
        {
            ans *= nums[i];
        }
    }
    else
    {
        error_handling("服务器运算符出错");
    }
    return ans;
}
int main(int argc, char *argv[])
{
    // 创建套接字
    int serv_sock = sock(AF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
    {
        error_handling("socket() error");
    }
    // bind,配置套接字
    struct sockaddr_in serv_adr;
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = PF_INET;
    serv_adr.sin_port = htons(argv[1]);
    serv_adr.sin_addr.s_addr = INADDR_ANY;
    if (bind(serv_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
    {
        error_handling("bind() error");
    }
    // listen
    if (listen(serv_sock, 5) == -1)
    {
        error_handling("listen() error");
    }
    // accept()
    for (int i = 0; i < 5; i++)
    {
        struct sockaddr_in client_adr;
        int client_sock = accept(serv_sock, (struct sockaddr *)&client_adr, sizeof(client_adr));
        if (client_sock == -1)
        {
            error_handling("accept() error");
        }
        printf("connected client%d", i + 1);
        int nums[BUF_SIZE];
        int num_len = 0; // 数字的个数
        char times[BUF_SIZE];
        int strlen = 0; // 每次read()调用读取字符的个数
        // 读取数字的个数
        while (strlen = read(client_sock, &times, BUF_SIZE - 1) != 0)
        {
            times[strlen] = 0;
            // 读取数字
            char temp[BUF_SIZE];
            for (int i = strtoint(times, strlen); i > 0; i--)
            {
                if (strlen = read(client_sock, &temp, BUF_SIZE) == -1)
                {
                    error_handling("read() error");
                }
                temp[strlen] = 0;
                nums[num_len++] = strtoint(temp, strlen);
            }
            // 读取运算符
            if (read(client_sock, &temp, 1) == -1)
            {
                error_handling("read() error");
            }
            char str[BUF_SIZE];
            sprintf(str, "%d", calculate(nums, num_len, temp[0]));
            if (write(client_sock, str, sizeof(str)) == -1)
            {
                error_handling("write() error");
            }
        }
        close(client_sock);
    }
    return 0;
}