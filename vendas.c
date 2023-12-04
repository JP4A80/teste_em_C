#include "produtos.h"
#include "cliente.h"
#include "vendas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Cliente *listaClientes = NULL; // Lista encadeada de clientes
Produto *listaProdutos = NULL;


venda *listaVendas = NULL;    // Lista encadeada de vendas
float faturamentoTotal = 0.0; // Variável global para o faturamento total

// Função auxiliar para buscar um cliente pelo nome
Cliente *buscarClientePorNome(char clienteNome[])
{
    // Implemente a lógica para buscar um cliente na lista de clientes
    Cliente *atual = listaClientes;
    while (atual != NULL)
    {
        if (strcmp(atual->nome, clienteNome) == 0)
        {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL; // Retorna NULL se o cliente não for encontrado
}

// Função auxiliar para buscar um produto pelo nome
Produto *buscarProdutoPorNome(char produtoNome[])
{
    // Implemente a lógica para buscar um produto na lista de produtos
    Produto *atual = listaProdutos;
    while (atual != NULL)
    {
        if (strcmp(atual->nome, produtoNome) == 0)
        {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL; // Retorna NULL se o produto não for encontrado
}

void registrarVenda(char data[], int quantidade, char produtoNome[], char clienteNome[])
{
    // Buscar cliente e produto
    Cliente *clienteEncontrado = buscarClientePorNome(clienteNome);
    Produto *produtoEncontrado = buscarProdutoPorNome(produtoNome);

    // Verificar se cliente e produto foram encontrados
    if (clienteEncontrado == NULL)
    {
        printf("Cliente %s não encontrado.\n", clienteNome);
        return;
    }

    if (produtoEncontrado == NULL)
    {
        printf("Produto %s não encontrado.\n", produtoNome);
        return;
    }

    // Criar uma nova venda
    venda *novaVenda = (venda *)malloc(sizeof(venda));
    if (novaVenda == NULL)
    {
        printf("Erro ao alocar memória para nova venda\n");
        return;
    }

    // Preencher os dados da venda
    novaVenda->codigo = rand(); // Atribui um código aleatório (pode ser mais elaborado)
    strcpy(novaVenda->data, data);
    novaVenda->quantidade = quantidade;
    novaVenda->cliente = *clienteEncontrado;
    novaVenda->produto = *produtoEncontrado;

    // Calcular preço total da venda
    novaVenda->precoTotal = quantidade * novaVenda->produto.preco;

    // Atualizar o estoque do produto
    if (produtoEncontrado->estoque >= quantidade)
    {
        produtoEncontrado->estoque -= quantidade;
    }
    else
    {
        printf("Estoque insuficiente para realizar a venda.\n");
        free(novaVenda);
        return;
    }

    // Atualizar o faturamento total
    faturamentoTotal += novaVenda->precoTotal;

    // Adicionar a venda à lista de vendas
    novaVenda->prox = listaVendas;
    listaVendas = novaVenda;

    printf("Venda registrada com sucesso!\n");
}

void removerVenda(int indice)
{
    venda *anterior = NULL;
    venda *atual = listaVendas;
    int codigo;

    while (atual != NULL)
    {
        if (atual->codigo == codigo)
        {
            if (anterior == NULL)
            {
                // Remoção do primeiro elemento
                listaVendas = atual->prox;
            }
            else
            {
                anterior->prox = atual->prox;
            }

            free(atual);
            printf("Venda removida com sucesso!\n");
            return;
        }

        anterior = atual;
        atual = atual->prox;
    }
    printf("Venda com código %d não encontrada.\n", codigo);
}

void alterarVenda(char data[], int quantidade, int codigo, char produtoNome[], char clienteNome[])
{
    venda *atual = listaVendas;
    while (atual != NULL)
    {
        if (atual->codigo == codigo)
        {
            // Buscar cliente e produto
            Cliente *clienteEncontrado = buscarClientePorNome(clienteNome);
            Produto *produtoEncontrado = buscarProdutoPorNome(produtoNome);

            // Verificar se cliente e produto foram encontrados
            if (clienteEncontrado == NULL)
            {
                printf("Cliente %s não encontrado.\n", clienteNome);
                return;
            }

            if (produtoEncontrado == NULL)
            {
                printf("Produto %s não encontrado.\n", produtoNome);
                return;
            }

            // Atualizar os dados da venda
            strcpy(atual->data, data);
            atual->quantidade = quantidade;
            atual->cliente = *clienteEncontrado;
            atual->produto = *produtoEncontrado;

            // Calcular preço total da venda
            atual->precoTotal = quantidade * atual->produto.preco;

            // Atualizar o estoque do produto
            if (produtoEncontrado->estoque + atual->quantidade >= quantidade)
            {
                produtoEncontrado->estoque = produtoEncontrado->estoque + atual->quantidade - quantidade;
            }
            else
            {
                printf("Estoque insuficiente para realizar a venda.\n");
                return;
            }

            printf("Venda alterada com sucesso!\n");
            return;
        }
        atual = atual->prox;
    }
    printf("Venda com código %d não encontrada.\n", codigo);
}

void imprimirVendas()
{
    venda *atual = listaVendas;

    if (atual == NULL)
    {
        printf("Lista de vendas vazia.\n");
        return;
    }

    printf("\n=========== LISTA DE VENDAS ===========\n");
    while (atual != NULL)
    {
        printf("Código: %d, Data: %s, Quantidade: %d, Cliente: %s, Produto: %s, Preço Total: %.2f\n",
               atual->codigo, atual->data, atual->quantidade, atual->cliente.nome, atual->produto.nome, atual->precoTotal);
        atual = atual->prox;
    }
}

void consultarVendaPorCliente(char clienteNome[])
{
    venda *atual = listaVendas;
    int encontradas = 0;

    while (atual != NULL)
    {
        if (strcmp(atual->cliente.nome, clienteNome) == 0)
        {
            printf("Código: %d, Data: %s, Quantidade: %d, Cliente: %s, Produto: %s, Preço Total: %.2f\n",
                   atual->codigo, atual->data, atual->quantidade, atual->cliente.nome, atual->produto.nome, atual->precoTotal);
            encontradas++;
        }

        atual = atual->prox;
    }

    if (encontradas == 0)
    {
        printf("Nenhuma venda encontrada para o cliente %s.\n", clienteNome);
    }
}

void liberarVendas()
{
    venda *atual = listaVendas;
    venda *proximo;

    while (atual != NULL)
    {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    listaVendas = NULL; // Atualiza a lista para indicar que está vazia
    printf("Espaço alocado para produtos liberado com sucesso.\n");
}

void menuVendas()
{
    int opcao;

    do
    {
        printf("\n====== MENU VENDAS ======\n");
        printf("1. Registrar Venda\n");
        printf("2. Remover Venda (por código)\n");
        printf("3. Alterar Venda\n");
        printf("4. Imprimir Lista de Vendas\n");
        printf("5. Consultar Vendas por Cliente\n");
        printf("0. Voltar ao Menu Principal\n");

        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
        {
            char data[20], produtoNome[50], clienteNome[50];
            int quantidade;

            printf("Data da Venda: ");
            scanf("%s", data);
            printf("Nome do Produto: ");
            scanf("%s", produtoNome);
            printf("Quantidade: ");
            scanf("%d", &quantidade);
            printf("Nome do Cliente: ");
            scanf("%s", clienteNome);

            registrarVenda(data, quantidade, produtoNome, clienteNome);
            break;
        }
        case 2:
        {
            int codigo;
            printf("Código da Venda a ser removida: ");
            scanf("%d", &codigo);

            removerVenda(codigo);
            break;
        }
        case 3:
        {
            int codigo, quantidade;
            char data[20], produtoNome[50], clienteNome[50];

            printf("Código da Venda a ser alterada: ");
            scanf("%d", &codigo);
            printf("Nova Data: ");
            scanf("%s", data);
            printf("Nova Quantidade: ");
            scanf("%d", &quantidade);
            printf("Novo Nome do Produto: ");
            scanf("%s", produtoNome);
            printf("Novo Nome do Cliente: ");
            scanf("%s", clienteNome);

            alterarVenda(data, quantidade, codigo, produtoNome, clienteNome);
            break;
        }
        case 4:
            imprimirVendas();
            break;
        case 5:
        {
            char clienteNome[50];
            printf("Nome do Cliente para Consulta: ");
            scanf("%s", clienteNome);

            consultarVendaPorCliente(clienteNome);
            break;
        }
        case 0:
            printf("Retornando ao Menu Principal.\n");
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 0);
}