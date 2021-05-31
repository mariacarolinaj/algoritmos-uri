/*
 * Maria Carolina Resende Jaudacy - Matrícula 667477 
 * Análise de complexidade para a solução desenvolvida abaixo para o pior cenário do problema "De dentro para fora":
 *  O(n) * O(200) onde:
 * n = Quantidade de casos de teste em análise
 * 200 representa o tamanho máximo da frase; no enunciado é dito que o tamanho máximo seria 100 caracteres,
 *     mas a entrada privada não dava 100% com apenas 100 no tamanho da entrada. Então aumentei para 200,
 *     sem saber ao certo qual seria esse tamanho máximo de verdade, mas deu 100%. Então é uma suposição de que essa
 *     é a quantidade máxima de caracteres. Essa complexidade se justifica como se todas as frases inseridas possuíssem
 *     200 caracteres cada uma.
 */

// TEMA: Tratamento de Strings

#include <iostream>
 #include <cstring>
 #include <cstdlib>

using std::string;
using std::getline;
using namespace std;
 
int main() {
    int n;
    
    cin >> n;
    cin.ignore();
    
    for (int iTeste = 0; iTeste < n; iTeste++) { // Complexidade: O(n)
	    char frase[200];
        
	    fgets(frase, 200, stdin);
        
	    int tamanhoFrase = strlen(frase) - 1; // o - 1 serve para remover o \n do fim da frase 	
        int metade = tamanhoFrase / 2;
        
        for (int iEsq = metade - 1; iEsq >= 0; iEsq--) {
            cout << frase[iEsq];
        }
        
        for (int iDir = tamanhoFrase - 1; iDir >= metade; iDir--) {
            cout << frase[iDir];
        }
        
        cout << endl;
    }
    
    return 0;
}