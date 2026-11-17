#pragma once

#include "ListaCompras.h"
#include "Similaridade.h"
#include <vector>

struct ProdutoRecomendado {
    int id_produto;
    double valor_ranking;
};

void recomendarProdutos(ModuloCompras* compras, ModuloSimilaridade* sim, int id_cliente, int k);
void testarRecomendacao(ModuloCompras* compras, ModuloSimilaridade* sim);
