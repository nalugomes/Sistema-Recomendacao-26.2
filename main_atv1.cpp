#include <iostream>
#include "ListaCompras.h"

using namespace std;

int main() {
    ModuloCompras minhasCompras;

    cout << "--- Iniciando Teste da Atividade 1 ---" << endl;
    carregarTodosArquivos(&minhasCompras);
    testarListaCompras(&minhasCompras);

    return 0;
}
