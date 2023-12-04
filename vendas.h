#include "cliente.h"
#include "produtos.h"

struct VENDA {
    int codigo;
    Cliente cliente;
    Produto produto;
    char data[20];
    int quantidade;
    float precoTotal;
    struct VENDA *prox;
};

typedef struct VENDA venda;

Cliente *buscarClientePorNome(char clienteNome[]);

Produto *buscarProdutoPorNome(char produtoNome[]);

void registrarVenda(char data[], int quantidade, char produtoNome[], char clienteNome[]);

void removerVenda(int indice);

void alterarVenda(char data[], int quantidade, int codigo, char produtoNome[], char clienteNome[]);

void imprimir();

void consultarVendaPorCliente(char clienteNome[]);

void liberaVendas();

void menuVendas();