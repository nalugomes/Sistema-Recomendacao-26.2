#include "Similaridade.h"
#include <iostream>

using namespace std;

void calcularSimilaridade(ModuloCompras* compras, ModuloSimilaridade* sim) {
    int n = compras->vetor_clientes.size();
    int m = compras->vetor_produtos.size();

    vector<vector<int>> A(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int id_produto : compras->lista_compras[i]) {
            A[i][id_produto] = 1;
        }
    }

    vector<vector<int>> T(m, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            T[j][i] = A[i][j]; 
        }
    }

    vector<vector<int>> I(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < m; k++) {
                I[i][j] += A[i][k] * T[k][j]; 
            }
        }
    }

    sim->matriz_similaridade.assign(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; i++) {
        int p_i = compras->lista_compras[i].size();
        
        for (int j = 0; j < n; j++) {
            if (p_i > 0) {
                sim->matriz_similaridade[i][j] = 1.0 - ((double)I[i][j] / (double)p_i); 
            } else {
                sim->matriz_similaridade[i][j] = 1.0;
            }
        }
    }
}

void testarSimilaridade(ModuloCompras* compras, ModuloSimilaridade* sim) {
    cout << "Calculando matriz de similaridade..." << endl;
    calcularSimilaridade(compras, sim);
    cout << "Calculo concluido!\n" << endl;

    for(int k = 0; k < 2; k++) {
        int id_busca;
        cout << "Digite o indice interno do cliente para buscar o mais similar (0 a " << compras->vetor_clientes.size() - 1 << "): ";
        cin >> id_busca;

        if (id_busca >= 0 && id_busca < (int)compras->vetor_clientes.size()) {
            double menor_distancia = 2.0; 
            int id_mais_similar = -1;

            for (int j = 0; j < (int)compras->vetor_clientes.size(); j++) {
                if (id_busca != j) {
                    if (sim->matriz_similaridade[id_busca][j] < menor_distancia) {
                        menor_distancia = sim->matriz_similaridade[id_busca][j];
                        id_mais_similar = j;
                    }
                }
            }

            cout << "O cliente mais similar ao " << id_busca 
                 << " (Codigo " << compras->vetor_clientes[id_busca] << ") e o " 
                 << id_mais_similar << " (Codigo " << compras->vetor_clientes[id_mais_similar] << ")" << endl;
            cout << "Distancia de Jaccard: " << menor_distancia << endl;
        } else {
            cout << "Indice invalido!" << endl;
        }
        cout << "-----------------------" << endl;
    }
}
