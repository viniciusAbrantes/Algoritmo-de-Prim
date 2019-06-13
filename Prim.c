#include <stdio.h>
#include <limits.h>
#define V 7 //Number of vertices in the graph

void primMst(int graph[V][V]);
int minKey(int keys[]);
void printKeys(int keys[], int exeCount);
int printMst(int parents[], int n, int graph[V][V]);

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
	primMst(graph);

	return 0;
}

void primMst(int graph[V][V]) {
	int parents[V];
	int keys[V];

	//Initialize key values
	for(int i = 0; i < V; i++) 
		keys[i] = 0;

	//Select the root node
	keys[V-1] = 1;
	parents[V-1] = -1;

	printKeys(keys, 0); //initial state	

	for(int count = 0; count < V-1; count++) {
		int u = minKey(keys); //Select the best vertex
		for(int v = 0; v < V; v++) {
			if(graph[u][v] && keys[v] != -1 && (keys[v] == 0 || graph[u][v] < keys[v])) {
				parents[v] = u;
				keys[v] = graph[u][v];	
			}
		}
		printKeys(keys, count + 1);
	}
	printMst(parents, V, graph);
}

int minKey(int keys[]) {
	int min = INT_MAX, minIndex;
	for(int v = 0; v < V; v++) {
		if(keys[v] > 0 && keys[v] < min) {
			min = keys[v];
			minIndex = v;
		}
	}
	keys[minIndex] = -1;
	return minIndex;
}

int printMst(int parents[], int n, int graph[V][V]) {
	printf("Edge \tWeight\n");
	for(int i = 0; i < V; i++)
		printf("%c - %c \t%d \n", parents[i]+65, i+65, graph[i][parents[i]]);
}

void printKeys(int keys[], int exeCount) {
	printf("Execution %i\n", exeCount);
	printf(" Vertex\tWeight\n");
	for(int i = 0; i < V; i++) {
		switch(keys[i]) {
			case 0:
				printf(" %c\t-\n", i + 65);
				break;
			case -1:
				printf(" %c\tin\n", i + 65);
				break;
			default:
				printf(" %c\t%i\n", i + 65, keys[i]);
		}
	}
	printf("\n");
}