#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

clock_t start, stop;
double duration;
// 格式化矩阵成迭代格式
void FormatMatrix(double A_[][9], double *b_,double M_[][9], double *f_);
//雅可比迭代
void Jacobi(double A_[][9], double *b_);
//高斯赛德尔迭代
void Seidel(double A_[][9], double *b_);
// 求矩阵范数
double MatrixNorm(double A_[][9]);
// 输出结果
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
    //雅可比迭代
    Jacobi(A,b);
    printf("\n\n");
    //高斯赛德尔迭代
    Seidel(A,b);
    printf("\n\n");

    stop = clock();
    duration = (double)(stop - start) / CLK_TCK;
    printf("程序运行所用时间：%f\n", duration);
    system("pause");
    return 0;
}

// 格式化矩阵为迭代格式
void FormatMatrix(double A_[][9], double *b_, double M_[][9], double *f_)
{
    // 复制矩阵
    for(int i =0; i<9;++i)
    {
        for (int j =0;j<9;++j)
        {
            M_[i][j] = A_[i][j];
        }
        f_[i] = b_[i];
    }
    // 格式化为迭代格式
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

//雅可比迭代
void Jacobi(double A_[][9], double *b_)
{
    double M[9][9];
    double f[9];
    // 格式化矩阵为迭代格式
    FormatMatrix(A_,b_,M,f);
    // 求矩阵M的范数
    double norm_matrix = MatrixNorm(M);
    printf("矩阵范数为：%f\n\n", norm_matrix);
    int count = 0;
    double x_previous[9] = {0.0};
    // 循环迭代
    while(1)
    {
        double x_next[9] = {0.0};
        // 迭代计算
        for(int i = 0; i <9; ++i)
        {
            for (int j =0;j<9; ++j)
            {
                x_next[i] += (M[i][j] * x_previous[j]);
            }
            x_next[i] += f[i];
        }
        //求x范数
        double norm_vector = {0.0};
        for(int i = 0; i <9; ++i)
        {
            norm_vector += fabs(x_next[i] - x_previous[i]);
            // 顺便更新下次迭代所用的x值
            x_previous[i] = x_next[i];
        }
        // 假如M的范数小于1，需要乘上M的范数再进行判断，否则忽略
        if(norm_matrix <1 )
        {
            norm_vector *= (norm_matrix / (1-norm_matrix));
        }
        // 判定条件
        if(norm_vector < 1e-5)
        {
            break;
        }
        ++count;
    }
    printf("Jacobi求解迭代次数为：%d次\n", count);
    printf("Jacobi求解结果为：\n");

    PrintResult(x_previous);
}

//高斯赛德尔迭代
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
        // 复制前一次的迭代结果备用，因为每一步都需要更新x的值
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
            // 更新下一步迭代所用的 “x_k” 为 “x_k+1”
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
    printf("Gauss-Seidel求解迭代次数为：%d次\n", count);
    printf("Gauss-Seidel求解结果为：\n");

    PrintResult(x_previous);
}

// 求矩阵范数
double MatrixNorm(double A_[][9])
{
    double max = 0;
    // 每一列元素绝对值求和，再求最大值
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

// 输出结果
void PrintResult(double *x)
{
    for(int i = 0; i <9; ++i)
        printf("%6f  ", x[i]);
}
