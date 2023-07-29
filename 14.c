#include <stdio.h>
#include <stdlib.h>

int cost[10][10], n, min_cost = 0, min, a, b, visited[10] = {0}, edges = 0, count = 0;

void createGraph()
{
    int i, j;
    printf("Enter no. of vertices: ");
    scanf("%d", &n);
    printf("Enter Weight Matrix: \n");
    for (i = 1; i <= n; ++i)
    {
        for (j = 1; j <= n; j++)
        {
            scanf("%d", &cost[i][j]);
            if (cost[i][j] == 0)
                cost[i][j] = 1000;
        }
    }
}
void prim()
{
    int i, j;
    
    printf("Minimum Cost Spanning Tree\n");
    visited[1] = 1;
    while (edges < n - 1)
    {
        min = 1000;
        for (i = 1; i <= n; i++)
        {
            count++;
            if (visited[i])
            {
                for (j = 1; j <= n; j++)
                {
                    if (cost[i][j] < min && !visited[j])
                    {
                        min = cost[i][j];
                        a = i;
                        b = j;
                    }
                }
            }
        }
        if(min<1000)
            printf("%d -> %d : Cost-%d\n", a, b, min);
        else
        {  
            printf("The Graph is disconnected,Prim's Algorithm not applicable\n");
            exit(1);
        }
        min_cost += min;
        visited[b] = 1;
        edges++;
    }

    printf("Minimum Cost: %d\n", min_cost);
}
void main()
{
    int i, j;
    createGraph();
    prim();
    printf("Operation Count : %d\n", count);
}
