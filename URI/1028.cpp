/*
 * Maria Carolina Resende Jaudacy - Matrícula 667477 
 * Análise de complexidade para a solução desenvolvida abaixo para o pior cenário do problema "Figurinhas":
 *  O(n) * O(menorQtdCards) onde:
 * n = Quantidade de casos de teste em análise
 * menorQtdCards = menor quantidade de figurinhas lidas (f1 ou f2); no pior caso, o for que envolve a busca
 *                 do MDC irá executar essa quantidade de vezes.
 */
// TEMA: Matemática e Lógica

#include <iostream>
#include <algorithm> 

using namespace std;
 
int main() {
 
   int n = 0, f1 = 0, f2 = 0;
   
   cin >> n;
   
   for (int iTeste = 0; iTeste < n; iTeste++) { // Complexidade: O(n)
       cin >> f1;
       cin >> f2;
       
       int tamanhoMaximoPilha = 0;
       int menorQtdCards = std::min(f1, f2);
       
	   /* a busca pelo MDC se inicia pela menor qtd de cartas informadas e vai de trás pra frente até 
        * encontrar o maior valor em que f1 e f2 tenham mod == 0 */

       for (tamanhoMaximoPilha = menorQtdCards; 
            tamanhoMaximoPilha > 0 && (f1 % tamanhoMaximoPilha != 0 || f2 % tamanhoMaximoPilha != 0); 
            tamanhoMaximoPilha--); // Complexidade: O(menorQtdCards)
       
       cout << tamanhoMaximoPilha << endl ;
   }
 
    return 0;
}