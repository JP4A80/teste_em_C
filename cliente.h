#ifndef CLIENTE_H
#define CLIENTE_H

struct CLIENTE{
char nome[40];
char cpf[20];
char rg[15];
char telefone[15];
int idade;
struct CLIENTE *prox;
};

typedef struct CLIENTE Cliente;

// Declare a variável global como extern
extern Cliente *listaClientes;

void inserirCliente(char nome[], char cpf[], char rg[], char telefone[], int idade);

void alterarCliente(char nome[], char cpf[], char rg[], char telefone[], int idade);

void removerClienteNome(char nome[]);

void obterClienteMaisVelho();

void obterClienteMaisNovo(); 

void imprimir();

void liberarCliente();

void menuClientes();

#endif