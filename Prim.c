#include <stdio.h>
#include <limits.h>
#include<stdbool.h>

#define V 7 //Number of vertices in the graph

int minKey(int key[]);
int printMST(int parent[], int n, int graph[V][V]);
void primMST(int graph[V][V]);

int main() {
	//Adjacency matrix
	int graph[V][V] = {{0, 5, 8, 7, 0, 0, 0},
	                   {5, 0, 0, 9, 0, 3, 0},
	                   {8, 0, 0, 6, 0, 0, 4},
	                   {7, 9, 6, 0, 3, 6, 5},
	                   {0, 0, 0, 3, 0, 5, 9},
	                   {0, 3, 0, 6, 5, 0, 0},
	                   {0, 0, 4, 5, 9, 0, 0}};

	//Execute the algorithm and print the solution
	primMST(graph);

	return 0;
}

void primMST(int graph[V][V]) {
	//Store constructed MST
	int parent[V];
	//Key values used to select the best vertex
	int key[V];

	//Initialize all keys as INT_MAX
	for(int i = 0; i < V; i++) {
		key[i] = INT_MAX;
	}

	//Insert the 1st vertex in MST. Make key 0 so that this vertex is picked as first vertex.
	key[0] = 0;
	parent[0] = -1; //First node is the root of MST

	//The MST will have V vertices
	for(int count = 0; count < V-1; count++) {
		//Pick the minimum key vertex from the set of vertices not yet included in MST
		int u = minKey(key);

		//Update key value and parent index of the adjacent vertices of the picked vertex.
		//Consider only those vertices which are not yet included in MST
		for(int v = 0; v < V; v++) {
			//graph[u][v] is non zero only for adjacent vertices
			//key[v] != -1 is false forvertices not yet included in MST
			if(graph[u][v] && key[v] != -1) {
				parent[v] = u;
				key[v] = graph[u][v];
			}
		}

		printf("Execution %i\n", count + 1);
		for(int i = 0; i < V; i++) 
			printf(" Vertex %c: %i\n", i + 65, key[i]);
		printf("\n");
	}

	printMST(parent, V, graph);
}

int minKey(int key[]) {
	int min = INT_MAX, minIndex;
	for(int v = 0; v < V; v++) {
		if(key[v] != -1 && key[v] < min) {
			min = key[v];
			minIndex = v;
		}
	}
	key[minIndex] = -1;
	return minIndex;
}

int printMST(int parent[], int n, int graph[V][V]) {
	printf("Edge \tWeight\n");
	for(int i = 1; i < V; i++)
		printf("%c - %c \t%d \n", parent[i]+65, i+65, graph[i][parent[i]]);
}