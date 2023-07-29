#include <stdio.h>
int a[10][10], n, opc = 0, visit[10], acyclic = 1, S[10], top = -1, pop[10], k = 0;
void dfs(int v)
{
    int i, f = 0;
    S[++top] = v;
    opc++;
    while (top != -1)
    {
        f = 0;
        v = S[top];
        visit[v] = 1;
        for (i = 1; i <= n; i++)
        {
            if (a[v][i] && visit[i] == 1)
            {
                acyclic = 0;
            }
            if (a[v][i] && visit[i] == -1)
            {
                opc++;
                S[++top] = i;
                visit[i] = 0;
                f = 1;
                break;
            }
        }
        if (f == 0)
        {
            opc++;
            visit[S[top]] = 2;
            pop[k++] = S[top--];
        }
    }
}
void topoSort()
{
    int i, j;
    for (i = 1; i <= n; i++)
    {
        if (visit[i] == -1 || visit[i] == 0)
            dfs(i);
    }
    if (acyclic)
    {
        printf("\nToplogical Sorting is \n");
        for (j = n - 1; j >= 0; j--)
            printf("%d ", pop[j]);
        printf("\n");
    }
    else
        printf("Toplogical Sorting is not possible because graph is Cyclic\n");
}
int main()
{
    int i, j, start = 1;
    printf("Enter the number of nodes : ");
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        visit[i] = -1;
    printf("Enter the adjacency matrix\n");
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            scanf("%d", &a[i][j]);
    dfs(start);
    topoSort();
    printf("Operation Count : %d\n", opc);
    return 0;
}
