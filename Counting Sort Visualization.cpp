#include "graphics.h"
#include <iostream>
#include <conio.h>
#include <dos.h>
#pragma comment(lib, "graphics.lib")

using namespace std;

int A[10];
int n;
int radius = 25;

void importArray(int A[], int& n) {
	cin >> n;
	do {
		if (n <= 1) {
			cout << "Invalid value. Please re-enter." << endl;
			cin >> n;
		}
	} while (n <= 1);
	for (int i = 0; i < n; i++)
		cin >> A[i];
}

void exportArray(int A[], int n) {
	for (int i = 0; i < n; i++)
		cout << A[i] << " ";
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

void glowBox(int x, int y, int data) {
	int j = 1;
	while (j != 100) {
		setcolor(j);
		j++;
		drawBox(x, y, data, j);
		delay(1);
	}
	drawBox(x, y, data, WHITE);
}

void drawArray(int A[], int n, int x, int y, int color) {
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
			drawBox(x + 50, y, A[i], color);
		else
			drawBox(x + 50 * i + 50, y, A[i], color);
	}
}

void comparison(int x, int y, int i, int j, int color) {
	string question1 = "Array[ ";
	string question2 = " ] < Array[ ";
	string question3 = " ] ?";
	char* q1 = (char*)question1.c_str();
	char* q2 = (char*)question2.c_str();
	char* q3 = (char*)question3.c_str();
	stringstream ssi;
	ssi << i;
	string si = ssi.str();
	char* tempi = (char*)si.c_str();		//Convert i, j from int to char*
	stringstream ssj;
	ssj << j;
	string sj = ssj.str();
	char* tempj = (char*)sj.c_str();
	setcolor(color);
	outtextxy(x, y, q1);
	outtextxy(x + 40, y, tempi);
	outtextxy(x + 50, y, q2);
	outtextxy(x + 115, y, tempj);
	outtextxy(x + 125, y, q3);
}

void countingSortVisualize(int A[], int n) {
	int Count[100];
	int Output[10];
	for (int i = 0; i < n; i++) {
		Count[i] = 0;
		Output[i] = 0;
	}

	setcolor(LIGHTGRAY);
	string array1 = "Unsorted Array: ";
	char* a1 = (char*)array1.c_str();
	outtextxy(50, 0, a1);
	drawArray(A, n, 100, 75, LIGHTGRAY);
	delay(1000);
	
	string countArray = "Count Array with [n] Zero elements: ";
	char* c = (char*)countArray.c_str();
	outtextxy(50, 125, c);
	delay(1000);
	drawArray(Count, n, 100, 200, LIGHTGRAY);
	delay(2000);

	string outputArray = "Empty Output Array with [n] elements: ";	
	char* o = (char*)outputArray.c_str();
	outtextxy(50, 275, o);
	drawArray(Output, n, 100, 350, LIGHTGRAY);
	delay(1000);
	
	string plus = "+";
	char* p = (char*)plus.c_str();
	string deleteOneChar = "  ";
	char* del1Char = (char*)deleteOneChar.c_str();
	
	string countArr = "Count Array:                                      ";
	char* c2 = (char*)countArr.c_str();
	outtextxy(50, 125, c2);
	for (int i = n - 1; i >= 1; i--) {
		for (int j = i - 1; j >= 0; j--) {
			comparison(350, 115, i, j, LIGHTGRAY);
			if (A[i] < A[j]) {
				glowBox(100 + 50 * i + 50, 75, A[i]);
				delay(1000);
				glowBox(100 + 50 * j + 50, 75, A[j]);
				delay(1000);
				comparison(350, 115, i, j, LIGHTGREEN);
				delay(500);
				glowBox(100 + 50 * j + 50, 200, Count[j]);
				setcolor(LIGHTGREEN);
				outtextxy(100 + 50 * j + 50, 225, p);
				delay(1000);
				Count[j]++;
				drawBox(100 + 50 * j + 50, 200, Count[j], LIGHTGREEN);
				delay(1000);
				outtextxy(100 + 50 * j + 50, 225, del1Char);
			}
			else {	
				glowBox(100 + 50 * i + 50, 75, A[i]);
				delay(1000);
				glowBox(100 + 50 * j + 50, 75, A[j]);
				delay(1000);
				comparison(350, 115, i, j, LIGHTRED);
				delay(500);
				glowBox(100 + 50 * i + 50, 200, Count[i]);
				setcolor(LIGHTRED);
				outtextxy(100 + 50 * i + 50, 225, p);
				delay(1000);
				Count[i]++;
				drawBox(100 + 50 * i + 50, 200, Count[i], LIGHTRED);
				delay(1000);
				outtextxy(100 + 50 * i + 50, 225, del1Char);
			}
		}
	}
	//Set everything back to normal
	drawArray(A, n, 100, 75, LIGHTGRAY);
	drawArray(Count, n, 100, 200, LIGHTGRAY);
	string noirSpace = "                                                                                                                                                                                         ";
	char* noir = (char*)noirSpace.c_str();
	outtextxy(100, 115, noir);

	string outputFinal = "Output Array:                                                              ";
	char* oF = (char*)outputFinal.c_str();
	outtextxy(50, 275, oF);
	delay(1000);
	for (int i = 0; i < n; i++) {
		Output[Count[i]] = A[i];
		glowBox(100 + 50 * i + 50, 200, Count[i]);
		delay(1000);
		glowBox(100 + 50 * Count[i] + 50, 350, 0);
		delay(1000);
		glowBox(100 + 50 * i + 50, 75, A[i]);
		delay(1000);
		drawMulticolorBox(100 + 50 * Count[i] + 50, 350, Output[Count[i]], LIGHTGRAY, YELLOW);
		delay(1000);
		//Export the array in Console
		exportArray(Output, n);
	}
	//	Finish stage
	drawArray(Output, n, 100, 350, YELLOW);
	int j = 0;
	string finish = "FINISH.";
	char* fin = (char*)finish.c_str();
	while (1) {
		j++;
		setcolor(j);
		outtextxy(300, 450, fin);
		delay(10);
	}
	system("pause");
}

int main() {
	int gd = DETECT, gm;
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	importArray(A, n);
	initgraph(&gd, &gm, "c:\\tc\\bgi");
	countingSortVisualize(A, n);
	closegraph();
	return 0;
}