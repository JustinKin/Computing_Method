#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

clock_t start, stop, linear_bg, linear_ed, cubic_ed;
double duration, duration_linear, duration_cubic;

float A1[5][6] = {0.0}, A2[5][6] = {0.0}, A3[5][6] = {0.0};
float t[9] = {0.0};
void ComputeMatrix(float *p, float A[5][6]);
void GaussSolve(float A[5][6]);
void LuSolve(float A[5][6]);

int main()
{
    start = clock();
    //��֪��ʼ��5�������
    float x[9] = {-386976.786, -397199.228, -403002.333, -404301.874, -401058.65, -393279.751, -381019.561, -364380.489, -343513.4};
    float y[9] = {106369.212, 70584.989, 34008.818, -2946.251, -39859.487, -76305.83, -111859.429, -146097.317, -178603.222};
    float z[9] = {61240.44, 41725.648, 21741.252, 1512.866, -18729.308, -38752.308, -58322.344, -77206.812, -95176.378};

    float tmp = 2.0 * 12.0 / 96.0;
    for (int i = 0; i < 9; ++i)
    {
        t[i] = tmp * i - 1;
    }
    printf("=========== X������Ͻ�� ===========\n");
    ComputeMatrix(x, A1);
    GaussSolve(A1);

    printf("=========== Y������Ͻ�� ===========\n");
    ComputeMatrix(y, A2);
    LuSolve(A2);
    // GaussSolve(A2);

    printf("=========== Z������Ͻ�� ===========\n");
    ComputeMatrix(z, A3);
    LuSolve(A3);
    // GaussSolve(A3);

    stop = clock();
    duration = (double)(stop - start) / CLK_TCK;
    printf("�ⷽ������ʱ�䣺%f\n", duration);

    system("pause");
    return 0;
}

void ComputeMatrix(float *p, float A[5][6])
{
    for (int i = 0; i < 5; ++i)
    {
        for (int j = i; j < 5; ++j)
        {
            for (int k = 0; k < 9; ++k)
            {
                A[i][j] += cos(i * acos(t[k])) * cos(j * acos(t[k]));
            }
            //�Գ���
            A[j][i] = A[i][j];
        }
        for (int k = 0; k < 9; ++k)
        {
            A[i][5] += p[k] * cos(i * acos(t[k]));
        }
    }
}

void GaussSolve(float A[5][6])
{
    //����������A
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
    //��˹˳����Ԫ
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
    //�ش����
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
    //�������ϵ��
    printf("Result = \n");
    for (int i = 0; i < 5; ++i)
    {
        printf("% 6f  ", result[i]);
    }
    printf("\n\n\n");
}

void LuSolve(float A[5][6])
{
    //����������A
    printf("A = \n");
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 6; ++j)
            printf("% 6f  ", A[i][j]);
        printf("\n");
    }
    printf("\n");
    //��LU����
    for (int i = 0; i < 5; ++i)
    {
        for (int j = i; j < 5; ++j)
        {
            //��U����
            float sum = 0.0;
            for (int k = 0; k < i; ++k)
            {
                sum += A[i][k] * A[k][j];
            }
            A[i][j] = A[i][j] - sum;
            //��L����
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
    //���LY = B
    float Y[5];
    for (int i = 0; i < 5; ++i)
    {
        float sum = 0.0;
        for (int j = 0; j < i; ++j)
            sum += A[i][j] * Y[j];
        Y[i] = A[i][5] - sum;
    }
    //���UX = Y
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
