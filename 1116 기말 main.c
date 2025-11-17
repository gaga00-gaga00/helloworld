#include <stdio.h>
#include <math.h>
#include "Pj.h"

//일단 메인을 다 짜고 분리해버리자!!!

//======================================
typedef struct ListWork {
	int num; //번호(과제번호)
	char Subject[30]; //과목명
	char workname[50];//과제명
	unsigned int day; //마감일 날
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

void insertList(linkedlist* L, listwork w)
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

void AddWork(linkedlist* L, listwork w) //과제 추가 기능! scanf 이용
{
	listwork w;

	printf("과제 번호: "); //근데 이걸 써야하나? 자동으로 입력되게 할 수는 없나?
	scanf("%d", &w.num); //일단 과제 번호 입력

	printf("과목명: ");
	scanf("%s", &w.Subject);

	printf("과제명: ");
	scanf("%s", &w.workname);

	printf("마감 날짜: ");
	scanf("%s", &w.day);

	printf("마감 시간: ");
	scanf("%s", &w.hour);

	printf("마감 분: "); //좀 더 편하게 쓸 수 있는 방법이 없을까
	scanf("%s", &w.minu);

	printf("제출 여부: ");
	scanf("%s", &w.send);

	w.next = NULL; //새 노드가 리스트의 끝이라는 뜻.
	insertList(L, w); //inserList 불러옴

	printf("\n");
	printf("과제가 추가되었습니다!\n");
}
//=======================================

void DeleteWork(linkedlist* L, listwork* w)
{
	listwork* pre; //지우려는 거의 앞을 가리키는 pre
	int want;

	if (L->head == NULL) //리스트가 비어있다면
	{
		printf("삭제할 과제가 존재하지 않습니다.\n");
		return;
	}

	if (w == NULL)
	{
		printf("삭제할 과제가 존재하지 않습니다.\n");
		return;
	}//******

	printf("삭제할 과제 번호를 입력하세요: ");//번호? 과제 이름? 과목명?
	scanf("%d", &want);
	//뭔가 원하던것과 다르다!

	pre = L->head;
	while (pre != NULL && pre->num != want) //NULL이 아닌데, 삭제하려던 번호가 아니면
	{
		pre = pre->next; //다음 넘어가기
	}
	if (pre == NULL)//NULL이면(비어있으면)
	{
		printf("과제 번호 %d를 찾을 수 없습니다.\n", want);
		return;
	}

	//어떻게 해야 찾을 수 있지?
	//printf("과제 %d번을 삭제하였습니다.\n", want);
		return 0;


	/*if (L->head == w)//삭제하려는게 헤드였으면
	{
		L->head = w->next; 
	}
	else//헤드가 아니었으면
	{
		pre = L->head;//head가 가리기는걸 pre가 가리키도록 함
		while (pre->next != w)//삭제하려는 것의 주소가 나오기 전까지 이동
		{
			pre = pre->next; //뒤로 계속 이동
			if (pre == NULL)//만약 없으면
			{
				return 0;
			}
		}
		return 1;
		
	}
	//======
	*/
}

//=======================================
void main() 
{
	
	linkedlist* L = (linkedlist*)malloc(sizeof(linkedlist)); //공간 할당
	listwork* w;


	int choice;
	//int first;
	//int second;

	printf("현재 과제 목록\n");
	//리스트 쫙 보여주기

	printf("(1) 마감까지 남은 시간 보기\n");
	printf("(2) 알림 시간대 설정\n");
	printf("(3) 과제 추가\n");
	printf("(4) 과제 삭제\n");
	printf("(5) 과제 수정\n");
	printf("(6) 과제 검색\n");
	printf("(7) 기간 지난 과제 일괄삭제\n");
	printf("(0) 종료\n");

	scanf("%d", &choice);

	switch (choice)//어디서부터 꼬인거야~
	{
	case 1: //마감까지 남은 시간 보기
	{
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
		AddWork(L);
		break;
	}
	case 4: //과제 삭제
	{
		break;
	}
	case 5: //과제 수정
	{
		break;
	}
	case 6: //과제 검색
	{
		break;
	}
	case 7: //기간 지난 과제 일괄 살제
	{
		break;
	}
	case 0: //종료
	{
		break;
	}
	}
}