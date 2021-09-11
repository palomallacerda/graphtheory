/*
    Implementação do algorítimo de Ford Fullkerson
*/
#include <iostream>
#include <vector> //vetor
#include <stdlib.h>
#include <queue> //pilha
#include <string.h> //memset
#include <climits>

using namespace std;

typedef vector <int> HI;
typedef vector <HI> ford; // Criando a lista de adjacencia

struct graph{
    int vertice;
    int aresta;
    ford grap_list;
};

// ---------------- BFS ALGORITHM -----------------
bool my_bfs(graph g, ford resto, int s, int e, int pai[]){
    bool last_visi[g.vertice];
    memset(last_visi, false, sizeof(bool) * g.vertice);
    last_visi[s] = true;
    queue<int> pilha;
    pilha.push(s);

    int deque;

    while(!pilha.empty()){
        deque = pilha.front();
        pilha.pop();

        for(int i = 0; i < g.vertice; i++){
            if(resto[deque][i] > 0 && !last_visi[i])
            {
                pai[i] = deque;
                last_visi[i] = true;
                pilha.push(i);
            }
        }
    }
    return last_visi[e];
}

int ford_fulkerson(graph g, int s, int e)
{
    int x, y, max_flow = 0;
    int *pai = new int[g.vertice];

    ford resto;
    resto.resize(g.vertice);

    for(int i = 0; i < g.vertice; i++){
        resto[i].resize(g.vertice);
        for(int j = 0; j < g.vertice; j++) resto[i][j] = g.grap_list[i][j];
    }

    while(my_bfs(g, resto, s, e,pai)){
        int path = INT_MAX;

        for (y = e;y != s; y = pai[y]){
			x = pai[y];
            if (resto[x][y] < path) path = resto[x][y];
		}

		for( y = e; y != s; y = pai[y]){ // a beleza da coisa
			x = pai[y];
			resto[x][y] -= path;
			resto[y][x] += path;
		}
        max_flow += path;
    }
    return max_flow;
}
// ----------------  Incicializando os vetores -----------------

void iniciando (int i, graph g, int v1, int v2, int weight, int fonte, int sumidouro){
    if(i< g.aresta){
        scanf("%d %d %d", &v1, &v2, &weight);
        g.grap_list[v1][v2] = weight;
        iniciando(i+1, g, v1, v2, weight, fonte, sumidouro);
    }else{
       int MAX_FLOW =  ford_fulkerson(g, fonte, sumidouro);
       printf("Your max flow is: %d\n",MAX_FLOW);
    }
}

int main()
{
    graph g;
    int  v1,v2, weight, fonte, sumidouro;

    scanf("%d%d", &g.vertice, &g.aresta); // Pega qtd vertices e arestas
    scanf("%d%d", &fonte, &sumidouro); // vertice incial e final

    g.grap_list.resize(g.vertice);

    for (int i = 0; i < g.vertice; i++){
        g.grap_list[i].resize(g.vertice);
    }

    iniciando(0, g, v1,v2,weight, fonte, sumidouro);
    return 0;
}
