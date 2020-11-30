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
            }
            else
            {
                float md[4] = {img[i][p[0]/10], img[i][p[1]/10], img[i][p[2]/10], img[i][p[3]/10]};
                float sum = md[0];
                float product = 1.0;
                for(int item=1, max=3; item<4; ++item,--max)
                {
                    for(int k = 0; k < max; ++k)
                    {
                        md[k] = (md[k+1] - md[k]) / (10 * item);
                    }
                    product *= (j - p[item-1]);
                    sum += md[0] * product;
                }
                tmp[i][j] = sum;
            }
        }
    }
    //����ǰ����10��
    for(int i = 0; i <50; ++i)
    {
        tmp[i][0] = img[i][0];
        tmp[i][490] = img[i][49];
        int p[4] ={0,10,20,30};
        float md[4] = {img[i][0], img[i][1], img[i][2], img[i][3]};
        for (int j = 1; j <10; j++)
        {
            float sum = md[0];
            float product = 1.0;
            for(int item=1, max=3; item<4; ++item,--max)
            {
                for(int k = 0; k < max; ++k)
                {
                    md[k] = (md[k+1] - md[k]) / (10 * item);
                }
                product *= (j - p[item-1]);
                sum += md[0] * product;
            }
            tmp[i][j] = sum;
        }
        p[0] = 460;
        p[1] = 470;
        p[2] = 480;
        p[3] = 490;
        md[0] = img[i][46];
        md[1] = img[i][47];
        md[2] = img[i][48];
        md[3] = img[i][49];
        for (int j = 481; j <490; j++)
        {
            float sum = md[0];
            float product = 1.0;
            for(int item=1, max=3; item<4; ++item,--max)
            {
                for(int k = 0; k < max; ++k)
                {
                    md[k] = (md[k+1] - md[k]) / (10 * item);
                }
                product *= (j - p[item-1]);
                sum += md[0] * product;
            }
            tmp[i][j] = sum;
        }
    }
    //��ֵ��
    // ��ѭ��j���У���ѭ��i����
    int cubic[491][491];
    for (int j = 0; j < 491; ++j)
    {
        int p[4] ={-10,0,10,20};
        //����ǰ����10�ж����в�ֵ
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
            }
            else
            {
                float md[4] = {tmp[p[0]/10][j], tmp[p[1]/10][j], tmp[p[2]/10][j], tmp[p[3]/10][j]};
                float sum = md[0];
                float product = 1.0;
                for(int item=1, max=3; item<4; ++item,--max)
                {
                    for(int k = 0; k < max; ++k)
                    {
                        md[k] = (md[k+1] - md[k]) / (10 * item);
                    }
                    product *= (j - p[item-1]);
                    sum += md[0] * product;
                }
                cubic[i][j] = sum;
            }
        }
    }
    //����ǰ����10��
    for (int j = 0; j < 491; ++j)
    {
        cubic[0][j] = tmp[0][j];
        cubic[490][j] = tmp[49][j];
        int p[4] ={0,10,20,30};
        float md[4] = {tmp[0][j], tmp[1][j], tmp[2][j], tmp[3][j]};
        for(int i = 0; i < 10; ++i)
        {
            float sum = md[0];
            float product = 1.0;
            for(int item=1, max=3; item<4; ++item,--max)
            {
                for(int k = 0; k < max; ++k)
                {
                    md[k] = (md[k+1] - md[k]) / (10 * item);
                }
                product *= (i - p[item-1]);
                sum += md[0] * product;
            }
            cubic[i][j] = sum;
        }
        p[0] = 460;
        p[1] = 470;
        p[2] = 480;
        p[3] = 490;
        md[0] = tmp[46][j];
        md[1] = tmp[47][j];
        md[2] = tmp[48][j];
        md[3] = tmp[49][j];
        for(int i = 481; i < 490; ++i)
        {
            float sum = md[0];
            float product = 1.0;
            for(int item=1, max=3; item<4; ++item,--max)
            {
                for(int k = 0; k < max; ++k)
                {
                    md[k] = (md[k+1] - md[k]) / (10 * item);
                }
                product *= (i - p[item-1]);
                sum += md[0] * product;
            }
            cubic[i][j] = sum;
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
