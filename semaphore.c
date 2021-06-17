/*
	세마포어 

	세마포어 값은 post함수가 호출되면 1 증가, wait함수가 호출되면 1 감소
	0보다 작아질수는 없어서 0인 상태에서 wait을 하면 블로킹 상태에서
	임계영역은 wait과 post사이, 이 사이에는 다른 쓰레드에 의한 진입이 허용되지 않는다
	
	바이너리 세마포어 : 0과 1을 오가는 세마포어 -> 실행 순서 컨트롤 중심의 동기화 
*/
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

void * read(void * arg);
void * accu(void * arg);
static sem_t sem_one;
static sem_t sem_two;
static int num;

int main(int argc, char argv[])
{
	pthread_t id_t1, id_t2;
	// 세마포어 두개 생성
	sem_init(&sem_one, 0, 0);
	sem_init(&sem_two, 0, 1);

	pthread_create(&id_t1, NULL, read, NULL);
	pthread_create(&id_t2, NULL, accu, NULL);

	pthread_join(id_t1, NULL);
	pthread_join(id_t2, NULL);

	sem_destroy(&sem_one);
	sem_destroy(&sem_two);
	return 0;
}

void * read(void * arg)
{
	int i;
	for(i=0;i<5;i++)
	{
		fputs("Input num: ", stdout);

		sem_wait(&sem_two);	// accu함수를 호출하는 쓰레드가 값을 가져가지도 않았는데, read함수를 호출하는 쓰레드가 값을 다시 가져다 놓는 상황을 막기 위해
		scanf("%d",&num);
		sem_post(&sem_one);	// read함수를 호출하는 쓰레드가 새로운 값을 가져다 놓기도 전에 accu함수가 값을 가져가 버리는 상황을 막기 위해
	}
	return NULL;
}

void * accu(void * arg)
{
	int sum=0,i;
	for(i=0;i<5;i++)
	{
		sem_wait(&sem_one);	// read함수를 호출하는 쓰레드가 새로운 값을 가져다 놓기도 전에 accu함수가 값을 가져가 버리는 상황을 막기 위해
		sum+=num;
		sem_post(&sem_two);	// accu함수를 호출하는 쓰레드가 값을 가져가지도 않았는데, read함수를 호출하는 쓰레드가 값을 다시 가져다 놓는 상황을 막기 위해
	}
	printf("Result: %d \n", sum);
	return NULL;
}
