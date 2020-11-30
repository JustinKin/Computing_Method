#include <stdio.h>
#include <stdlib.h>
#include <time.h>

clock_t start, stop, linear_bg, linear_ed, cubic_ed;
double duration, duration_linear, duration_cubic;

int main()
{
    start = clock();

    FILE *read = NULL;
    FILE *write1 = NULL;
    FILE *write2 = NULL;
    //��.txt�ļ�
    //��ԭʼ���ݵ��ļ�
    fopen_s(&read, "image_data/1.txt", "r");
    if (!read)
    {
        perror("fail to read !");
        exit(-1);
    }
    //�����������Բ�ֵ������ļ�
    fopen_s(&write1, "image_data/Newton_linear.txt", "w");
    if (!write1)
    {
        perror("fail to write1 !");
        exit(-2);
    }
    //�����������β�ֵ������ļ�
    fopen_s(&write2, "image_data/Newton_cubic.txt", "w");
    if (!write2)
    {
        perror("fail to write1 !");
        exit(-3);
    }
    //����.txt�ļ�����
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
    // =====================================���Բ�ֵ=====================================
    //49 * 10 +1 = 491
    int tmp[50][491];
    //�Ȳ�ֵ�У�����50�У�ÿ�е�50�б��491��
    // ��ѭ��i���У���ѭ��j����
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
                md = (img[i][p2 / 10] - img[i][p1 / 10]) / (p2 - p1);
            }
            else
            {
                tmp[i][j] = img[i][p1 / 10] + md * (j - p1);
            }
        }
    }
    //��ֵ��
    // ��ѭ��j���У���ѭ��i����
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
                md = (tmp[p2 / 10][j] - tmp[p1 / 10][j]) / (p2 - p1);
            }
            else
            {
                linear[i][j] = tmp[p1 / 10][j] + md * (i - p1);
            }
        }
    }
    //���Բ�ֵ���д��.txt
    for (int i = 0; i < 491; i++)
    {
        for (int j = 0; j < 491; j++)
        {
            fprintf(write1, "%3d  ", linear[i][j]);
        }
        fprintf(write1, "\n");
    }
    linear_ed = clock();
    // =====================================���β�ֵ=====================================
    //�Ȳ�ֵ�У�����50�У�ÿ�е�50�б��491��
    // ��ѭ��i���У���ѭ��j����
    for (int i = 0; i < 50; i++)
    {
        int p[4] ={-10,0,10,20};
        float md[6] = {0.0};
        //����ǰ����10�ж����в�ֵ
        for (int j = 10; j < 481; j++)
        {
            if (j % 10 == 0)
            {
                tmp[i][j] = img[i][j / 10];
                p[0] += 10;
                p[1] += 10;
                p[2] += 10;
                p[3] += 10;
                md[0] = (img[i][p[1]/10] - img[i][p[0]/10]) / (p[1] - p[0]);
                md[1] = (img[i][p[2]/10] - img[i][p[1]/10]) / (p[2] - p[1]);
                md[2] = (img[i][p[3]/10] - img[i][p[2]/10]) / (p[3] - p[2]);
                md[3] = (md[1] - md[0]) / (p[2] - p[0]);
                md[4] = (md[2] - md[1]) / (p[3] - p[1]);
                md[5] = (md[4] - md[3]) / (p[3] - p[0]);
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
    //����ǰ����10��
    for(int i = 0; i <50; ++i)
    {
        tmp[i][0] = img[i][0];
        tmp[i][490] = img[i][49];
        int p[4] ={0,10,20,30};
        float md[6] = {0.0};
        md[0] = (img[i][p[1]/10] - img[i][p[0]/10]) / (p[1] - p[0]);
        md[1] = (img[i][p[2]/10] - img[i][p[1]/10]) / (p[2] - p[1]);
        md[2] = (img[i][p[3]/10] - img[i][p[2]/10]) / (p[3] - p[2]);
        md[3] = (md[1] - md[0]) / (p[2] - p[0]);
        md[4] = (md[2] - md[1]) / (p[3] - p[1]);
        md[5] = (md[4] - md[3]) / (p[3] - p[0]);
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
        md[0] = (img[i][p[1]/10] - img[i][p[0]/10]) / (p[1] - p[0]);
        md[1] = (img[i][p[2]/10] - img[i][p[1]/10]) / (p[2] - p[1]);
        md[2] = (img[i][p[3]/10] - img[i][p[2]/10]) / (p[3] - p[2]);
        md[3] = (md[1] - md[0]) / (p[2] - p[0]);
        md[4] = (md[2] - md[1]) / (p[3] - p[1]);
        md[5] = (md[4] - md[3]) / (p[3] - p[0]);
        for (int j = 481; j <490; j++)
        {
            tmp[i][j] = img[i][46]
                      + md[0] * (j - p[0])
                      + md[3] * (j - p[0]) * (j - p[1])
                      + md[5] * (j - p[0]) * (j - p[1]) * (j - p[2]);
        }
    }
    //��ֵ��
    // ��ѭ��j���У���ѭ��i����
    int cubic[491][491];
    for (int j = 0; j < 491; ++j)
    {
        int p[4] ={-10,0,10,20};
        //����ǰ����10�ж����в�ֵ
        float md[6] = {0.0};
        for (int i = 10; i < 481; ++i)
        {
            if (i % 10 == 0)
            {
                // cubic[i][j] = 0;
                cubic[i][j] = tmp[i / 10][j];
                p[0] += 10;
                p[1] += 10;
                p[2] += 10;
                p[3] += 10;
                md[0] = (tmp[p[1]/10][j] - tmp[p[0]/10][j]) / (p[1] - p[0]);
                md[1] = (tmp[p[2]/10][j] - tmp[p[1]/10][j]) / (p[2] - p[1]);
                md[2] = (tmp[p[3]/10][j] - tmp[p[2]/10][j]) / (p[3] - p[2]);
                md[3] = (md[1] - md[0]) / (p[2] - p[0]);
                md[4] = (md[2] - md[1]) / (p[3] - p[1]);
                md[5] = (md[4] - md[3]) / (p[3] - p[0]);
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
    //����ǰ����10��
    for (int j = 0; j < 491; ++j)
    {
        cubic[0][j] = tmp[0][j];
        cubic[490][j] = tmp[49][j];
        int p[4] ={0,10,20,30};
        float md[6] = {0.0};
        md[0] = (tmp[p[1]/10][j] - tmp[p[0]/10][j]) / (p[1] - p[0]);
        md[1] = (tmp[p[2]/10][j] - tmp[p[1]/10][j]) / (p[2] - p[1]);
        md[2] = (tmp[p[3]/10][j] - tmp[p[2]/10][j]) / (p[3] - p[2]);
        md[3] = (md[1] - md[0]) / (p[2] - p[0]);
        md[4] = (md[2] - md[1]) / (p[3] - p[1]);
        md[5] = (md[4] - md[3]) / (p[3] - p[0]);
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
        md[0] = (tmp[p[1]/10][j] - tmp[p[0]/10][j]) / (p[1] - p[0]);
        md[1] = (tmp[p[2]/10][j] - tmp[p[1]/10][j]) / (p[2] - p[1]);
        md[2] = (tmp[p[3]/10][j] - tmp[p[2]/10][j]) / (p[3] - p[2]);
        md[3] = (md[1] - md[0]) / (p[2] - p[0]);
        md[4] = (md[2] - md[1]) / (p[3] - p[1]);
        md[5] = (md[4] - md[3]) / (p[3] - p[0]);
        for(int i = 481; i < 490; ++i)
        {
            cubic[i][j] = tmp[46][j]
                        + md[0] * (i - p[0])
                        + md[3] * (i - p[0]) * (i - p[1])
                        + md[5] * (i - p[0]) * (i - p[1]) * (i - p[2]);
        }

    }
    //���β�ֵ���д��.txt
    for (int i = 0; i < 491; i++)
    {
        for (int j = 0; j < 491; j++)
        {
            fprintf(write2, "%3d  ", cubic[i][j]);
        }
        fprintf(write2, "\n");
    }
    cubic_ed = clock();
    //�رղ�ֵ����ļ�
    fclose(write1);
    fclose(write2);

    stop = clock();
    duration_linear = (double)(linear_ed - linear_bg) / CLK_TCK;
    duration_cubic = (double)(cubic_ed - linear_ed) / CLK_TCK;
    duration = (double)(stop - start) / CLK_TCK;
    printf("ţ�����Բ�ֵ����ʱ�䣺%f\n", duration_linear);
    printf("ţ�����β�ֵ����ʱ�䣺%f\n", duration_cubic);
    printf("������������ʱ�䣺%f\n", duration);

    system("pause");
    return 0;
}
