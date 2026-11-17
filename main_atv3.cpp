#include <iostream>
#include "ListaCompras.h"
#include "Similaridade.h"
#include "Recomendacao.h"

using namespace std;

int main() {
    ModuloCompras minhasCompras;
    ModuloSimilaridade minhaSimilaridade;

    carregarTodosArquivos(&minhasCompras);

    cout << "Calculando matriz de similaridade..." << endl;
    calcularSimilaridade(&minhasCompras, &minhaSimilaridade);
    cout << "Calculo concluido!\n" << endl;

    testarRecomendacao(&minhasCompras, &minhaSimilaridade);

    return 0;
}
