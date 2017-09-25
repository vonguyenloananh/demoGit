#include<stdio.h>  
#include<conio.h>  
#define NRA 62
#define NCA 15
#define NCB 7


void main()
{
	int a[100][100], b[100][100], matrantich[100][100];
	int i;
	int j;
	int k;

	/*printf("Nhap so hang = ");
	scanf_s("%d", &hang);
	printf("\nNhap so cot = ");
	scanf_s("%d", &cot);
	printf("\nNhap cac phan tu cua ma tran thu nhat\n");
	for (i = 0; i<hang; i++)
	{
		for (j = 0; j<cot; j++)
		{
			scanf_s("%d", &a[i][j]);
		}
	}
	printf("Nhap so hang = ");
	scanf_s("%d", &hang);
	printf("\nNhap so cot = ");
	scanf_s("%d", &cot);
	printf("\nNhap cac phan tu cua ma tran thu hai\n");
	for (i = 0; i<hang; i++)
	{
		for (j = 0; j<cot; j++)
		{
			scanf_s("%d", &b[i][j]);
		}
	}*/

	for (i = 0; i < NRA; i++)
	{
		for (j = 0; j < NCA; j++)
		{
			a[i][j] = i + j;
			for (i = 0; i < NCA; i++)
			{
				for (j = 0; j < NCB; j++)
				{
					b[i][j] = i * j;
				}
			}
		}
	}

	printf("\nTich cua hai ma tran la:\n");
	for (i = 0; i<NCA; i++)
	{
		for (j = 0; j<NCB; j++)
		{
			matrantich[i][j] = 0;
			for (k = 0; k<NCB; k++)
			{
				matrantich[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	// hien thi ket qua  
	for (i = 0; i<NCA; i++)
	{
		for (j = 0; j<NCB; j++)
		{
			printf("%d\t", matrantich[i][j]);
		}
		printf("\n");
	}

	
}