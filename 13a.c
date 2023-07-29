#include<stdio.h>

int n,cap,opc=0;

int max(int a,int b)
{
	return a>b?a:b;
}

void kS(int f[n+1][cap+1],int w[],int v[])
{
	for(int i=0;i<=n;i++)
		f[i][0]=0;
	for(int j=0;j<=cap;j++)
		f[0][j]=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=cap;j++)
		{
			opc++;
			if(j-w[i]>=0)
				f[i][j]=max(f[i-1][j],v[i]+f[i-1][j-w[i]]);
			else
				f[i][j]=f[i-1][j];
		}
	printf("The optimal solution is : %d",f[n][cap]); 
}

void comp(int f[n+1][cap+1],int w[])
{
	int k=0,j=cap,subset[n];
	for(int i=n;i>=1;i--)
		if(f[i][j]!=f[i-1][j])
		{
			subset[k++]=i;
			j-=w[i];
		}
	printf("The composition of the knapsack is : ");
	for(int i=0;i<k;i++)
		printf("%d ",subset[i]);
}

void main()
{
	printf("Enter the number of items and knapSack capacity : ");
	scanf("%d %d",&n,&cap);
	int f[n+1][cap+1],w[n+1],v[n+1];
	for(int i=1;i<=n;i++)
	{
		printf("Enter the value and weight for item %d : ",i);
		scanf("%d%d",&v[i],&w[i]);
	}
	kS(f,w,v);
	comp(f,w);
	printf("The operation count is : %d",opc);
}
