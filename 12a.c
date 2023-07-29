#include<stdio.h>
#include<stdio.h>

int n,opc=0;

void cpy(int s[n+1][n+1],int d[n+1][n+1])
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			d[i][j]=s[i][j];
}

void warshall(int a[n+1][n+1])
{
	int r0[n+1][n+1],r1[n+1][n+1];
	cpy(a,r0);
	for(int k=1;k<=n;k++)
	{
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			{
				opc++;
				if(r0[i][j]||(r0[i][k]&&r0[k][j]))
					r1[i][j]=1;
				else
					r1[i][j]=0;
			}
		cpy(r1,r0);
	}
	printf("The transitivity closure is :\n");
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			printf("%d  ",r1[i][j]);
		printf("\n");
	}
}

int checkDAG(int a[n+1][n+1])
{	
	int f=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(a[i][j]&&a[j][i])
			{
				f=0;
				break;
			}
	return f;
}

void main()
{
	printf("Enter the number of vertices : ");
	scanf("%d",&n);
	int a[n+1][n+1];
	printf("Enter the adjacency matrix : \n");
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&a[i][j]);
	if(checkDAG(a))
		warshall(a);
	else
		printf("Graph not a DAG,Warshall's algorithm not applicable\n");
}
