#include <stdio.h>
#include "cliente.h"
#include "produtos.h"
#include "vendas.h"

int main()
{
    int opcao;

    do
    {
        printf("\n=========== MENU PRINCIPAL ===========\n");
        printf("1. Menu de Clientes\n");
        printf("2. Menu de Produtos\n");
        printf("3. Menu de Vendas\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            menuClientes();
            break;
        case 2:
            menuProdutos();
            break;
        case 3:
            menuVendas();
            break;
        case 0:
            printf("Saindo do programa. Até mais!\n");
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}