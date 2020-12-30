#include <stdio.h>
#pragma warning(disable:4996)
#define MAX_N 1000

int arrlen[MAX_N + 1];
int result = 0;
int N = 0;

int main() {
	int T;
	int temp = 0;
	int sum[15];
	int sum1 = 0;

	freopen("input.txt", "r", stdin);
	scanf("%d", &T);

	for (int i = 0; i < T; i++) {
		scanf("%d", &N);

		for (int j = 0; j < N; j++) {
			scanf("%d", &arrlen[j]);
		}
		for (int k = 0; k < N; k++) {
			sum[k] = 0;
		}

		//각 테스트 케이스에 대한 경우의 수 구하고, 출력하기
		result = 0;
		//Bubble Sort를 활용해서 오름차순으로 정렬한 후 앞의 두 개부터 순서대로 더한다.
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N - i - 1; j++) {
				if (arrlen[j] > arrlen[j + 1]) {
					temp = arrlen[j];
					arrlen[j] = arrlen[j + 1];
					arrlen[j + 1] = temp;
				}
			}
		}
		for (int i = 0; i < N; i++) {
			printf("%d ", arrlen[i]);
		}
		printf("\n");

		for (int i = 0; i < N - 2; i = i + 2) {
			for (int j = 0; j < N - 1; j++) {
				sum1 = arrlen[i] + arrlen[i + 1];
				sum[j] = sum1 + arrlen[i];
				printf("arrlen[%d] : %d ", i, arrlen[i]);
				printf("sum[%d] : %d\n", j, sum[j]);
			}
		} 

		for (int n = 0; n < N; n++) {
			result += sum[n];
		}
		printf("%d\n", result);
	}
}