#include<stdio.h>
#include<stdio.h>
#include<pthread.h>
void* thread_main(void *arg);

int main(int argc, char *argv[])
{
	pthread_t t_id;
	int thread_param=5;

	// thread_main 함수의 호출을 시작으로 별도의 실행흐름을 구성하는 쓰레드의 생성을 요청하고있다. 
	// 더불어 thread_main함수 호출시 인자로 변수 thread_param주소값을 전달하고있다.
	if(pthread_create(&t_id, NULL, thread_main, (void*)&thread_param)!=0)
	{
		puts("pthread_create() error");
		return -1;
	};
	// sleep함수를 통해서 main 함수의 실행을 10초간 중지 -> 프로세스의 종료시기를 늦추기 위해
	// 쓰레드의 실행을 보장하기 위해 삽입
	sleep(10); puts("end of main");
	return 0;
}

// 매개변수 arg로 전달되는 것은 pthread_create함수의 네번째 전달인자
void* thread_main(void *arg)
{
	int i;
	int cnt=*((int*)arg);
	for(i=0;i<cnt;i++)
	{
		sleep(1); puts("running thread");
	}
	return NULL;
}
