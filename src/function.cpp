#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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
    start = clock();

    FILE *read = NULL;
    FILE *write1 = NULL;
    FILE *write2 = NULL;
    //打开.txt文件
    //打开原始数据的文件
    fopen_s(&read, "image_data/1.txt", "r");
    if (!read)
    {
        perror("fail to read !");
        exit(-1);
    }
    //创建保存线性插值结果的文件
    fopen_s(&write1, "image_data/Newton_linear.txt", "w");
    if (!write1)
    {
        perror("fail to write1 !");
        exit(-2);
    }
    //创建保存三次插值结果的文件
    fopen_s(&write2, "image_data/Newton_cubic.txt", "w");
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
        float md = 0.0;
        for (int j = 0; j < 491; j++)
        {
            if (j % 10 == 0)
            {
                tmp[i][j] = img[i][j / 10];
                p1 += 10;
                p2 += 10;
                md = (img[i][p2 / 10] - img[i][p1 / 10]) * 0.1;
            }
            else
            {
                tmp[i][j] = img[i][p1 / 10] + md * (j - p1);
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
        float md = 0.0;
        for (int i = 0; i < 491; ++i)
        {
            if (i % 10 == 0)
            {
                linear[i][j] = tmp[i / 10][j];
                p1 += 10;
                p2 += 10;
                md = (tmp[p2 / 10][j] - tmp[p1 / 10][j]) * 0.1;
            }
            else
            {
                linear[i][j] = tmp[p1 / 10][j] + md * (i - p1);
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
        int p[4] ={-10,0,10,20};
        float md[6] = {0.0};
        //除了前、后10列都进行插值
        for (int j = 10; j < 481; j++)
        {
            if (j % 10 == 0)
            {
                tmp[i][j] = img[i][j / 10];
                p[0] += 10;
                p[1] += 10;
                p[2] += 10;
                p[3] += 10;
                md[0] = (img[i][p[1]/10] - img[i][p[0]/10]) * 0.1;
                md[1] = (img[i][p[2]/10] - img[i][p[1]/10]) * 0.1;
                md[2] = (img[i][p[3]/10] - img[i][p[2]/10]) * 0.1;
                md[3] = (md[1] - md[0]) * 0.05;
                md[4] = (md[2] - md[1]) * 0.05;
                md[5] = (md[4] - md[3]) * 0.03333333;
            }
            else
            {
                tmp[i][j] = img[i][j / 10 - 1]    //watchout -1
                            + md[0] * (j - p[0])
                            + md[3] * (j - p[0]) * (j - p[1])
                            + md[5] * (j - p[0]) * (j - p[1]) * (j - p[2]);
            }
        }
    }
    //处理前、后10列
    for(int i = 0; i <50; ++i)
    {
        tmp[i][0] = img[i][0];
        tmp[i][490] = img[i][49];
        int p[4] ={0,10,20,30};
        float md[6] = {0.0};
        md[0] = (img[i][p[1]/10] - img[i][p[0]/10]) * 0.1;
        md[1] = (img[i][p[2]/10] - img[i][p[1]/10]) * 0.1;
        md[2] = (img[i][p[3]/10] - img[i][p[2]/10]) * 0.1;
        md[3] = (md[1] - md[0]) * 0.05;
        md[4] = (md[2] - md[1]) * 0.05;
        md[5] = (md[4] - md[3]) * 0.03333333;
        for (int j = 1; j <10; j++)
        {
            tmp[i][j] = img[i][0]
                      + md[0] * (j - p[0])
                      + md[3] * (j - p[0]) * (j - p[1])
                      + md[5] * (j - p[0]) * (j - p[1]) * (j - p[2]);
        }
        p[0] = 460;
        p[1] = 470;
        p[2] = 480;
        p[3] = 490;
        md[0] = (img[i][p[1]/10] - img[i][p[0]/10]) * 0.1;
        md[1] = (img[i][p[2]/10] - img[i][p[1]/10]) * 0.1;
        md[2] = (img[i][p[3]/10] - img[i][p[2]/10]) * 0.1;
        md[3] = (md[1] - md[0]) * 0.05;
        md[4] = (md[2] - md[1]) * 0.05;
        md[5] = (md[4] - md[3]) * 0.03333333;
        for (int j = 481; j <490; j++)
        {
            tmp[i][j] = img[i][46]
                      + md[0] * (j - p[0])
                      + md[3] * (j - p[0]) * (j - p[1])
                      + md[5] * (j - p[0]) * (j - p[1]) * (j - p[2]);
        }
    }
    //插值列
    // 外循环j是列，内循环i是行
    int cubic[491][491];
    for (int j = 0; j < 491; ++j)
    {
        int p[4] ={-10,0,10,20};
        //除了前、后10行都进行插值
        float md[6] = {0.0};
        for (int i = 10; i < 481; ++i)
        {
            if (i % 10 == 0)
            {
                cubic[i][j] = tmp[i / 10][j];
                p[0] += 10;
                p[1] += 10;
                p[2] += 10;
                p[3] += 10;
                md[0] = (tmp[p[1]/10][j] - tmp[p[0]/10][j]) * 0.1;
                md[1] = (tmp[p[2]/10][j] - tmp[p[1]/10][j]) * 0.1;
                md[2] = (tmp[p[3]/10][j] - tmp[p[2]/10][j]) * 0.1;
                md[3] = (md[1] - md[0]) * 0.05;
                md[4] = (md[2] - md[1]) * 0.05;
                md[5] = (md[4] - md[3]) * 0.03333333;
            }
            else
            {
                cubic[i][j] = tmp[i / 10 - 1][j]    //watchout -1
                            + md[0] * (i - p[0])
                            + md[3] * (i - p[0]) * (i - p[1])
                            + md[5] * (i - p[0]) * (i - p[1]) * (i - p[2]);
            }
        }
    }
    //处理前、后10行
    for (int j = 0; j < 491; ++j)
    {
        cubic[0][j] = tmp[0][j];
        cubic[490][j] = tmp[49][j];
        int p[4] ={0,10,20,30};
        float md[6] = {0.0};
        md[0] = (tmp[p[1]/10][j] - tmp[p[0]/10][j]) * 0.1;
        md[1] = (tmp[p[2]/10][j] - tmp[p[1]/10][j]) * 0.1;
        md[2] = (tmp[p[3]/10][j] - tmp[p[2]/10][j]) * 0.1;
        md[3] = (md[1] - md[0]) * 0.05;
        md[4] = (md[2] - md[1]) * 0.05;
        md[5] = (md[4] - md[3]) * 0.03333333;
        for(int i = 0; i < 10; ++i)
        {
            cubic[i][j] = tmp[0][j]
                        + md[0] * (i - p[0])
                        + md[3] * (i - p[0]) * (i - p[1])
                        + md[5] * (i - p[0]) * (i - p[1]) * (i - p[2]);
        }
        p[0] = 460;
        p[1] = 470;
        p[2] = 480;
        p[3] = 490;
        md[0] = (tmp[p[1]/10][j] - tmp[p[0]/10][j]) * 0.1;
        md[1] = (tmp[p[2]/10][j] - tmp[p[1]/10][j]) * 0.1;
        md[2] = (tmp[p[3]/10][j] - tmp[p[2]/10][j]) * 0.1;
        md[3] = (md[1] - md[0]) * 0.05;
        md[4] = (md[2] - md[1]) * 0.05;
        md[5] = (md[4] - md[3]) * 0.03333333;
        for(int i = 481; i < 490; ++i)
        {
            cubic[i][j] = tmp[46][j]
                        + md[0] * (i - p[0])
                        + md[3] * (i - p[0]) * (i - p[1])
                        + md[5] * (i - p[0]) * (i - p[1]) * (i - p[2]);
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
    printf("牛顿线性插值所用时间：%f\n", duration_linear);
    printf("牛顿三次插值所用时间：%f\n", duration_cubic);
    printf("程序运行所用时间：%f\n", duration);

}

void LS()
{
/*
    float A[5][6] = { 0.0 };
    float t[9] = { 0.0 };
    void ComputeMatrix(float *coords);
    void GaussSolve();
    void LuSolve();

    int main()
    {
        start = clock();
        //已知初始的5个坐标点
        float x[9] = { -386976.786, -397199.228, -403002.333, -404301.874, -401058.65, -393279.751, -381019.561, -364380.489, -343513.4 };
        float y[9] = { 106369.212, 70584.989, 34008.818, -2946.251, -39859.487, -76305.83, -111859.429, -146097.317, -178603.222 };
        float z[9] = { 61240.44, 41725.648, 21741.252, 1512.866, -18729.308, -38752.308, -58322.344, -77206.812, -95176.378 };

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
 */
}

void Simpson()
{
    start = clock();

    FILE *read = NULL;
    //打开曲面数据的文件
    fopen_s(&read, "surface_data.txt", "r");
    if (!read)
    {
        perror("fail to read !");
        exit(-1);
    }
    //读入.txt文件数据
    double surface[101][101];
    for (int i = 0; i < 101; i++)
    {
        for (int j = 0; j < 101; j++)
        {
            fscanf(read, "%lf", &surface[i][j]);
        }
    }
    fclose(read);

    double area[101] = {0.0};
    for (int i = 0; i < 101; ++i)
    {
        double piece = surface[i][0] + surface[i][100];
        for (int j = 1; j < 50; ++j)
        {
            piece += (4.0 * surface[i][2 * j - 1] + 2.0 * surface[i][2 * j]);
        }
        piece += (4.0 * surface[i][99]);
        area[i] = piece / 75;
    }
    // second Simpson
    double volume = area[0] + area[100];
    for (int i = 1; i < 50; ++i)
    {
        volume += (4.0 * area[2 * i - 1] + 2.0 * area[2 * i]);
    }
    volume += (4.0 * area[99]);
    volume /= 75;
    printf("所求体积为：%f\n", volume);

    stop = clock();
    duration = (double)(stop - start) / CLK_TCK;
    printf("程序运行所用时间：%f\n", duration);
}

void Runge_Kutta()
{
    int height[10] = {30, 40, 50, 60, 80, 90, 100, 110, 120, 130};
    double roh[10] = {7394136673.0, 1858858651.0, 467310199.6, 117480058.3, 7424751.8,
                         1866555.2,     497400.3,    117966.5,     24900.2, 8377.1};
    double sum_x = 0.0, sum_y = 0.0, sum_x2 = 0.0, sum_xy = 0.0;
    // 最小二乘法
    for (int i = 0; i < 10; ++i)
    {
        sum_x += height[i];
        sum_y += log(roh[i]);
        sum_x2 += (height[i] * height[i]);
        sum_xy += (height[i] * log(roh[i]));
    }
    // 解系数方程组
    double H0 = (sum_x2 / sum_x - sum_x / 10.0) / (sum_y / 10.0 - sum_xy / sum_x);
    double r_0 = exp((sum_y + sum_x / H0) / 10.0);
    // 高度70km的大气密度
    double r_70 = r_0 * exp(-70.0 / H0);
    // 统一单位，合并化简微分方程系数
    double b = -1e-11 * r_70;
    float h = 0.0;
    int t = 180;
    double k[5] = {0};
    // Runge-Kutta
    while (true)
    {
        float vn = 11.0;
        float sum = 0.0;
        // 设置Runge-Kutta步长
        printf("请输入计算步长：\n");
        scanf("%f", &h);
        while (sum < t)
        {
            k[1] = h * b * vn * vn;
            k[2] = h * b * (vn + 0.5 * k[1]) * (vn + 0.5 * k[1]);
            k[3] = h * b * (vn + 0.5 * k[2]) * (vn + 0.5 * k[2]);
            k[4] = h * b * (vn + k[3]) * (vn + k[3]);
            vn += (1.0 / 6.0 * (k[1] + 2 * k[2] + 2 * k[3] + k[4]));
            sum += h;
        }
        printf("步长为 %f 四阶Runge-Kutta法计算结果：%f\n", h, vn);
    }

}

void JacobiAndSeidel()
{
/*
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
 */
}

void NewtonIter()
{
	// 已知
	double G = 6.67e-11;
	double M = 5.965e24;
	double R = 6371000.0;
	double H = 100000.0;
	double v1 = 6941.05;
	// 化简
	double d1 = R + H;
	double coeA = v1 * v1 * d1 * d1;
	double coeB = G * M;
	double coeC = 0.5 * v1 * v1 - coeB / d1;
	// 初值
	double d2 = 100.0;
	int count = 0;
	// 第一次迭代，求d2
	while(1)
	{
		++count;
		double tmp = d2 + (coeC * pow(d2,3) + coeB * pow(d2,2) - 0.5 * coeA * d2) / (coeB * d2 - coeA);
		if(fabs(d2 - tmp) < 1e-8)
		{
			d2 = tmp;
			break;
		}
		d2 = tmp;
	}
	printf("第一次Newton迭代：%d 次\n", count);
	// 计算椭圆轨道方程参数
	double a = 0.5 * (d1 + d2);
	double y0 = 0.5 * (d1 - d2);
	double b = sqrt(a * a - y0 * y0);
	// 初值
	double yt = 100.0;
	count = 0;
	// 第一次迭代，求yt
	while(1)
	{
		++count;
		double tmp = yt - ((R*R -yt*yt)/(b*b) + pow(yt-y0,2)/(a*a) - 1) / (2*(yt-y0)/(a*a) - 2*yt/(b*b));
		if(fabs(yt - tmp) < 1e-8)
		{
			yt = tmp;
			break;
		}
		yt = tmp;
	}
	printf("第二次Newton迭代：%d 次\n", count);
	// 求xt
	double xt = sqrt(R * R - yt * yt);
	printf("航天器落点坐标为：(%f, %f)\n", xt, yt);
}