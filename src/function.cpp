#include <stdio.h>
#include <stdlib.h>
#include <time.h>

clock_t start, stop, linear_bg, linear_ed, cubic_ed;
double duration, duration_linear, duration_cubic;

void Gauss()
{
    start = clock();
    //已知初始的5个坐标点
    float x[5] = {-2.312, 2.061, -0.8545, -3.519, 2.815};
    float y[5] = {0.5027, -1.257, -2.915, -1.156, -2.815};
    float A[5][6];
    //生成增广矩阵A
    for (int i = 0; i < 5; ++i)
    {
        A[i][0] = x[i] * y[i];
        A[i][1] = y[i] * y[i];
        A[i][2] = x[i];
        A[i][3] = y[i];
        A[i][4] = 1;
        A[i][5] = -x[i] * x[i];
    }
    //输出增广矩阵A
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
    //输出上三角矩阵
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            printf("% 6f  ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
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
    //输出椭圆方程系数
    for (int i = 0; i < 5; ++i)
    {
        printf("% 6f  ", result[i]);
    }
    printf("\n");

    stop = clock();
    duration = (double)(stop - start) / CLK_TCK;
    printf("解方程所用时间：%f\n", duration);

}

void LU()
{
    start = clock();
    //已知初始的5个坐标点
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

    stop = clock();
    duration = (double)(stop - start) / CLK_TCK;
    printf("解方程所用时间：%f\n", duration);
}

void Lagrange()
{
    start = clock();

    FILE *read = NULL;
    FILE *write1 = NULL;
    FILE *write2 = NULL;
    //打开.txt文件
    //打开原始数据的文件
    fopen_s(&read, "image_data/2.txt", "r");
    if (!read)
    {
        perror("fail to read !");
        exit(-1);
    }
    //创建保存线性插值结果的文件
    fopen_s(&write1, "image_data/2_linear.txt", "w");
    if (!write1)
    {
        perror("fail to write1 !");
        exit(-2);
    }
    //创建保存三次插值结果的文件
    fopen_s(&write2, "image_data/2_cubic.txt", "w");
    if (!write2)
    {
        perror("fail to write1 !");
        exit(-3);
    }
    //读入.txt文件数据
    int img[50][50];
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            fscanf(read, "%d", &img[i][j]);
        }
    }
    fclose(read);
    linear_bg = clock();
    // =====================================线性插值=====================================
    //49 * 10 +1 = 491
    int tmp[50][491];
    //先插值行，共有50行，每行的50列变成491列
    // 外循环i是行，内循环j是列
    for (int i = 0; i < 50; i++)
    {
        int p1 = -10;
        int p2 = 0;
        for (int j = 0; j < 491; j++)
        {
            if (j % 10 == 0)
            {
                tmp[i][j] = img[i][j / 10];
                p1 += 10;
                p2 += 10;
            }
            else
            {
                tmp[i][j] = img[i][p1 / 10] * (j - p2) / (p1 - p2)
                          + img[i][p2 / 10] * (j - p1) / (p2 - p1);
            }
        }
    }
    //插值列
    // 外循环j是列，内循环i是行
    int linear[491][491];
    for (int j = 0; j < 491; ++j)
    {
        int p1 = -10;
        int p2 = 0;
        for (int i = 0; i < 491; ++i)
        {
            if (i % 10 == 0)
            {
                linear[i][j] = tmp[i / 10][j];
                p1 += 10;
                p2 += 10;
            }
            else
            {
                linear[i][j] = tmp[p1 / 10][j] * (i - p2) / (p1 - p2)
                             + tmp[p2 / 10][j] * (i - p1) / (p2 - p1);
            }
        }
    }
    //线性插值结果写入.txt
    for (int i = 0; i < 491; i++)
    {
        for (int j = 0; j < 491; j++)
        {
            fprintf(write1, "%3d  ", linear[i][j]);
        }
        fprintf(write1, "\n");
    }
    linear_ed = clock();
    // =====================================三次插值=====================================
    //先插值行，共有50行，每行的50列变成491列
    // 外循环i是行，内循环j是列
    for (int i = 0; i < 50; i++)
    {
        int p1 = -10;
        int p2 = 0;
        int p3 = 10;
        int p4 = 20;
        //除了前、后10列都进行插值
        for (int j = 10; j < 481; j++)
        {
            if (j % 10 == 0)
            {
                tmp[i][j] = img[i][j / 10];
                p1 += 10;
                p2 += 10;
                p3 += 10;
                p4 += 10;
            }
            else
            {
                tmp[i][j] = img[i][p1 / 10] * (j - p2) * (j - p3) * (j - p4) / ((p1 - p2) * (p1 - p3) * (p1 - p4))
                          + img[i][p2 / 10] * (j - p1) * (j - p3) * (j - p4) / ((p2 - p1) * (p2 - p3) * (p2 - p4))
                          + img[i][p3 / 10] * (j - p1) * (j - p2) * (j - p4) / ((p3 - p1) * (p3 - p2) * (p3 - p4))
                          + img[i][p4 / 10] * (j - p1) * (j - p2) * (j - p3) / ((p4 - p1) * (p4 - p2) * (p4 - p3));
            }
        }
    }
    //处理前、后10列
    for(int i = 0; i <50; ++i)
    {
        tmp[i][0] = img[i][0];
        tmp[i][490] = img[i][49];
        int p1 = 0;
        int p2 = 10;
        int p3 = 20;
        int p4 = 30;
        for (int j = 1; j <10; j++)
        {
            tmp[i][j] = img[i][0] * (j - p2) * (j - p3) * (j - p4) / ((p1 - p2) * (p1 - p3) * (p1 - p4))
                      + img[i][1] * (j - p1) * (j - p3) * (j - p4) / ((p2 - p1) * (p2 - p3) * (p2 - p4))
                      + img[i][2] * (j - p1) * (j - p2) * (j - p4) / ((p3 - p1) * (p3 - p2) * (p3 - p4))
                      + img[i][3] * (j - p1) * (j - p2) * (j - p3) / ((p4 - p1) * (p4 - p2) * (p4 - p3));
        }
        p1 = 460;
        p2 = 470;
        p3 = 480;
        p4 = 490;
        for (int j = 481; j <490; j++)
        {
            tmp[i][j] = img[i][46] * (j - p2) * (j - p3) * (j - p4) / ((p1 - p2) * (p1 - p3) * (p1 - p4))
                      + img[i][47] * (j - p1) * (j - p3) * (j - p4) / ((p2 - p1) * (p2 - p3) * (p2 - p4))
                      + img[i][48] * (j - p1) * (j - p2) * (j - p4) / ((p3 - p1) * (p3 - p2) * (p3 - p4))
                      + img[i][49] * (j - p1) * (j - p2) * (j - p3) / ((p4 - p1) * (p4 - p2) * (p4 - p3));
        }
    }
    //插值列
    // 外循环j是列，内循环i是行
    int cubic[491][491];
    for (int j = 0; j < 491; ++j)
    {
        int p1 = -10;
        int p2 = 0;
        int p3 = 10;
        int p4 = 20;
        //除了前、后10行都进行插值
        for (int i = 10; i < 481; ++i)
        {
            if (i % 10 == 0)
            {
                cubic[i][j] = tmp[i / 10][j];
                p1 += 10;
                p2 += 10;
                p3 += 10;
                p4 += 10;
            }
            else
            {
                cubic[i][j] = tmp[p1 / 10][j] * (i - p2) * (i - p3) * (i - p4) / ((p1 - p2) * (p1 - p3) * (p1 - p4))
                            + tmp[p2 / 10][j] * (i - p1) * (i - p3) * (i - p4) / ((p2 - p1) * (p2 - p3) * (p2 - p4))
                            + tmp[p3 / 10][j] * (i - p1) * (i - p2) * (i - p4) / ((p3 - p1) * (p3 - p2) * (p3 - p4))
                            + tmp[p4 / 10][j] * (i - p1) * (i - p2) * (i - p3) / ((p4 - p1) * (p4 - p2) * (p4 - p3));
            }
        }
    }
    //处理前、后10行
    for (int j = 0; j < 491; ++j)
    {
        cubic[0][j] = tmp[0][j];
        cubic[490][j] = tmp[49][j];
        int p1 = 0;
        int p2 = 10;
        int p3 = 20;
        int p4 = 30;
        for(int i = 0; i < 10; ++i)
        {
            cubic[i][j] = tmp[0][j] * (i - p2) * (i - p3) * (i - p4) / ((p1 - p2) * (p1 - p3) * (p1 - p4))
                        + tmp[1][j] * (i - p1) * (i - p3) * (i - p4) / ((p2 - p1) * (p2 - p3) * (p2 - p4))
                        + tmp[2][j] * (i - p1) * (i - p2) * (i - p4) / ((p3 - p1) * (p3 - p2) * (p3 - p4))
                        + tmp[3][j] * (i - p1) * (i - p2) * (i - p3) / ((p4 - p1) * (p4 - p2) * (p4 - p3));
        }
        p1 = 460;
        p2 = 470;
        p3 = 480;
        p4 = 490;
        for(int i = 481; i < 490; ++i)
        {
            cubic[i][j] = tmp[46][j] * (i - p2) * (i - p3) * (i - p4) / ((p1 - p2) * (p1 - p3) * (p1 - p4))
                        + tmp[47][j] * (i - p1) * (i - p3) * (i - p4) / ((p2 - p1) * (p2 - p3) * (p2 - p4))
                        + tmp[48][j] * (i - p1) * (i - p2) * (i - p4) / ((p3 - p1) * (p3 - p2) * (p3 - p4))
                        + tmp[49][j] * (i - p1) * (i - p2) * (i - p3) / ((p4 - p1) * (p4 - p2) * (p4 - p3));
        }

    }
    //三次插值结果写入.txt
    for (int i = 0; i < 491; i++)
    {
        for (int j = 0; j < 491; j++)
        {
            fprintf(write2, "%3d  ", cubic[i][j]);
        }
        fprintf(write2, "\n");
    }
    cubic_ed = clock();
    //关闭插值结果文件
    fclose(write1);
    fclose(write2);

    stop = clock();
    duration_linear = (double)(linear_ed - linear_bg) / CLK_TCK;
    duration_cubic = (double)(cubic_ed - linear_ed) / CLK_TCK;
    duration = (double)(stop - start) / CLK_TCK;
    printf("拉格朗日线性插值所用时间：%f\n", duration_linear);
    printf("拉格朗日三次插值所用时间：%f\n", duration_cubic);
    printf("程序运行所用时间：%f\n", duration);

}

void Newton()
{

}