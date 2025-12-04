#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h> //strcpy
#include <windows.h> 
#include <conio.h> //키보드를 바로 입력 받을 수 있도록 해줌. kbhit getch
#include "Project1.h"


//=======================================
int main()
{

	linkedlist* L = (linkedlist*)malloc(sizeof(linkedlist)); //공간 할당
	//listwork* w;
	listwork w = { 0 };
	L->head = NULL;
	L->length = 0;//기본 0

	w.minu = 00;
	w.second = 00;

	int choice;
	int SaveChoice; //진짜 저장하시겠습니까? 질문
	//int first;
	//int second;
	int run = 1;//main이 계속 선택 진행이 가능하도록 함.
	

	char ChooseNumber; //아래에서 실시간 입력받으면서 선택지 선택할때 사용 /getch가 문자로 받음..
	int autoNumber = 1; //IMSI

	int SystemAlarm = 3; //기본은 3시간

	OpenMyFile(L);
	
	if (L->length > 0)
	{
		autoNumber = L->length + 1;//파일에들어간거만큼 다시 추가
	}

	
	//리스트 쫙 보여주기
	while (run)
	{
		system("cls");

		CheckAlarm(L, SystemAlarm);
	
		
		
		printf("   [현재 과제 목록]\n");
		printf("\n");

		printf("   [번호]  [과목명]     [과제명]  [마감 년] [월] [일] [시] [분] [제출여부]\n");

		displayList(L);

		printf("(1) 마감까지 남은 시간 보기\n");
		printf("(2) 알림 시간대 설정\n");
		printf("(3) 과제 추가\n");
		printf("(4) 과제 삭제\n");
		printf("(5) 과제 수정\n");
		printf("(6) 마감일 순 정렬\n");
		printf("(7) 기간 지난 과제 일괄삭제\n");
		printf("(8) 현재 파일 저장\n");
		printf("(0) 종료\n");

		printf("선택: ");
		scanf("%d", &choice);

		switch (choice)//어디서부터 꼬인거야~
		{
		case 1: //마감까지 남은 시간 보기     / 현 문제 상황. 다른 과제들이 목록에 있어도, 1번과제 마감시감만 보여주고 있음. 왜지? =>lasttime을 현재 끝마치지 못해서 myworklist = myworklist->next; 이게 작동하지 않고 있음.
		{
			
			system("cls");

			int choice1running = 1; //1번선택했을때 거기서 계속 진행이 가능하도록 해줌

			listwork* myworklist = L->head;
			if (myworklist == NULL) //과제있니
			{
				printf("과제가 존재하지 않습니다.\n");//없으면 출력
			}
			else//있으면
			{
				while (choice1running == 1)
				{
					listwork* myworklist = L->head;//다시 끌고오기

					while (myworklist != NULL)//끝까지 다시출력
					{
						LastTime(*myworklist);//시간출력
						myworklist = myworklist->next; //다음이동하면서 출력
					}
					printf("(1) 메인 메뉴로 돌아가기    (2) 마감일 순으로 정렬하기");
					printf("\n\n"); //옮김

					if (_kbhit()) //키보드 입력 확인
					{
						ChooseNumber = _getch(); //이제 입력받게된다. scanf처럼 \n을 입력받지 않아도 바로 입력받은즉시출력

						switch (ChooseNumber)
						{
						case '1'://1입력받았을 때
						{
							choice1running = 0;
							printf("메뉴로 돌아갑니다.\n");
							printf("\n");
							break;
						}//case1끝
						case '2': //2입력받았을 때
						{
					
							ZungRrull(L);
							printf("목록을 마감일 순으로 정렬합니다.\n");
							Sleep(1000);
							break;
							
						}
						default:
						{
							choice1running = 1;

						}//default끝
							

							
						}//switch끝
					}//if끝

					Sleep(1000);
					system("cls");
				}
				
			}
			//time_t timer = time(NULL);//time.h, timer...   /timer을 struct tm 값으로 변환
			//struct tm tm = *localtime(&timer);//time.h, tm...   time_t와 localtime은 둘다 time.h라이브러리의 함수
			//LastTime(w);
			break;
		}
		case 2: //알림 시간대 설정
		{
			int MyAlarm;
			printf("\n");
			printf("<<알람창은 화면 전환시마다 띄워집니다>>\n\n");
			printf("현재 알림 시간 설정: 마감 %d 시간 전에 알림 받기\n", SystemAlarm);
			printf("몇 시간 전부터 알림을 받겠습니까? (시간 단위로 입력): ");
			
			if (scanf("%d", &MyAlarm)== 1 && MyAlarm >= 1)
			{
				SystemAlarm = MyAlarm;
				printf("알림 설정이 마감 %d시간 전으로 변경되었습니다! \n", SystemAlarm);
			}
			else
			{
				while (getchar() != '\n');//입력버퍼지우기
				printf("잘못된 입력입니다! 1이상의 정수를 입력해주세요\n");
			}
			Sleep(1000);
			system("cls");
			
			break;
		}
		case 3: //과제 추가
		{
			//일단 만들어두기
			//위로옮김

			AddWork(L, &autoNumber);

			break;
		}
		case 4: //과제 삭제
		{
			DeleteWork(L, &autoNumber);
			break;
		}
		case 5: //과제 수정
		{
			ReWork(L);
			break;
		}
		case 6: //마감일 순 정렬===>변경!
		{
			ZungRrull(L);
			//생각하지 못한 점: 한글은 strchr로 검색이 안됨... =========> 삭제해야하나
			break;
		}
		case 7: //기간 지난 과제 일괄 살제
		{
			LastClear(L, &autoNumber);
			break;
		}
		case 8: ///현재 변경사항 파일에 저장.
		{
			printf("***!!***현재 변경사항을 파일에 저장하시겠습니까?***!!***\n");
			printf("(1)아니오    (2)예\n");
			
			scanf("%d", &SaveChoice);

			switch (SaveChoice)
			{
			case 1:
			{
				printf("메인 화면으로 돌아갑니다.\n");
				Sleep(1000);
				system("cls");
				break;
			}//1
			case 2:
			{
				SaveMyFile(L); //현재 파일 저장
				//printf("저장되었습니다.\n");======> 이미 SaveMyFile에서 확인메시지 출력.
				printf("메인 화면으로 돌아갑니다.\n");
				Sleep(1000);
				system("cls");
				break;
			}//2
			default:
			{
				printf("아무것도 선택되지 않았습니다.\n");
				printf("메인 화면으로 돌아갑니다.\n");
				Sleep(1000);
				system("cls");
				break;
			}//default
			}//swtich
			break; //이건 main으로 돌아감 run은 그대로 1이기 떄문에 main으로 돌아갈 수 있믐
		}//case 8
		case 0: //종료
		{
			printf("프로그램을 종료합니다.\n"); //여기다가 그 SDL써도 되려나??
			run = 0;
			break;
		}//case0
		}//switch    잠만... 알림기능 어디감?
	}//while
	free(L);//... 필요? 일단 linkedlist엔 있었음
	return 0;
}