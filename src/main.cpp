#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

clock_t start, stop;
double duration;

int main()
{
    start = clock();
    double A[9][9] = {0.0};
    double b[9] = { -15.0, 27.0, -23.0, 0.0, -20.0, 12.0, -7.0, 7.0, -10};
    A[0][0] = 31.0;  A[0][1] = -13.0; A[0][5] = -10.0;
    A[1][0] = -13.0; A[1][1] = 35.0;  A[1][2] = -9.0;  A[1][4] = -11.0;
    A[2][1] = -9.0;  A[2][2] = 31.0;  A[2][3] = -10.0;
    A[3][2] = -10.0; A[3][3] = 79.0;  A[3][4] = -30.0; A[3][8] = -9.0;
    A[4][3] = -30.0; A[4][4] =57.0;   A[4][5] = -7.0;  A[4][7] = -5.0;
    A[5][4] = 7.0;   A[5][5] = 47.0;  A[5][6] = -30.0;
    A[6][5] = -30.0; A[6][6] = 41.0;
    A[7][4] = -5.0;  A[7][7] = 27.0;  A[7][8] = -2.0;
    A[8][3] = -9.0;  A[8][7] = -2.0;  A[8][8] = 29.0;














    stop = clock();
    duration = (double)(stop - start) / CLK_TCK;
    printf("程序运行所用时间：%f\n", duration);

    system("pause");
    return 0;
}
