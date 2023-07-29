#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int c = 0;
void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}
int part(int *a, int l, int r) {
  int p = a[l], i = l, j = r + 1;
  do {
    do {
      i++;
      c++;
    } while (a[i] < p);
    do {
      j--;
      c++;
    } while (a[j] > p);
    swap(&a[i], &a[j]);
  } while (i < j);
  swap(&a[i], &a[j]);
  swap(&a[l], &a[j]);
  return j;
}

void QSort(int *a, int l, int r) {
  if (l < r) {
    int s = part(a, l, r);
    QSort(a, l, s - 1);
    QSort(a, s + 1, r);
  }
}

void writeCount(int n, FILE *fp) {
  fprintf(fp, "%d\t%d\n", n, c);
  c = 0;
}
void writeArr(int *a, int n, FILE *fp) {
  fprintf(fp, "Array : \n");
  for (int i = 0; i < n; i++)
    fprintf(fp, "%d\t", a[i]);
  fprintf(fp, "\n");
}
void recordCount(int *a, int n, FILE *f, FILE *fp) {
  writeArr(a, n, f);
  QSort(a, 0, n - 1);
  writeArr(a, n, f);
  writeCount(n, fp);
}
void main() {
  FILE *f = fopen("QSArrayInfo.txt", "w");
  FILE *fc = fopen("QSBest.txt", "w");
  int *a;
  srand(time(0));
  fprintf(f, "\t\tBest Case \n");
  for (int n = 10; n <= 100; n += 10) {
    a = (int *)malloc(n * sizeof(int));
    a[0] = rand() % 100;
    for (int i = 1; i < n; i++)
      a[i] = a[i - 1];
    recordCount(a, n, f, fc);
  }
  fclose(fc);
  fc = fopen("QSWorst.txt", "w");
  fprintf(f, "\t\tWorst Case \n");
  for (int n = 10; n <= 100; n += 10) {
    a = (int *)malloc(n * sizeof(int));
    a[0] = rand() % 100;
    for (int i = 1; i < n; i++)
      a[i] = a[i - 1] + rand() % 10;
    recordCount(a, n, f, fc);
  }
  fclose(fc);
  fclose(f);
  FILE *fg = fopen("QSplot.gnu", "w");
  fprintf(fg,
          "set xlabel \"n\"\nset ylabel \"t\"\nplot \"QSBest.txt\" w l ti "
          "\"Best Case\", \"QSWorst.txt\" w l smooth bezier ti \"Worst "
          "Case\"\nset term png\nset output \"QSG.png\"\nreplot\nset term x11");
  fclose(fg);
  system("gnuplot \"QSplot.gnu\"");
  system("eog QSG.png");
}
