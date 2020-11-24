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
    //��.txt�ļ�
    //��ԭʼ���ݵ��ļ�
    fopen_s(&read,"image_data/1.txt","r");
    if(!read)
    {
        perror("fail to read !");
        exit (-1);
    }
    //�����������Բ�ֵ������ļ�
    fopen_s(&write1,"image_data/1_linear.txt","w");
    if(!write1)
    {
        perror("fail to write1 !");
        exit (-1);
    }
    //�����������β�ֵ������ļ�
    fopen_s(&write2,"image_data/1_cubic.txt","w");
    if(!write2)
    {
        perror("fail to write1 !");
        exit (-1);
    }
    //����.txt�ļ�����
    int img[50][50];
    for(int i=0; i<50; i++)
    {
        for(int j=0; j<50; j++)
        {
            fscanf(read, "%d",&img[i][j]);
        }
    }
    fclose(read);
    // =====================================���Բ�ֵ=====================================
    //49 * 10 +1 = 491
    int  tmp[50][491];
    //�Ȳ�ֵ�У�����50�У�ÿ�е�50�б��491��
    // ��ѭ��i���У���ѭ��j����
    for(int i=0; i<50; i++)
    {
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
    //��ֵ��
    // ��ѭ��j���У���ѭ��i����
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
    //���Բ�ֵ���д��.txt
    for(int i=0; i<491; i++)
    {
        for(int j=0; j<491; j++)
        {
            fprintf(write1,"%3d  ", linear[i][j]);
        }
        fprintf(write1,"\n");
    }

    // =====================================���β�ֵ=====================================
    //�Ȳ�ֵ�У�����50�У�ÿ�е�50�б��491��
    // ��ѭ��i���У���ѭ��j����
    for(int i=0; i<50; i++)
    {
        // tmp[i][0] = img[i][0];
        int p1 = -10;
        int p2 = 0;
        int p3 = 10;
        int p4 = 20;
        for(int j=0; j<491; j++)
        {
            if(j % 10 == 0)
            {
                tmp[i][j] = img[i][j/10];
                p1 += 10;
                p2 += 10;
                p3 += 10;
                p4 += 10;
            }
            else
            {
                tmp[i][j] = img[i][p1/10] * (j - p2) * (j - p3) * (j - p4) / ((p1 -p2) * (p1 - p3) * (p1 - p4))
                          + img[i][p2/10] * (j - p1) * (j - p3) * (j - p4) / ((p2 -p1) * (p2 - p3) * (p2 - p4))
                          + img[i][p3/10] * (j - p1) * (j - p2) * (j - p4) / ((p3 -p1) * (p3 - p2) * (p3 - p4))
                          + img[i][p4/10] * (j - p1) * (j - p2) * (j - p3) / ((p4 -p1) * (p4 - p2) * (p4 - p3));
            }
        }
    }
    //��ֵ��
    // ��ѭ��j���У���ѭ��i����
    int  cubic[491][491];
    for(int j = 0; j < 491 ; ++j)
    {
        int p1 = -10;
        int p2 = 0;
        int p3 = 10;
        int p4 = 20;
        for(int i = 0; i <491; ++i)
        {
            if(i % 10 == 0)
            {
                cubic[i][j] = tmp[i/10][j];
                p1 += 10;
                p2 += 10;
                p3 += 10;
                p4 += 10;
            }
            else
            {
                cubic[i][j] = tmp[p1/10][j] * (i - p2) * (i - p3) * (i - p4) / ((p1 -p2) * (p1 - p3) * (p1 - p4))
                            + tmp[p2/10][j] * (i - p1) * (i - p3) * (i - p4) / ((p2 -p1) * (p2 - p3) * (p2 - p4))
                            + tmp[p2/10][j] * (i - p1) * (i - p2) * (i - p4) / ((p3 -p1) * (p3 - p2) * (p3 - p4))
                            + tmp[p2/10][j] * (i - p1) * (i - p2) * (i - p3) / ((p4 -p1) * (p4 - p2) * (p4 - p3));
            }
        }
    }
    //���β�ֵ���д��.txt
    for(int i=0; i<491; i++)
    {
        for(int j=0; j<491; j++)
        {
            fprintf(write2,"%3d  ", cubic[i][j]);
        }
        fprintf(write2,"\n");
    }

   //�رղ�ֵ����ļ�
    fclose(write1);
    fclose(write2);

    stop = clock();
    duration = (double)(stop - start) / CLK_TCK;
    printf("�ⷽ������ʱ�䣺%f\n", duration);

    system("pause");
    return 0;
}
