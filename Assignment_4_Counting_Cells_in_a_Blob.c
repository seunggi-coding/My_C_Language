#include <stdio.h>
#define BACKGROUND_PIXEL 0
#define IMAGE_PIXEL 1
#define COUNTED 2

int cells[][8] = {
	{0, 0, 1, 0, 0, 0, 0, 1},
	{1, 1, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 0, 1, 0, 1, 0},
	{0, 0, 0, 0, 0, 1, 0, 0},
	{0, 1, 0, 1, 0, 1, 0, 0},
	{0, 1, 0, 1, 0, 1, 0, 0},
	{1, 0, 0, 0, 1, 1, 0, 0},
	{0, 1, 1, 0, 0, 0, 1, 1}
};

int countCells(int x, int y) {
	//알고리즘 구현 p.34
	int count_num = 0;

	if (cells[x][y] == BACKGROUND_PIXEL)
		return 0;
	if (cells[x][y] == COUNTED)
		return 0;
	if (x < 0 || x > 7 || y < 0 || y > 7)
		return 0;

	if (cells[x][y] == IMAGE_PIXEL) {
		cells[x][y] = COUNTED;
		count_num = 1;
		return count_num + countCells(x - 1, y) + 
				 countCells(x - 1, y + 1) + countCells(x, y + 1) +
				 countCells(x + 1, y + 1) + countCells(x + 1, y) + 
				 countCells(x + 1, y - 1) + countCells(x, y - 1) +
				 countCells(x - 1, y - 1);	
	}
}

int main() {
	printf("%d\n", countCells(3, 5));
}