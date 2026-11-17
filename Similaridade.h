#pragma once

#include <vector>
#include "ListaCompras.h"

using namespace std;

typedef struct {
    vector<vector<double>> matriz_similaridade; 
} ModuloSimilaridade;

void calcularSimilaridade(ModuloCompras* compras, ModuloSimilaridade* sim);
void testarSimilaridade(ModuloCompras* compras, ModuloSimilaridade* sim);
