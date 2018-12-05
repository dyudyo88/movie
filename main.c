#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movie.h"
#include "linkedList.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	FILE *fp; //FILE pointer for reading movie data 
	char name[200]; //movie name
	char country[10]; //movie country
	int runTime; //movie runtime
	float score; //movie score
	
	int exit_flag = 0; //flag variable for while loop
	int option; //user input option
	void *list, *mvInfo; //pointers for linked list and a specific structure instance for a movie data
	int (*repFunc)(void* obj, void* arg); //function pointer for using list_repeatFunc() function
	void *arg; //a void pointer for passing argument to repFunc
	int cnt; //integer variable
	
	//1. reading the movie.dat-----------------------------
	printf("Reading the data files...\n");
	//1.1 FILE open
	fp = fopen("movie.dat","r");
	
	
	//1.2 list generation (use function list_genList() )
	list = list_genList();
	
	if(fp==NULL) //파일열기를 실패 할 경우의 출력  
	{
		printf("ERROR! 파일 오픈 실패");
		return 1; // 파일 오픈을 실패했으므로 return 1
	}
	
	
	
	//1.3 read each movie data from the file and add it to the linked list
	while (fscanf(fp, "%s %s %d %f", name, country, &runTime, &score) != EOF) //파일 정보를 입력 받음  
	{	
		//generate a movie info instance(mvInfo) with function mv_genMvInfo()
		mvInfo = mv_genMvInfo(name, score, runTime, country); //mvInfo에다가 my_genMvInfo 정보 대입  
		list_addTail(mvInfo, list);
	}
	
	printf("Read done! %d items are read! \n\n"); 
	//1.4 FILE close 파일 닫기  
	fclose(fp);  
	
	//2. program start
	while(exit_flag == 0)
	{
		//2.1 print menu message and get input option
		printf("-------------------- Menu --------------------\n");
		printf("1. print all the movies\n");
		printf("2. search for specific country movies\n");
		printf("3. search for specific runtime movies\n");
		printf("4. search for specific score movies\n");
		printf("5. exit\n");
		printf("-------------------- Menu --------------------\n\n");
		printf("-- select an option :");
		scanf("%d",&option);
		
		switch(option)
		{	
			case 1: //print all the movies
				printf("\nprinting all the movies in the list.....\n\n\n");
				printf("----------------------------------------\n");
				
				repFunc = mv_printAll;	//repFunc에 매개변수에 만들었던 함수 넣기, mv_printAll 함수 넣음->전부 다 출력
				arg = NULL;				//arg 필요하지 않으므로 null 
				
				exit_flag = 0; //exit_flag = 1 일때 함수가 끝남 
				break;
				
			case 2: //print movies of specific country
				printf("select a country :");
				scanf("%s",&country);
				repFunc = mv_printCountry; //repFunc에 매개변수에 만들었던 함수 넣기,mv_printCountry 함수 넣음
				arg = country;				//arg 에 Country넣기(영화 제작 국가) 
				
				exit_flag = 0; //exit_flag = 1 일때 함수가 끝남
				break;
				
			case 3: //print movies with long runtime
				printf("lowest runtime :");
				scanf("%d",&runTime);
				repFunc = mv_printRunTime; //repFunc에 매개변수에 만들었던 함수 넣기,mv_printRunTime 함수 넣음
				arg = &runTime;				//arg 에 runtime넣기(영화의 최소 상영시간 입력받는 것 ) 
				
				exit_flag = 0;	//exit_flag = 1 일때 함수가 끝남 
				break;
				
			case 4: //print movies with high score
				printf("lowest score :");
				scanf("%f",&score);
				repFunc = mv_printScore; //repFunc에 매개변수에 만들었던 함수 넣기,mv_prinScore 함수 넣음
				arg = &score;				//arg 에 score넣기(영화의 최소 평점  입력받는 것 ) 
				
				exit_flag = 0;	//exit_flag = 1 일때 함수가 끝남 
				break;
				
			case 5:
				printf("\n\nBye!\n\n");
				exit_flag = 1;	//함수가 끝남 
				break;
				
			default:
				printf("wrong command! input again\n");
				exit_flag = 0; //exit_flag = 1 일때 함수가 끝남  
				break;
		}
		
		//2.2 printing operation by function pointer (list_repeatFunc() is called here)
		list_repeatFunc(repFunc, arg, list); //교수님이 알려주신 힌트 
		//2.3 print number of movies
		//printf("\n    - totally %d movies are listed!\n\n\n", ?); 
	}
	
	return 0;

}


