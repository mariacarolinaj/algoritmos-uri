/*
 * Maria Carolina Resende Jaudacy - Matrícula 667477 
 * Análise de complexidade para a solução desenvolvida abaixo para o pior cenário do problema Pontes de São Petersburgo" usando o algoritmo de knapsack baseado no site GeeksForGeeks:
 *  O(r*k) onde r = número de regiões e k = número de pontes
 */
//TEMA: Grafos e KnapSack (algoritmo da mochila)

#include <bits/stdc++.h>
using namespace std;
int max(int a, int b) { return (a > b) ? a : b; }
 
int knapSackRec(int K, vector<int> qtdPontes, int i, int** auxt)
{
    if (i < 0) return 0; // regiões começam em 1; 0 estará vazia
    if (auxt[i][K] != -1) return auxt[i][K]; // -1 representa aresta já utilizada
 
    if (qtdPontes[i] > K) {
        auxt[i][K] = knapSackRec(K, qtdPontes, i - 1, auxt);
        return auxt[i][K];
    }
    else {
        auxt[i][K] = max(qtdPontes[i] + knapSackRec(K - qtdPontes[i], qtdPontes, i - 1, auxt),
                       knapSackRec(K, qtdPontes, i - 1, auxt));
 
        return auxt[i][K];
    }
}
 
int knapSack(int K, vector<int> qtdPontes, int n)
{
    int** auxt;
    auxt = new int*[n];
 
    for (int i = 0; i < n; i++)
        auxt[i] = new int[K + 1];
 
    for (int i = 0; i < n; i++) // inicializa tabela de pesos com -1
        for (int j = 0; j < K + 1; j++) auxt[i][j] = -1;

    return knapSackRec(K, qtdPontes, n - 1, auxt);
}
 
int main()
{
    int r, k;
    
    while (cin >> r >> k) {
        vector<int> qtdPontes(r);
        int a, b;
        
        for (int iPonte = 0; iPonte < k; ++iPonte) {
            cin >> a >> b;
            qtdPontes[--a]++;
            qtdPontes[--b]++;
        }
        
        bool ehPossivel = knapSack(k, qtdPontes, r) == k;
        
        if (ehPossivel) cout << "S" << endl;
        else cout << "N" << endl;
    }
    
    return 0;
}