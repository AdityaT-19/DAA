#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int c = 0;

void swap(int *a, int *b) 
{
  int t = *a;
  *a = *b;
  *b = t;
}

void heapify(int *a, int n, int ro)
{
  int lar = ro, l = 2 * ro, r = 2 * ro + 1;
  c += 2;
  if (l <= n && a[l] > a[lar])
    lar = l;
  if (r <= n && a[r] > a[lar])
    lar = r;
  if (lar != ro) {
    swap(&a[lar], &a[ro]);
    heapify(a, n, lar);
  }
}

void heapSort(int *a, int n)
{
  for (int i = n / 2; i >= 1; i--)
    heapify(a, n, i);
  for (int i = n; i > 1; i--) 
  {
    swap(&a[1], &a[i]);
    heapify(a, i - 1, 1);
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
  for (int i = 1; i <= n; i++)
    fprintf(fp, "%d\t", a[i]);
  fprintf(fp, "\n");
}
void recordCount(int *a, int n, FILE *f, FILE *fp) 
{
  writeArr(a, n, f);
  heapSort(a, n);
  writeArr(a, n, f);
  writeCount(n, fp);
}
void main() 
{
  FILE *f = fopen("HSArrayInfo.txt", "w");
  FILE *fc = fopen("HSBest.txt", "w");
  int *a;
  srand(time(0));
  fprintf(f, "\t\tBest Case \n");
  for (int n = 10; n <= 100; n += 10) {
    a = (int *)malloc((n + 1) * sizeof(int));
    a[1] = rand() % 100;
    for (int i = 2; i <= n; i++)
      a[i] = a[i - 1];
    recordCount(a, n, f, fc);
    free(a);
  }
  fclose(fc);
  fc = fopen("HSWorst.txt", "w");
  fprintf(f, "\t\tWorst Case \n");
  for (int n = 10; n <= 100; n += 10) {
    a = (int *)malloc((n + 1) * sizeof(int));
    a[1] = rand() % 100;
    for (int i = 2; i <= n; i++)
      a[i] = a[i - 1] + rand() % 10;
    recordCount(a, n, f, fc);
    free(a);
  }
  fclose(fc);
  fclose(f);
  FILE *fg = fopen("HSplot.gnu", "w");
  fprintf(fg, "set xlabel \"n\"\nset ylabel \"t\"\nplot \"HSBest.txt\" w l ti "
              "\"Best Case\", \"HSWorst.txt\" w l smooth bezier ti \"Worst "
              "Case\", \"HSAvg.txt\" w l ti \"Average Case\"\nset term "
              "png\nset output \"HSG.png\"\nreplot\nset term x11");
  fclose(fg);
  system("gnuplot \"HSplot.gnu\"");
  system("eog HSG.png");
}
