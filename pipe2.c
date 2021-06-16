#include<stdio.h>
#include<unistd.h>
#define BUF_SIZE 30

int main(int argc, char *argv[])
{
	int fds[2];
	char str1[]="Who are you?";
	char str2[]="Thank you for your message";
	char buf[BUF_SIZE];
	pid_t pid;

	pipe(fds);
	pid=fork();
	if(pid==0)	/*자식 프로세스 실행 영역*/
	{
		write(fds[1], str1, sizeof(str1));	// 데이터 전송
		sleep(2);
		read(fds[0], buf, BUF_SIZE);		// 데이터 수신
		printf("Child proc output:%s \n", buf);
	}
	else	/*부모 프로세스 실행 영역*/
	{
		read(fds[0], buf, BUF_SIZE);	// 데이터 수신, 자식 프로세스가 전송하는 데이터를 수신하기 위함
		printf("Parent proc output: %s \n", buf);
		write(fds[1], str2, sizeof(str2));	// 데이터 전송, 자식프로세스에게 수신됨
		sleep(3);
	}
	return 0;
}
