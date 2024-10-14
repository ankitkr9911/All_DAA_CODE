#include<stdio.h>
#include<stdbool.h>
#include<limits.h>

#define V 7 //No of vertices in the graph

int minkey(int key[],bool mstset[])
{
    int min = INT_MAX;
    int min_index;
    for(int v=0;v<V;v++)
    {
        if(mstset[v]==false && key[v]<min)
        {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

void printMST(int parent[],int graph[V][V])
{
    printf("Edge\tWeight\n");
    for(int i=1;i<V;i++)
    {
        printf("%d - %d \t%d\n",i,parent[i],graph[i][parent[i]]);
    }
    printf("\n");
}

void primMST(int graph[V][V])
{
    int parent[V]; //Array to store the constructed MST 
    int key[V];    //Used to pick minimum weight edge from the key
    bool mstset[V];  //represent which vertex included in the MST

    for(int i=0;i<V;i++)
    {
        key[i] = INT_MAX;
        mstset[i] = false;
    }
    key[0] = 0;
    parent[0] = -1; // parent[v] is used to store the predecessor vertex of v 

    for(int j=0;j<V-1;j++)
    {
        //find out the edge with minimum weight
        int u = minkey(key,mstset);

        //include this vertex in the mst
        mstset[u] = true;

        // Update key value and parent index of the adjacent vertices of the picked vertex
        for(int v=0;v<V;v++)
        {
            if(mstset[v]!=true && graph[u][v]!=0 && graph[u][v]<key[v])
            {
                key[v] = graph[u][v];
                parent[v] = u; 

            }
        }
    }

    printMST(parent,graph);
}

int main()
{
    int graph[V][V] = {
        {0,0,8,0,13,17,0},
        {0,0,20,0,0,0,6},
        {8,20,0,11,0,0,0},
        {0,0,11,0,12,0,0},
        {13,0,0,12,0,15,0},
        {17,0,0,0,15,0,18},
        {0,6,0,0,0,18,0}
    };

    primMST(graph);

    return 0;
}
