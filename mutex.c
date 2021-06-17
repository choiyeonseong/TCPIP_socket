/*
	뮤텍스 mutual exclusion
	쓰레드의 동시접근을 허용하지 않는다
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#define NUM_THREAD 100
void * thread_inc(void * arg);
void * thread_des(void * arg);

long long num=0;
pthread_mutex_t mutex;	// 뮤텍스의 참조 값 저장을 위한 변수가 선언되었다. 뮤텍스의 접근이 thread_inc, thread_des 두개의 함수 내에서 이뤄지기 때문에 전역변수로 선언

int main(int argc, char * argv[])
{
	pthread_t thread_id[NUM_THREAD];
	int i;

	pthread_mutex_init(&mutex, NULL);

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
	pthread_mutex_destroy(&mutex);	// 뮤텍스 소멸
	return 0;
}

void * thread_inc(void * arg)
{
	int i;
	pthread_mutex_lock(&mutex);	// 실제 임계영역은 40행 하나지만 여기서는 반복문 까지 임계영역으로 포함해서 lock, unlock함수를 호출하고 있다.
	for(i=0;i<50000000;i++)
		num+=1;
	pthread_mutex_unlock(&mutex);
	return NULL;
}

void * thread_des(void * arg)
{
	int i;
	for(i=0;i<50000000;i++)
	{
		pthread_mutex_lock(&mutex);	// 임계영역에 해당하는 51행만 뮤텍스의 lock, unlock 함수로 감싸고 있다.
		num-=1;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}
