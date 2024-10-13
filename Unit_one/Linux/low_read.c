#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#define BUF_SIZE 100
void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
int main(void) {
    int fd = open("data.txt", O_RDONLY);
    if(fd == -1) {
        error_handling("open() error");
    }
    printf("file descriptor: %d \n", fd);
    char BUF[BUF_SIZE];
    if(read(fd,BUF,sizeof(BUF)) == -1) {
        error_handling("read() error");
    }
    printf("file data: %s", BUF);
    close(fd);
    return 0;
}