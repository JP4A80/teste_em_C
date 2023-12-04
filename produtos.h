#ifndef PRODUTOS_H
#define PRODUTOS_H

struct PRODUTO {
    int codigo;
    char nome[50];
    int estoque;
    float preco;
    char fornecedor[50];
    struct PRODUTO *prox;
};

typedef struct PRODUTO Produto;

extern Produto *listaProdutos;

void inserirProduto(int codigo, char nome[], int estoque, float preco, char fornecedor[]);

void removerProduto(int codigo);

void removerProdutoNome(char nome[]);

void alterarProduto(int codigo, char nome[], int estoque, float preco, char fornecedor[]);

void mostrarEstoqueProduto(char nome[]);

void imprimirProdutos();

void produtoMaisCaro();

void produtoComEstoqueZerado();

void atualizarEstoque(char tipoOperacao, char produtoNome[], int quantidade);

void liberarProdutos();

void menuProdutos();

#endif