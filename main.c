#include <stdio.h>
#include <limits.h>

#define MAXVALUE 10 //Max number of vertices in the graph.

char getLabel(int vertex) {
    return 'A' + vertex;
}

int minDistance(int dist[], int sptSet[], int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

void printSolution(int dist[], int parent[], int src, int dest) {
    printf("\nThe shortest path from %c to %c:\n", getLabel(src), getLabel(dest));
    printf("Vertex: \t Distance from Source: \t Path:\n");
    printf("%c \t\t %d \t\t\t\t %c", getLabel(dest), dist[dest], getLabel(dest));

    int v = dest;
    while (parent[v] != -1) {
        printf(" <- %c", getLabel(parent[v]));
        v = parent[v];
    }

    printf("\n\n");
}

void printMatrixWithPath(int graph[MAXVALUE][MAXVALUE], int path[MAXVALUE], int V, int steps[MAXVALUE][MAXVALUE]) {
    printf("\nAdjacency Matrix with Path Marked (Step Numbers):\n");
    printf("  ");
    for (int i = 0; i < V; i++) {
        printf("%c  ", getLabel(i));
    }
    printf("\n");

    for (int i = 0; i < V; i++) {
        printf("%c ", getLabel(i));
        for (int j = 0; j < V; j++) {
            if (path[i] == 1 && path[j] == 1) {
                printf(" (%d) ", steps[i][j]);
            } else {
                printf(" %d ", graph[i][j]);
            }
        }
        printf("\n");
    }
}

void dijkstraAlgo(int graph[MAXVALUE][MAXVALUE], int src, int dest, int V) {
    int dist[MAXVALUE]; //The output array holds the shortest distance from source to i.
    int sptSet[MAXVALUE];
    int parent[MAXVALUE]; //Array to store shortest path tree.

    //Initialize distances as infinite, sptSet as false, parent as -1.
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
        parent[i] = -1;
    }

    //Distance to source vertex from itself will always be 0.
    dist[src] = 0;

    //Find the shortest path for all the vertices.
    for (int count = 0; count < V - 1; count++) {
        //Pick vertex of min distance from the set of vertices not processed.
        //'u' is equal to source in first iteration.
        int u = minDistance(dist, sptSet, V);

        //Mark the selected vertex as processed.
        sptSet[u] = 1;

        //Update dist value of the adjacent vertices of the chosen vertex.
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    //Create step numbers for each edge visited.
    int steps[MAXVALUE][MAXVALUE];
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            steps[i][j] = 0;
        }
    }

    int stepNumber = 1;
    for (int v = dest; parent[v] != -1; v = parent[v]) {
        steps[parent[v]][v] = stepNumber++;
    }

    //Print the distance array as well as the shortest path.
    printSolution(dist, parent, src, dest);
    //Print adjacency matrix with the full path marked.
    printMatrixWithPath(graph, sptSet, V, steps);
}

int main() {
    int V;
    printf("Enter the number of vertices (max of %d): ", MAXVALUE);
    scanf("%d", &V);

    int graph[MAXVALUE][MAXVALUE];

    printf("\nEnter the adjacency matrix (0 for no edge, spaces between.):\n");
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            scanf("%d", &graph[i][j]);

    int src, dest;
    printf("\nEnter the starting vertex: ");
    scanf("%d", &src);

    printf("Enter the ending vertex: ");
    scanf("%d", &dest);

    dijkstraAlgo(graph, src, dest, V);

    return 0;
}
