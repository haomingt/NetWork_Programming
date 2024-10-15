#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    char *addr1 = "1.2.3.4";
    char *addr2 = "1.2.3.256";
    // inet_addr函数可以把IP地址转成32位整数型，还可以检测无效的IP地址
    // 且输出结果转换为网络字节序
    unsigned long conv_addr = inet_addr(addr1);
    if (conv_addr == INADDR_NONE)
    {
        printf("Error occured! \n");
    }
    else
    {
        printf("NetWork orderf integer addr: %#lx \n", conv_addr);
    }
    conv_addr = inet_addr(addr2);
    if (conv_addr == INADDR_NONE)
    {
        printf("Error occured! \n");
    }
    else
    {
        printf("NetWork orderf integer addr: %#lx \n", conv_addr);
    }
    return 0;
}