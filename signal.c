#include<stdio.h>
#include<unistd.h>
#include<signal.h>

// 시그널 핸들러
void timeout(int sig)
{
	if(sig==SIGALRM)
		puts("Time out!");
	alarm(2);	// 2초간격으로 시그널을 반복 발생
}
void keycontrol(int sig)
{
	if(sig==SIGINT)
		puts("CTRL+C pressed");
}

int main(int argc, char *argv[])
{
	int i;
	// 시그널 핸들러 등록
	signal(SIGALRM, timeout);
	signal(SIGINT, keycontrol);
	alarm(2);	// SIGALRM발생을 2초뒤로 예약

	for(i=0;i<3;i++)
	{
		puts("wait...");
		sleep(100);	//시그널 발생과 핸들러의 실행을 확인하기 위해 100초간 총 3회의 대기시간을 갖도록 반복문내에서 sleep함수 호출
	}
	return 0;
}
