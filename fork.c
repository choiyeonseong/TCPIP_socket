#include<stdio.h>
#include<unistd.h>

int gval=10;
int main(int argc, char *argv[])
{
	pid_t pid;
	int lval=20;
	gval++, lval+=5;

	// 자식 프로세스를 생성하고 있다.
	// 따라서 부모 프로세스의 pid에는 자식 프로세스의 ID가 저장되며,
	// 자식 프로세서의 pid에는 0이 저장된다.
	pid=fork();
	if(pid==0)	// if Child Process
		gval+=2, lval+=2;
	else		// if Parent Process
		gval-=2, lval-=2;

	if(pid==0)	// if Child Process
		printf("Child Proc: [%d, %d] \n", gval, lval);
	else		// if Parent Process
		printf("Parent Proc: [%d, %d] \n", gval, lval);
	return 0;
}
