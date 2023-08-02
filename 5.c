#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int c = 0;
void merge(int *b, int p, int *C, int q, int *a)
{
  int i = 0, j = 0, k = 0;
  while (i < p && j < q) 
  {
    c++;
    if (b[i] <= C[j])
      a[k++] = b[i++];
    else
      a[k++] = C[j++];
  }
  if (i == p)
    while (j < q)
      a[k++] = C[j++];
  else
    while (i < p)
      a[k++] = b[i++];
}
void cpy(int *a, int s, int e, int *C)
{
  int i = s, j = 0;
  while (i <= e)
    C[j++] = a[i++];
}
void MSort(int *a, int n)
{
  if (n > 1) {
    int b[n / 2], C[(n + 1) / 2];
    cpy(a, 0, (n - 1) / 2, b);
    cpy(a, n / 2, n - 1, C);
    MSort(b, n / 2);
    MSort(C, (n + 1) / 2);
    merge(b, n / 2, C, (n + 1) / 2, a);
  }
}
void join(int arr[], int left[], int right[], int l, int m, int r) 
{
  int i, j;
  for (i = 0; i <= m - l; i++)
    arr[i] = left[i];
  for (j = 0; j < r - m; j++)
    arr[i + j] = right[j];
}

void split(int arr[], int left[], int right[], int l, int m, int r) 
{
  for (int i = 0; i <= m - l; i++)
    left[i] = arr[i * 2];
  for (int j = 0; j < r - m; j++)
    right[j] = arr[j * 2 + 1];
}

void genWorstCase(int arr[], int l, int r) 
{
  if (l < r) {
    int m = l + (r - l) / 2;
    int left[m - l + 1];
    int right[r - m];
    split(arr, left, right, l, m, r);
    genWorstCase(left, l, m);
    genWorstCase(right, m + 1, r);
    join(arr, left, right, l, m, r);
  }
}
void writeCount(int n, FILE *fp) 
{
  fprintf(fp, "%d\t%d\n", n, c);
  c = 0;
}
void writeArr(int *a, int n, FILE *fp) 
{
  fprintf(fp, "Array : \n");
  for (int i = 0; i < n; i++)
    fprintf(fp, "%d\t", a[i]);
  fprintf(fp, "\n");
}
void recordCount(int *a, int n, FILE *f, FILE *fp) 
{
  writeArr(a, n, f);
  MSort(a, n);
  writeArr(a,n,f);
  writeCount(n, fp);
}
void main() 
{
  FILE *f = fopen("MSArrayInfo.txt", "w");
  FILE *fc = fopen("MSBest.txt", "w");
  int *a;
  srand(time(0));
  fprintf(f, "\t\tBest Case \n");
  for (int n = 10; n <= 100; n += 10) 
  {
    a = (int *)malloc(n * sizeof(int));
    a[0] = rand() % 100;
    for (int i = 1; i < n; i++)
      a[i] = a[i - 1] + rand() % 10;
    recordCount(a, n, f, fc);
  }
  fclose(fc);
  fc = fopen("MSWorst.txt", "w");
  fprintf(f, "\t\tWorst Case \n");
  for (int n = 10; n <= 100; n += 10) 
  {
    a = (int *)malloc(n * sizeof(int));
    a[0] = rand() % 100;
    for (int i = 1; i < n; i++)
      a[i] = a[i - 1] + rand() % 10;
    genWorstCase(a, 0, n - 1);
    recordCount(a, n, f, fc);
  }
  fclose(fc);
  fclose(f);
  FILE *fg = fopen("MSplot.gnu", "w");
  fprintf(fg,
          "set xlabel \"n\"\nset ylabel \"t\"\nplot \"MSBest.txt\" w l ti "
          "\"Best Case\", \"MSWorst.txt\" w l smooth bezier ti \"Worst "
          "Case\"\nset term png\nset output \"MSG.png\"\nreplot\nset term x11");
  fclose(fg);
  system("gnuplot \"MSplot.gnu\"");
  system("eog MSG.png");
}
