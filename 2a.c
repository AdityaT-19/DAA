#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define ini 10
#define fin 100
#define ste 10
int c=0;
void writeCount(int n, FILE *fp)
{
	fprintf(fp,"%d\t%d\n",n,c);
	c=0;
}
void lSearch(int *a,int n,int key)
{
	for(int i=0;i<n;i++)
	{
		c++;
		if(a[i]==key)
			break;
	}
}
void main()
{
	int *a;
	FILE *f=fopen("LSarrayInfo.txt","w");
	FILE *fB=fopen("LSBest.txt","w");
	FILE *fW=fopen("LSWorst.txt","w");
	srand(time(0));
	for(int n=ini;n<=fin;n+=ste)
	{
		a=(int *)malloc(n*sizeof(int));
		fprintf(f,"Array : \n");
		for(int i=0;i<n;i++)
		{
			a[i]=(rand()+1)%100;
			fprintf(f,"%d\t",a[i]);
		}
		fprintf(f,"\nBest Search : %d\t\tWorst Search : 9999\n",a[0]);
		lSearch(a,n,a[0]);
		writeCount(n,fB);
		lSearch(a,n,9999);
		writeCount(n,fW);
	}
	fclose(f);
	fclose(fB);
	fclose(fW);
	FILE *fg = fopen("LSplot.gnu","w");
fprintf(fg,"set yrange [0:*]\nset xlabel \"n\"\nset ylabel \"t\"\nplot \"LSBest.txt\" w l ti \"Best Case\", \"LSWorst.txt\" w l smooth bezier ti \"Worst Case\", \"LSAvg.txt\" w l ti \"Average Case\"\nset term png\nset output \"LSG.png\"\nreplot\nset term x11");
fclose(fg);
system("gnuplot \"LSplot.gnu\"");
system("eog LSG.png");
}
