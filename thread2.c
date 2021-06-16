#include<stdio.h>
#include<stdio.h>
#include<string.h>
#include<pthread.h>
void* thread_main(void *arg);

int main(int argc, char *argv[])
{
	pthread_t t_id;
	int thread_param=5;
	void * thr_ret;

	if(pthread_create(&t_id, NULL, thread_main, (void*)&thread_param)!=0)
	{
		puts("pthread_create() error");
		return -1;
	};

	// main함수에서 13행에소 생성한 쓰레드를 대상으로 pthread_join함수를 호출하고 있다. 때문에 main함수는 변수 t_id에 저장된 ID의 쓰레드가 종료될때까지 대기하게 된다.
	if(pthread_join(t_id, &thr_ret)!=0)
	{
		puts("pthread_join() error");
		return -1;
	}

	printf("Thread return message:%s \n",(char*)thr_ret);
	free(thr_ret);
	return 0;
}

void* thread_main(void *arg)
{
	int i;
	int cnt=*((int*)arg);
	char * msg=(char*)malloc(sizeof(char)*50);
	strcpy(msg, "Hello, I'am thread~ \n");
	
	for(i=0;i<cnt;i++)
	{
		sleep(1); puts("running thread");
	}
	return (void*)msg;	// 반환되는 값은 pthread_join의 두번째 인자로 전달된 변수 thr_ret에 저장된다. 그리고 이 반환값은 thread_main함수 내에서 동적으로 할당된 메모리 공간의 주소값이라는 사실도 관심을 두기를 바란다.
}
