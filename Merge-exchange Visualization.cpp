#include "graphics.h"
#include <dos.h>
#include <iostream>
#pragma comment (lib, "graphics.lib")

using namespace std;

int A[100];
int n;
int radius = 25;

void importArray(int A[], int& n) {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> A[i];
}
void exportArray(int A[], int n) {
    for (int i = 0; i < n; i++)
        cout << A[i] << " ";
    cout << endl;
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
    setcolor(color);
    circle(x, y, radius);
    writeText(x, y, data, color);
}

void drawArray(int x, int y, int A[], int n, int color) {
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
            drawBox(x + 50, y, A[i], color);
        else
            drawBox(x + 50 * i + 50, y, A[i], color);
    }
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
        drawBox(x, y, data, j);
        j++;
        delay(10);
    }
    drawBox(x, y, data, WHITE);
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

void comparison(int x, int y, int i, int d, int color, int colorNum) {
    char q1[] = "Array[ ";
    char q2[] = " ] > Array[ ";
    char q3[] = " ] ?";
    int z = i + d;
    setcolor(color);
    outtextxy(x, y, q1);
    writeText(x + 40, y, i, colorNum);
    setcolor(color);
    outtextxy(x + 50, y, q2);
    writeText(x + 115, y, z, colorNum);
    setcolor(color);
    outtextxy(x + 125, y, q3);
}

// Find t - 1
int floorLog2(int value) {
    int result = -1;
    for (int i = 1; i < value; i <<= 1, ++result);  //i = i * 2
    return result;
}

void mergeSortVisualize(int A[], int n) {    
    setcolor(LIGHTGRAY);    
    char unsorted[] = "Array: ";
    outtextxy(200, 25, unsorted);
    drawArray(350, 200, A, n, LIGHTGRAY);
    delay(100);

    int t = floorLog2(n); 
    char tt[] = "t = ";
    outtextxy(100, 100, tt);
    writeText(125, 100, t + 1, LIGHTGRAY);
    int p0 = (1 << t);  // p0 = 2^t;
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
                glowBox(350 + 50 * i + 50, 200, A[i]);
                delay(100);
                glowBox(350 + 50 * (i + d) + 50, 200, A[i + d]);
                writeText(140, 350, a, YELLOW);
                delay(100);
                if ((i & p) == r) {
                    setcolor(LIGHTGREEN);
                    outtextxy(100, 375, iANDp);
                    delay(100);
                    if (A[i] > A[i + d]) {
                        comparison(100, 400, i, d, LIGHTGREEN, LIGHTGREEN);
                        delay(100);
                        swapBox(350 + 50 * i + 50, 200, A[i], WHITE, 350 + 50 * (i + d) + 50, A[i + d], WHITE);
                        delay(100);
                        int swap = A[i];
                        A[i] = A[i + d];
                        A[i + d] = swap;
                        //Export the array in Console
                        exportArray(A, n);
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
    drawArray(350, 200, A, n, YELLOW);
    char fin[] = "FINISH.";
    int j = 1;
    while (1) {
        setcolor(j);
        outtextxy(400, 400, fin);
        delay(10);
        j++;
    }
    system("pause");
}

int main() {
    importArray(A, n);
    initwindow(1200, 600);
    mergeSortVisualize(A, n);
    closegraph();
    return 0;
}
