#include<stdio.h>
#include<unistd.h>
#define BUF_SIZE 30

int main(int argc, char *argv[])
{
	int fds[2];
	char str[]="Who are you?";
	char buf[BUF_SIZE];
	pid_t pid;

	pipe(fds);	// pipe 함수호출을 통해서 파이프를 생성하고 있다. 이로 인해서 배열 fds에는 입출력을 위한 파일 디스크립터가 각각 저장된다.
	pid=fork();	// 자식 프로세스는 pipe함수 호출을 통해서 얻게된 두개의 파일 디스크립터를 함께 소유, 부모와 자식 프로세스가 동시에 입출력 파일 디스크립터를 모두 소유
	if(pid==0)
	{
		write(fds[1], str, sizeof(str));	// 자식프로세스는 write를 통해서 파이프로 문자열을 전달
	}
	else
	{
		read(fds[0], buf, BUF_SIZE);		// 부모 프로세스는 read를 통해 파이프로 문자열을 수신
		puts(buf);
	}
	return 0;
}
