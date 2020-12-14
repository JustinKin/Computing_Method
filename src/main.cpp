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

    double area = 0.0;
    for (int i = 0; i < 100; ++i)
    {
        double piece = surface[i][0] + surface[i][101];
        for (int j = 1; j < 50; ++j)
        {
            piece += (4.0 * surface[i][2 * j - 1] + 2.0 * surface[i][2 * j]);
        }
        piece += (4.0 * surface[i][99]);
        area += piece;
    }
    area /= 150.0;
    double volume = area * 0.04;
    printf("所求体积为：%f\n", volume);

    stop = clock();
    duration = (double)(stop - start) / CLK_TCK;
    printf("程序运行所用时间：%f\n", duration);

    system("pause");
    return 0;
}
