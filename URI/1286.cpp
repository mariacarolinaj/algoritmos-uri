/*
 * Maria Carolina Resende Jaudacy - Matrícula 667477 
 * Análise de complexidade para o pior cenário do problema "Motoboy" com a solução desenvolvida abaixo usando o algoritmo da mochila (KnapSack):
 *  O(2^n) onde n = número de pedidos recebidos pela pizzaria, devido à análise de todas as combinações dos subgrupos de pedidos em seus respectivos 
 *  pesos (quantidade de pizzas do pedido) e valores (tempo em minutos que o pedido leva para ser entregue por Roberto).
 */
 
#include <bits/stdc++.h>

using namespace std;

int max(int a, int b) { return (a > b) ? a : b; }

class Pedido {
public: 
    int tempoPreparo, qtdPizzas;
    
    Pedido() { }
    
    Pedido(int tempo, int pizzas) {
        tempoPreparo = tempo;
        qtdPizzas = pizzas;
    }
};
 
int knapSack(int qtdPizzasASeremEntregues, vector<Pedido> pedidos, int qtdPedidos)
{
    if (qtdPedidos == 0 || qtdPizzasASeremEntregues == 0)
        return 0;

    if (pedidos[qtdPedidos - 1].qtdPizzas > qtdPizzasASeremEntregues)
        return knapSack(qtdPizzasASeremEntregues, pedidos, qtdPedidos - 1);
     else
        return max(pedidos[qtdPedidos - 1].tempoPreparo + knapSack(qtdPizzasASeremEntregues - pedidos[qtdPedidos - 1].qtdPizzas, pedidos, qtdPedidos - 1), 
                   knapSack(qtdPizzasASeremEntregues, pedidos, qtdPedidos - 1)
                  );
}
 
int calcularTempoEntregaMaximo(int qtdMaxEntregas, vector<Pedido> pedidos) {
    return knapSack(qtdMaxEntregas, pedidos, pedidos.size());
}

int main()
{
    int n, p; // n = número de pedidos, p = qtd. máxima de pizzas que podem ser entregues por Roberto
    
    do {
        cin >> n;
        if (n != 0) {
            cin >> p;
            
            vector<Pedido> pedidos(n);
            int tempo, qtdPizzas;
        
            for (int iPedido = 0; iPedido < n; iPedido++) {
                cin >> tempo >> qtdPizzas;
                pedidos[iPedido] = Pedido(tempo, qtdPizzas);
            }
        
            cout << calcularTempoEntregaMaximo(p, pedidos) << " min." << endl;
        }
     } while (n != 0);
    
    return 0;
}