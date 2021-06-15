#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void timeout(int sig)
{
	if(sig==SIGALRM)
		puts("Time out!");
	alarm(2);
}

int main(int argc, char *argv[])
{
	int i;
	struct sigaction act;		// 시그널 발생시 호출될 함수의 등록을 위해서 구조체 변수 선언
	act.sa_handler=timeout;		// 구조체 멤버에 함수 포인터 값을 지정
	sigemptyset(&act.sa_mask);	// 앞서 sigaction구조체를 설명하면서 멤버 sa_mask의 모든 비트를 0으로 초기화
	act.sa_flags=0;				// signal함수를 대신하기 위해서 필요한 멤버가 아니므로 0으로 초기화
	sigaction(SIGALRM, &act, 0);	// 시그널 SIGALRM에 대한 핸들러 지정

	alarm(2);		// 2초뒤 SIGALRM의 발생 예약

	for(i=0;i<3;i++)
	{
		puts("wait...");
		sleep(100);
	}
	return 0;
}
