//tính số pi
#include<stdio.h>
#include<conio.h>
#include<math.h>
double pi(double n)
{
	double tong = 0;
	double x;
	for (int i = 0; i <= n; i++)
	{
		x = (i - 1/2) / n;
		tong = tong + x;
	}
	return 1/n * tong;
}
void main()
{
	double a;
	printf("Nhập n:");
	scanf_s("%d",a);
	printf("%.16lf\n", pi(a));
}