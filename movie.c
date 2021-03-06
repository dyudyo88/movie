#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movie.h"

//structure definition 구조체 정의  
typedef struct movInfo //struct의 다른 이름을 "movInfo"로 하겠다. 
{
	char name[100]; 	//영화 이름 
	float score;		//영화 평점  
	int runTime;		//영화 상영시간  
	char madeIn[10];	//영화 제작 국가  
}movInfo_t; 			//구조체 변수선언  


int mvPtr; //포인터로 사용 할 변수 선언하기  


void* mv_genMvInfo(char* name, float score, int runTime, char* country)
{
	movInfo_t* mvPtr;//구조체 변수 movInfo_t의 포인터mvPtr를 선언함   
	//allocate memory and set the member variables
	mvPtr = (movInfo_t*)malloc(sizeof(movInfo_t)); //동적메모리 할당
	strcpy(mvPtr->name, name); 	//문자열 복사 strcpy(대상, 원본)->파일에서 가져온 name정보를 포인터로 name에 저장함 
	strcpy(mvPtr->madeIn, country);	//문자열 복사 strcpy(대상, 원본)->파일에서 가져온 country정보를 포인터로madeIn에 저장함  
	//파일에서 가져온 score 정보랑 runTime 정보를 가져와서 저장해야 됨.
	mvPtr->score = score; //파일에서 가져온 score 정보를 score에 저장  
	mvPtr->runTime = runTime; //파일에서 갖온 runTime 정보를 runTime 에 저장  
	
	return (void*)mvPtr; //(void*)mvPtr반환 해주기  
}

void printMv(void* obj)
{
	movInfo_t* mvPtr = (movInfo_t*)obj; //mvPtr에 obj 대입 
	
	if (mvPtr == NULL) //mvPtr이 NULL일 때 출력  
	{
		printf("[ERROR] failed to print the movie Info! (object is NULL)\n"); 
		return 0; 
	}
	
	printf("Name : %s (%s)\n", mvPtr->name, mvPtr->madeIn); //영화 이름, 제작국가 출력  
	printf("running time : %i, score : %f\n", mvPtr->runTime, mvPtr->score); //영화 상영시간, 평점 출력  
	printf("------------------------------------------------------\n");
	
	return 0; // 노드는 끝나지 않음 
}

int mv_printAll(void* obj, void* arg)
{
	movInfo_t* mvPtr = (movInfo_t*)obj; //mvPtr에 obj 대입 
	
	if (mvPtr == NULL) //mvPtr이 NULL일 때 출력  
	{
		printf("[ERROR] failed to print the movie Info! (object is NULL)\n");
		return 0;  
	}
	
	printf("Name : %s (%s)\n", mvPtr->name, mvPtr->madeIn); //영화 이름, 제작국가 출력  
	printf("running time : %i, score : %f\n", mvPtr->runTime, mvPtr->score); //영화 상영시간, 평점 출력  
	printf("------------------------------------------------------\n");
	return 1; //return 1 : 노드는 끝남. 
}

 
int mv_printScore(void* obj, void* arg)
{
	movInfo_t* mvPtr = (movInfo_t*)obj; //mvPtr에 obj 대입  
	
	if (mvPtr == NULL) //mvPtr이 NULL일 때 출력  
	{
		printf("[ERROR] failed to print the movie Info! (object is NULL)\n");
		return 0; //return 0 : 노드는 끝나지 않음
	}
	
	if( (mvPtr->score) > *(float*)(arg) )//입력한 것 보다 높은 평점을 가진 영화를 출력해야 됨
										//void*형을 float*형으로 변환하기 + mvPtr->score과 비교하기    
	{
		printf("Name : %s (%s)\n", mvPtr->name, mvPtr->madeIn); //영화 이름, 제작국가 출력  
		printf("running time : %i, score : %f\n", mvPtr->runTime, mvPtr->score); //영화 상영시간, 평점 출력  
		printf("------------------------------------------------------\n");
		return 1; //return 1 : 노드는 끝남. 
	}
	
	return 0;  //return 0 : 노드는 끝나지 않음
				// return의 값은 출력할 때만 증가시키는 것 이니까 출력하지 않으면 0을 리턴 
				// 전체 출력이니까 출력 할 때마다 리턴해서 1을 증가 시킴  
}

int mv_printRunTime(void* obj, void* arg)
{
	movInfo_t* mvPtr = (movInfo_t*)obj; //mvPtr에 obj 대입 
	
	if (mvPtr == NULL) //mvPtr이 NULL일 때 출력  
	{
		printf("[ERROR] failed to print the movie Info! (object is NULL)\n");
		return 0;  //return 0 : 노드는 끝나지 않음
	}
	
	if( (mvPtr->runTime) > *(int*)(arg) ) //void*형을 int*형으로 변환하기 + mvPtr->runTime과 비교하기  
	{
		printf("Name : %s (%s)\n", mvPtr->name, mvPtr->madeIn); //영화 이름, 제작국가 출력  
		printf("running time : %i, score : %f\n", mvPtr->runTime, mvPtr->score); //영화 상영시간, 평점 출력  
		printf("------------------------------------------------------\n");
		
		return 1; //return 1 : 노드는 끝남.  
	}
	
	return 0;  //return 0 : 노드는 끝나지 않음
				// return의 값은 출력할 때만 증가시키는 것 이니까 출력하지 않으면 0을 리턴 
				// 전체 출력이니까 출력 할 때마다 리턴해서 1을 증가 시킴
}

int mv_printCountry(void* obj, void* arg)
{
	movInfo_t* mvPtr = (movInfo_t*)obj; //mvPtr에 obj 대입 
	if (mvPtr == NULL) //mvPtr이 NULL일 때 출력  
	{
		printf("[ERROR] failed to print the movie Info! (object is NULL)\n");
		return 0;  	//return 0 : 노드는 끝나지 않음
	}
	
	if( strcmp(mvPtr->madeIn , arg) == 0)   //mvPtr->madeIn 과 arg(Country) 문자열을 비교해서 같은지 비교하는 것,문자열이 같으면 0이 반환된다. 
	{
		printf("Name : %s (%s)\n", mvPtr->name, mvPtr->madeIn); 				 //영화 이름, 제작국가 출력  
		printf("running time : %i, score : %f\n", mvPtr->runTime, mvPtr->score); //영화 상영시간, 평점 출력  
		printf("------------------------------------------------------\n"); 
		return 1; //return 1 : 노드는 끝남.  
	}
	
	return 0;   //return 0 : 노드는 끝나지 않음
				// return의 값은 출력할 때만 증가시키는 것 이니까 출력하지 않으면 0을 리턴
				// 전체 출력이니까 출력 할 때마다 리턴해서 1을 증가 시킴  
}




