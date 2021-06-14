#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
void error_handling(char *message);

int main(void)
{
	int fd;
	char buff[]="Let's go!\n";
	
	fd=open("data.txt", O_CREAT|O_WRONLY|O_TRUNC);	// 아무것도 저장되어있지 않은 새로운 파일이 생성되어 쓰기만 가능
	if(fd==-1)
		error_handling("open() error!");
	printf("file descriptor: %d \n",fd);
	
	if(write(fd, buf, sizeof(buf))==-1)	// fd에 저장된 파일 디스크립터에 해당하는 파일에 buf에 저장된 데이터를 전송하고있다.
		error_handling("write() error!");
	close(fd);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n',stderr);
	exit(1);
}