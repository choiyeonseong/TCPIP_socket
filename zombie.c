#include<stdio.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
	pid_t pid=fork();

	if(pid==0)
	{
		puts("Hi, I am a child process");
	}
	else
	{
		// 자식 프로세스의 ID를 출력하고있다.
		// 이 값을 통해서 자식 프로세스의 상태를 확인할수 있다.
		printf("Child Process ID: %d \n", pid);	
		// 부모 프로세스가 종료되면 좀비상태에 있던 자식 프로세스도 함께 소멸되기 때문에 
		// 좀비의 확인을 위해서는 부모 프로세스의 종료를 지연시킬 필요가 있다.
		sleep(30);	
	}

	if(pid==0)
		puts("End child process");
	else
		puts("End parent process");
	return 0;
}
