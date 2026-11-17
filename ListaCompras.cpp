#include "ListaCompras.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>

using namespace std;

void processarListaCompras(const char* caminhoArquivo, ModuloCompras* dados) {
    FILE *arquivo = fopen(caminhoArquivo, "r");
    
    if (arquivo == NULL) {
        cout << "Erro ao abrir o arquivo: " << caminhoArquivo << endl;
        return;
    }

    int dataCompra;
    char codCliente[50], codProduto[50], nomeProduto[150];
    char cabecalho[256];

    if (fgets(cabecalho, sizeof(cabecalho), arquivo) == NULL) {
        cout << "O arquivo esta vazio!" << endl;
        fclose(arquivo);
        return;
    }

    while (fscanf(arquivo, "%d,%49[^,],%49[^,],%149[^\r\n]\r\n", &dataCompra, codCliente, codProduto, nomeProduto) == 4) {
        string str_cliente = codCliente; 
        string str_cod_produto = codProduto; 
        string str_nome_produto = nomeProduto; 

        if (dados->mapa_clientes.find(str_cliente) == dados->mapa_clientes.end()) {
            dados->mapa_clientes[str_cliente] = dados->vetor_clientes.size();
            dados->vetor_clientes.push_back(str_cliente);
        }

        if (dados->mapa_produtos.find(str_cod_produto) == dados->mapa_produtos.end()) {
            dados->mapa_produtos[str_cod_produto] = dados->vetor_produtos.size();
            dados->vetor_produtos.push_back(str_nome_produto);
        }
    }

    dados->lista_compras.resize(dados->vetor_clientes.size());
    rewind(arquivo);
    fgets(cabecalho, sizeof(cabecalho), arquivo);

    while (fscanf(arquivo, "%d,%49[^,],%49[^,],%149[^\r\n]\r\n", &dataCompra, codCliente, codProduto, nomeProduto) == 4) {
        int id_cliente = dados->mapa_clientes[codCliente];
        int id_produto = dados->mapa_produtos[codProduto];
        
        // Garante que cada produto unico comprado pelo cliente apareca uma unica vez (conjunto P_i)
        auto& compras_cli = dados->lista_compras[id_cliente];
        if (find(compras_cli.begin(), compras_cli.end(), id_produto) == compras_cli.end()) {
            compras_cli.push_back(id_produto);
        }
    }

    fclose(arquivo);
}

void carregarTodosArquivos(ModuloCompras* dados) {
    char caminho[150];
    cout << "Carregando arquivos, aguarde..." << endl;

    // Carrega o cluster 0 (pode ajustar o intervalo se desejar carregar mais clusters, ex: i <= 20)
    for (int i = 0; i <= 0; i++) { 
        sprintf(caminho, "dados_venda_cluster_%d.csv", i);
        processarListaCompras(caminho, dados);
    }

    if (dados->vetor_clientes.size() > 0) {
        cout << "Arquivos carregados com sucesso!" << endl;
        cout << "Total de clientes registrados: " << dados->vetor_clientes.size() << endl;
        cout << "Total de produtos registrados: " << dados->vetor_produtos.size() << "\n\n";
    } else {
        cout << "Nao foi possivel ler os arquivos CSV na pasta atual." << endl;
    }
}

void testarListaCompras(ModuloCompras* dados) {
    string cliente_busca;

    cin.clear();
    
    for(int i = 0; i < 3; i++) {
        cout << "Digite o codigo do cliente (ex: 99CL9Y01): ";
        cin >> cliente_busca; 
        
        if (dados->mapa_clientes.find(cliente_busca) != dados->mapa_clientes.end()) {
            int id = dados->mapa_clientes[cliente_busca];
            cout << "Produtos comprados pelo cliente " << cliente_busca << " (ID interno " << id << "):" << endl;
            
            for (int id_prod : dados->lista_compras[id]) {
                cout << "- " << dados->vetor_produtos[id_prod] << endl;
            }
        } else {
            cout << "Cliente nao encontrado na base." << endl;
        }
        cout << "-----------------------" << endl;
    }
}
