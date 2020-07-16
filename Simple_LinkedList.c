//제목 : 프로젝트2_단순연결리스트
//작성자 : 문승기
//날짜 : 2020.05.25

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct name_card {
	char name[20];
	int id;
	struct name_card* link;
} Namecard;

Namecard* head;			//헤드포인터

//pos 위치의 노드(에 대한 포인터)를 찾는 함수
//반환값이 NULL이면, pos 위치의 노드를 찾지 못한 것임
//반환값잉 NULL이 아니면, pos 위치의 노드를 찾은 것임
Namecard* getNode(int pos) {
	Namecard* p;

	p = head;
	for (int i = 0; i < pos; i++) {
		if (p == NULL) {		//위치 오류(해당 되는 위치의 노드가 없음
			return NULL;		//호출함수는 없는 위치이므로, 에러 처리하여야 함
		}
		p = p->link;
	}
	return p;
}
Namecard make_Namecard(char name[], int id) {	//Namecard 생성 함수
	Namecard newCard;

	strcpy(newCard.name, name);
	newCard.id = id;
	newCard.link = NULL;

	return newCard;
}

//1번째 연산
void init() {
	Namecard* p, * removed;
	
	for (p = head; p != NULL;) {
		removed = p;
		p = p->link;
		free(removed);
	}

	head = NULL;
}

/************* 나머지 연산(함수) 구현 *************/

//2번째 연산
int is_empty() {
	if (head == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

//3번째 연산
void insert(int pos, Namecard item) {
	Namecard* new;
	Namecard* pre = getNode(pos - 1);

	new = (Namecard*)malloc(sizeof(Namecard));
	strcpy(new->name, item.name);
	new->id = item.id;

	if (pos == 0) {
		if (head == NULL) {
			head = new;
			new->link = NULL;

		}
		else {
			new->link = getNode(pos);
			head = new;
		}				
	}
	else {
		if (pre != NULL) {
			new->link = pre->link;
			pre->link = new;
		}
	}
	if(pos > size()) {
		printf("삽입 위치 오류\n");
	}
}

//4번째 연산
void delete(int pos) {
	Namecard* pre = NULL;
	Namecard* removed = NULL;

	if (head == NULL) {
		printf("공백상태 오류\n");
	}
	else if (pos == 0) {
		removed = head;
		head = removed->link;
		free(removed);
	}
	else {
		if (getNode(pos) != NULL) {
			pre = getNode(pos - 1);
			removed = pre->link;
			pre->link = removed->link;
			free(removed);
		}
	}
	if (pos > size()) {
		printf("삭제 위치 오류\n");
	}
}

//5번째 연산
Namecard get_entry(int pos) {
	if (getNode(pos) != NULL) {
		return *getNode(pos);
	}
}

//6번째 연산
int find(Namecard item) {
	int n = 0;
	for (int i = 0; i < size(); i++) {
		if ((strcmp(getNode(i)->name, item.name) == 0) && getNode(i)->id == item.id) {
			n = i;
		}
		else {
			n = -1;
		}
	}
	return n;
}

//7번째 연산
void replace(int pos, Namecard item) {
	Namecard *p;
	for (p = head; p != NULL; p = p->link) {
		if (is_empty() == 0 && pos >= 0 && pos < size()) {
			strcpy(getNode(pos)->name, item.name);
			getNode(pos)->id = item.id;
		}
	}
	if (pos > size()) {
		printf("교체 위치 오류\n");
	}
}

//8번째 연산
int size() {
	Namecard* p;
	int j = 0;
	for (p = head; p != NULL; p = p->link) {
		j = j + 1;
	}
	return j;
}

//9번째 연산
void print_list(char* msg) {
	Namecard* p;

	printf("%s: ", msg);
	for (p = head; p != NULL; ) {
		printf("(%s, %d) ", p->name, p->id);
		p = p->link;
	}
	printf("\n\n");
}

int main() {
	init();
	print_list("Init");

	insert(0, make_Namecard("문승기", 20191516));
	insert(0, make_Namecard("김래훈", 20191520));
	insert(1, make_Namecard("임태윤", 20191507));
	insert(size(), make_Namecard("박찬형", 20191546));
	insert(3, make_Namecard("박동준", 20191528));
	insert(size(), make_Namecard("유용기", 20191513));
	insert(10, make_Namecard("권기현", 20191518));
	print_list("Insert");

	replace(size() - 1, make_Namecard("장승종", 20191544));
	replace(4, make_Namecard("유일한", 20191539));
	replace(20, make_Namecard("성도영", 20191530));
	print_list("Replace");

	delete(3);
	delete(size() - 1);
	delete(0);
	delete(30);
	print_list("Delete");

	printf("%s is found at %d\n", "유일한", find(make_Namecard("유일한", 20191539)));
	printf("%s is found at %d\n", "전시온", find(make_Namecard("전시온", 20191545)));

	Namecard temp = get_entry(1);
	printf("\nEntry 1: (%s, %d)\n", temp.name, temp.id);
}