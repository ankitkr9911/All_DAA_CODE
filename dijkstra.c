#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define V 9

int minDistance(int dist[], bool sptset[])
{
    int min = INT_MAX;
    int min_index;

    for (int i = 0; i < V; i++)
    {
        if (sptset[i]!=true && dist[i] < min)
        {
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

void printMST(int dist[], int parent[])
{
    printf("Vertex\tDistance From Source\tPath\n");
    for (int i = 1; i < V; i++)
    {
        printf("%d \t\t %d \t\t", i, dist[i]);

        int j = i;
        printf("%d ", j);
        while (parent[j] != -1)
        {
            printf("<- %d ", parent[j]);
            j = parent[j];
        }
        printf("\n");
    }
    printf("\n");
}

void dijkstra(int graph[V][V])
{
    int dist[V];    // dist[i] stores the shortest distance of i from source 0
    int parent[V];  // stores the sbortest path tree
    bool sptset[V]; // stores whether vertex is included in the shortest path tree or not

    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
        sptset[i] = false;
        parent[i] = -1;
    }

    dist[0] = 0;

    for (int v = 0; v < V - 1; v++)
    {
        // picking the vertex with minimum weight
        int u = minDistance(dist, sptset);

        // including the vertex in the sptset
        sptset[u] = true;

        for (int v = 0; v < V; v++)
        {
            if (!sptset[v] && graph[u][v] != 0 && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    printMST(dist, parent);
}

int main()
{
    int graph[V][V] = {
        {0,4,0,0,8,0,0,0,0},
        {4,0,8,0,11,0,0,0,0},
        {0,8,0,7,0,0,4,0,2},
        {0,0,7,0,0,0,14,9,0},
        {8,11,0,0,0,1,0,0,7},
        {0,0,0,0,1,0,2,0,6},
        {0,0,4,14,0,2,0,10,0},
        {0,0,0,9,0,0,10,0,0},
        {0,0,2,0,7,6,0,0,0}
    };

    dijkstra(graph);

    return 0;
}