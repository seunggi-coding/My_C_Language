#include <stdio.h>
#pragma warning(disable:4996)
#define MAX_N 15

int weight[MAX_N + 1];				//학생 몸무게 데이터
int result = 0;						//각 테스트 결과에 대한 결과(경우의 수)
int N = 0;							//학생 수

void countTeams(int h, int wA, int wB, int wC) {
	//Base case: 모든 학생들을 팀에 넣은 후, A, B, C팀의 몸무게가 같은 경우 result 1 증가
	//h번째 학생을 팀 A/ 팀 B/ 팀 C/ 아무팀에도 안 넣는 경우(4가지)에 대해 재귀 호출
	int sum1 = 0; int sum2 = 0; int sum3 = 0;
	if (h == 0) {
		if (wA == wB && wB == wC && wC == wA) {
			result += 1;
		}
	}
	else {
		sum1 = wA + weight[h];
		countTeams(h - 1, sum1, wB, wC);

		sum2 = wB + weight[h];
		countTeams(h - 1, wA, sum2, wC);

		sum3 = wC + weight[h];
		countTeams(h - 1, wA, wB, sum3);

		countTeams(h - 1, wA, wB, wC);
	}
}

int main() {
	int T;

	freopen("input.txt", "r", stdin);
	scanf("%d", &T);

	for (int i = 0; i < T; i++) {
		scanf("%d", &N);

		for (int j = 1; j <= N; j++) {
			scanf("%d", &weight[j]);
		}

		//각 테스트 케이스에 대한 경우의 수 구하고, 출력하기
		result = 0;
		countTeams(N, 0, 0, 0);
		printf("%d\n", result);
	}
}