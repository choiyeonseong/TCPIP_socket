/*
	결과 num은 0이 아님
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#define NUM_THREAD 100

void * thread_inc(void * arg);
void * thread_des(void * arg);

long long num=0;

int main(int argc, char * argv[])
{
	pthread_t thread_id[NUM_THREAD];
	int i;

	printf("sizeof long long: %d \n", sizeof(long long));
	for(i=0;i<NUM_THREAD;i++)
	{
		if(i%2)
			pthread_create(&(thread_id[i]), NULL, thread_inc, NULL);
		else
			pthread_create(&(thread_id[i]), NULL, thread_des, NULL);
	}
	
	for(i=0;i<NUM_THREAD;i++)
		pthread_join(thread_id[i], NULL);

	printf("result: %lld \n", num);
	return 0;
}

void * thread_inc(void * arg)
{
	int i;
	for(i=0;i<50000000;i++)
		num+=1;
	return NULL;
}

void * thread_des(void * arg)
{
	int i;
	for(i=0;i<50000000;i++)
		num-=1;
	return NULL;
}

/*
쓰레드 : 프로세스 관점에서 별도의 실행 흐름을 구성하는 단위 - 하나의 프로세스 내에서 둘 이상의 실행흐름을 형성하기 위한 도구
프로세스 : 운영체제 관점에서 별도의 실행 흐름을 구성하는 단위 - 하나의 운영체제 안에서 둘이상의 실행흐름을 형성하기 위한 도구

*/