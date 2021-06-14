/*
	Iterative 클라이언트
	
	에코 서버, 클라이언트가 문자열 단위로 에코됨
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int sock;
	char message[BUF_SIZE];
	int str_len;
	struct sockaddr_in serv_adr;

	if(argc!=3){
		printf("Usage :%s <IP> <port>\n", argv[0]);
		exit(1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
		error_handling("socket() error");

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_adr.sin_port = htons(atoi(argv[2]));

	// 연결 요청 정보가 서버의 대기 큐에 등록이 되면, connect 함수는 정상적으로 호출을 완료
	// 연결되었다는 문자열 정보가 출력되더라도 서버에서 accept 함수를 호출하지 않은 상황이라면 실제 서비스가 이뤄지지않음
	if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
		error_handling("connect() error!");
	else
		puts("Connected..........");

	while(1)
	{
		fputs("Input message(Q to quit): ",stdout);
		fgets(message, BUF_SIZE, stdin);

		if(!strcmp(message, "q\n")||!strcmp(message, "Q\n"))
			break;

		write(sock, message, strlen(message));
		str_len = read(sock, message, BUF_SIZE-1);
		message[str_len]=0;
		printf("Message from server: %s", message);
	}
	// 상대 소켓으로 EOF가 전송(EOF : 연결의 끝)
	close(sock);
	return 0;
}

void error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n',stderr);
	exit(1);
}
