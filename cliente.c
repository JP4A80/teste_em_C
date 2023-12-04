#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"

Cliente *listaClientes = NULL; // Lista encadeada de clientes

void inserirCliente(char nome[], char cpf[], char rg[], char telefone[], int idade)
{
    Cliente *novoCliente = (Cliente *)malloc(sizeof(Cliente));
    if (novoCliente == NULL)
    {
        printf("Erro ao alocar memória para novo cliente\n");
        return;
    }

    strcpy(novoCliente->nome, nome);
    strcpy(novoCliente->cpf, cpf);
    strcpy(novoCliente->rg, rg);
    strcpy(novoCliente->telefone, telefone);
    novoCliente->idade = idade;

    novoCliente->prox = listaClientes;
    listaClientes = novoCliente;

    printf("Cliente %s inserido com sucesso!\n", nome);
}

void alterarCliente(char nome[], char cpf[], char rg[], char telefone[], int idade)
{
    Cliente *atual = listaClientes; // Adicione esta linha

    while (atual != NULL)
    {
        if (strcmp(atual->nome, nome) == 0)
        {
            strcpy(atual->cpf, cpf);
            strcpy(atual->rg, rg);
            strcpy(atual->telefone, telefone);
            atual->idade = idade;
            printf("Cliente %s alterado com sucesso!\n", nome);
            return;
        }
        atual = atual->prox;
    }

    printf("Cliente %s não encontrado.\n", nome);
}

void removerClienteNome(char nome[])
{

    Cliente *anterior = NULL;
    Cliente *atual = listaClientes;

    while (atual != NULL)
    {
        if (strcmp(atual->nome, nome) == 0)
        {
            if (anterior == NULL)
            {
                // Remoção do primeiro elemento
                listaClientes = atual->prox;
            }
            else
            {
                anterior->prox = atual->prox;
            }

            free(atual);
            printf("Cliente %s removido com sucesso!\n", nome);
            return;
        }

        anterior = atual;
        atual = atual->prox;
    }

    printf("Cliente %s não encontrado.\n", nome);
}

void obterClienteMaisVelho()
{
    if (listaClientes == NULL)
    {
        printf("Lista de clientes vazia.\n");
        return;
    }

    Cliente *maisVelho = listaClientes;
    Cliente *atual = listaClientes->prox;

    while (atual != NULL)
    {
        if (atual->idade > maisVelho->idade)
        {
            maisVelho = atual;
        }

        atual = atual->prox;
    }

    printf("Cliente mais velho: %s, Idade: %d\n", maisVelho->nome, maisVelho->idade);
}

void obterClienteMaisNovo()
{

    if (listaClientes == NULL)
    {
        printf("Lista de clientes vazia.\n");
        return;
    }

    Cliente *maisNovo = listaClientes;
    Cliente *atual = listaClientes->prox;

    while (atual != NULL)
    {
        if (atual->idade < maisNovo->idade)
        {
            maisNovo = atual;
        }

        atual = atual->prox;
    }

    printf("Cliente mais novo: %s, Idade: %d\n", maisNovo->nome, maisNovo->idade);
}

void imprimir()
{

    Cliente *atual = listaClientes;

    if (atual == NULL)
    {
        printf("Lista de clientes vazia.\n");
        return;
    }

    printf("\n=========== LISTA DE CLIENTES ===========\n");
    while (atual != NULL)
    {
        printf("Nome: %s, CPF: %s, RG: %s, Telefone: %s, Idade: %d\n",
            atual->nome, atual->cpf, atual->rg, atual->telefone, atual->idade);
        atual = atual->prox;
    }
}

void liberarCliente()
{
    Cliente *atual = listaClientes;
    Cliente *proximo;

    while (atual != NULL)
    {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    listaClientes = NULL; // Atualiza a lista para indicar que está vazia
    printf("Espaço alocado para produtos liberado com sucesso.\n");
}

void menuClientes()
{
    int opcao;

    do
    {
        printf("\n====== MENU CLIENTES ======\n");
        printf("1. Inserir Cliente\n");
        printf("2. Alterar Cliente\n");
        printf("3. Remover Cliente (por índice)\n");
        printf("4. Remover Cliente (por nome)\n");
        printf("5. Obter Cliente Mais Velho\n");
        printf("6. Obter Cliente Mais Novo\n");
        printf("7. Imprimir Lista de Clientes\n");
        printf("0. Voltar ao Menu Principal\n");

        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
        {
            char nome[50], cpf[15], rg[15], telefone[15];
            int idade;

            printf("Nome: ");
            scanf("%s", nome);
            printf("CPF: ");
            scanf("%s", cpf);
            printf("RG: ");
            scanf("%s", rg);
            printf("Telefone: ");
            scanf("%s", telefone);
            printf("Idade: ");
            scanf("%d", &idade);

            inserirCliente(nome, cpf, rg, telefone, idade);
            break;
        }
        case 2:
        {
            char nome[50], cpf[15], rg[15], telefone[15];
            int idade;

            printf("Nome do Cliente a ser alterado: ");
            scanf("%s", nome);
            printf("Novo CPF: ");
            scanf("%s", cpf);
            printf("Novo RG: ");
            scanf("%s", rg);
            printf("Novo Telefone: ");
            scanf("%s", telefone);
            printf("Nova Idade: ");
            scanf("%d", &idade);

            alterarCliente(nome, cpf, rg, telefone, idade);
            break;
        }
        /*case 3:
        {
            int indice;
            printf("Índice do Cliente a ser removido: ");
            scanf("%d", &indice);

            removerCliente(indice);
            break;
        }*/
        case 4:
        {
            char nome[50];
            printf("Nome do Cliente a ser removido: ");
            scanf("%s", nome);

            removerClienteNome(nome);
            break;
        }
        case 5:
            obterClienteMaisVelho();
            break;
        case 6:
            obterClienteMaisNovo();
            break;
        case 7:
            imprimir();
            break;
            
        case 0:
            printf("Retornando ao Menu Principal.\n");
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 0);
}


int main0(){
    menuClientes();
}
