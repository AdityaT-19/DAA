#include<stdio.h>

int a[10][10],visit[10],con[20],j=0,acy=1,n,c=0,stk[10],top=-1,p[10];

void dfs(int st)
{
	visit[st]=0;
	stk[++top]=st;
	int s;
	p[st]=0;
	while(top!= -1)
	{
	    s= stk[top];
	    visit[s]=1;
	    for(int i=1;i<=n;i++)
	    {	
	    	if(a[s][i]&&visit[i]==1&&i!=p[s])
	    		acy=0;
		    if(a[s][i]&&visit[i]==-1)
			{
			    stk[++top]=i;
			    visit[i]=0;
			    p[i]=s;
			    break;
			}
	    }
	    if(stk[top]==s)
	    {
	        visit[stk[top]]=2;
	        con[j++]=s;
	        top--;
	    }
	}
}

void concyc()
{
	int i,f=1;
	for(i=1;i<=n;i++)
		if(visit[i]==-1)
		{
			f=0;
			con[j++]=0;
			dfs(i);
		}
	if(f)
		printf("Graph is connected\n");
	else
	{
	    int cc=1;
		printf("Graph is not connected\n{");
		for(int i=0;i<j;i++)
		    if(!con[i])
		    {
		        cc++;
		        printf(" }{ ");
		    }
		    else
		     printf(" %d ",con[i]);
	    printf(" }\nThere are %d connected component\n",cc);
	}
	if(acy)
		printf("Graph is Acyclic\n");
	else
		printf("Graph is Cyclic\n");	
}
void main()
{
	int i,j;
	printf("Enter the number of vertices : ");
	scanf("%d",&n);
	for(i=1;i<=n;i++)
		visit[i]=-1;
	printf("Enter the adjacency matrix : \n");
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
		{
		    c++;
		    scanf("%d",&a[i][j]);
		}
	dfs(1);
	concyc();
	printf("The operation count is : %d\n",c);
}
