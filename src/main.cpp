#include <stdio.h>
#include <stdlib.h>
#include <time.h>

clock_t start, stop;
double duration;

int main()
{
    start = clock();

    FILE* read=NULL;
    FILE* write1=NULL;
    FILE* write2=NULL;
    //打开.txt文件
    fopen_s(&read,"image_data/1.txt","r");
    if(!read)
    {
        perror("fail to read !");
        exit (-1);
    }
    fopen_s(&write1,"image_data/1_linear.txt","w");
    if(!write1)
    {
        perror("fail to write1 !");
        exit (-1);
    }
    fopen_s(&write2,"image_data/1_cubic.txt","w");
    if(!write2)
    {
        perror("fail to write1 !");
        exit (-1);
    }
    //读入.txt文件数据
    int img[50][50];
    for(int i=0; i<50; i++)
    {
        for(int j=0; j<50; j++)
        {
            fscanf(read, "%d",&img[i][j]);
        }
    }
    fclose(read);
    //49 * 10 +1 = 491
    int  tmp[50][491];
    //先插值行，共有50行，每行的50列变成491列
    // 外循环i是行，内循环j是列
    for(int i=0; i<50; i++)
    {
        // tmp[i][0] = img[i][0];
        int p1 = -10;
        int p2 = 0;
        for(int j=0; j<491; j++)
        {
            if(j % 10 == 0)
            {
                tmp[i][j] = img[i][j/10];
                p1 += 10;
                p2 += 10;
            }
            else
            {
                tmp[i][j] = img[i][p1/10] * (j - p2) / (p1 -p2)
                          + img[i][p2/10] * (j - p1) / (p2 -p1);
            }
        }
    }
    //插值列
    // 外循环j是列，内循环i是行
    int  linear[491][491];
    for(int j = 0; j < 491 ; ++j)
    {
        // linear[0][j] = tmp[0][j];
        int p1 = -10;
        int p2 = 0;
        for(int i = 0; i <491; ++i)
        {
            if(i % 10 == 0)
            {
                linear[i][j] = tmp[i/10][j];
                p1 += 10;
                p2 += 10;
            }
            else
            {
                linear[i][j] = tmp[p1/10][j] * (i - p2) / (p1 -p2)
                             + tmp[p2/10][j] * (i - p1) / (p2 -p1);
            }
        }
    }







    for(int i=0; i<491; i++)
    {
        for(int j=0; j<491; j++)
        {
            fprintf(write1,"%3d  ", linear[i][j]);
        }
        fprintf(write1,"\n");
    }





/*
    for (int i = 0; i < 50; ++i)
    {
        for (int j = 0; j < 50; ++j)
        {
            printf("%3d  ", img[i][j]);
        }
        printf("\n");
    }
 */
        fclose(write1);





















    stop = clock();
    duration = (double)(stop - start) / CLK_TCK;
    printf("解方程所用时间：%f\n", duration);

    system("pause");
    return 0;
}
