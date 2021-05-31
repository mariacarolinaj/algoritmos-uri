/*
 * Maria Carolina Resende Jaudacy - Matrícula 667477 
 * Análise de complexidade para a solução desenvolvida abaixo para o pior cenário do problema dos pares mais próximos
 * usando o algoritmo de força bruta baseado no site GeeksForGeeks (https://www.geeksforgeeks.org/closest-pair-of-points-onlogn-implementation/):
 *  O(n*log n) onde n = quantidade de pontos analisados
 */
// TEMA: Força bruta

#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;
  
struct Ponto
{
    int x, y;
};

float obterDistancia(Ponto p1, Ponto p2)
{
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

float menor(float x, float y)
{
    return (x < y)? x : y;
}

float obterMenorDistanciaVect(Ponto strip[], int size, float d)
{
    float menorDistancia = d;
  
    for (int i = 0; i < size; ++i)
        for (int j = i+1; j < size && (strip[j].y - strip[i].y) < menorDistancia; ++j)
            if (obterDistancia(strip[i],strip[j]) < menorDistancia) menorDistancia = obterDistancia(strip[i], strip[j]);
  
    return menorDistancia;
}

// implementação do algoritmo de força bruta para cálculo da menor distância
float forcaBruta(Ponto P[], int n)
{
    float menorDistancia = 1000000;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (obterDistancia(P[i], P[j]) < menorDistancia)
                menorDistancia = obterDistancia(P[i], P[j]);
    return menorDistancia;
}

float obterDistCoordenadaMaisProxima(Ponto coordenadasX[], Ponto coordenadasY[], int n)
{
    if (n <= 3)
        return forcaBruta(coordenadasX, n);
  
    int meio = n/2;
  
    Ponto menorprimeiraMetadeY[meio];  
    Ponto menorsegundaMetadeY[n - meio]; 
    int iPrimeiraMetade = 0, iSegundaMetade = 0;

    for (int iC = 0; iC < n; iC++)
    {
      if (coordenadasY[iC].x <= coordenadasX[meio].x && iPrimeiraMetade<meio)
         menorprimeiraMetadeY[iPrimeiraMetade++] = coordenadasY[iC];
      else
         menorsegundaMetadeY[iSegundaMetade++] = coordenadasY[iC];
    }
    
    float menorValorPrimeiraMetade = obterDistCoordenadaMaisProxima(coordenadasX, menorprimeiraMetadeY, meio);
    float menorValorSegundaMetade = obterDistCoordenadaMaisProxima(coordenadasX + meio, menorsegundaMetadeY, n-meio);
  
    float menorDistancia = menor(menorValorPrimeiraMetade, menorValorSegundaMetade);
  
    Ponto strip[n];
    int j = 0;
    for (int iC = 0; iC < n; iC++)
        if (abs(coordenadasY[iC].x - coordenadasX[meio].x) < menorDistancia)
            strip[j] = coordenadasY[iC], j++;
  
    return obterMenorDistanciaVect(strip, j, menorDistancia);
}

int compareX(const void* a, const void* b)
{
    Ponto *p1 = (Ponto *)a,  *p2 = (Ponto *)b;
    return (p1->x - p2->x);
}

int compareY(const void* a, const void* b)
{
    Ponto *p1 = (Ponto *)a,   *p2 = (Ponto *)b;
    return (p1->y - p2->y);
}

float obterMenorDistancia(Ponto P[], int n)
{
    Ponto Px[n];
    Ponto Py[n];

    // separa as coordenadas X e Y de cada ponto
    for (int i = 0; i < n; i++)
    {
        Px[i] = P[i];
        Py[i] = P[i];
    }
  
    qsort(Px, n, sizeof(Ponto), compareX); // ordena as coordenadas X de cada ponto
    qsort(Py, n, sizeof(Ponto), compareY); // ordena as coordenadas Y de cada ponto
  
    return obterDistCoordenadaMaisProxima(Px, Py, n);
}

int main() 
{ 
    while(true){
        int n;
        cin >> n;
        
        if(n == 0) return 0; // encerra execução do programa
        
        Ponto pontos[n];
        
        for(int iPonto = 0; iPonto < n; iPonto++) 
            cin >> pontos[iPonto].x >> pontos[iPonto].y; // realiza leitura de cada ponto
            
        double menorDistancia = obterMenorDistancia(pontos, n); 
        
        if(menorDistancia > 10000) cout << "INFINITY\n";
        else printf("%.4lf\n", menorDistancia);
    }
} 

