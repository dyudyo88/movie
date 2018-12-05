#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movie.h"

//structure definition 구조체 정의  
typedef struct movInfo //struct의 다른 이름을 "movInfo"로 하겠다. 
 {
	char name[100]; //영화 이름 
	float score;	//영화 평점  
	int runTime;	//영화 상영시간  
	char madeIn[10];	//영화 제작 국가  
}  movInfo_t; //구조체 변수선언  

int mvPtr; 

void* mv_genMvInfo(char* name, float score, int runTime, char* country)
{
	movInfo_t* mvPtr; //구조체 변수 movInfo_t의 포인터mvPtr를 선언함   
	//allocate memory and set the member variables
	mvPtr = (movInfo_t*)malloc(sizeof(movInfo_t)); //동적메모리 할당
	strcpy(mvPtr->name, name); //문자열 복사 strcpy(대상, 원본)->파일에서 가져온 name정보를 포인터로 name에 저장함 
	strcpy(mvPtr->madeIn, country);//문자열 복사 strcpy(대상, 원본)->파일에서 가져온 country정보를 포인터로madeIn에 저장함  
	//파일에서 가져온 score 정보랑 runTime 정보를 가져와서 저장해야됨.
	mvPtr->score = score;
	mvPtr->runTime = runTime;
	
	return (void*)mvPtr; 
}

void printMv(void* obj)
{
	movInfo_t* mvPtr = (movInfo_t*)obj;
	if (mvPtr == NULL)
	{
		printf("[ERROR] failed to print the movie Info! (object is NULL)\n");
	}
	
	printf("Name : %s (%s)\n", mvPtr->name, mvPtr->madeIn);
	printf("running time : %i, score : %f\n", mvPtr->runTime, mvPtr->score);
	
	return;
}

int mv_printAll(void* obj, void* arg)
{
	movInfo_t* mvPtr = (movInfo_t*)obj; //mvPtr에 obj 대입 
	if (mvPtr == NULL)
	{
		printf("[ERROR] failed to print the movie Info! (object is NULL)\n");
	}
	
	printf("Name : %s (%s)\n", mvPtr->name, mvPtr->madeIn);
	printf("running time : %i, score : %f\n", mvPtr->runTime, mvPtr->score);
	
	return;
}

 
int mv_printScore(void* obj, void* arg)
{
	movInfo_t* mvPtr = (movInfo_t*)obj; //mvPtr에 obj 대입  
	if (mvPtr == NULL)
	{
		printf("[ERROR] failed to print the movie Info! (object is NULL)\n");
	}
	
	if( (mvPtr->score) > *(arg) )//입력한 것 보다 높은 평점을 가진 영화를 출력해야 됨  
	{
		printf("Name : %s (%s)\n", mvPtr->name, mvPtr->madeIn);
		printf("running time : %i, score : %f\n", mvPtr->runTime, mvPtr->score);
	}
	
	return;
}

int mv_printRunTime(void* obj, void* arg)
{
	movInfo_t* mvPtr = (movInfo_t*)obj; //mvPtr에 obj 대입 
	if (mvPtr == NULL)
	{
		printf("[ERROR] failed to print the movie Info! (object is NULL)\n");
	}
	
	 
	printf("Name : %s (%s)\n", mvPtr->name, mvPtr->madeIn);
	printf("running time : %i, score : %f\n", mvPtr->runTime, mvPtr->score);
	
	return;
}

int mv_printCountry(void* obj, void* arg)
{
	movInfo_t* mvPtr = (movInfo_t*)obj;
	if (mvPtr == NULL)
	{
		printf("[ERROR] failed to print the movie Info! (object is NULL)\n");
	}
	
	printf("Name : %s (%s)\n", mvPtr->name, mvPtr->madeIn);
	printf("running time : %i, score : %f\n", mvPtr->runTime, mvPtr->score);
	
	return;
}




