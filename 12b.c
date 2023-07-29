#include<stdio.h>
#include<stdio.h>

int n,opc=0;

int min(int a,int b)
{	
	return a < b ? a : b;
}

void cpy(int s[n+1][n+1],int d[n+1][n+1])
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			d[i][j]=s[i][j];
}

void floyd(int a[n+1][n+1])
{
	int r0[n+1][n+1],r1[n+1][n+1];
	cpy(a,r0);
	for(int k=1;k<=n;k++)
	{
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			{
				opc++;
				r1[i][j]=min(r0[i][j],r0[i][k]+r0[k][j]);
			}
		cpy(r1,r0);
	}
	printf("The all pair shortest distance matrix is :\n");
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			printf("%d  ",r1[i][j]);
		printf("\n");
	}
}

void main()
{
	printf("Enter the number of vertices : ");
	scanf("%d",&n);
	int a[n+1][n+1];
	printf("Enter the weight matrix : \n");
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&a[i][j]);
	floyd(a);		
}
