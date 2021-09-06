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

/*
	Implementação do algoritmo de Kruskal
*/
#include <iostream>
#include <vector>
#include <algorithm> // sort
#include <string.h> // memset

using namespace std;
class Aresta{
	int vertice1, vertice2, peso;

public:
	Aresta(int v1, int v2, int peso){
		vertice1 = v1;
		vertice2 = v2;
		this->peso = peso;
	}
	int obterVertice1()	{
		return vertice1;
	}
	int obterVertice2()	{
		return vertice2;
	}
	int obterPeso(){
		return peso;
	}
	// sobrescrita do operador "<"
	bool operator < (const Aresta& aresta2) const
	{
		return (peso < aresta2.peso);
	}
};

class Grafo{
	int V; // número de vértices
	vector<Aresta> arestas; // vetor de arestas
public:
	Grafo(int V){ 
		this->V = V;
	}

	// função que adiciona uma aresta
	void adicionarAresta(int v1, int v2, int peso){
		Aresta aresta(v1, v2, peso);
		arestas.push_back(aresta);
	}

	// função que busca o subconjunto de um elemento "i"
	int buscar(int subset[], int i){
		if(subset[i] == -1)
			return i;
		return buscar(subset, subset[i]);
	}

	// função para unir dois subconjuntos em um único subconjunto
	void unir(int subset[], int v1, int v2){
		int v1_set = buscar(subset, v1);
		int v2_set = buscar(subset, v2);
		subset[v1_set] = v2_set;
	}

	/// função que roda o algoritmo de Kruskal
	void kruskal(){
		vector<Aresta> arvore;
		int size_arestas = arestas.size();

		// ordena as arestas pelo menor peso
		sort(arestas.begin(), arestas.end());

		// aloca memória para criar "V" subconjuntos
		int * subset = new int[V];

		// inicializa todos os subconjuntos como conjuntos de um único elemento
		memset(subset, -1, sizeof(int) * V);

		for(int i = 0; i < size_arestas; i++){
			int v1 = buscar(subset, arestas[i].obterVertice1());
			int v2 = buscar(subset, arestas[i].obterVertice2());

			if(v1 != v2)
			{
				// se forem diferentes é porque NÃO forma ciclo, insere no vetor
				arvore.push_back(arestas[i]);
				unir(subset, v1, v2); // faz a união
			}
		}

		int size_arvore = arvore.size();

		// mostra as arestas selecionadas com seus respectivos pesos
		for(int i = 0; i < size_arvore; i++){
			char v1 = 'A' + arvore[i].obterVertice1();
			char v2 = 'A' + arvore[i].obterVertice2();
			cout << "(" << v1 << ", " << v2 << ") = " << arvore[i].obterPeso() << endl;
		}
	}
};

void iniciando(int i,Grafo g, int v, int aresta, int inicial, int final){
	if(i < aresta){
		scanf("%d %d", &inicial, &final);

		g.adicionarAresta(inicial, final, v);
		iniciando(i+1, g, v, aresta, inicial, final);
	}
	else g.kruskal(); // roda o algoritmo de Kruskal	
}

int main(int argc, char *argv[]){

	int vertice = 0, aresta=0, v1=0, v2=0;
	// Pega a qtd de vértices
	scanf("%d %d",&vertice, &aresta);
	Grafo g(vertice); // grafo
	// adiciona as arestas
	
	iniciando(0, g, vertice, aresta, v1, v2);
	return 0;
}