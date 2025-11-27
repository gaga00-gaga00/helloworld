#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h> //strcpy

//교수님죄송합니다

//목표 1) 과제번호 자동 입력되기. 먼저온놈이 일빠따
// 목표 1-2) 번호가 자동으로 들어간만큼, 숫자 빠지면 자리 하나씩 옮겨지도록 해야할듯
// ========================================================================================드가자잇 호잇짜 짜잇호 완료!
// 
// ******************** 응 근데 과제수정만드는게 먼저야~~~~~~**************
// =========================================================================================끼요오오옹오오옷옷옷 해냈어어어어엇 물론 인터넷 도움을 받긴 했지ㅁㄴ. 그래도 원판은 내가했다고고고오오오오옷 끼얏호우
// 
// new표 ) 일단 쉬운것부터 하자. 기간 지난 과제 일괄 삭제 어떤감. 그냥 기간 지났으면 삭제해달라 ... 아잠만 작제된거 개수 세서 그만큼 또 번호수 맞춰야하네 이걸로 가자. 
// 
// =====가는거야~  내가 알림프로젝트의 신이될게===========>패배! 어떻게 해야할지 순서를 모르겠다!! 느아아아아아ㅏ아ㅏㅅ
// 
//목표 2) 과제 띄어쓰기 있게? 없게? 없게할거면 띄어쓰기있으면 감지해서 공백 없이 작성해달라하기 과목명, 과제명 둘다
// 목표3) 이것도 위랑 비슷한데, 아잠만 아니다 됐다. 과제번호 자동입력되면 굳이 그렇게 할 필요없겠네....... 아니다 그 시간대 숫자만 입력해주라고 해야겠다
// 목표4) 제출미제출 이거 봐야하나.... 수정탭-> 제출여부 수정 들어가야하나? 그냥 뺄까
// 
// 목표5) 다 하고나서 선택 시 되돌아가기 기능 있어야함.
// 목표6) 아 맞다 파일입출력.
// 
// SDL을 굳이 써야할까?
// 
// 만약 잘못 삭제했다면, 되돌리는 기능이 있다면 얼마나 좋을까
// 
// 편의성기능이 있을까?
// 
// 지금 남은게... 알림 시간대 설정/ 과제 수정/ 과제 검색/ 기간 지난 과제 일괄 삭제 //알림 시간대에 맞춰 알림( 급한순으로 출력되도록 해야함.)=====> (1순위). 가까운 마감 시간 순. (2순위).제출 여부. 
// 
// 목표0=> 이거 그래서 왜만듦? 좀 바로바로 보이는 알림 프로그램이 필요해서... // 내 프로그램만의 장점이 있는가? 
// 
// 가독성은 다 만들고나서 하는거야하하하하핫
// 링크드리스트어쩌라는거냐아아아앗
// 날아간줄 알고 식겁했네
// 얘는 대체 저장을 어떻게 해야하는거냐앗 또 날아간줄 알았네
//======================================
typedef struct ListWork {
	int num; //번호(과제번호) ========================================================> 자동 입력되도록 만드랒
	char Subject[30]; //과목명
	char workname[50];//과제명
	int year; //년도(추가)
	int month; //달 (추가)
	int day; //마감일 날
	int hour; //마감일 시간
	int minu; //마감일 분
	char send[6]; //제출/미제출
	struct ListWork* next; //다음 노드 이어붙이기위해 필요한듯
}listwork;

typedef struct ListWork listwork;

typedef struct LinkedList { //사작점head
	listwork* head;
	int length;//사실이건잘모르겠다
}linkedlist;

typedef struct LinkedList linkedlist;

//=======================================

/*struct tm
{
	int tm_year;
	int tm_mon;
	int tm_day;
	int tm_hour;
	int tm_minu;
};
*/
//=========================================
/*void insertFirst(linkedlist* L, int num, char* Sub, char) //리스트의 첫번째 노드로 삽입
{
	listNode* newNode;
	newNode = (listNode*)malloc(sizeof(listNode));//동적 생성        =(listNode*)calloc(?,sizeof(listNode));
	newNode->no = a;//상품번호       (*newNode).no에  a(번호)를 넣겠다
	strcpy(newNode->fName, b);//과일이름             b(과일이름)를 복사해서 (*newNode).fName에 복사
	newNode->price = c;//가격        (*newNode).price에  c(가격)을 넣겠다
	newNode->link = L->head; //뒤로 연결. 자기참조구조체? ** link에 원래 head가 가리키던 주소주기****
	L->head = newNode; //헤드가 새 노드 링크가리키기
	L->length++;//리스트길이 증가~
}*/
//==================================================
int MonthtoDay(int wyear, int wmonth)// listwork year, listwork month //숫자 반환하므로 int 쓰기...
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
void LastTime(listwork w)//남은시간 보여주기...현재시간 -  날. 시 분 보여주면 되겠지?
{
	//현재 시간 가져오기 (current_tm에 저장)
	time_t current_tm = time(NULL);
	struct tm tm = *localtime(&current_tm);
	//printf("%d, %5s, %5s, %5d월 %5d일, %5d시, %3d분, %5s", w.num, w.Subject, w.workname, w.month - tm.tm_mon + 1, w.day - tm.tm_mday, w.hour - tm.tm_hour, w.minu - tm.tm_min, w.send);//모두 출력
	printf("%d, %5s, %5s", w.num, w.Subject, w.workname);

	int minmin = w.minu; //본래 값 바꿨다가 뭔일 날까봐 만들어놓음
	int houror = w.hour;
	int monthth = w.month;
	int dayday = w.day;
	int yearar = w.year;


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
	if (lastyear == 0 && lastmonth == 0 && lastday == 0 && lasthour == 0 && lastmin < 0)
	{
		printf(" -> 기한이 만료된 과제입니다!\n\n");
		return;
	}
	printf("남은 시간: %d년 %d개월 %d일 %d시간 %d분\n", lastyear, lastmonth, lastday, lasthour, lastmin);
	printf("\n\n");
}

//=======================================================================================================================================================

void displayList(linkedlist* L) { //리스트 안 모든 항목 표시하기
	listwork* w;
	w = L->head; //헤더가 가리키는거(처음)로 둠
	while (w != NULL) {//끝까지 안 갔으면~
		printf("%d, %5s, %5s, %5d년 %5d월 %5d일, %5d시, %3d분, %5s", w->num, w->Subject, w->workname, w->year, w->month, w->day, w->hour, w->minu, w->send);//모두 출력
		w = w->next; //다음노드
		if (w != NULL)
		{
			printf(" \n--> ");
		}
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
	

	/*
	printf("과제 번호: "); //근데 이걸 써야하나? 자동으로 입력되게 할 수는 없나?
	scanf("%d", &w.num); //일단 과제 번호 입력
	*/
	w.num = *autoNumber;

	printf("과목명: ");
	scanf("%s", w.Subject);

	printf("과제명: ");
	scanf("%s", w.workname);

	printf("마감 년도: "); //년도 추가 입력
	scanf("%d", &w.year);

	printf("마감 월: "); //월 추가 입력
	scanf("%d", &w.month);

	/*if (w.month <= 0 || w.month > 12)
	{
		printf("")
	}*/

	printf("마감 날짜(일): ");
	scanf("%d", &w.day);

	printf("마감 시간(시): ");
	scanf("%d", &w.hour);

	printf("마감 분: "); //좀 더 편하게 쓸 수 있는 방법이 없을까
	scanf("%d", &w.minu);

	printf("제출 여부: "); //======================================================>이건 솔직히 필요없는거같은데......
	scanf("%s", w.send);

	*autoNumber = *autoNumber + 1; //이러면 자동으로 들어가려나?

	w.next = NULL; //새 노드가 리스트의 끝이라는 뜻.
	insertList(L, w); //inserList 불러옴

	printf("\n");
	printf("과제가 추가되었습니다!\n");
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
	//순서???



	//pre = L->head;
	//hun = NULL;

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
	//어떻게 해야 찾을 수 있지?
	//printf("과제 %d번을 삭제하였습니다.\n", want);
		//return 0;


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

	/*if (backNum != NULL && backNum < pre)//아직 끝에 도달하지 못했어. 그리고 이제 pre의 주소와 같거나, pre의 주소보다 뒤면
	{
		backNum->num = backNum - 1; //하나씩 줄입시다
		*autoNumber = *autoNumber - 1;
	}*/
	L->length--; //빠졌으니 길이 줄이기
	printf("과제 %d번을 삭제하였습니다!\n", want);

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

		//listwork* pre = NULL; //수정 거의 앞을 가리키는 pre(앞 노드) (? 이거 안필요할듯)
		listwork* hun = L->head; //현재

		while (hun != NULL && hun->num != mynum) //NULL이 아닌데, 수정하려던 번호가 아니면
		{
			hun = hun->next; //다음 번호로 넘어가기
		}

		if (hun == NULL)//NULL이면(비어있으면) ==========================이거 순서 중요할라나 엉 중요하네
		{
			printf("%d번째 과제는 존재하지 않습니다. 다시 입력해 주십시오.\n", mynum);
			continue; //써도 됐는지 기억이 안난다.
			//break는 그냥 Rework 함수를 끝내버린다...주의ㅣ..
			
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
				printf("새 과목명: ");
				scanf("%s", NewSubject);
				strcpy(hun->Subject, NewSubject); //strcpy! 잘 되련가 진짜 다 잊었네 큰일났다앗 검색해서 알았네
				printf("\n");
				break;
			}
			case 2:
			{
				printf("과제명: ");
				scanf("%s", NewWork);
				strcpy(hun->workname, NewWork);
				printf("\n");
				break;
			}
			case 3:
			{
				printf("새 마감 년도: ");
				scanf("%d", &NewYear);
				hun->year= NewYear; //문자열이 strcpy~ 
				printf("\n");
				break;
			}
			case 4:
			{
				printf("마감 월: ");
				scanf("%d", &NewMonth);
				hun->month = NewMonth;
				printf("\n");
				break;
			}
			case 5:
			{
				printf("마감 날짜(일): ");
				scanf("%d", &NewDay);
				hun->day = NewDay;
				printf("\n");
				break;
			}
			case 6:
			{
				printf("마감 시간(시): ");
				scanf("%d", &NewHour);
				hun->hour =  NewHour;
				printf("\n");
				break;
			}
			case 7:
			{
				printf("마감 분: ");
				scanf("%d", &NewMin);
				hun->minu = NewMin;
				printf("\n");
				break;
			}
			case 8:
			{
				printf("제출 여부: ");
				scanf("%s", NewSend);//send는 문자열...배열...
				strcpy(hun->send, NewSend);
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
			//바로 나가게할까 아니면 여기서도 선택지를 줄까...
			//printf("더 수정하시겠습니까?\n");
			//printf("(1) 예           (2) 아니오");
			//그냥 나가자
			run = 0;
		}
	
	}//while


}
//====================================이 위는 과제 수정하는 함수=======================================
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
/*
int ISZero(linkedlist* L, int lastyear)
{
	if (lastyear < 0) //얘까지 빼면 안돌아가고
	{

		want = w.num; //이런 애의 번호가 타깃이 된다.
	}
	if (lastyear == 0 && lastmonth < 0)
	{
		want = w.num;//목표
	}
	if (lastyear == 0 && lastmonth == 0 && lastday < 0)
	{
		want = w.num;//목표의 번호
	}
	if (lastyear == 0 && lastmonth == 0 && lastday == 0 && lasthour < 0)
	{
		want = w.num;//목표의 번호를 want로 두기
	}//이건 또 뺴면 돌아가네?? 뭐지
	if (lastyear == 0 && lastmonth == 0 && lastday == 0 && lasthour == 0 && lastmin < 0)
	{
		want = w.num;//목표번호
	}
}*/

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
	int run = 0;
	listwork* pre = NULL; //hun의 이전 노드(내가 지우려는 거의 이전 노드)
	listwork* hun = L->head; //현재 노드

	listwork* backNum;// 숫자 빠질 시 뒤 리스트들의 숫자를 줄이기 위해 만듦

	while (hun != NULL) //끝까지 도달하기 전까지 계속 실행
	{
		time_t current_tm = time(NULL);
		struct tm tm = *localtime(&current_tm);

		int minmin = hun->minu; //현재 있는 노드 기준으로 봐야하니까...
		int houror = hun->hour;
		int monthth = hun->month;
		int dayday = hun->day;
		int yearar = hun->year;


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
	//istwork* pre = NULL; //hun의 이전 노드(내가 지우려는 거의 이전 노드)
	//istwork* hun = L->head; //현재 노드
	// int deletecount = 0;//지운거 개수만큼 뒤에 노드 숫자 줄여줘야함
		//잊지마시게~!
		if (run == 1)//목표번호가 생겼으면...
		{
			if (pre == NULL) //내 앞이 head.(내가 1번)
			{
				L->head = hun->next; //Deletework 참조 근데 이건 왜 필요하더라

				listwork* Deletehun = hun;// ************
				backNum = hun->next; // 숫자 빠질 시 뒤 리스트들의 숫자를 줄이기 위해 만듦

				hun = hun->next; //다음으로. hun삭제
				
				//free(hun);  여기서 쓰면 hunnext가 사라져버림...  그럼 hun어떻게 없애지
				free(Deletehun);// free부분은 AI도움 받았습니다.

				while (backNum != NULL)
				{
					backNum->num = backNum->num - 1; //숫자 감소해라
					backNum = backNum->next; //다음칸으로 계속 이동
				}
				*autoNumber = *autoNumber - 1; //숫자 하나 감소
				deletecount = deletecount + 1;
				

				
			}
			else //head가 아니면
			{
				listwork* Deletehun = hun;// ************
				backNum = hun->next; // 숫자 빠질 시 뒤 리스트들의 숫자를 줄이기 위해 선언.

				pre->next = hun->next; //다음으로 연결=> hun(현재)가 사라짐
				hun = hun->next;
				//현상태  pre | (지울거.) | next.(=hun)(=pre의 다음 노드)
				
				//free(hun);//얘도 위처럼...
				free(Deletehun);

				while (backNum != NULL)
				{
					backNum->num = backNum->num - 1; //숫자 감소해라
					backNum = backNum->next; //다음칸으로 계속 이동
				}
				*autoNumber = *autoNumber - 1; //숫자 하나 감소
				deletecount = deletecount + 1;
			}
			
			L->length--;
			
		}
		else //목표번호가 안 생겼으면
		{
			pre = hun;
			hun = hun->next; //계속 순회
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
	
}

//=======================================
int main()
{

	linkedlist* L = (linkedlist*)malloc(sizeof(linkedlist)); //공간 할당
	//listwork* w;
	listwork w = { 0 };
	L->head = NULL;
	L->length = 0;//기본 0

	int choice;
	//int first;
	//int second;
	int run = 1;//계속 선택 진행이 가능하도록 함.

	int* autoNumber = 1; //IMSI

	printf("현재 과제 목록\n");
	//리스트 쫙 보여주기
	while (run)
	{
		displayList(L);
		//AddWork(L, 1, "프실", "기말", 2025, 12, 2, 14, 00, "아니오");//번호과목명과제이름년월일시간분

		printf("(1) 마감까지 남은 시간 보기\n");
		printf("(2) 알림 시간대 설정\n");
		printf("(3) 과제 추가\n");
		printf("(4) 과제 삭제\n");
		printf("(5) 과제 수정\n");
		printf("(6) 과제 검색\n");
		printf("(7) 기간 지난 과제 일괄삭제\n");
		printf("(0) 종료\n");

		printf("선택: ");
		scanf("%d", &choice);

		switch (choice)//어디서부터 꼬인거야~
		{
		case 1: //마감까지 남은 시간 보기
		{
			listwork* myworklist = L->head;
			if (myworklist == NULL) //과제있니
			{
				printf("과제가 존재하지 않습니다.\n");//없으면 출력
			}
			else//있으면
			{
				while (myworklist != NULL)//끝까지 다
				{
					LastTime(*myworklist);//시간출력
					myworklist = myworklist->next; //다음이동하면서 출력
				}
			}
			//time_t timer = time(NULL);//time.h, timer...   /timer을 struct tm 값으로 변환
			//struct tm tm = *localtime(&timer);//time.h, tm...   time_t와 localtime은 둘다 time.h라이브러리의 함수
			//LastTime(w);
			break;
		}
		case 2: //알림 시간대 설정
		{
			break;
		}
		case 3: //과제 추가
		{
			//일단 만들어두기
			//위로옮김

			AddWork(L,&autoNumber);
			
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
		case 6: //과제 검색
		{
			break;
		}
		case 7: //기간 지난 과제 일괄 살제
		{
			LastClear(L, &autoNumber);
			break;
		}
		case 0: //종료
		{
			printf("프로그램을 종료합니다.\n"); //여기다가 그 SDL써도 되려나??
			run = 0;
			break;
		}
		}//잠만... 알림기능 어디감?
	}
	free(L);//... 필요?
	return 0;
}