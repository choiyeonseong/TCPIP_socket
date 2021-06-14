/*
	클라이언트 프로그램
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
void error_handling(char *message);

int main(int argc, char* argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	char message[30];
	int str_len;

	if(argc!=3)
	{
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	// TCP 소켓 생성
	sock=socket(PF_INET, SOCK_STREAM,0);	
	if(sock==-1)
		error_handling("socket() error");

	// 구조체 변수 serv_addr에 IP와 PORT정보를 초기화 하고있다.
	// 초기화되는 값은 연결을 목적으로 하는 서버 소켓의 IP와 PORT정보이다.
	memset(&serv_addr,0,sizeof(serv_addr));	
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));

	// connect 함수호출을 통해서 서버로 연결요청을 하고있다.
	if(connect(sock, (struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
		error_handling("connect() error!");

	// 연결요청을 성공한 후에 서버로부터 정송되는 데이터를 수신하고 있다.
	str_len=read(sock, message, sizeof(message)-1);
	if(str_len==-1)
		error_handling("read() error!");
	printf("Message from server : %s \n",message);
	
	// 데이터 수신이후에 close 함수호출을 통해서 소켓을 닫고있다.
	// 따라서 서버와의 연결은 종료가 된다.
	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n',stderr);
	exit(1);
}
