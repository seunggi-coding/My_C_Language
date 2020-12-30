#include <stdio.h>
#pragma warning(disable:4996)
#define MAX_N 100000

int price[MAX_N + 1];			//최대 데이터 수
int result = 0;						//각 테스트 결과에 대한 결과
int N = 0;							//옷의 개수

//선택정렬에서 최소값을 찾아 맨 앞부터 정렬, 3개씩 묶음
void Descending_order_sort(int a[], int n) {
	int i = 0, j = 0, tmp = 0;
	for (i = 0; i < n - 1; i++) {
		for (j = i + 1; j < n; j++) {
			if (a[i] < a[j]) {
				tmp = a[j];
				a[j] = a[i];
				a[i] = tmp;
			}
		}
	}

	for (int p = 0; p < n; p++) {
		if (n % 3 == 0) {
			if (p % 3 == 0)
				result += (a[p] + a[p + 1]);
		}
		else if (n % 3 != 0) {
			if (p % 3 == 0) {
				result += (a[p] + a[p + 1]);

				if (n % 3 == 1 && p == n) {
					result += a[n - 1];
					break;
				}
			}
		}
		else if (n < 3) {
			for (int k = 0; k < n; k++) {
				result += a[k];
			}
		}
	}
}
	

int main() {
	int T;

	freopen("input.txt", "r", stdin);
	scanf("%d", &T);

	for (int i = 0; i < T; i++) {
		scanf("%d", &N);

		for (int j = 0; j < N; j++) {
			scanf("%d", &price[j]);
		}

		//각 테스트 케이스에 대한 경우의 수 구하고, 출력하기
		result = 0;
		Descending_order_sort(price, N);
		printf("%d\n", result);
	}
}