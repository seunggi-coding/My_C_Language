//제목 : 프로젝트4 - 이벤트 시뮬레이션
//작성자 : 문승기
//날짜 : 2020.06.19

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable:4996)

#define MAX_QUEUE_SIZE 100

typedef struct {
	int id;
	int tEvent;
	int tService;
} Event;

typedef Event element;
typedef struct {
	int front;
	int rear;
	element data[MAX_QUEUE_SIZE];
} QueueType;

int tSimulation;		//시뮬레이션 시간
double probEvent;		//단위시간(1초)에 이벤트가 발생할 확률
int tMaxService;		//한 이벤트에 대한 최대 처리 시간
int totalWaitTime;		//전체 대기 시간
int nEvents;			//전체 이벤트의 수
int nServedEvents;		//처리된 전체 이벤트의 수

double unitRand() {
	return (rand() / (double)RAND_MAX);
}

void error(char* message) {
	fprintf(stderr, "%s\n", message);
}

void init_queue(QueueType* q) {
	q->rear = 0;
	q->front = 0;
}

int is_full(QueueType* q) {
	return (q->front == (q->rear + 1) % MAX_QUEUE_SIZE);
}

int is_empty(QueueType* q) {
	return (q->front == q->rear);
}

void enqueue(QueueType* q, element item) {
	if (is_full(q)) {
		error("큐가 포화상태입니다.");
		return;
	}
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType* q) {
	if (is_empty(q)) {
		error("큐가 공백상태입니다.");
		exit(1);
	}
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

void insertEvent(QueueType* q, int eventTime) {
	//슬라이드 36의 내용을 수행하는 코드 작성
	Event q_two;

	nEvents++;
	q_two.id = nEvents;
	q_two.tEvent = eventTime;
	q_two.tService = (int)(unitRand() * tMaxService);
	enqueue(q, q_two);
	//이벤트 발생 내용 출력
	printf(" 이벤트 %d 발생 (처리시간: %d초)\n", q_two.id, q_two.tService);
}

int main() {
	QueueType q;
	init_queue(&q);
	Event a;							//큐에서 꺼낸 이벤트를 저장
	int serviceTime = 0;				//현재 처리 중인 이벤트의 남은 처리 시간
	int sec;

	srand((unsigned int)time(NULL));

	totalWaitTime = 0;					//전체 대기시간
	nEvents = 0;						//전체 이벤트의 수
	nServedEvents = 0;					//처리된 이벤트의 수

	//시뮬레이션 파라미터 입력
	printf("시뮬레이션 할 최대 시간 (단위:초) = ");
	scanf("%d", &tSimulation);
	printf("단위시간(1초)에 이벤트가 발생할 확률 (예:0.1) = ");
	scanf("%lf", &probEvent);
	printf("한 이벤트에 대한 최대 처리 시간 (단위:초) = ");
	scanf("%d", &tMaxService);
	printf("================================================================\n");

	//시뮬레이션 수행 (for-loop 사용) (슬라이드 37과 햄버거 시뮬레이션 참조)
	for (sec = 0; sec < tSimulation; sec++) {
		printf("현재 시간: %d\n", sec);

		//이벤트 발생 여부 확인
		if (unitRand() <= probEvent) {
			insertEvent(&q, sec);
		}
		if (serviceTime <= 0 && !is_empty(&q)) {
			//현재 처리 중인 이벤트가 없고, 처리할 이벤트가 큐에 있으면 해당 이벤트 처리 시작
			//serviceTime을 1 감소
			a = dequeue(&q);
			nServedEvents++;
			totalWaitTime += (sec - a.tEvent);
			serviceTime = a.tService;
			//serviceTime = q.data[nServedEvents].tService;
			printf(" 이벤트 %d 처리 시작 (대기시간:%d초)\n", a.id, sec - a.tEvent);
			//printf(" 이벤트 %d 처리 시작 (대기시간:%d초)\n", a.id, sec - q.data[q.front].tEvent);
		}
		serviceTime--;
	}
	//시뮬레이션 결과 출력
	printf("================================================================\n");
	printf("Simulation Report!\n\n");
	printf(" 처리된 이벤트 수\t = %d\n", nServedEvents);
	printf(" 전체 대기 시간\t\t = %d초\n", totalWaitTime);
	printf(" 이벤트 당 평균대기시간\t = %.2f 초\n", ((double)totalWaitTime / (double)nServedEvents));
	printf(" 현재 대기 이벤트 수\t = %d\n", nEvents - nServedEvents);
}