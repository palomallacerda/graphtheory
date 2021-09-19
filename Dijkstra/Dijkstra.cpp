#include <iostream>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <math.h>

using namespace std;

struct Adjacency // Lista de adjacência contendo os pesos das arestas e vertices
{
    int vertice; //Vértice de destino
    int peso; // Peso da aresta que leva ao vértice de destino
    Adjacency *prox; // prox item de adjacência
};
struct Vertice // estrutura que guarda as cabeças das listas de adjacência
{
    Adjacency *head;
};

struct Graph // Estrurura contendo o grafo
{
    int vertices;
    int arestas;
    Vertice *adj;
};

Graph *Create_graph(int v) // Função que cria o grafo
{
    Graph *G = (Graph*)malloc(sizeof(Graph));

    G->vertices = v;
    G->arestas = 0;
    G->adj = (Vertice*)malloc( (v + 1) * sizeof(Adjacency));

    for (int i = 0; i <= v; i++)
    {
        G->adj[i].head = NULL;
    }

    return(G);

}
Adjacency *vertic(int v, int weigth)// coloca o peso da aresta entre o vétice de inicio e v que é o de chegada
{
    Adjacency *aux = (Adjacency*)malloc(sizeof(Adjacency));
    aux->vertice = v;
    aux->peso = weigth;
    aux->prox = NULL;

    return aux;
}
bool Create_Arest(Graph *G, int vi, int vf, int weitgh) // cria as arestas entre os vétices, sendo vi o vértice de inicio e vf o vértice de chegada;
{
    if(!G) return false;
    if(vi < 0 || vi > G->vertices) return false;
    if(vf < 0 || vf > G->vertices) return false;

    Adjacency *novo = vertic(vf , weitgh);
    Adjacency *aux = vertic(vi, weitgh);


    novo->prox = G->adj[vi].head;
    G->adj[vi].head = novo;



    aux->prox = G->adj[vf].head;
    G->adj[vf].head = aux;


    G->arestas++;

    return true;
}
Adjacency *Remove(Adjacency *T, int vrtc)//Função remover para retirar os vértices já verificados
{
    if (T == NULL)
    {
        return T;
    }
    else
    {
        Adjacency *aux = T;
        Adjacency *anterior;

        if (T->vertice == vrtc)
        {
            T = T->prox;
            free(aux);
            return T;
        }



        while (aux->vertice != vrtc)
        {
            anterior = aux;
            aux = aux->prox;
        }

        anterior->prox = aux->prox;
        free(aux);

        return T;
    }
}
Adjacency *Create_queue(Graph *G,double key[])// Cria a fila de vértices
{
    Adjacency *fila = NULL, *novo = NULL;


    for (int i = 1; i <= G->vertices; i++)
    {
        if (fila == NULL)
        {
            novo = vertic(i, key[i]);
            fila = novo;
        }
        else
        {
            novo = vertic(i, key[i]);
            Adjacency *aux = fila;

            while (aux->prox != NULL)
            {
                aux = aux->prox;
            }
            aux->prox = novo;
        }
    }
    return fila;
}
int extrair_min(Adjacency *T,double keys[])// extrai a aresta com menor peso
{
    Adjacency *aux = T;
    int u = aux->vertice;
    float min = INFINITY;

    while (aux != NULL)
    {
        if (keys[aux->vertice] < min)
        {
            min = keys[aux->vertice];
            u = aux->vertice;
        }
        aux = aux->prox;
    }

    return u;
}
bool belong(Adjacency *G, Adjacency *T)// Verifica se um vértice está na fila T
{

    Adjacency *aux = T;

    while (aux != NULL)
    {
        if (G->vertice == aux->vertice)
        {
            return true;
        }
      aux = aux->prox;
    }
    return false;
}
int Dijkstra(Graph *G) // Algoritmo de Prim para calcular a Arvore Geradora Mínima(AGM) ou Minimum Spanning Tree(MST)
{
    int initial;
    int father[G->vertices + 1]; // lista que indica de qual vértice chegou ao vértice atual;
    Adjacency *T = NULL; // Subgrafo no qual será armazenado a árvore;

    double key[G->vertices + 1];

    scanf("%d", &initial);

    if (initial < 0 || initial > G->vertices)
    {
        printf("O vértice não existe\n");

        return 0;
    }

    for (int i = 1; i <= G->vertices; i++)
    {
        key[i] = INFINITY;
        father[i] = -1;
    }
    key[initial] = 0;
    T = Create_queue(G, key);


    while (T != NULL)
    {
        int u = extrair_min(T, key);

        Adjacency *aux = G->adj[u].head;

        while (aux != NULL)
        {
            if (belong(aux, T) == true && (aux->peso + key[u] < key[aux->vertice]))
            {
                father[aux->vertice] = u;
                key[aux->vertice] = aux->peso + key[u];

            }
            aux = aux->prox;
        }
        T = Remove(T, u);
    }


    printf("do you want to print the distance from the starting vertex to a specific vertex?\n(0) : no\n(1) : yes\n\n");

    int decision;

    printf("Decision: ");
    scanf("%d", &decision);

    if (decision == 1)
    {
        int final;
        printf("\nSpecific vertice: ");
        scanf("%d", &final);

        printf("\nDistance(%d, %d) = %.lf\n", initial, final, key[final]);

    }
    else
    {
        printf("\n\n");
        for (int i = 1; i <= G->vertices; i++)
        {
            printf("Distance(%d, %d) = %.lf\n", initial, i, key[i]);
        }

    }
    return 0;


}
int main()
{
    Graph *G;

    int V;
    int E;

    scanf("%d %d", &V, &E);

    G = Create_graph(V);

    for (int i = 0; i < E; i++)
    {
        int vi, vf, Peso;

        scanf("%d %d %d", &vi, &vf, &Peso);

        Create_Arest(G, vi, vf, Peso);
    }

    int cost = Dijkstra(G);

    return 0;
}