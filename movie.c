#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movie.h"

//structure definition ����ü ����  
typedef struct movInfo //struct�� �ٸ� �̸��� "movInfo"�� �ϰڴ�. 
 {
	char name[100]; //��ȭ �̸� 
	float score;	//��ȭ ����  
	int runTime;	//��ȭ �󿵽ð�  
	char madeIn[10];	//��ȭ ���� ����  
}  movInfo_t; //����ü ��������  

int mvPtr; 

void* mv_genMvInfo(char* name, float score, int runTime, char* country)
{
	movInfo_t* mvPtr; //����ü ���� movInfo_t�� ������mvPtr�� ������   
	//allocate memory and set the member variables
	mvPtr = (movInfo_t*)malloc(sizeof(movInfo_t)); //�����޸� �Ҵ�
	strcpy(mvPtr->name, name); //���ڿ� ���� strcpy(���, ����)->���Ͽ��� ������ name������ �����ͷ� name�� ������ 
	strcpy(mvPtr->madeIn, country);//���ڿ� ���� strcpy(���, ����)->���Ͽ��� ������ country������ �����ͷ�madeIn�� ������  
	//���Ͽ��� ������ score ������ runTime ������ �����ͼ� �����ؾߵ�.
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
	printf("------------------------------------------------------\n");
	return;
}

int mv_printAll(void* obj, void* arg)
{
	movInfo_t* mvPtr = (movInfo_t*)obj; //mvPtr�� obj ���� 
	if (mvPtr == NULL)
	{
		printf("[ERROR] failed to print the movie Info! (object is NULL)\n");
	}
	
	printf("Name : %s (%s)\n", mvPtr->name, mvPtr->madeIn);
	printf("running time : %i, score : %f\n", mvPtr->runTime, mvPtr->score);
	printf("------------------------------------------------------\n");
	return;
}

 
int mv_printScore(void* obj, void* arg)
{
	movInfo_t* mvPtr = (movInfo_t*)obj; //mvPtr�� obj ����  
	if (mvPtr == NULL)
	{
		printf("[ERROR] failed to print the movie Info! (object is NULL)\n");
	}
	
	if( (mvPtr->score) > *(float*)(arg) )//�Է��� �� ���� ���� ������ ���� ��ȭ�� ����ؾ� ��
										//void*���� float*������ ��ȯ�ϱ� + mvPtr->score�� ���ϱ�    
	{
		printf("Name : %s (%s)\n", mvPtr->name, mvPtr->madeIn);
		printf("running time : %i, score : %f\n", mvPtr->runTime, mvPtr->score);
		printf("------------------------------------------------------\n");
	}
	
	return;
}

int mv_printRunTime(void* obj, void* arg)
{
	movInfo_t* mvPtr = (movInfo_t*)obj; //mvPtr�� obj ���� 
	if (mvPtr == NULL)
	{
		printf("[ERROR] failed to print the movie Info! (object is NULL)\n");
	}
	
	if( (mvPtr->runTime) > *(int*)(arg) ) //void*���� int*������ ��ȯ�ϱ� + mvPtr->runTime�� ���ϱ�  
	{
		printf("Name : %s (%s)\n", mvPtr->name, mvPtr->madeIn);
		printf("running time : %i, score : %f\n", mvPtr->runTime, mvPtr->score);
		printf("------------------------------------------------------\n");
	}
	
	return;
}

int mv_printCountry(void* obj, void* arg)
{
	movInfo_t* mvPtr = (movInfo_t*)obj;
	if (mvPtr == NULL)
	{
		printf("[ERROR] failed to print the movie Info! (object is NULL)\n");
	}
	
	if( strcmp(mvPtr->madeIn , arg) == 0)   //mvPtr->madeIn �� arg(Country) ���ڿ��� ���ؼ� ������ ���ϴ� ��,���ڿ��� ������ 0�� ��ȯ�ȴ�. 
	{
		printf("Name : %s (%s)\n", mvPtr->name, mvPtr->madeIn);
		printf("running time : %i, score : %f\n", mvPtr->runTime, mvPtr->score);
		printf("------------------------------------------------------\n");
	}
	
	return;
}




