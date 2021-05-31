// Ainda não está funcionando corretamente, mas o caminho para a resolução está correto!!
// TEMA: Back Tracking

#include <iostream>
#include <list>

using namespace std;

class Posicao {
public:
  int x, y;

  bool operator==(const Posicao &p) const { return x == p.x && y == p.y; }
  bool operator!=(const Posicao &p) const { return !operator==(p); }

  Posicao() {}

  Posicao(int posicaoX, int posicaoY) {
    x = posicaoX;
    y = posicaoY;
  }
};

class Tabuleiro {
public:
  Posicao cavalo;
  list<Posicao> peoes;
  list<Posicao> posicoesInvalidas;

  int jogadas;
  int quantidadeLinhas;
  int quantidadeColunas;

  Tabuleiro(int linhas, int colunas) {
    quantidadeLinhas = linhas;
    quantidadeColunas = colunas;
    jogadas = 0;
  }

  void removePeao(Posicao posicao) {
    peoes.remove(posicao);
    /*list<Posicao> peoesAtuais = peoes;
    peoes.clear();

    for (list<Posicao>::iterator it = peoesAtuais.begin();
         it != peoesAtuais.end(); ++it) {
      if (!(posicao.x == it->x && posicao.y == it->y)) {
        peoes.push_back(*it);
      }
    }*/
  }

  bool moveCavalo(int movimento) {
    int x[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int y[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    int novoX = cavalo.x + x[movimento];
    int novoY = cavalo.y + y[movimento];

    cavalo = Posicao(novoX, novoY);

    for (list<Posicao>::iterator it = peoes.begin(); it != peoes.end(); ++it) {
      if (cavalo.x == it->x && cavalo.y == it->y) {
        removePeao(*it);
        return true;
      }
    }

    return false;
  }

  void desfazMovimentoCavalo(int jogada) {
    int x[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int y[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    int novoX = cavalo.x - x[jogada];
    int novoY = cavalo.y - y[jogada];

    cavalo = Posicao(novoX, novoY);
  }

  bool cavaloEstaEmPosicaoInvalida() {
    if (cavalo.x >= quantidadeLinhas || cavalo.y >= quantidadeColunas ||
        cavalo.x < 0 || cavalo.y < 0) {
      return true;
    }
    for (list<Posicao>::iterator it = posicoesInvalidas.begin();
         it != posicoesInvalidas.end(); ++it) {
      if (cavalo.x == it->x && cavalo.y == it->y) {
        return true;
      }
    }
    return false;
  }
};

int retornaSolucao(Tabuleiro tab) {
  if (tab.peoes.empty()) {
    return tab.jogadas;
  }

  int melhor = 10000;

  tab.jogadas++;
  for (int i = 0; i < 8; i++) {

    bool peaoFoiComido = tab.moveCavalo(i);

    if (!tab.cavaloEstaEmPosicaoInvalida()) {
      int atual = retornaSolucao(tab);
      if (atual < melhor) {
        melhor = atual;
      }

      if (peaoFoiComido) {
        tab.peoes.push_back(Posicao(tab.cavalo.x, tab.cavalo.y));
      }
    }
    tab.desfazMovimentoCavalo(i);
  }
  tab.jogadas--;
  return melhor;
}

int main() {
  int n, m, k; // n = linhas do tabuleiro, m = colunas do tabuleiro, k =
               // quantidade de peoes

  do {
    cin >> n >> m >> k;

    if (n != 0) { // tabuleiro existe
      Tabuleiro tabuleiro(n, m);
      Posicao posInicialCavalo;

      for (int iL = 0; iL < n; iL++) {
        for (int iC = 0; iC < m; iC++) {
          char posicaoAtual;
          cin >> posicaoAtual; // '.' = posição válida, '#' = posição
                               // inválida, 'C' = cavalo, 'P' = peão
          switch (posicaoAtual) {
          case 'C':
            posInicialCavalo = Posicao(iL, iC);
            tabuleiro.cavalo = posInicialCavalo;
            break;
          case '#':
            tabuleiro.posicoesInvalidas.push_back(Posicao(iL, iC));
            break;
          case 'P':
            tabuleiro.peoes.push_back(Posicao(iL, iC));
            break;
          default:
            break;
          }
        }
      }

      cout << retornaSolucao(tabuleiro) * 2 << endl;
    }
  } while (n != 0);

  return 0;
}