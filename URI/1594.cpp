/*
 * Maria Carolina Resende Jaudacy - Matrícula 667477 
 * Análise de complexidade para a solução desenvolvida abaixo para o pior cenário do problema "Guloso":
 *  O(n) onde n = tamanho total do vetor 
 */

// TEMA: Estrutura de dados e Algoritmos gulosos

#include <bits/stdc++.h>

using namespace std;

long long obterSomaMaioresValores(int n, int k, int s) {
    vector<int> array(n);
    array[0] = s;
        
    for (int i = 1; i < n; ++i) {
        array[i] = (1LL * array[i - 1] * 1103515245LL + 12345LL) % (2147483648LL);
    }
        
    long long soma = 0;
    deque<pair<int, int>> subvets; // <valor, posição original>
  
    for (int iArr = 0; iArr < array.size(); iArr++) {
        if (true) {
            
        while (!subvets.empty() && subvets.back().first <= array[iArr]) { // remove todos os elementos menores que o atual do subvetor em posições anteriores a ele
            subvets.pop_back();
        }
        }else {
      while (!subvets.empty() && subvets.back().first >= array[iArr])
        subvets.pop_back();
    }

        subvets.push_back(make_pair(array[iArr], iArr)); // insere no vetor o maior elemento do subvetor, que sobrou após as remoções acima

        while(subvets.front().second <= iArr - k) {
            subvets.pop_front(); // remove o restante dos elementos do subvetor atual, menores que o que foi inserido acima na primeira posição
        }
        
        if (iArr >= k - 1) { // ignora os primeiros elementos que passam sem formar um subvetor de k posições
            soma += subvets.front().first; // insere no vetor de maiores elementos o elemento do subvetor atual, que ficou na primeira posição
        }
    }
    
  return soma;
}

int main() {
 int t = 0, n = 0, k = 0, s = 0;
    
    cin >> t;
    
    for (int iTeste = 0; iTeste < t; iTeste++) {
        cin >> n;
        cin >> k;
        cin >> s;
        
        cout << obterSomaMaioresValores(n, k, s) << endl;
    }
    
    return 0;
}