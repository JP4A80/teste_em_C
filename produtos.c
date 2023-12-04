#include "produtos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void inserirProduto(int codigo, char nome[], int estoque, float preco, char fornecedor[])
{
  Produto *novoProduto = (Produto *)malloc(sizeof(Produto));
  if (novoProduto == NULL)
  {
    printf("Erro ao alocar memória para novo produto\n");
    return;
  }

  novoProduto->codigo = codigo;
  strcpy(novoProduto->nome, nome);
  novoProduto->estoque = estoque;
  novoProduto->preco = preco;
  strcpy(novoProduto->fornecedor, fornecedor);

  novoProduto->prox = listaProdutos;
  listaProdutos = novoProduto;

  printf("Produto %s inserido com sucesso!\n", nome);
}

void removerProduto(int codigo)
{
  Produto *anterior = NULL;
  Produto *atual = listaProdutos;

  while (atual != NULL)
  {
    if (atual->codigo == codigo)
    {
      if (anterior == NULL)
      {
        // Remoção do primeiro elemento
        listaProdutos = atual->prox;
      }
      else
      {
        anterior->prox = atual->prox;
      }

      free(atual);
      printf("Produto removido com sucesso!\n");
      return;
    }

    anterior = atual;
    atual = atual->prox;
  }

  printf("Produto com código %d não encontrado.\n", codigo);
}

void removerProdutoNome(char nome[])
{
  Produto *anterior = NULL;
  Produto *atual = listaProdutos;

  while (atual != NULL)
  {
    if (strcmp(atual->nome, nome) == 0)
    {
      if (anterior == NULL)
      {
        // Remoção do primeiro elemento
        listaProdutos = atual->prox;
      }
      else
      {
        anterior->prox = atual->prox;
      }

      free(atual);
      printf("Produto %s removido com sucesso!\n", nome);
      return;
    }

    anterior = atual;
    atual = atual->prox;
  }

  printf("Produto %s não encontrado.\n", nome);
}

void alterarProduto(int codigo, char nome[], int estoque, float preco, char fornecedor[])
{
  Produto *atual = listaProdutos;
  while (atual != NULL)
  {
    if (atual->codigo == codigo)
    {
      strcpy(atual->nome, nome);
      atual->estoque = estoque;
      atual->preco = preco;
      strcpy(atual->fornecedor, fornecedor);
      printf("Produto %s alterado com sucesso!\n", nome);
      return;
    }
    atual = atual->prox;
  }

  printf("Produto com código %d não encontrado.\n", codigo);
}

void mostrarEstoqueProduto(char nome[])
{
  Produto *atual = listaProdutos;
  while (atual != NULL)
  {
    if (strcmp(atual->nome, nome) == 0)
    {
      printf("Estoque do produto %s: %d unidades\n", nome, atual->estoque);
      return;
    }
    atual = atual->prox;
  }

  printf("Produto %s não encontrado.\n", nome);
}

void imprimirProdutos()
{
  Produto *atual = listaProdutos;

  if (atual == NULL)
  {
    printf("Lista de produtos vazia.\n");
    return;
  }

  printf("\n=========== LISTA DE PRODUTOS ===========\n");
  while (atual != NULL)
  {
    printf("Código: %d, Nome: %s, Estoque: %d, Preço: %.2f, Fornecedor: %s\n",
           atual->codigo, atual->nome, atual->estoque, atual->preco,
           atual->fornecedor);
    atual = atual->prox;
  }
}

void produtoMaisCaro()
{
  if (listaProdutos == NULL)
  {
    printf("Lista de produtos vazia.\n");
    return;
  }

  Produto *maisCaro = listaProdutos;
  Produto *atual = listaProdutos->prox;

  while (atual != NULL)
  {
    if (atual->preco > maisCaro->preco)
    {
      maisCaro = atual;
    }

    atual = atual->prox;
  }

  printf("Produto mais caro: %s, Preço: %.2f\n", maisCaro->nome,
         maisCaro->preco);
}

void produtoComEstoqueZerado()
{
  Produto *atual = listaProdutos;
  int encontrados = 0;

  while (atual != NULL)
  {
    if (atual->estoque == 0)
    {
      printf("Produto com estoque zerado: %s\n", atual->nome);
      encontrados++;
    }

    atual = atual->prox;
  }

  if (encontrados == 0)
  {
    printf("Nenhum produto com estoque zerado encontrado.\n");
  }
}

void atualizarEstoque(char tipoOperacao, char produtoNome[], int quantidade)
{
  Produto *atual = listaProdutos;

  while (atual != NULL)
  {
    if (strcmp(atual->nome, produtoNome) == 0)
    {
      if (tipoOperacao == 'C' || tipoOperacao == 'c')
      {
        // Compra
        atual->estoque += quantidade;
        printf("Estoque de %s atualizado: +%d unidades\n", produtoNome,
               quantidade);
      }
      else if (tipoOperacao == 'V' || tipoOperacao == 'v')
      {
        // Venda
        if (atual->estoque >= quantidade)
        {
          atual->estoque -= quantidade;
          printf("Estoque de %s atualizado: -%d unidades\n", produtoNome,
                 quantidade);
        }
        else
        {
          printf("Estoque insuficiente para realizar a venda.\n");
        }
      }
      else
      {
        printf("Operação inválida.\n");
      }
      return;
    }
    atual = atual->prox;
  }

  printf("Produto %s não encontrado.\n", produtoNome);
}

void liberarProdutos()
{
  Produto *atual = listaProdutos;
  Produto *proximo;

  while (atual != NULL)
  {
    proximo = atual->prox;
    free(atual);
    atual = proximo;
  }

  listaProdutos = NULL; // Atualiza a lista para indicar que está vazia
  printf("Espaço alocado para produtos liberado com sucesso.\n");
}

void menuProdutos()
{
  int opcao;

  do
  {
    printf("\n====== MENU PRODUTOS ======\n");
    printf("1. Inserir Produto\n");
    printf("2. Alterar Produto\n");
    printf("3. Remover Produto (por código)\n");
    printf("4. Remover Produto (por nome)\n");
    printf("5. Mostrar Estoque de Produto\n");
    printf("6. Imprimir Lista de Produtos\n");
    printf("7. Produto Mais Caro\n");
    printf("8. Produto com Estoque Zerado\n");
    printf("9. Atualizar Estoque (Compra ou Venda)\n");
    printf("0. Voltar ao Menu Principal\n");

    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
    {
      int codigo, estoque;
      float preco;
      char nome[50], fornecedor[50];

      printf("Código: ");
      scanf("%d", &codigo);
      printf("Nome: ");
      scanf("%s", nome);
      printf("Estoque: ");
      scanf("%d", &estoque);
      printf("Preço: ");
      scanf("%f", &preco);
      printf("Fornecedor: ");
      scanf("%s", fornecedor);

      inserirProduto(codigo, nome, estoque, preco, fornecedor);
      break;
    }
    case 2:
    {
      int codigo, estoque;
      float preco;
      char nome[50], fornecedor[50];

      printf("Código do Produto a ser alterado: ");
      scanf("%d", &codigo);
      printf("Novo Nome: ");
      scanf("%s", nome);
      printf("Novo Estoque: ");
      scanf("%d", &estoque);
      printf("Novo Preço: ");
      scanf("%f", &preco);
      printf("Novo Fornecedor: ");
      scanf("%s", fornecedor);

      alterarProduto(codigo, nome, estoque, preco, fornecedor);
      break;
    }
    case 3:
    {
      int codigo;
      printf("Código do Produto a ser removido: ");
      scanf("%d", &codigo);

      removerProduto(codigo);
      break;
    }
    case 4:
    {
      char nome[50];
      printf("Nome do Produto a ser removido: ");
      scanf("%s", nome);

      removerProdutoNome(nome);
      break;
    }
    case 5:
    {
      char nome[50];
      printf("Nome do Produto: ");
      scanf("%s", nome);

      mostrarEstoqueProduto(nome);
      break;
    }
    case 6:
      imprimirProdutos();
      break;
    case 7:
      produtoMaisCaro();
      break;
    case 8:
      produtoComEstoqueZerado();
      break;
    case 9:
    {
      char tipoOperacao, produtoNome[50];
      int quantidade;

      printf("Tipo de Operação (C para Compra, V para Venda): ");
      scanf(" %c", &tipoOperacao); // Espaço antes de %c para consumir a quebra de linha anterior
      printf("Nome do Produto: ");
      scanf("%s", produtoNome);
      printf("Quantidade: ");
      scanf("%d", &quantidade);

      atualizarEstoque(tipoOperacao, produtoNome, quantidade);
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
