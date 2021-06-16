/*
	select함수 : 한곳에 여러개의 파일 디스크립터를 모아놓고 동시에 관찰가능
	파일디스크립터 0:입력, 1:출력, 2:에러
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/select.h>
#define BUF_SIZE 30

int main(int argc, char *argv[])
{
	fd_set reads, temps;
	int result, str_len;
	char buf[BUF_SIZE];
	struct timeval timeout;

	FD_ZERO(&reads);		// fd_set형 변수를 초기화
	FD_SET(0, &reads);		// 파일 디스크립터 0의 위치를 1로 설정, 표준 입력에 변화가 있는지 확인

	/*0
	// select함수 호출후에는 구조체 timeval의 멤버 tv_sec와 tv_usec에 저장된 값이 타임아웃이 발생하기까지 남았던 시간으로 바뀐다.
	// 따라서 select를 호출하기 전에 매번 timeval 구조체 변수의 초기화를 반복해야한다.
	timeout.tv_sec=5;
	timeout.tv_usec=5000;
	*/

	while(1)
	{
		temps=reads;	// select 함수 호출이 끝나면 변화가 생긴 파일 디스크립터의 위치를 제외한 나머지 위치의 비트들은 0으로 초기화된다. 따라서 원본의 유지를 위해서는 반드시 복사의 과정을 거쳐야한다.
		// timeval 구조체 변수의 초기화 코드를 반복문안에 삽입하여 select함수가 호출되기전에 매번 새롭게 값이 초기화 되도록 해야한다.
		timeout.tv_sec=5;
		timeout.tv_usec=0;
		result=select(1, &temps, 0,0,&timeout);	// 콘솔로 부터 입력된 데이터가 있다면 0보다 큰수가 반환, 입력된 데이터가 없어서 timeout발생하면 0이 반환 
		if(result==-1)
		{
			puts("select() error!");
			break;
		}
		else if(result==0)
		{
			puts("Time-out!");
		}
		else
		{
			if(FD_ISSET(0,&temps))	/*select함수가 0보다 큰 수를 반환했을때 실행되는 영역*/
			{	
				// 변화를 보인 파일 디스크립터가 표준입력이 맞는지 확인하고, 맞으면 표준 입력으로부터 데이터를 읽어서 콘솔로 데이터를 출력하고있다.
				str_len=read(0,buf,BUF_SIZE);
				buf[str_len]=0;
				printf("message from console: %s", buf);
			}
		}
	}
	return 0;
}
