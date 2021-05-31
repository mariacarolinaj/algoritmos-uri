// https://onlinejudge.org/external/118/11857.pdf
// TEMA: Grafos usando Kruskal

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> coordenada;

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
            // inicializa todos os pares como posição 0
            posicao[i] = 0;
            // torna cada elemento pai de si mesmo
            pai[i] = i;
        }
    }

    int buscarPai(int vertice)
    {
        if (vertice != pai[vertice])
            pai[vertice] = buscarPai(pai[vertice]);
        return pai[vertice];
    }

    // conecta os pares
    void merge(int vertice1, int vertice2)
    {
        vertice1 = buscarPai(vertice1);
        vertice2 = buscarPai(vertice2);

        // caso o peso do vertice 1 seja maior que o do vértice 2, faz com que o pai do vértice 2 seja
        // o vértice 1, criando uma subárvore, senão faz o contrário
        if (posicao[vertice1] > posicao[vertice2])
            pai[vertice2] = vertice1;
        else
            pai[vertice1] = vertice2;

        if (posicao[vertice1] == posicao[vertice2])
            posicao[vertice2]++;
    }
};

class Grafo
{
public:
    int quantidadeVertices, quantidadeArestas;
    vector<pair<int, coordenada>> arestas;

    Grafo(int qV, int qA)
    {
        this->quantidadeVertices = qV;
        this->quantidadeArestas = qA;
    }

    void inserirAresta(int vertice1, int vertice2, double peso)
    {
        arestas.push_back({peso, {vertice1, vertice2}});
    }

    double gerarArvoreMinimaKruskal()
    {
        double menorPeso = -1;

        // organiza arestas de acordo com seu peso, do menor para o maior
        sort(arestas.begin(), arestas.end());
        // inicializa os "sets" (conjuntos de pares de vértices conectados por uma aresta)
        Pares pares(quantidadeVertices);

        //vector<int> cidadesConectadas(quantidadeVertices)
        // cria iterator para passar por todos os vértices inseridos
        vector<pair<int, coordenada>>::iterator i;
        for (i = arestas.begin(); i != arestas.end(); i++)
        {
            int vertice1 = i->second.first;  // primeiro vértice do par
            int vertice2 = i->second.second; // segundo vértice do par

            int paiVertice1 = pares.buscarPai(vertice1);
            int paiVertice2 = pares.buscarPai(vertice2);

            // verifica se a aresta atual forma um ciclo com a árvore mínima atual
            if (paiVertice1 != paiVertice2)
            {
                if (i->first > menorPeso) menorPeso = i->first;
                pares.merge(paiVertice1, paiVertice2);
            }
        }
        
        return menorPeso;
    }
};

int main() {
    int n, m; // n = qtd de cidades, m = qtd de rodovias
    bool executa = true;
    
    while (executa) {
        cin >> n >> m;
        
        if (n == 0 && m == 0){
            executa = false;
        } else {
            Grafo mapa(n, m); // armazena as ligaçoes entre cidades (vertices) atraves das rodovias (arestas)
            
            for (int iRodovia = 0; iRodovia < m; iRodovia++) {
                int cidadeA, cidadeB, distancia;
                cin >> cidadeA >> cidadeB >> distancia;
                
                mapa.inserirAresta(cidadeA, cidadeB, distancia);
            }
            
            if (m == 0) { // não existem rodovidas, logo é impossível
                cout << "IMPOSSIBLE" << endl;
            } else {
                int distanciaMinimaEntreCidades = mapa.gerarArvoreMinimaKruskal();
            
                if ((n <= m) && distanciaMinimaEntreCidades > 0) {
                    cout << distanciaMinimaEntreCidades << endl;
                } else {
                    cout << "IMPOSSIBLE" << endl;
                }
            }
        }
    }
    
    return 0;
}