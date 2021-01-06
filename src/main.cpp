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
	// ��֪
	double G = 6.67e-11;
	double M = 5.965e24;
	double R = 6371000.0;
	double H = 100000.0;
	double v1 = 6941.05;
	// ����
	double d1 = R + H;
	double coeA = v1 * v1 * d1 * d1;
	double coeB = G * M;
	double coeC = 0.5 * v1 * v1 - coeB / d1;
	// ��ֵ
	double d2 = 100.0;
	int count = 0;
	// ��һ�ε�������d2
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
	printf("��һ��Newton������%d ��\n", count);
	// ������Բ������̲���
	double a = 0.5 * (d1 + d2);
	double y0 = 0.5 * (d1 - d2);
	double b = sqrt(a * a - y0 * y0);
	// ��ֵ
	double yt = 100.0;
	count = 0;
	// ��һ�ε�������yt
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
	printf("�ڶ���Newton������%d ��\n", count);
	// ��xt
	double xt = sqrt(R * R - yt * yt);
	printf("�������������Ϊ��(%f, %f)\n", xt, yt);

	stop = clock();
	duration = (double)(stop - start) / CLK_TCK;
	printf("������������ʱ�䣺%f\n", duration);
	system("pause");
	return 0;
}