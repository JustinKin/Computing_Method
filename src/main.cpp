#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

clock_t start, stop, linear_bg, linear_ed, cubic_ed;
double duration, duration_linear, duration_cubic;

int main()
{
	start = clock();













    float x[5] = {-2.312, 2.061, -0.8545, -3.519, 2.815};
    float y[5] = {0.5027, -1.257, -2.915, -1.156, -2.815};
    float A[5][5];
    float B[5];
    //生成矩阵A、B,AX=B
    for (int i = 0; i < 5; ++i)
    {
        A[i][0] = x[i] * y[i];
        A[i][1] = y[i] * y[i];
        A[i][2] = x[i];
        A[i][3] = y[i];
        A[i][4] = 1;
        B[i] = -x[i] * x[i];
    }
    //输出矩阵A
    printf("A = \n");
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
            printf("% 6f  ", A[i][j]);
        printf("\n");
    }
    printf("\n");
    //输出矩阵B
    printf("B = \n");
    for (int i = 0; i < 5; ++i)
        printf("% 6f  ", B[i]);
    printf("\n\n");
    //求LU矩阵
    for (int i = 0; i < 5; ++i)
    {
        for (int j = i; j < 5; ++j)
        {
            //求U矩阵
            float sum = 0.0;
            for (int k = 0; k < i; ++k)
            {
                sum += A[i][k] * A[k][j];
            }
            A[i][j] = A[i][j] - sum;
            //求L矩阵
            sum = 0.0;
            if (j > i)
            {
                for (int k = 0; k < i; ++k)
                {
                    sum += A[j][k] * A[k][i];
                }
                A[j][i] = (A[j][i] - sum) / A[i][i];
            }
        }
    }
    //输出L矩阵
    printf("L = \n");
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            if (j == i)
                printf("% 6f  ", 1.0);
            if (j > i)
                printf("% 6f  ", 0.0);
            if (j < i)
                printf("% 6f  ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    //输出U矩阵
    printf("U = \n");
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            if (j >= i)
                printf("% 6f  ", A[i][j]);
            if (j < i)
                printf("% 6f  ", 0.0);
        }
        printf("\n");
    }
    printf("\n");
    //求解LY = B
    float Y[5];
    for (int i = 0; i < 5; ++i)
    {
        float sum = 0.0;
        for (int j = 0; j < i; ++j)
            sum += A[i][j] * Y[j];
        Y[i] = B[i] - sum;
    }
    //求解UX = Y
    float X[5];
    for (int i = 4; i > -1; --i)
    {
        float sum = 0.0;
        for (int j = 4; j > i; --j)
            sum += A[i][j] * X[j];
        X[i] = (Y[i] - sum) / A[i][i];
    }
    printf("Result = \n");
    for (int i = 0; i < 5; ++i)
        printf("% 6f  ", X[i]);
    printf("\n\n");

	system("pause");
	return 0;
}
