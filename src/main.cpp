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
    // first Simpson
    double area[101] = {0.0};
    for (int i = 0; i < 101; ++i)
    {
        double piece = surface[i][0] + surface[i][100];
        for (int j = 1; j < 50; ++j)
        {
            piece += (4.0 * surface[i][2 * j - 1] + 2.0 * surface[i][2 * j]);
        }
        piece += (4.0 * surface[i][99]);
        area[i] = piece/75;
    }
    // second Simpson
    double volume = area[0] + area[100];
    for(int i = 1; i < 50; ++i)
    {
        volume += (4.0 * area[2 * i - 1] + 2.0 * area[2 * i]);
    }
    volume += (4.0 * area[99]);
    volume /= 75;
    printf("所求体积为：%f\n", volume);

    stop = clock();
    duration = (double)(stop - start) / CLK_TCK;
    printf("程序运行所用时间：%f\n", duration);

    system("pause");
    return 0;
}
