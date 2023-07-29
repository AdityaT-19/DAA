#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int c = 0;
int strMat(char *t, int n, char *p, int m) 
{
  for (int i = 0; i < n - m; i++) 
  {
    int j;
    for (j = 0; j < m; j++) 
    {
      c++;
      if (t[i + j] != p[j])
        break;
    }
    if (j == 3)
      return i;
  }
  return -1;
}
void writeCount(int n, FILE *fp) 
{
  fprintf(fp, "%d\t%d\n", n, c);
  c = 0;
}
void main() 
{
  char *t, *p;
  FILE *fB = fopen("SMBest.txt", "w");
  FILE *fW = fopen("SMWorst.txt", "w");
  srand(time(0));
  char pB[3] = "aaa", pW[3] = "aab";
  for (int n = 10; n <= 100; n += 10) 
  {
    t = (char *)malloc(n * sizeof(char));
    for (int i = 0; i < n; i++)
      t[i] = 'a';
    strMat(t, n, pB, 3);
    writeCount(n, fB);
    strMat(t, n, pW, 3);
    writeCount(n, fW);
  }
  fclose(fB);
  fclose(fW);
  FILE *fg = fopen("SMplot.gnu", "w");
  fprintf(fg,
          "set yrange[0:*]\nset xlabel \"n\"\nset ylabel \"t\"\nplot "
          "\"SMBest.txt\" w l ti \"Best Case\",\"SMWorst.txt\" w l ti \"Worst "
          "Case\"\nset term png\nset output \"SMG.png\"\nreplot\nset term x11");
  fclose(fg);
  system("gnuplot \"SMplot.gnu\"");
  system("eog SMG.png");
}
