#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char *argv[])
{
	int status;
	pid_t pid=fork();	// 자식 프로세스 생성

	if(pid==0)
	{
		return 3;	// 자식 프로세스 실행 종료
	}
	else
	{
		printf("Child PID: %d \n", pid);
		pid=fork();	// 자식 프로세스 생성
		if(pid==0)
		{
			exit(7);	// 자식프로세스 종료
		}
		else
		{
			printf("Child PID: %d \n", pid);
			wait(&status);	// 종료된 프로세스 관련 정보는 status에 담기게 되고, 해당 정보의 프로세스는 완전히 소멸
			
			// WIFEXITED함수를 통해 자식 프로세스의 정상종료 여부를 확인
			// 정상 종료인 경우 WEXITSTATUS함수를 호출해 자식 프로세스가 전달한 값을 출력
			if(WIFEXITED(status))	
				printf("Child send one: %d \n", WEXITSTATUS(status));

			// 자식 프로세스가 2개이므로 wait함수와 매크로 함수 호출 진행
			wait(&status);
			if(WIFEXITED(status))
				printf("Child send two: %d \n", WEXITSTATUS(status));
			sleep(30);	// 프로세스 종료를 멈추기 위해 삽입
		}
	}
	return 0;
}
