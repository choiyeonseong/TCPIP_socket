#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define BUF_SIZE 100
void error_handling(char *message);
void read_childproc(int sig);

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	int fds[2];

	pid_t pid;
	struct sigaction act;
	socklen_t adr_sz;
	int str_len, state;
	char buf[BUF_SIZE];
	if(argc!=2)
	{
		printf("Usage: %s <port>\n", argv[0]);
		exit(1);
	}

	act.sa_handler=read_childproc;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;
	state=sigaction(SIGCHLD, &act, 0);

	serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port=htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
		error_handling("bind() error");
	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");

	pipe(fds);	// 파이프 생성
	pid=fork();	// 파일의 데이터 저장을 담당을 프로세스를 생성
	if(pid==0)	/*자식 프로세스에 의해 실행*/
	{
		FILE *fp=fopen("echomsg.txt","wt");
		char msgbuf[BUF_SIZE];
		int i, len;

		for(i=0;i<10;i++)	// 서버가 종료되지 않고 클라이언트에게 계속
		
		해서 서비스를 제공하기 때문에 어느정도 채워지면 파일을 닫음
		{
			// 파이프의 출구인 fds[0]으로 전달되는 데이터를 읽어서 파일에 저장
			len=read(fds[0], msgbuf, BUF_SIZE);	
			fwrite((void*)msgbuf, 1, len, fp);
		}
		fclose(fp);
		return 0;
	}

	while(1)
	{
		adr_sz=sizeof(clnt_adr);
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);
		if(clnt_sock==-1)
			continue;
		else
			puts("new client connected...");

		pid=fork();
		if(pid==0)
		{
			close(serv_sock);
			while((str_len=read(clnt_sock, buf, BUF_SIZE))!=0)
			{
				write(clnt_sock, buf, str_len);
				write(fds[1], buf, str_len);	// 73행에서 생성되는 모든 자식 프로세스는 47행에서 생성한 파이프의 파일 디스크립터를 복사, 때문에 파이프의 입구인 fds[1]을 통해 문자열 정보를 전달할수 있다.
			}
			close(clnt_sock);
			puts("client disconnected...");
			return 0;
		}
		else
			close(clnt_sock);
	}
	close(serv_sock);
	return 0;
}

void read_childproc(int sig)
{
	pid_t pid;
	int status;
	pid=waitpid(-1, &status, WNOHANG);
	printf("removed proc id: %d \n", pid);
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
