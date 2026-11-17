#include <iostream>
#include "ListaCompras.h"
#include "Similaridade.h"

using namespace std;

int main() {
    ModuloCompras minhasCompras;
    ModuloSimilaridade minhaSimilaridade;

    cout << "--- Iniciando Teste da Atividade 2 ---" << endl;
    carregarTodosArquivos(&minhasCompras);
    testarSimilaridade(&minhasCompras, &minhaSimilaridade);

    return 0;
}
