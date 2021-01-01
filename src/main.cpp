#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

clock_t start, stop;
double duration;
// ��ʽ������ɵ�����ʽ
void FormatMatrix(double A_[][9], double *b_,double M_[][9], double *f_);
//�ſɱȵ���
void Jacobi(double A_[][9], double *b_);
//��˹���¶�����
void Seidel(double A_[][9], double *b_);
// �������
double MatrixNorm(double A_[][9]);
// ������
void PrintResult(double *);

int main()
{
    start = clock();
    double A[9][9] = {{31,-13,0,0,0,-10,0,0,0},
                      {-13,35,-9,0,-11,0,0,0,0},
                      {0,-9,31,-10,0,0,0,0,0},
                      {0,0,-10,79,-30,0,0,0,-9},
                      {0,0,0,-30,57,-7,0,-5,0},
                      {0,0,0,0,7,47,-30,0,0},
                      {0,0,0,0,0,-30,41,0,0},
                      {0,0,0,0,-5,0,0,27,-2},
                      {0,0,0,-9,0,0,0,-2,29}};
    double b[9] = { -15.0, 27.0, -23.0, 0.0, -20.0, 12.0, -7.0, 7.0, -10};
    //�ſɱȵ���
    Jacobi(A,b);
    printf("\n\n");
    //��˹���¶�����
    Seidel(A,b);
    printf("\n\n");

    stop = clock();
    duration = (double)(stop - start) / CLK_TCK;
    printf("������������ʱ�䣺%f\n", duration);
    system("pause");
    return 0;
}

// ��ʽ������Ϊ������ʽ
void FormatMatrix(double A_[][9], double *b_, double M_[][9], double *f_)
{
    // ���ƾ���
    for(int i =0; i<9;++i)
    {
        for (int j =0;j<9;++j)
        {
            M_[i][j] = A_[i][j];
        }
        f_[i] = b_[i];
    }
    // ��ʽ��Ϊ������ʽ
    for(int i = 0; i <9; ++i)
    {
        for(int j = 0; j<9; ++j)
        {
            if( j != i)
            {
                M_[i][j] /= (-M_[i][i]);
            }
        }
        f_[i] /= M_[i][i];
        M_[i][i] = 0.0;
    }
}

//�ſɱȵ���
void Jacobi(double A_[][9], double *b_)
{
    double M[9][9];
    double f[9];
    // ��ʽ������Ϊ������ʽ
    FormatMatrix(A_,b_,M,f);
    // �����M�ķ���
    double norm_matrix = MatrixNorm(M);
    printf("������Ϊ��%f\n\n", norm_matrix);
    int count = 0;
    double x_previous[9] = {0.0};
    // ѭ������
    while(1)
    {
        double x_next[9] = {0.0};
        // ��������
        for(int i = 0; i <9; ++i)
        {
            for (int j =0;j<9; ++j)
            {
                x_next[i] += (M[i][j] * x_previous[j]);
            }
            x_next[i] += f[i];
        }
        //��x����
        double norm_vector = {0.0};
        for(int i = 0; i <9; ++i)
        {
            norm_vector += fabs(x_next[i] - x_previous[i]);
            // ˳������´ε������õ�xֵ
            x_previous[i] = x_next[i];
        }
        // ����M�ķ���С��1����Ҫ����M�ķ����ٽ����жϣ��������
        if(norm_matrix <1 )
        {
            norm_vector *= (norm_matrix / (1-norm_matrix));
        }
        // �ж�����
        if(norm_vector < 1e-5)
        {
            break;
        }
        ++count;
    }
    printf("Jacobi����������Ϊ��%d��\n", count);
    printf("Jacobi�����Ϊ��\n");

    PrintResult(x_previous);
}

//��˹���¶�����
void Seidel(double A_[][9], double *b_)
{
    double M[9][9];
    double f[9];
    FormatMatrix(A_,b_,M,f);
    int count = 0;
    double x_previous[9] = {0.0};
    while(1)
    {
        double x_next[9] = {0.0};
        double x_current[9] = {0.0};
        // ����ǰһ�εĵ���������ã���Ϊÿһ������Ҫ����x��ֵ
        for(int i = 0; i <9; ++i)
        {
            x_current[i] = x_previous[i];
        }
        for(int i = 0; i <9; ++i)
        {
            for (int j =0;j<9; ++j)
            {
                x_next[i] += (M[i][j] * x_current[j]);
            }
            x_next[i] += f[i];
            // ������һ���������õ� ��x_k�� Ϊ ��x_k+1��
            x_current[i] = x_next[i];
        }
        double norm_vector = {0.0};
        for(int i = 0; i <9; ++i)
        {
            norm_vector += fabs(x_next[i] - x_previous[i]);
            x_previous[i] = x_next[i];
        }
        if(norm_vector < 1e-5)
        {
            break;
        }
        ++count;
    }
    printf("Gauss-Seidel����������Ϊ��%d��\n", count);
    printf("Gauss-Seidel�����Ϊ��\n");

    PrintResult(x_previous);
}

// �������
double MatrixNorm(double A_[][9])
{
    double max = 0;
    // ÿһ��Ԫ�ؾ���ֵ��ͣ��������ֵ
    for(int i = 0; i <9; ++i)
    {
        double sum = 0.0;
        for(int j = 0; j<9; ++j)
        {
            sum += fabs(A_[j][i]);
        }
        if(max < sum)
        {
            max = sum;
        }
    }
    return max;
}

// ������
void PrintResult(double *x)
{
    for(int i = 0; i <9; ++i)
        printf("%6f  ", x[i]);
}
