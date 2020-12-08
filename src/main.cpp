#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

clock_t start, stop;
double duration;

float A[5][6] = {0.0};
float t[9] = {0.0};
void ComputeMatrix(float *coords);
void GaussSolve();
void LuSolve();

int main()
{
    start = clock();
    //已知初始的5个坐标点
    float x[9] = {-386976.786, -397199.228, -403002.333, -404301.874, -401058.65, -393279.751, -381019.561, -364380.489, -343513.4};
    float y[9] = {106369.212, 70584.989, 34008.818, -2946.251, -39859.487, -76305.83, -111859.429, -146097.317, -178603.222};
    float z[9] = {61240.44, 41725.648, 21741.252, 1512.866, -18729.308, -38752.308, -58322.344, -77206.812, -95176.378};

    float tmp = 2.0 * 12.0 / 96.0;
    for (int i = 0; i < 9; ++i)
    {
        t[i] = tmp * i - 1;
    }
    printf("=========== X坐标拟合结果 ===========\n");
    ComputeMatrix(x);
    GaussSolve();

    printf("=========== Y坐标拟合结果 ===========\n");
    ComputeMatrix(y);
    LuSolve();
    // GaussSolve();

    printf("=========== Z坐标拟合结果 ===========\n");
    ComputeMatrix(z);
    LuSolve();
    // GaussSolve();

    stop = clock();
    duration = (double)(stop - start) / CLK_TCK;
    printf("解方程所用时间：%f\n", duration);

    system("pause");
    return 0;
}

void ComputeMatrix(float *coords)
{
    for (int i = 0; i < 5; ++i)
    {
        for (int j = i; j < 5; ++j)
        {
            float sum = 0.0;
            for (int k = 0; k < 9; ++k)
            {
                sum += cos(i * acos(t[k])) * cos(j * acos(t[k]));
            }
            //对称性
            A[i][j] = sum;
            A[j][i] = sum;
        }
        float sum = 0.0;
        for (int k = 0; k < 9; ++k)
        {
            sum += coords[k] * cos(i * acos(t[k]));
        }
        A[i][5] = sum;
    }
}

void GaussSolve()
{
    //输出增广矩阵A
    printf("A = \n");
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            printf("% 6f  ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    //高斯顺序消元
    for (int i = 0; i < 4; ++i)
    {
        for (int j = i + 1; j < 5; ++j)
        {
            float rate = A[j][i] / A[i][i];
            for (int k = 0; k < 6; ++k)
            {
                A[j][k] = A[j][k] - rate * A[i][k];
            }
        }
    }
    //回代求解
    float result[5];
    result[4] = A[4][5] / A[4][4];
    for (int i = 5 - 2; i >= 0; --i)
    {
        float s = 0;
        for (int j = i + 1; j <= 5 - 1; ++j)
        {
            s += A[i][j] * result[j];
        }
        result[i] = (-s + A[i][5]) / A[i][i];
    }
    //输出方程系数
    printf("Result = \n");
    for (int i = 0; i < 5; ++i)
    {
        printf("% 6f  ", result[i]);
    }
    printf("\n\n\n");
}

void LuSolve()
{
    //输出增广矩阵A
    printf("A = \n");
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 6; ++j)
            printf("% 6f  ", A[i][j]);
        printf("\n");
    }
    printf("\n");
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
    //求解LY = B
    float Y[5];
    for (int i = 0; i < 5; ++i)
    {
        float sum = 0.0;
        for (int j = 0; j < i; ++j)
            sum += A[i][j] * Y[j];
        Y[i] = A[i][5] - sum;
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
    printf("\n\n\n");
}
