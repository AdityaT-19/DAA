#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int c=0;
void bSort(int *a,int n)
{
	for(int i = 0;i<n-1;i++)
	{
		int ex=0;
		for(int j=0;j<n-1-i;j++)
		{
			c++;
			if(a[j+1]<a[j])
			{
				ex++;
				int t=a[j];
				a[j]=a[j+1];
				a[j+1]=t;
			}
		}
		if(!ex) break;
	}
}
void sSort(int *a,int n)
{
	int j,min;
	for(int i = 0;i<n-1;i++)
	{
		min=i;
		for(j=i+1;j<n;j++)
		{
			c++;
			if(a[j]<a[min])
			{
				min=j;
				
			}
		}
		int t=a[min];
		a[min]=a[i];
		a[i]=t;
	}
}
void ISort(int *a,int n)
{
	for(int i=1;i<n;i++)
	{
		int j,t=a[i];
		for(j=i-1;j>=0;j--)
		{
			c++;
			if(a[j]>t)
				a[j+1]=a[j];
			else 
				break;
		}
		a[j+1]=t;
	}
}
void writeCount(int n,FILE *fp)
{
	fprintf(fp,"%d\t%d\n",n,c);
	c=0;
}
void writeArr(int *a,int n,FILE *fp)
{	
	fprintf(fp,"Array : \n");
	for(int i = 0;i<n;i++)
		fprintf(fp,"%d\t",a[i]);
	fprintf(fp,"\n");
}
void recordCount(int *a,int n,FILE *f,FILE *fp,void (*Sort)(int *,int))
{
	writeArr(a,n,f);
	Sort(a,n);
	writeArr(a,n,f);
	writeCount(n,fp);
}
void main()
{
	FILE *f=fopen("BSArrayInfo.txt","w");
	FILE *fc=fopen("BSBest.txt","w");
	int *a;srand(time(0));
	fprintf(f,"\t\tBest Case \n");
	for(int n=10;n<=100;n+=10)
	{
		a=(int *)malloc(n*sizeof(int));
		a[0]=rand()%100;
		for(int i=1;i<n;i++)
			a[i]=a[i-1]+rand()%10;
		recordCount(a,n,f,fc,bSort);
	}
	fclose(fc);
	fc=fopen("BSWorst.txt","w");
	fprintf(f,"\t\tWorst Case \n");
	for(int n=10;n<=100;n+=10)
	{
		a=(int *)malloc(n*sizeof(int));
		a[n-1]=rand()%100;
		for(int i=n-1;i>0;i--)
			a[i-1]=a[i]+rand()%10;
		recordCount(a,n,f,fc,bSort);
	}
	fclose(fc);
	fclose(f);
	f=fopen("SSArrayInfo.txt","w");
	fc=fopen("SSCount.txt","w");
	for(int n=10;n<=100;n+=10)
	{
		a=(int *)malloc(n*sizeof(int));
		for(int i=0;i<n;i++)
			a[i]=rand()%100;
		recordCount(a,n,f,fc,sSort);
	}
	fclose(fc);
	fclose(f);
	f=fopen("ISArrayInfo.txt","w");
	fc=fopen("ISBest.txt","w");
	fprintf(f,"\t\tBest Case \n");
	for(int n=10;n<=100;n+=10)
	{
		a=(int *)malloc(n*sizeof(int));
		a[0]=rand()%100;
		for(int i=1;i<n;i++)
			a[i]=a[i-1]+rand()%10;
		recordCount(a,n,f,fc,ISort);
	}
	fclose(fc);
	fc=fopen("ISWorst.txt","w");
	fprintf(f,"\t\tWorst Case \n");
	for(int n=10;n<=100;n+=10)
	{
		a=(int *)malloc(n*sizeof(int));
		a[n-1]=rand()%100;
		for(int i=n-1;i>0;i--)
			a[i-1]=a[i]+rand()%10;
		recordCount(a,n,f,fc,ISort);
	}
	fclose(fc);
	fclose(f);
	FILE *fg = fopen("BSplot.gnu","w");
	fprintf(fg,"set xlabel \"n\"\nset ylabel \"t\"\nplot \"BSBest.txt\" w l ti \"Best Case\", \"BSWorst.txt\" w l smooth bezier ti \"Worst Case\", \"BSAvg.txt\" w l ti \"Average Case\"\nset term png\nset output \"BSG.png\"\nreplot\nset term x11");
	fclose(fg);
	system("gnuplot \"BSplot.gnu\"");
	system("eog BSG.png");
}
