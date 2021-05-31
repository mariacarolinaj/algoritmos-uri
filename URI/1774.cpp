/*
 * Maria Carolina Resende Jaudacy - Matrícula 667477 
 * Análise de complexidade para a solução desenvolvida abaixo para o pior cenário do problema "Roteadores" baseada do site GeeksForGeeks:
 *  O(c log r) onde c = quantidade total de cabos que conectam os roteadores antes da otimização e 
 *		    r = quantidade total de roteadores
 *
 */

// TEMA: Grafos usando Kruskal

#include <iostream>
#include <bits/stdc++.h>
#include <cmath>

using namespace std;

typedef pair<int, int> roteadores;

class Pares
{
public:
    int *pai, *posicao;
    int quantidadeVertices;

    Pares(int qV)
    {
        this->quantidadeVertices = qV;
        pai = new int[qV + 1];
        posicao = new int[qV + 1];

        for (int i = 0; i <= qV; i++)
        {
            // inicializa todos os pares de roteadores como posição 0
            posicao[i] = 0;
            // torna cada elemento pai de si mesmo, para evitar segmentation fault
            pai[i] = i;
        }
    }

    int buscarPai(int vertice)
    {
        if (vertice != pai[vertice])
            pai[vertice] = buscarPai(pai[vertice]);
        return pai[vertice];
    }

    // conecta os roteadores
    void merge(int vertice1, int vertice2)
    {
        vertice1 = buscarPai(vertice1);
        vertice2 = buscarPai(vertice2);

        // caso o peso do vertice 1 seja maior que o do vértice 2, faz com que o pai do vértice 2 seja
        // o vértice 1, criando uma subárvore
        if (posicao[vertice1] > posicao[vertice2]) pai[vertice2] = vertice1;
        else pai[vertice1] = vertice2;

        if (posicao[vertice1] == posicao[vertice2]) posicao[vertice2]++;
    }
};

class Grafo
{
public:
    int quantidadeVertices;
    vector<pair<int, roteadores>> arestas;

    Grafo(int qV)
    {
        this->quantidadeVertices = qV;
    }

    void inserirAresta(int vertice1, int vertice2, double peso)
    {
        arestas.push_back({peso, {vertice1, vertice2}});
        // reorganiza arestas de acordo com seu peso, do menor para o maior
        sort(arestas.begin(), arestas.end());
    }

    double gerarArvoreMinimaKruskal(Pares pares)
    {
        double pesoTotal = 0;

        for (vector<pair<int, roteadores>>::iterator i = arestas.begin(); i != arestas.end(); i++)
        {
            int paiVertice1 = pares.buscarPai(i->second.first);
            int paiVertice2 = pares.buscarPai(i->second.second);

            // verifica se a aresta atual forma um ciclo com a árvore mínima atual
            if (paiVertice1 != paiVertice2)
            {
                pesoTotal += i->first;
                pares.merge(paiVertice1, paiVertice2);
            }
        }
        return pesoTotal;
    }
};

int main()
{
    int r, c;
    
    cin >> r >> c;
    
    Grafo grafo(r);
    
    for (int iCabo = 0; iCabo < c; iCabo++) {
        int v, w, p;
        
        cin >> v >> w >> p;
        
        grafo.inserirAresta(v, w, p);       
    }
    
    Pares pares(r); // cria um auxiliar para os pares de roteadores
    
    cout << grafo.gerarArvoreMinimaKruskal(pares);
    
    return 0;
}
