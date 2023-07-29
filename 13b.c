#include<stdio.h>

int n,cap,opc=0;
int f[10][10],w[10],v[10];

int max(int a,int b)
{
	return a>b?a:b;
}

int mFkS(int i ,int j)
{
	if(f[i][j]==-1)
	{
			opc++;
			int val;
			if(j-w[i]>=0)
				val=max(mFkS(i-1,j),v[i]+mFkS(i-1,j-w[i]));
			else
				val=mFkS(i-1,j);
			f[i][j]=val;
	}
}

void comp()
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
	for(int i=1;i<=n;i++)
	{
		printf("Enter the value and weight for item %d : ",i);
		scanf("%d%d",&v[i],&w[i]);
	}
	for(int i=0;i<=n;i++)
		f[i][0]=0;
	for(int j=0;j<=cap;j++)
		f[0][j]=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=cap;j++)
			f[i][j]=-1;
	printf("The optimal solution is : %d\n",mFkS(n,cap)); 
	comp();
	printf("\nThe operation count is : %d\n",opc);
}
