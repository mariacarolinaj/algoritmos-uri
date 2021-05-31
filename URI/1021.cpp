/*
 * Maria Carolina Resende Jaudacy - Matrícula 667477 
 * Análise de complexidade para a solução desenvolvida abaixo para o pior cenário do problema Notas e Moedas:
 *  O(1) porque independente do valor inserido serão executadas 12 operações de loop na verificação das moedas, e O(12) = O(1).
 */
// TEMA: Algoritmos gulosos

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int processarValor (vector<double> cedulas, string tipo, int valorInteiro) {
     for (int i = 0; i < cedulas.size(); i++) {
        int valorInteiroCedula = cedulas[i] * 100;
        int quantidadeCedulas = 0;
        
        if (valorInteiro / valorInteiroCedula > 0) {
            quantidadeCedulas = valorInteiro / valorInteiroCedula;
            valorInteiro -= valorInteiroCedula * quantidadeCedulas;
        }
        
        cout << quantidadeCedulas << " " << tipo << "(s) de R$ " << cedulas[i] << endl; 
    }
    
    return valorInteiro;
}

int main() {
    vector<double> notas = { 100.00, 50.00, 20.00, 10.00, 5.00, 2.00 };
    vector<double> moedas = { 1.00, 0.50, 0.25, 0.10, 0.05, 0.01 };
    
    double valor;
    cin >> valor;
    
    cout << fixed << setprecision(2); // imprime 2 casas decimais em todas as impressões de valores em ponto flutuante
    
    int valorInteiro = valor * 100; // remove a casa decimal
    
    cout << "NOTAS:" << endl;
    valorInteiro = processarValor(notas, "nota", valorInteiro);
    
    cout << "MOEDAS:" << endl;
    processarValor (moedas, "moeda", valorInteiro);
    
    return 0;
}