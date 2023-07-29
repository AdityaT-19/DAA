#include<stdio.h>
#include<stdlib.h>

int n,a[10][10],q[10],r=-1,f=0,co=0,opc=0;
int indeg[10]={};

void calindeg()
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
		    opc++;
			if(a[j][i])
				indeg[i]++;
		}
	for(int i=1;i<=n;i++)
        if(!indeg[i])
            q[++r]=i;
}

void topoSort()
{
    int* topo=calloc(n+1,sizeof(int));

	while(r>=f)
	{
		int v=q[f++];
		topo[co++]=v;
		for(int j=1;j<=n;j++)
			if(a[v][j])
			{
				a[v][j]=0;
				indeg[j]--;
				if(indeg[j]==0)
					q[++r]=j;
			}
	}
	if(co<n)
	    printf("The topological sorting is not possible");
	else
	{
	    printf("topological Sorting is : ");
	    for(int i=0;i<co;i++)
	        printf("%d ",topo[i]);
	   printf("\nThe operation count is %d",opc);
	}
	printf("\n");
}

void main()
{
	printf("Enter the number of vertices : ");
	scanf("%d",&n);

	printf("Enter the adjacency matrix : \n");
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&a[i][j]);
	calindeg();
	topoSort();
	
}
