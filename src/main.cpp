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
    int height[10] = {30, 40, 50, 60, 80, 90, 100, 110, 120, 130};
    double roh[10] = {7394136673.0, 1858858651.0, 467310199.6, 117480058.3, 7424751.8,
                         1866555.2,     497400.3,    117966.5,     24900.2, 8377.1};
    double sum_x = 0.0, sum_y = 0.0, sum_x2 = 0.0, sum_xy = 0.0;
    // ��С���˷�
    for (int i = 0; i < 10; ++i)
    {
        sum_x += height[i];
        sum_y += log(roh[i]);
        sum_x2 += (height[i] * height[i]);
        sum_xy += (height[i] * log(roh[i]));
    }
    // ��ϵ��������
    double H0 = (sum_x2 / sum_x - sum_x / 10.0) / (sum_y / 10.0 - sum_xy / sum_x);
    double r_0 = exp((sum_y + sum_x / H0) / 10.0);
    // �߶�70km�Ĵ����ܶ�
    double r_70 = r_0 * exp(-70.0 / H0);
    // ͳһ��λ���ϲ�����΢�ַ���ϵ��
    double b = -1e-11 * r_70;
    float h = 0.0;
    int t = 180;
    double k[5] = {0};
    // Runge-Kutta
    while (true)
    {
        float vn = 11.0;
        float sum = 0.0;
        // ����Runge-Kutta����
        printf("��������㲽����\n");
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
        printf("����Ϊ %f �Ľ�Runge-Kutta����������%f\n", h, vn);
    }
    stop = clock();
    duration = (double)(stop - start) / CLK_TCK;
    printf("������������ʱ�䣺%f\n", duration);

    system("pause");
    return 0;
}
