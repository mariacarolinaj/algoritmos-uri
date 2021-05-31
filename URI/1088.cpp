/*
 * Maria Carolina Resende Jaudacy - Matrícula 667477 
 * Análise de complexidade para a solução desenvolvida abaixo para o pior cenário do problema Bolhas e Baldes usando o algoritmo de ordenação ShellSort:
 *  O(n*n) onde n = quantidade de valores da sequencia
 */

// TEMA: Algoritmo de divisão e conquista -- ordenação usando ShellSort

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int shellSort(vector<int> sequencia, int n)
{
    int qtdTrocas = 0;
    
    // reduz o vetor em porções, reduzindo pela metade o valor anterior até que se tenha o menor pedaço do vetor possível;
    // 'intervalo' representa o tamanho da porção atual
    for (int intervalo = n / 2; intervalo > 0; intervalo /= 2)
    {
        // percorre todos os elementos do intervalo, alocando-os em sua posição correta
        for (int i = intervalo; i < n; i += 1)
        {
            int aux = sequencia[i];
  
            // desloca os valores até que se encontre a posição (representada por j) onde o valor de aux deverá ser inserido
            int j;
            for(j = i; j >= intervalo && sequencia[j - intervalo] > aux; j -= intervalo){
                sequencia[j] = sequencia[j - intervalo];
                qtdTrocas++;
            }
              
            // aloca o valor de aux em sua posição correta na porção analisada atualmente
            sequencia[j] = aux;
        }
    }
    
    return qtdTrocas;
}



string bolhasEBaldes(int n, vector<int> sequencia) {
    int qtdJogadas = shellSort(sequencia, n);
    string vencedor;
    
    // se a quantidade de jogadas for ímpar, Marcelo ganhou pois foi o primeiro a jogar
    if (qtdJogadas % 2 != 0) {
        vencedor = "Marcelo";
    } else {
        vencedor = "Carlos";
    }
    
    return vencedor;
}

int main() {
    bool executa = true;
    
    while (executa) {
        int n;
        cin >> n;
        
        if (n == 0) { // não realizará a próxima leitura
            executa = false; 
        } else {
            vector<int> sequencia;
            for (int iS = 0; iS < n; iS++) {
                int valor;
                cin >> valor;
                sequencia.push_back(valor);
            }
            
            cout << bolhasEBaldes(n, sequencia) << endl;
        }
    }
}