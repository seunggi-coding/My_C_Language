//제목 : 리스트 ADT를 배열로 구현
//작성자 : 문승기
//날짜 : 2020.07.14
//ps. 과제로 만들었던 프로젝트1은 약간의 오류 존재.

#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)

#define MAX_IOT_LIST_SIZE 45

typedef struct {
	char name[20];
	int id;
} Namecard;

typedef struct {
	Namecard iot_list[MAX_IOT_LIST_SIZE];
	int length;
} IoT_List_Type;

IoT_List_Type L;

Namecard make_Namecard(char name[], int id) {
	Namecard newCard;

	strcpy(newCard.name, name);
	newCard.id = id;

	return newCard;
}

void init() {
	L.length = 0;
}

void insert(int pos, Namecard item) {
	int i;

	if (is_full() == 0 && pos >= 0 && pos <= L.length) {
		for (i = L.length; i > pos; i--) {
			L.iot_list[i] = L.iot_list[i - 1];
		}
		L.iot_list[pos] = item;
		L.length++;
	}
	else
		printf("포화상태 오류 또는 삽입 위치 오류\n");
}

void delete(int pos) {
	int i;
	
	if (is_empty() == 0 && pos >= 0 && pos < L.length) {
		for (i = pos; i < L.length - 1; i++) {
			L.iot_list[i] = L.iot_list[i + 1];
		}
		L.length--;
	}
	else
		printf("공백상태 오류 또는 삭제 위치 오류\n");
}

Namecard get_entry(int pos) {
	int i;

	for (i = 0; i < L.length; i++) {
		if (i == pos) {
			return L.iot_list[pos];
		}
	}
}

int is_empty() {
	if (L.length == 0)
		return 1;
	else
		return 0;
}

int is_full() {
	if (L.length == MAX_IOT_LIST_SIZE)
		return 1;
	else
		return 0;
}

int find(Namecard item) {
	int i;
	int n = 0;

	for (i = 0; i < L.length; i++) {
		if (item.id == L.iot_list[i].id && strcmp(item.name, L.iot_list[i].name) == 0) {
			return i;
		}
		else {
			n = -1;
		}
	}
	return n;
}

void replace(int pos, Namecard item) {
	if (is_empty() == 0 && pos >= 0 && pos < L.length) {
		L.iot_list[pos] = item;
	}
	else {
		printf("교체 위치 오류\n");
	}
}

int size() {
	return L.length;
}

void sort_list() {
	int i, j;
	Namecard temp;
	
	for (i = 0; i < L.length; i++) {
		for (j = i+1; j < L.length; j++) {
			if (L.iot_list[i].id > L.iot_list[j].id) {		/*앞의 인덱스가 뒤보다 크다면 큰 수를 뒤로 옮겨야 하기 때문*/
				temp = L.iot_list[j];
				L.iot_list[j] = L.iot_list[i];
				L.iot_list[i] = temp;
			}
		}
	}
}

void print_list(char* msg) {
	int i;
	printf("%s: ", msg);
	
	for (i = 0; i < L.length; i++) {
		printf("(%s, %d)", L.iot_list[i].name, L.iot_list[i].id);
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

	sort_list();
	print_list("Sort");

	printf("%s is found at %d\n", "유일한", find(make_Namecard("유일한", 20191539)));
	printf("%s is found at %d\n", "전시온", find(make_Namecard("전시온", 20191545)));
}