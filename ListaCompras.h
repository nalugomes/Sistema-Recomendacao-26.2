#pragma once

#include <vector>
#include <map>
#include <list>
#include <string>

using namespace std;

typedef struct {
    vector<string> vetor_clientes;
    map<string, int> mapa_clientes;
    vector<string> vetor_produtos;
    map<string, int> mapa_produtos;
    vector<list<int>> lista_compras;
} ModuloCompras;

void processarListaCompras(const char* caminhoArquivo, ModuloCompras* dados);
void carregarTodosArquivos(ModuloCompras* dados);
void testarListaCompras(ModuloCompras* dados);
