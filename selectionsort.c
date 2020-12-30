#include <stdio.h>

int array[10] = { 12, 35, 121, 52, 3, 4, 78, 9, 34, 23 };

int selectionSort(int a[], int n) {

	int tmp = 0;
	int largest = 0;

	for (int i = 0; i < n - 1; i++) {
		if (a[i] > a[i + 1]) {
			tmp = a[i];
			
		}
		else {
			tmp = a[i];
			a[i] = a[i + 1];
			a[i + 1] = tmp;
		}
	}
}

int main() {

}