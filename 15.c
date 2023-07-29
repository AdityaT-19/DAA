#include <stdio.h>
#include <stdlib.h>

int cost[10][10], n, visited[10] = {0}, opc = 0;
int distance[10], parent[10];

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
void Dijkstra(int start)
{
    int count, mindistance, nextnode, i, j;
    for (i = 1; i <= n; i++)
    {
        distance[i] = cost[start][i];
        parent[i] = start;
        visited[i] = 0;
    }

    distance[start] = 0;
    visited[start] = 1;
    count = 0;

    while (count < n - 1)
    {
        mindistance = 999;

        for (i = 1; i <= n; i++)
        {
            opc++;
            if (distance[i] < mindistance && !visited[i])
            {
                mindistance = distance[i];
                nextnode = i;
            }
        }
        visited[nextnode] = 1;
        for (i = 1; i <= n; i++)
            if (!visited[i])
                if (mindistance + cost[nextnode][i] < distance[i])
                {
                    distance[i] = mindistance + cost[nextnode][i];
                    parent[i] = nextnode;
                }
        count++;
    }
    for (i = 1; i <= n; i++)
        if (i != start&&distance[i]<1000)
        {
            printf("%d to %d Distance : %d\n", start, i, distance[i]);
        }
}
void main()
{
    int source;
    createGraph();
    printf("Enter the source : ");
    scanf("%d", &source);
    printf("Minimum Distance from Source(%d) to other Vertices\n", source);
    Dijkstra(source);
    printf("Operation Count : %d\n", opc);
}
