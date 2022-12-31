#include "graphics.h"
#include <iostream>
#include <conio.h>
#include <dos.h>
#pragma comment(lib, "graphics.lib")

using namespace std;

struct Record {
	char data;
	int key;
};

Record R[100];
int n;
int radius = 25;

void importArray(Record R[], int& n) {
	cout << "Enter the number of elements: ";
	cin >> n;
	do {
		if (n <= 1) {
			cout << "Invalid value. Please re-enter." << endl;
			cin >> n;
		}
	} while (n <= 1);
	cout << "Enter the elements: ";
	for (int i = 0; i < n; i++)
		cin >> R[i].key;
}

void exportArray(Record R[], int n) {
	for (int i = 0; i < n; i++)
		cout << R[i].key << " ";
	cout << endl;
}

void drawCircle(int x, int y, int color) {
	setcolor(color);
	circle(x, y, radius);
}

void writeText(int x, int y, int data, int color) {
	stringstream ss;
	ss << data;
	string s = ss.str();
	char* t = (char*)s.c_str();
	setcolor(color);
	outtextxy(x, y, t);
}

void drawBox(int x, int y, int data, int color) {
	drawCircle(x, y, color);
	writeText(x, y, data, color);
}

void drawMulticolorBox(int x, int y, int data, int colorCircle, int colorText) {
	drawCircle(x, y, colorCircle);
	writeText(x, y, data, colorText);
}

void glowText(int x, int y, int data) {
	int j = 1;
	while (j != 50) {
		writeText(x, y, data, j);
		delay(10);
		j++;
	}
	writeText(x, y, data, WHITE);
}

void glowBox(int x, int y, int data) {
	int j = 1;
	while (j != 50) {
		setcolor(j);
		j++;
		drawBox(x, y, data, j);
		delay(1);
	}
	drawBox(x, y, data, WHITE);
}

void drawArray(Record R[], int n, int x, int y, int color) {
	string index = "Index: ";
	char* indx = (char*)index.c_str();
	setcolor(color);
	outtextxy(50, y - 50, indx);
	//Write array indexes
	for (int i = 0; i < n; i++)
		writeText(x + 50 * i + 50, y - 50, i, color);
	//Draw array
	for (int i = 0; i < n; i++) {
		if (i == 0)
			drawBox(x + 50, y, R[i].key, color);
		else
			drawBox(x + 50 * i + 50, y, R[i].key, color);
	}
}

void drawMergeArray(Record R[], int n, int x, int y, int color) {
	string index = "Index: ";
	char* indx = (char*)index.c_str();
	setcolor(color);
	outtextxy(200, y - 100, indx);
	//Write array indexes
	for (int i = 0; i < n; i++)
		writeText(x + 50 * i + 50, y - 100, i, color);
	//Draw array
	for (int i = 0; i < n; i++) {
		if (i == 0)
			drawBox(x + 50, y, R[i].key, color);
		else
			drawBox(x + 50 * i + 50, y, R[i].key, color);
	}
}

void deleteBox(int x, int y, int data) {
	drawBox(x, y, data, BLACK);
}
// Swap boxes in an array
void swapBox(int x1, int y1, int data1, int color1, int x2, int data2, int color2) {
	int y2 = y1;
	int y = y1;
	int x = x1;
	for (int i = 1; i <= 50; i++) {
		deleteBox(x1, y1, data1);
		y1--;
		drawBox(x1, y1, data1, color1);
		deleteBox(x2, y2, data2);
		y2++;
		drawBox(x2, y2, data2, color2);
		delay(1);
	}
	while (x2 != x) {
		deleteBox(x1, y1, data1);
		x1++;
		drawBox(x1, y1, data1, color1);
		deleteBox(x2, y2, data2);
		x2--;
		drawBox(x2, y2, data2, color2);
	}
	for (int i = 1; i <= 50; i++) {
		deleteBox(x1, y1, data1);
		y1++;
		drawBox(x1, y1, data1, color1);
		deleteBox(x2, y2, data2);
		y2--;
		drawBox(x2, y2, data2, color2);
		delay(1);
	}
}

void comparison(int x, int y, int i, int j, int color, int colorNum) {
	char q1[] = "Key[ ";
	char q2[] = " ] < Key[ ";
	char q3[] = " ] ?";
	setcolor(color);
	outtextxy(x, y, q1);
	writeText(x + 40, y, i, colorNum);
	setcolor(color);
	outtextxy(x + 50, y, q2);
	writeText(x + 115, y, j, colorNum);
	setcolor(color);
	outtextxy(x + 125, y, q3);
}
//													COMPARISON COUNTING SORT VISUALIZATION
void countingSortVisualize(Record R[], int n) {
	Record Count[100];
	Record Output[10];
	for (int i = 0; i < n; i++) {
		Count[i].key = 0;
		Output[i].key = 0;
	}

	setcolor(LIGHTGRAY);
	char array[] = "Unsorted Array: ";
	outtextxy(50, 0, array);
	drawArray(R, n, 100, 75, LIGHTGRAY);
	delay(100);

	char countArray[] = "Count Array with [n] Zero elements: ";
	outtextxy(50, 125, countArray);
	delay(100);
	drawArray(Count, n, 100, 200, LIGHTGRAY);
	delay(200);

	char outputArray[] = "Empty Output Array with [n] elements: ";
	outtextxy(50, 275, outputArray);
	drawArray(Output, n, 100, 350, LIGHTGRAY);
	delay(100);

	char plus[] = "+";
	char deleteOneChar[] = "  ";

	char countArr[] = "Count Array:                                      ";
	outtextxy(50, 125, countArr);
	for (int i = n - 1; i >= 1; i--) {
		for (int j = i - 1; j >= 0; j--) {
			comparison(350, 115, i, j, LIGHTGRAY, YELLOW);
			if (R[i].key < R[j].key) {
				glowBox(100 + 50 * i + 50, 75, R[i].key);
				delay(100);
				glowBox(100 + 50 * j + 50, 75, R[j].key);
				delay(100);
				comparison(350, 115, i, j, LIGHTGREEN, LIGHTGREEN);
				delay(100);
				glowBox(100 + 50 * j + 50, 200, Count[j].key);
				setcolor(LIGHTGREEN);
				outtextxy(100 + 50 * j + 50, 225, plus);
				delay(100);
				Count[j].key++;
				drawBox(100 + 50 * j + 50, 200, Count[j].key, LIGHTGREEN);
				delay(100);
				outtextxy(100 + 50 * j + 50, 225, deleteOneChar);
			}
			else {
				glowBox(100 + 50 * i + 50, 75, R[i].key);
				delay(100);
				glowBox(100 + 50 * j + 50, 75, R[j].key);
				delay(100);
				comparison(350, 115, i, j, LIGHTRED, LIGHTRED);
				delay(100);
				glowBox(100 + 50 * i + 50, 200, Count[i].key);
				setcolor(LIGHTRED);
				outtextxy(100 + 50 * i + 50, 225, plus);
				delay(100);
				Count[i].key++;
				drawBox(100 + 50 * i + 50, 200, Count[i].key, LIGHTRED);
				delay(100);
				outtextxy(100 + 50 * i + 50, 225, deleteOneChar);
			}
		}
	}
	//Set everything back to normal
	drawArray(R, n, 100, 75, LIGHTGRAY);
	drawArray(Count, n, 100, 200, LIGHTGRAY);
	char noirSpace[] = "                                                                                                                                                                                         ";
	outtextxy(100, 115, noirSpace);

	char outputFinal[] = "Output Array:                                                              ";
	outtextxy(50, 275, outputFinal);
	delay(1000);
	//Form the Output array
	for (int i = 0; i < n; i++) {
		Output[Count[i].key].key = R[i].key;
		glowBox(100 + 50 * i + 50, 200, Count[i].key);
		delay(100);
		glowBox(100 + 50 * Count[i].key + 50, 350, 0);
		delay(100);
		glowBox(100 + 50 * i + 50, 75, R[i].key);
		delay(100);
		drawMulticolorBox(100 + 50 * Count[i].key + 50, 350, Output[Count[i].key].key, LIGHTGRAY, YELLOW);
		delay(100);
		//Export the array in Console
		exportArray(Output, n);
	}
	//Finish Stage
	drawArray(Output, n, 100, 350, YELLOW);
	int j = 1;
	char fin[] = "FINISH.";
	while (1) {
		setcolor(j);
		outtextxy(100 + n * 50 / 2, 450, fin);
		delay(10);
		j++;
	}
	system("pause");
}
//															End Comparison Counting.
//														MERGE-EXCHANGE SORT VISUALIZATION
// Find t - 1
int findTsubOne(int value) {
	int result = -1;
	for (int i = 1; i < value; i <<= 1, ++result);  //i *= 2
	return result;
}

void mergeSortVisualize(Record R[], int n) {
	setcolor(LIGHTGRAY);
	char unsorted[] = "Array: ";
	outtextxy(200, 25, unsorted);
	drawMergeArray(R, n, 350, 200, LIGHTGRAY);
	delay(100);

	int t = findTsubOne(n);
	char tt[] = "t = ";
	outtextxy(100, 100, tt);
	writeText(125, 100, t + 1, LIGHTGRAY);
	int p0 = (1 << t);  // p0 = 2^(t-1);
	int p = p0;
	char pp[] = "p = ";
	outtextxy(100, 125, pp);
	writeText(125, 125, p, LIGHTGRAY);

	char qq[] = "q = ";
	char rr[] = "r = ";
	char dd[] = "d = ";
	char ii[] = "i = ";
	char qEqualP[] = "q != p ?";
	char rEqual0[] = "r == 0 ?";
	char iANDpResult[] = "i ^ p = ";
	char iANDp[] = "i ^ p == r ?";
	int q, r, d;
	do {
		q = p0;
		setcolor(LIGHTGRAY);
		outtextxy(100, 150, qq);
		writeText(125, 150, q, LIGHTGRAY);
		r = 0;
		outtextxy(100, 175, rr);
		writeText(125, 175, r, LIGHTGRAY);
		d = p;
		outtextxy(100, 200, dd);
		writeText(125, 200, d, LIGHTGRAY);
		delay(100);

		while (r == 0 || q != p) {
			if (r != 0) {
				d = q - p;
				setcolor(LIGHTBLUE);
				outtextxy(100, 200, dd);
				writeText(125, 200, d, LIGHTBLUE);
				q >>= 1;    // q /= 2
				outtextxy(100, 150, qq);
				writeText(125, 150, q, LIGHTBLUE);
				delay(100);
			}

			for (int i = 0; i < n - d; i++) {
				int a = i & p;
				// i =
				setcolor(LIGHTGRAY);
				outtextxy(100, 300, ii);
				writeText(120, 300, i, LIGHTGRAY);
				delay(100);
				// i ^ p = 
				setcolor(LIGHTGRAY);
				outtextxy(100, 350, iANDpResult);
				glowText(350 + 50 * i + 50, 100, i);
				delay(100);
				glowText(125, 125, p);
				delay(100);
				outtextxy(100, 375, iANDp); // i ^ p == r ?
				delay(100);
				// A[i] > A[i+d] ?
				comparison(100, 400, i, d, LIGHTGRAY, YELLOW);
				delay(100);
				glowBox(350 + 50 * i + 50, 200, R[i].key);
				delay(100);
				glowBox(350 + 50 * (i + d) + 50, 200, R[i + d].key);
				writeText(140, 350, a, YELLOW);
				delay(100);
				if ((i & p) == r) {
					setcolor(LIGHTGREEN);
					outtextxy(100, 375, iANDp);
					delay(100);
					if (R[i].key > R[i + d].key) {
						comparison(100, 400, i, d, LIGHTGREEN, LIGHTGREEN);
						delay(100);
						swapBox(350 + 50 * i + 50, 200, R[i].key, WHITE, 350 + 50 * (i + d) + 50, R[i + d].key, WHITE);
						delay(100);
						int swap = R[i].key;
						R[i].key = R[i + d].key;
						R[i + d].key = swap;
						//Export the array in Console
						exportArray(R, n);
					}
					else {
						comparison(100, 400, i, d, LIGHTRED, LIGHTRED);
						delay(100);
					}
				}
				else {
					setcolor(LIGHTRED);
					outtextxy(100, 375, iANDp);
					delay(100);
					comparison(100, 400, i, d, LIGHTRED, LIGHTRED);
					delay(100);
				}
			}
			r = p;
			setcolor(WHITE);
			outtextxy(100, 175, rr);
			writeText(125, 175, r, WHITE);
			delay(100);
		}

		p >>= 1;    // p /= 2
		outtextxy(100, 125, pp);
		writeText(125, 125, p, WHITE);
	} while (p > 0);
	//Set everything back to normal
	char noirSpace[] = "                                                       ";
	setcolor(LIGHTGRAY);
	outtextxy(100, 125, pp);
	writeText(125, 125, p, LIGHTGRAY);
	outtextxy(100, 150, qq);
	writeText(125, 150, q, LIGHTGRAY);
	outtextxy(100, 175, rr);
	writeText(125, 175, r, LIGHTGRAY);
	outtextxy(100, 200, dd);
	writeText(125, 200, d, LIGHTGRAY);
	outtextxy(100, 300, noirSpace);
	outtextxy(100, 350, noirSpace);
	outtextxy(100, 375, noirSpace);
	outtextxy(100, 400, noirSpace);
	//Finish Stage
	drawMergeArray(R, n, 350, 200, YELLOW);
	char fin[] = "FINISH.";
	int j = 1;
	while (1) {
		setcolor(j);
		outtextxy(350 + n * 50 / 2, 400, fin);
		delay(10);
		j++;
	}
	system("pause");
}
//																End Merge-exchange.
void showConsoleMenu() {
	cout << "\n1. Comparison Counting Sort\n2. Merge-exchange Sort\n";
	int choice;
	cin >> choice;
	initwindow(1200, 600);
	switch (choice) {
	case 1:
		countingSortVisualize(R, n);
		break;
	case 2:
		mergeSortVisualize(R, n);
		break;
	}
	closegraph();
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	importArray(R, n);
	showConsoleMenu();
	return 0;
}