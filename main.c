#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movie.h" 								//movie.c의 헤더  
#include "linkedList.h" 						//linkedList의 헤더  

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[])
{
	
	FILE *fp; 									//FILE pointer for reading movie data 
	char name[200]; 							//movie name
	char country[10]; 							//movie country
	int runTime; 								//movie runtime
	float score; 								//movie score
	
	int exit_flag = 0; 							//flag variable for while loop
	int option; 								//user input option
	void *list, *mvInfo;						//pointers for linked list and a specific structure instance for a movie data
	int (*repFunc)(void* obj, void* arg); 		//function pointer for using list_repeatFunc() function
	void *arg; 									//a void pointer for passing argument to repFunc
	int cnt; 									//integer variable
	
	
	
	//1. reading the movie.dat-----------------------------
	printf("Reading the data files...\n");
	//1.1 FILE open
	fp = fopen("movie.dat","r"); //영화 DB파일 열기  
	
	
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
		mvInfo = mv_genMvInfo(name, score, runTime, country); //mvInfo에다가 my_genMvInfo 정보 대입(영화 제목, 평점, 상영시간, 제작 국가)
		list_addTail(mvInfo, list);  //addTail node 
	}
	
	
	printf("Read done! %d items are read! \n\n",list_len(list)); //몇 개의 영화가 읽혔는지 출력  
	
	
	//1.4 FILE close 파일 닫기  
	fclose(fp);  //파일 닫기  
	
	//2. program start
	while(exit_flag == 0)
	{
		//2.1 print menu message and get input option
		printf("-------------------- Menu --------------------\n");
		printf("1. print all the movies\n"); 						//옵션1 : 모든 영화 DB출력  
		printf("2. search for specific country movies\n"); 			//옵션2 : 특정 제작국가 영화 DB출력   
		printf("3. search for specific runtime movies\n"); 			//옵션3 : 특정 상영시간  DB출력  
		printf("4. search for specific score movies\n");			//옵션4 : 특정 영화 평점  DB출력 
		printf("5. exit\n"); 										//옵션5 : 프로그램 끝내기(나가기) 
		printf("-------------------- Menu --------------------\n\n");
		printf("-- select an option :"); 							//선택할 옵션  
		scanf("%d",&option); 										//선택할 옵션 입력받기  
		
		switch(option) //선택한 옵션에 따라서 프로그램 실행 및 출력 하기  
		{	
			case 1: //print all the movies ->옵션 1을 선택했을 때  
				printf("\nprinting all the movies in the list.....\n\n\n"); 
				printf("------------------------------------------------------\n");
				
				repFunc = mv_printAll;	//repFunc에 매개변수에 만들었던 함수 넣기, mv_printAll 함수 넣음->전부 다 출력
				arg = NULL;				//arg가 필요하지 않으므로 null 
				
				exit_flag = 0; 			//exit_flag = 1 일때 함수가 끝남 
				break;
				
			case 2: //print movies of specific country ->옵션 2를 선택했을 때  
				printf("select a country :");  
				scanf("%s",&country); 		//제작국가 입력받기  
				printf("------------------------------------------------------\n");
				repFunc = mv_printCountry;  //repFunc에 매개변수에 만들었던 함수 넣기,mv_printCountry 함수 넣음
				arg = country;				//arg 에 Country넣기(영화 제작 국가) 
				
				exit_flag = 0; 				//exit_flag = 1 일때 함수가 끝남
				break;						//switch문 종료  
				
			case 3: //print movies with long runtime ->옵션 3을 선택 했을 때  
				printf("lowest runtime :");
				scanf("%d",&runTime);		//최소 상영시간 입력받기  
				printf("------------------------------------------------------\n");
				repFunc = mv_printRunTime; //repFunc에 매개변수에 만들었던 함수 넣기,mv_printRunTime 함수 넣음
				arg = &runTime; //arg 에 runtime넣기(영화의 최소 상영시간 입력받는 것 ) 
				
				exit_flag = 0;	//exit_flag = 1 일때 함수가 끝남 
				break;			//switch문 종료    
				
			case 4: //print movies with high score ->옵션 4를 선택했을 때  
				printf("lowest score :");
				scanf("%f",&score);			//최소 평점 입력 받기  
				printf("------------------------------------------------------\n");
				repFunc = mv_printScore; //repFunc에 매개변수에 만들었던 함수 넣기,mv_prinScore 함수 넣음
				arg = &score;//arg 에 score넣기(영화의 최소 평점  입력받는 것 ) 
				
				exit_flag = 0;	//exit_flag = 1 일때 함수가 끝남 
				break;			//switch문 종료  
				
			case 5:
				printf("\n\n   Bye!\n\n");
				exit_flag = 1;	//함수가 끝남 
				break;	//switch문 종료  
				
			default:
				printf("wrong command! input again\n"); //1~5까지의 옵션 중 선택한 문자가 아닐 때 출력하는 것   
				exit_flag = 0; //exit_flag = 1 일때 함수가 끝남  
				break;	//switch문 종료  
		}
		
		
		//2.2 printing operation by function pointer (list_repeatFunc() is called here)
		
		if(1<=option && option<=4) //option을 1~4까지 선택했을 때만 몇 개의 영화가 출력되었는지 출력하도록 하기 
		{	
			cnt = list_repeatFunc(repFunc, arg, list); //몇 개의 영화리스트가 출력(검색) 되었는지 알려주는 함수  		
			//2.3 print number of movies
			printf("\n    - totally %d movies are listed!\n\n\n", cnt);  //몇 개의 영화 리트스가 검색되었는지 출력  
		}
		
	}
	
	return 0;  
}


