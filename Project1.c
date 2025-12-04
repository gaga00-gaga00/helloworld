#include "Project1.h"

void OpenMyFile(linkedlist* L) //파일 입출력 참조.
{

	FILE* file;
	listwork w;

	char input[200]; //이거면 충분하겠지?
	int CheckRead;

	file = fopen("MyList.txt", "r"); //파일 읽기

	printf("과제 목록을 불러옵니다.\n");

	if (file == NULL) //파일이 없으면
	{
		printf("파일을 열 수 없습니다. 저장된 과제가 존재하지 않습니다.\n");
		//exit(1);
		return; //그냥 main으로만 돌아가도록 하자.
	}

	//fgets(input, sizeof(input), file); //fgets로 한 줄씩 읽어오기
	//input[strcspn(input, "\n")] = 0;

	while ((fgets(input, sizeof(input), file) != NULL))//파일을 끝까지 한줄씩 읽어오겠다. 이것도 AI도움받음...
	{
		input[strcspn(input, "\n")] = 0;//\n을 제거하겠다
		CheckRead = sscanf(input, "%d %s %s %d %d %d %d %d %d %s\n", &w.num, w.Subject, w.workname, &w.year, &w.month, &w.day, &w.hour, &w.minu, &w.second, w.send); //배열의 이름은 주소이므로 & 안 붙여도 됨을 인지할것!!!
		//sscanf를 이용해서 띄어쓰기가 나올떄마다 차례로 넣엊무

		if (CheckRead == 10) //번호, 과제명~~ 제출여부까지, 파일에 있는게 10개 다 들어가있으면
		{
			insertList(L, w);//<<<***이건 AI도움받음. 뒤로 보내줘야 자리배정을 해 줘서 다음에 계속 수행할때 오류가 나지 않도록 해줌. 여기 넣어줘야 줄마다 넣어줌
		}
		else
		{
			printf("내용이 이상한 줄이 존재!!! 다시 확인하십시오");
		}
	}
	//insertList(L,w); //<<<***이건 AI도움받음. 뒤로 보내줘야 자리배정을 해 줘서 다음에 계속 수행할때 오류가 나지 않도록 해줌.

	fclose(file);//열었으니까 닫기
	
	Sleep(1000);
	system("cls");
}
//*******************************************************
void SaveMyFile(linkedlist* L)//**************************
{
	FILE* file;
	listwork* w;

	file = fopen("MyList.txt", "w");//w, 파일에 쓴다.

	if (file == NULL)
	{
		printf("파일을 열 수 없습니다. 저장된 과제가 존재하지 않습니다.\n");
		return;
	}
	w = L->head;
	while (w != NULL)
	{
		fprintf(file, "%d %s %s %d %d %d %d %d %d %s\n", w->num, w->Subject, w->workname, w->year, w->month, w->day, w->hour, w->minu, w->second, w->send); //배열의 이름은 주소이므로 & 안 붙여도 됨을 인지할것!!! 아직도 ->하고.하고 왜 다른지 잘 모르겠다..
		w = w->next;
	}
	fclose(file);
	printf("저장되었습니다.");
	Sleep(1000);
	system("cls");
}

//==================================================
int MonthtoDay(int wyear, int wmonth)// listwork year, listwork month //숫자 반환하므로 int 쓰기... 왜 안돌아가나 했다
{
	if (wmonth == 2)//윤년먼저. 윤년일시 +29
	{
		if ((wyear % 4) == 0 && (wyear % 100) != 0 || (wyear % 400) == 0)
		{
			return 29;
		}
		else
		{
			return 28;
		}


	}
	if (wmonth == 1 || wmonth == 3 || wmonth == 5 || wmonth == 7 || wmonth == 8 || wmonth == 10 || wmonth == 12) // 31일인 달 (+31)
	{
		return 31;
	}
	if (wmonth == 4 || wmonth == 6 || wmonth == 9 || wmonth == 11) //30일인 달 (+30)
	{
		return 30;
	}
	return 0;
}

void LastTime(listwork w)//남은시간 보여주기...현재시간 -  날. 시 분 보여주면 되겠지? /// 지금 고쳐야 할 것. 여기 루프가 안 끝남. //while제거. 이걸 main으로 옮기면?
{
	//현재 시간 가져오기 (current_tm에 저장)
	time_t current_tm = time(NULL);
	struct tm tm = *localtime(&current_tm);
	//printf("%d, %5s, %5s, %5d월 %5d일, %5d시, %3d분, %5s", w.num, w.Subject, w.workname, w.month - tm.tm_mon + 1, w.day - tm.tm_mday, w.hour - tm.tm_hour, w.minu - tm.tm_min, w.send);//모두 출력
	printf("%d, %5s, %5s", w.num, w.Subject, w.workname);

	//(과제 마감 시간들)
	int chocho = w.second; //초! 
	int minmin = w.minu; //본래 값 바꿨다가 뭔일 날까봐 만들어놓음
	int houror = w.hour;
	int monthth = w.month;
	int dayday = w.day;
	int yearar = w.year;

	int lastcho = chocho - tm.tm_sec;
	if (lastcho < 0) //초 계산
	{
		minmin = minmin - 1;
		lastcho = lastcho + 60;
	}


	int lastmin = minmin - tm.tm_min;
	if (lastmin < 0) //분 계산
	{
		houror = houror - 1;
		lastmin = lastmin + 60;
	}

	int lasthour = houror - tm.tm_hour;
	if (lasthour < 0)
	{
		dayday = dayday - 1;
		lasthour = lasthour + 24;
	}

	int lastday = dayday - tm.tm_mday;
	if (lastday < 0)
	{
		monthth = monthth - 1;
		if (monthth == 0) //0월은 없다!
		{
			monthth = 12; //12월로 바꾸기
			yearar = yearar - 1; //년도 -1
		}
		lastday = lastday + MonthtoDay(yearar, monthth); //실수ㅜㅇ
		//여기 함수 하나 다시만들어야할듯. 월에 따라 그 뭐냐 날수도 다르고 2월은 특히 짧으니깐
	}

	int lastmonth = monthth - (tm.tm_mon + 1);// tm.tm.mon은 0~11이라함... 원하는값 얻을라면 +1
	if (lastmonth < 0)
	{
		yearar = yearar - 1;
		lastmonth = lastmonth + 12;
	}

	int lastyear = yearar - (tm.tm_year + 1900); //년도는 빼올 수 있는 곳이 없으니 이대로 마무리... tm.tm_year은 1900년대 이후로 지난 시간이라 1900을 더해줘야 한다고 함...


	if (lastyear < 0) //얘까지 빼면 안돌아가고
	{
		printf(" -> 기한이 만료된 과제입니다!\n\n");
		return;
	}
	/*if (lastyear == 0 && lastmonth < 0)
	{
		printf(" -> 기한이 만료된 과제입니다!\n\n");
		return;
	}
	if (lastyear == 0 && lastmonth == 0 && lastday < 0)
	{
		printf(" -> 기한이 만료된 과제입니다!\n\n");
		return;
	}
	if (lastyear == 0 && lastmonth == 0 && lastday == 0 && lasthour < 0)
	{
		printf(" -> 기한이 만료된 과제입니다!\n\n");
		return;
	}*///이건 또 뺴면 돌아가네?? 뭐지

	if (lastyear == 0 && lastmonth == 0 && lastday == 0 && lasthour == 0 && lastmin == 0 && lastcho < 0)
	{
		printf(" -> 기한이 만료된 과제입니다!\n\n");
		return;
	}
	printf("   남은 시간: %d년 %d개월 %d일 %d시간 %d분 %d초\n", lastyear, lastmonth, lastday, lasthour, lastmin, lastcho);
	printf("\n");
	
}

//=======================================================================================================================================================
void CheckAlarm(linkedlist* L, int systemAL)
{
	listwork* current = L->head;

	int AlarmMin = systemAL * 60; //분으로 바꾸기
	int ALcount = 0; //알람 카운트

	while (current != NULL) //끝까지 안 갔으면
	{
		//위의 lasttime에서 가져옴
		//현재 시간 가져오기 (current_tm에 저장)
		time_t current_tm = time(NULL);
		struct tm tm = *localtime(&current_tm);

		//(과제 마감 시간들)
		int chocho = current->second; //초! 
		int minmin = current->minu; //본래 값 바꿨다가 뭔일 날까봐 만들어놓음
		int houror = current->hour;
		int monthth = current->month;
		int dayday = current->day;
		int yearar = current->year;

		int lastcho = chocho - tm.tm_sec;
		if (lastcho < 0) //초 계산
		{
			minmin = minmin - 1;
			lastcho = lastcho + 60;
		}


		int lastmin = minmin - tm.tm_min;
		if (lastmin < 0) //분 계산
		{
			houror = houror - 1;
			lastmin = lastmin + 60;
		}

		int lasthour = houror - tm.tm_hour;
		if (lasthour < 0)
		{
			dayday = dayday - 1;
			lasthour = lasthour + 24;
		}

		int lastday = dayday - tm.tm_mday;
		if (lastday < 0)
		{
			monthth = monthth - 1;
			if (monthth == 0) //0월은 없다!
			{
				monthth = 12; //12월로 바꾸기
				yearar = yearar - 1; //년도 -1
			}
			lastday = lastday + MonthtoDay(yearar, monthth);

		}

		int lastmonth = monthth - (tm.tm_mon + 1);// tm.tm.mon은 0~11이라함... 원하는값 얻을라면 +1
		if (lastmonth < 0)
		{
			yearar = yearar - 1;
			lastmonth = lastmonth + 12;
		}

		int lastyear = yearar - (tm.tm_year + 1900); //년도는 빼올 수 있는 곳이 없으니 이대로 마무리... tm.tm_year은 1900년대 이후로 지난 시간이라 1900을 더해줘야 한다고 함...

		int armarm = 0;//알림 울릴지말지 체크

		if (lastyear < 0) //얘까지 빼면 안돌아가고
		{
			armarm = 1;
		}
		else if (lastyear == 0 && lastmonth < 0)
		{
			armarm = 1;
		}
		else if (lastyear == 0 && lastmonth == 0 && lastday < 0)
		{
			armarm = 1;
		}
		else if (lastyear == 0 && lastmonth == 0 && lastday == 0 && lasthour < 0)
		{
			armarm = 1;
		}
		else if (lastyear == 0 && lastmonth == 0 && lastday == 0 && lasthour == 0 && lastmin == 0 && lastcho < 0)
		{
			armarm = 1;
		}
		else if (lastyear == 0 && lastmonth == 0 && lastday == 0 && lasthour == 0 && lastmin == 0 && lastcho <= 0)
		{
			armarm = 1;
		}

		int Finallastmin = 0;//남은시간===> 분으로 변경

		if (armarm != 1)
		{
			Finallastmin = Finallastmin + lastday * 24 * 60;//시간변환! 주의!
			Finallastmin = Finallastmin + lasthour * 60;
			Finallastmin = Finallastmin + lastmin;

		}
		if (armarm != 1 && Finallastmin > 0 && Finallastmin <= AlarmMin)//Alarmmin = systemAL*60
		{
			printf("[알림] %s 과목의 %s 마감이 %d 시간 내로 임박: 남은 시간: 약 %d분\n", current->Subject, current->workname, systemAL, Finallastmin);
			printf("\n");

			ALcount++; //ALcount = ALcount+1은 카운트가 안됨...
		}
		current = current->next; //다음으로 넘어가서 체크
	}
	if (ALcount > 0)
	{
		printf("\n");
		printf("모든 알림을 확인하였습니다. 엔터를 누를 시 메인 메뉴로 돌아갑니다.");
		while (getchar() != '\n'); //입력버퍼비우기

		getchar();
		system("cls");

	}
}

//==============
void displayList(linkedlist* L) { //리스트 안 모든 항목 표시하기
	listwork* w;
	w = L->head; //헤더가 가리키는거(처음)로 둠
	while (w != NULL) {//끝까지 안 갔으면~                                 // 초는 딱히 보여줄 필요 없지 않나

		if (w->change == 1)//  추가추가~
		{
			printf("-->");
		}
		else
		{
			printf("   "); //공백 맞추기...
		}

		/*
		printf("%3d, %5s, %5s, %5d년 %5d월 %5d일, %5d시, %3d분, %5s", w->num, w->Subject, w->workname, w->year, w->month, w->day, w->hour, w->minu, w->send);//모두 출력
		*/

		printf("%-5d | %-10s | %-10s | %4d   %02d   %02d   %02d   %02d | %-4s",
			w->num,
			w->Subject,
			w->workname,
			w->year,
			w->month,
			w->day,
			w->hour,
			w->minu,
			w->send);

		w->change = 0; //다음에는 --> 안 나오도록

		w = w->next; //다음노드

		if (w != NULL)//한줄한줄
		{
			printf("\n");
		}//if
	}
	printf("\n");

}
//===================

void insertList(linkedlist* L, listwork w) //linkedlist 과제 참고
{
	listwork* newwork = (listwork*)malloc(sizeof(listwork)); //공간 할당
	*newwork = w; //newwork는 listwork 구조체를 복사받음
	newwork->next = NULL; //처음 가리키는거주소 null

	if (L->head == NULL) //처음 가리키는게 NULL이면(가리키는게 없으면)
	{
		L->head = newwork; //newwork를 가리킴
	}
	else //null이 아니면(가리키는게 있으면)
	{
		listwork* temp = L->head; //빈칸에 head넣기
		while (temp->next != NULL)
		{
			temp = temp->next; //NULL찾을때까지 뒤로 쭉감
		}
		temp->next = newwork; //새로 연결
	}

	L->length++;
}

void AddWork(linkedlist* L, int* autoNumber) //과제 추가 기능! scanf 이용
{
	listwork w;

	int ChooseSend;
	int RunAddWork = 1;

	w.change = 1;

	
	w.num = *autoNumber;

	printf("과목명(공백 없이 영어로 입력): ");
	scanf("%s", w.Subject);

	printf("과제명(공백 없이 영어로 입력): ");
	scanf("%s", w.workname);

	printf("마감 년도: "); //년도 추가 입력
	scanf("%d", &w.year);

	printf("마감 월: "); //월 추가 입력
	scanf("%d", &w.month);

	

	printf("마감 날짜(일): ");
	scanf("%d", &w.day);

	printf("마감 시간(시) (예: 오후 2시 -> 14시) : ");
	scanf("%d", &w.hour);

	printf("마감 분: "); //좀 더 편하게 쓸 수 있는 방법이 없을까
	scanf("%d", &w.minu);

	w.second = 0;


	while (RunAddWork)
	{
		printf("제출 여부 \n"); //======================================================>이건 솔직히 필요없는거같은데...... 그냥 사용자가 확인할 수 있도록 해주는거라 하자.
		printf("(1) YES      (2) NO\n");
		printf("선택: ");



		if (scanf("%d", &ChooseSend) == 1) // 숫자 잘 입력받음
		{
			switch (ChooseSend)
			{
			case 1:
			{
				strcpy(w.send, "YES");
				RunAddWork = 0;
				break;
			}
			case 2:
			{
				strcpy(w.send, "NO");
				RunAddWork = 0;
				break;
			}
			default:
			{
				printf("1,2중에서 다시 선택해 주십시오");
				break;
			}
			}//switch
		}
		else
		{
			printf("잘못된 입력입니다. 숫자로 다시 입력해 주세요");
			while (getchar() != '\n'); //입력버퍼지우기
		}
	}

	*autoNumber = *autoNumber + 1; //이러면 자동으로 들어가려나?

	w.next = NULL; //새 노드가 리스트의 끝이라는 뜻.
	insertList(L, w); //inserList 불러옴

	printf("\n");
	printf("--> %d번,  %s %s\n", w.num, w.Subject, w.workname);
	printf("과제가 추가되었습니다!\n");
	Sleep(1800);
	system("cls");
}
//=======================================

void DeleteWork(linkedlist* L, int* autoNumber)
{
	if (L->head == NULL) //리스트가 비어있다면
	{
		printf("삭제할 과제가 존재하지 않습니다.\n");
		return;
	}

	int want;

	printf("삭제할 과제 번호를 입력하세요: ");//번호? 과제 이름? 과목명?
	scanf("%d", &want);
	//want는 삭제하려는 번호. 


	listwork* pre = NULL; //지우려는 거의 앞을 가리키는 pre(앞 노드)
	listwork* hun = L->head; //현재
	

	while (hun != NULL && hun->num != want) //NULL이 아닌데, 삭제하려던 번호가 아니면
	{
		pre = hun;//현재값을 pre에 넘겨주기.
		hun = hun->next; //다음 넘어가기
	}

	if (hun == NULL)//NULL이면(비어있으면)
	{
		printf("과제 번호 %d를 찾을 수 없습니다.\n", want);
		return;
	}
	

	if (pre == NULL)//삭제하려는게 헤드였으면
	{
		L->head = hun->next;  //현재 다음거...
	}
	else//헤드가 아니었으면
	{
		pre->next = hun->next; //현재의 다음걸 pre의 다음으로
	}
	listwork* backNum = hun->next;

	free(hun);

	while (backNum != NULL)
	{
		backNum->num = backNum->num - 1; //숫자 감소해라
		backNum = backNum->next; //다음칸으로 계속 이동
	}
	*autoNumber = *autoNumber - 1; //숫자 하나 감소

	L->length--; //빠졌으니 길이 줄이기
	printf("과제 %d번을 삭제하였습니다!\n", want);
	Sleep(1000);
	system("cls");

}
//==================위는 과제 삭제============================아래는 과제 수정=======================
void ReWork(linkedlist* L)//넣어야 할것. 번호 없으면 없다고 말하기& 다시 입력할 수 있도록 하기 / 번호 누르면, 과제명, 과목명, 등등 중에서 어떤거 수정할거냐고 묻기 switchcase문으로. 취소하는거 만들어야한다. 
{
	listwork* w;
	//DeletrWork 참고좀 합시다~~~
	if (L->head == NULL) //리스트가 비어있다면
	{
		printf("수정할 수 있는 과제가 존재하지 않습니다.\n");
		return;
	}
	int mynum; //수정하려는 과제의 번호.... want로 통일시키는게 나을까? 아니다. 그냥 하자
	int run = 1;
	int choose;

	char NewSubject[30];
	char NewWork[50];
	int NewYear;
	int NewMonth;
	int NewDay;
	int NewHour;
	int NewMin;
	char NewSend[6];

	while (run)
	{
		printf("수정할 과제 번호를 입력하세요: ");// 과제 이름 과목명 선택할수있도록 하기 
		scanf("%d", &mynum);

		
		listwork* hun = L->head; //현재

		while (hun != NULL && hun->num != mynum) //NULL이 아닌데, 수정하려던 번호가 아니면
		{
			hun = hun->next; //다음 번호로 넘어가기
		}

		if (hun == NULL)//NULL이면(비어있으면) ==========================이거 순서 중요할라나 엉 중요하네 바꾸니까안된다
		{
			printf("%d번째 과제는 존재하지 않습니다. 다시 입력해 주십시오.\n", mynum);
			continue; //써도 됐는지 기억이 안난다.
			//break는 그냥 Rework 함수를 끝내버린다...주의ㅣ

		}

		if (hun->num == mynum)
		{
			printf("수정하려는 항목을 선택해 조십시오.\n\n");
			printf("(1) 과목명 (2) 과제명 (3)마감 년도 (4)마감 달 (5)마감 일 (6)마감 시간 (7)마감 분 (8)제출 여부 (9)수정 취소\n\n");
			printf("선택: ");

			if (scanf("%d", &choose) != 1) //************ 저번에 선택지 게임때 썼던거긴한데... 쓸만하려나
			{
				while (getchar() != '\n');
				choose = -1;
			}
			// Subject workname year month day hour minu send
			switch (choose)
			{
			case 1:
			{
				hun->change = 1;
				printf("새 과목명: ");
				scanf("%s", NewSubject);
				strcpy(hun->Subject, NewSubject); //strcpy! 잘 되련가 진짜 다 잊었네 큰일났다앗 검색해서 알았네
				printf("\n");
				break;
			}
			case 2:
			{
				hun->change = 1;
				printf("새 과제명: ");
				scanf("%s", NewWork);
				strcpy(hun->workname, NewWork);
				printf("\n");
				break;
			}
			case 3:
			{
				hun->change = 1;
				printf("새 마감 년도: ");
				scanf("%d", &NewYear);
				hun->year = NewYear; //문자열이 strcpy~ 
				printf("\n");
				break;
			}
			case 4:
			{
				hun->change = 1;
				printf("새 마감 월: ");
				scanf("%d", &NewMonth);
				hun->month = NewMonth;
				printf("\n");
				break;
			}
			case 5:
			{
				hun->change = 1;
				printf("새 마감 날짜(일): ");
				scanf("%d", &NewDay);
				hun->day = NewDay;
				printf("\n");
				break;
			}
			case 6:
			{
				hun->change = 1;
				printf("새 마감 시간(시): ");
				scanf("%d", &NewHour);
				hun->hour = NewHour;
				printf("\n");
				break;
			}
			case 7:
			{
				hun->change = 1;
				printf("새 마감 분: ");
				scanf("%d", &NewMin);
				hun->minu = NewMin;
				printf("\n");
				break;
			}
			case 8:
			{
				hun->change = 1;
				printf("제출 여부를 변경합니다.\n");
				if (strcmp(hun->send, "YES") == 0) //!!!문자열비교는  strcmp. 같0 다1
				{
					strcpy(hun->send, "NO");
					printf("제출 여부를 NO로 변경 완료했습니다.\n");
				}
				else
				{
					strcpy(hun->send, "YES");
					printf("제출 여부를 YES로 변경 완료했습니다.\n");
				}
				printf("\n");
				break;
			}
			case 9:
			{
				printf("과제 수정을 마칩니다.\n");
				run = 0;
				break;
			}
			default:
			{
				printf("잘못된 선택입니다.\n");
				break;
			}
			}//switchcase문
			printf("%d번의 과제가 수정되었습니다!\n", mynum);
			Sleep(1000);
			system("cls");
			
			run = 0;
		}

	}//while


}
//====================================이 위는 과제 수정하는 함수=======================================
void ZungRrull(linkedlist* L)
{

	listwork* w;

	listwork* i;
	listwork* j;

	listwork temp; //임시공간 (되는진 모르겠음)

	int Renum = 0;
	listwork* HUN = L->head;


	if (L->head == NULL) //리스트가 비어있다면
	{
		printf("정렬할 수 있는 과제가 존재하지 않습니다.\n");
		return;
	}
	for (i = L->head; i != NULL; i = i->next)//버블정렬이 좋지 않을까? 처음은 년도비교/월/일/시/분 순 (마감일 비교)
	{
		for (j = i->next; j != NULL; j = j->next)
		{
			int GC = 0;//*gotochange. 바꾸라는 뜻.*

			if (j->year < i->year)//년도비교,    j가 빠름. JJJ
			{
				GC = 1;
			}
			else if (j->year == i->year) //년도같으면
			{
				if (j->month < i->month)//월 비교
				{
					GC = 1;
				}
				else if (j->month == i->month)//월 같으면
				{
					if (j->day < i->day) //날짜 비교
					{
						GC = 1;
					}
					else if (j->day == i->day)//날짜가 같으면
					{
						if (j->hour < i->hour)//시 비교
						{
							GC = 1;
						}
						else if (j->hour == i->hour)//시가 같으면
						{
							if (j->minu < i->minu) //분 비교
							{
								GC = 1;
							}//초는 동일하게 맞춰놔서...

						}
					}
				}
			}

			if (GC == 1) //j(뒤) 가 i(앞)보다 마감일이 빠르면
			{

				temp.num = i->num;
				strcpy(temp.Subject, i->Subject);
				strcpy(temp.workname, i->workname);
				temp.year = i->year;
				temp.month = i->month;
				temp.day = i->day;
				temp.hour = i->hour;
				temp.minu = i->minu;
				temp.second = i->second;
				strcpy(temp.send, i->send); //i꺼 다 tmep로 넘김


				i->num = j->num; //? 이것도 넘겨줘야하나? ===============> 번호 안넘기니까 이상해짐
				strcpy(i->Subject, j->Subject); //j꺼를 i에 복사
				strcpy(i->workname, j->workname); //아래로 반복
				i->year = j->year;
				i->month = j->month;
				i->day = j->day;
				i->hour = j->hour;
				i->minu = j->minu;
				i->second = j->second;
				strcpy(i->send, j->send); //j꺼 다 i로 넘김

				j->num = temp.num; //? 넘겨줘야하나????=====================>번호 안넘기니까 이상해짐!!
				strcpy(j->Subject, temp.Subject);
				strcpy(j->workname, temp.workname);
				j->year = temp.year;
				j->month = temp.month;
				j->day = temp.day;
				j->hour = temp.hour;
				j->minu = temp.minu;
				j->second = temp.second;
				strcpy(j->send, temp.send); //temp(i)꺼 다 j로 넘김




			}
		}//for2
	}//for1

	//=====================번호 다시매기기 필요=====================


	while (HUN != NULL)//끝까지 다시
	{
		Renum = Renum + 1;
		HUN->num = Renum; //1번부터 차례로 수 다시 정렬
		HUN = HUN->next; //다음 이동
	}
	printf("\n");
	printf("과제를 마감일 순으로 정렬했습니다.\n");
	Sleep(1000);
	system("cls");

}



void Search(linkedlist* L)
{
	listwork* w;
	//DeletrWork 참고좀 합시다~~~
	if (L->head == NULL) //리스트가 비어있다면
	{
		printf("검색할 수 있는 과제가 존재하지 않습니다.\n");
		return;
	}
	char Find[50];
	printf("");

}
//====================================================


void LastClear(linkedlist* L, int* autoNumber) //마감기한 지난건 이 버튼 하나만 누르면 싹~~클리어~~~ LastClear 지금 당장 만나보세요오오오옷
{
	//이건 솔직히 AI도움을 많이 받았습니다.

	//마감기한 나타내는거 가지고와서 거기서 마감기한 지났다 뜨는거 번호 다 해서 싹 지우고 맨 앞에있는거부터 다시 번호 부여하면될듯? 
	//함수 일부만 가져오는건 안되나 너무 공간낭비아니려나...=======================================================================================>>>>>>>>>>>이거 가능한건가???????

	//아오 헷갈려 1번. 시간이 0이하인 애들을 찾는다 => 그거의 번호를 찾는다=> 처음부터 쭉 나가는 pre와 현재내값 linkedlist인가 work를 만든다. 그 번호 찾으면 건너뛰도록 한다. null이 될때까지 간다. 번호들은 뺴진 값만큼 세서 저번처럼 뒤에 있는 값들이 +1이 될 수 있도록 한다.
	//현재 시간 가져오기 (current_tm에 저장)

	//이건 위에있던거 그대로


	//=================================================================================
	//pre는 그대로 두고, hun은 다시 뒤로 한번더, hun이 null이 되기전깢 반복
	//listwork w; 안씀. 안쓰는거 맞겠지 혹시모르니 그냥 둬야겠다

	if (L->head == NULL)
	{
		printf("삭제할 과제가 존재하지 않습니다.\n");
		return;
	} //이건 솔직히 맞다.

	int want;
	int deletecount = 0;//지운거 개수만큼 뒤에 노드 숫자 줄여줘야함=========> 몇개 줄였는지 알려주는 역할로 변경
	//int run = 0;
	listwork* pre = NULL; //hun의 이전 노드(내가 지우려는 거의 이전 노드)
	listwork* hun = L->head; //현재 노드



	while (hun != NULL) //끝까지 도달하기 전까지 계속 실행
	{
		time_t current_tm = time(NULL);
		struct tm tm = *localtime(&current_tm);

		//hun 기준 시간들
		int chocho = hun->second; //초! 
		int minmin = hun->minu; //현재 있는 노드 기준으로 봐야하니까...
		int houror = hun->hour;
		int monthth = hun->month;
		int dayday = hun->day;
		int yearar = hun->year;

		int lastcho = chocho - tm.tm_sec;
		if (lastcho < 0) //초 계산
		{
			minmin = minmin - 1;
			lastcho = lastcho + 60;
		}

		int lastmin = minmin - tm.tm_min;
		if (lastmin < 0) //분 계산
		{
			houror = houror - 1;
			lastmin = lastmin + 60;
		}

		int lasthour = houror - tm.tm_hour;
		if (lasthour < 0)
		{
			dayday = dayday - 1;
			lasthour = lasthour + 24;
		}

		int lastday = dayday - tm.tm_mday;
		if (lastday < 0)
		{
			monthth = monthth - 1;
			if (monthth == 0)
			{
				monthth = 12;
				yearar = yearar - 1;
			}
			lastday = lastday + MonthtoDay(yearar, monthth);
		}

		int lastmonth = monthth - (tm.tm_mon + 1);// tm.tm.mon은 0~11이라함... 원하는값 얻을라면 +1
		if (lastmonth < 0)
		{
			yearar = yearar - 1;
			lastmonth = lastmonth + 12;
		}

		int lastyear = yearar - (tm.tm_year + 1900); //년도는 빼올 수 있는 곳이 없으니 이대로 마무리... tm.tm_year은 1900년대 이후로 지난 시간이라 1900을 더해줘야 한다고 함...

		int run = 0;
		if (lastyear < 0) //얘까지 빼면 안돌아가고
		{

			want = hun->num; // 음수가 될때, 이때 hun의 번호가 내가 원하는수(빠지기를 원하는 수)가 된다.
			run = 1;
		}
		if (lastyear == 0 && lastmonth < 0)
		{
			want = hun->num;//목표
			run = 1;
		}
		if (lastyear == 0 && lastmonth == 0 && lastday < 0)
		{
			want = hun->num;//목표의 번호
			run = 1;
		}
		if (lastyear == 0 && lastmonth == 0 && lastday == 0 && lasthour < 0)
		{
			want = hun->num;//목표의 번호를 want로 두기
			run = 1;
		}//이건 또 뺴면 돌아가네?? 뭐지
		if (lastyear == 0 && lastmonth == 0 && lastday == 0 && lasthour == 0 && lastmin < 0)
		{
			want = hun->num;//목표번호
			run = 1;
		}
		if (lastyear == 0 && lastmonth == 0 && lastday == 0 && lasthour == 0 && lastmin == 0 && lastcho < 0)
		{
			want = hun->num;//목표번호
			run = 1;
		}
		
		listwork* HunNext = hun->next; //이것도
		listwork* backNum;// 숫자 빠질 시 뒤 리스트들의 숫자를 줄이기 위해 만듦

		if (run == 1)//목표번호가 생겼으면...
		{
			listwork* Deletehun = hun; //바뀌지 않게 두기

			if (pre == NULL) //내 앞이 head.(내가 1번)
			{
				L->head = HunNext; //Deletework 참조 근데 이건 왜 필요하더라
				//중복되는거 아래로 이동
			}
			else //head가 아니면
			{
				pre->next = HunNext; //다음으로 연결=> hun(현재)가 사라짐
				//중복되는거 아래로 이동
			}

			listwork* backNum = HunNext;
			//***
			while (backNum != NULL)
			{
				backNum->num = backNum->num - 1; //숫자 감소해라
				backNum = backNum->next; //다음칸으로 계속 이동
			}
			*autoNumber = *autoNumber - 1; //숫자 하나 감소
			deletecount = deletecount + 1;
			//***
			L->length--;
			free(Deletehun);
			hun = HunNext;

		}
		else //목표번호가 안 생겼으면
		{
			pre = hun;
			hun = HunNext; //계속 순회
		}
	} //while 종료. =>hun이 끝까지 갔다는 뜻.
	if (deletecount >= 1)
	{
		printf("%d개의 만료된 과제를 삭제하였습니다!\n", deletecount);
	}
	else //만료된 과제가 없으면
	{
		printf("기간이 만료된 과제가 없습니다!\n");
	}

	Sleep(1000);
	system("cls");

}
