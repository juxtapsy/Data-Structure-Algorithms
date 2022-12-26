#include "graphics.h"
#include <dos.h>
#include <iostream>
#pragma comment (lib, "graphics.lib")

using namespace std;

int A[100];
int n;

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

int floorLog2(int value)
{
    int result = -1;
    for (int i = 1; i < value; i <<= 1, ++result);  //i = i * 2
    return result;
}

void BatcherMergeSort(int A[], int n)
{
    int t = floorLog2(n);
    int p0 = (1 << t);  // p0 = 2^t;
    int p = p0;

    do
    {
        int q = p0;
        int r = 0;
        int d = p;

        while (r == 0 || q != p)
        {
            if (r != 0)
            {
                d = q - p;
                q >>= 1;    // q /= 2
            }

            for (int i = 0; i < n - d; i++)
            {       // Check 
                if (((i & p) == r) && A[i] > A[i + d])
                {
                    int swap = A[i];
                    A[i] = A[i + d];
                    A[i + d] = swap;
                }
            }
            exportArray(A, n);
            r = p;
        }

        p >>= 1;    // p /= 2
    } while (p > 0);
}

int main() {
    importArray(A, n);
    BatcherMergeSort(A, n);
    return 0;
}
