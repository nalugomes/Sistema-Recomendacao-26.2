#include "Recomendacao.h"
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

// Na Atividade 3, quanto MENOR o produto das distancias de Jaccard (R_p), maior a relevancia
bool compararPorRanking(const ProdutoRecomendado &a, const ProdutoRecomendado &b) {
    return a.valor_ranking < b.valor_ranking; 
}

void recomendarProdutos(ModuloCompras* compras, ModuloSimilaridade* sim, int id_cliente, int k) {
    int num_produtos = compras->vetor_produtos.size();
    int num_clientes = compras->vetor_clientes.size();
    
    // Identificar vizinhos V_c (clientes com distancia de Jaccard < 1.0)
    vector<int> vizinhos;
    for (int v = 0; v < num_clientes; v++) {
        if (v != id_cliente && sim->matriz_similaridade[id_cliente][v] < 1.0) {
            vizinhos.push_back(v);
        }
    }

    // Vetor R inicializado com 1.0 (elemento neutro da multiplicacao)
    vector<double> R(num_produtos, 1.0);
    const list<int>& ja_comprados = compras->lista_compras[id_cliente];

    // Acumular produtorio: R[p] *= s(c, v) para cada vizinho v que comprou p
    for (int v : vizinhos) {
        double s_cv = sim->matriz_similaridade[id_cliente][v];
        for (int p : compras->lista_compras[v]) {
            bool comprou = (find(ja_comprados.begin(), ja_comprados.end(), p) != ja_comprados.end());
            if (!comprou) {
                R[p] *= s_cv;
            }
        }
    }

    // Filtrar apenas produtos nao comprados pelo cliente c que tiveram algum vizinho comprador (R[p] < 1.0)
    vector<ProdutoRecomendado> ranqueamento;
    for (int p = 0; p < num_produtos; p++) {
        bool comprou = (find(ja_comprados.begin(), ja_comprados.end(), p) != ja_comprados.end());
        if (!comprou && R[p] < 1.0) {
            ranqueamento.push_back({p, R[p]});
        }
    }

    // Ordenar em ordem crescente de R_p
    sort(ranqueamento.begin(), ranqueamento.end(), compararPorRanking);

    cout << "\n--- TOP " << k << " RECOMENDACOES ---" << endl;
    int limite = min(k, (int)ranqueamento.size());
    
    if (limite == 0) {
        cout << "Nenhum produto para recomendar." << endl;
    } else {
        for (int i = 0; i < limite; i++) {
            int id_prod = ranqueamento[i].id_produto;
            cout << i + 1 << "o Lugar: " << compras->vetor_produtos[id_prod] 
                 << " (R_p: " << ranqueamento[i].valor_ranking << ")" << endl;
        }
    }
}

void testarRecomendacao(ModuloCompras* compras, ModuloSimilaridade* sim) {
    string cliente_busca;
    int k;
    
    cout << "\n===============================" << endl;
    cout << "     TESTADOR ATIVIDADE 3      " << endl;
    cout << "===============================" << endl;
    
    cin.clear();

    for(int i = 0; i < 3; i++) {
        cout << "Digite o CODIGO ORIGINAL do cliente (ex: 99CL9Y01): ";
        cin >> cliente_busca;

        if (compras->mapa_clientes.find(cliente_busca) != compras->mapa_clientes.end()) {
            int id_interno = compras->mapa_clientes[cliente_busca];
            
            cout << "Quantos produtos (k) deseja recomendar? ";
            cin >> k;

            recomendarProdutos(compras, sim, id_interno, k);
        } else {
            cout << "Cliente nao encontrado na base!" << endl;
        }
        cout << "-----------------------------------" << endl;
    }
}
