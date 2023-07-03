#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "produtos.h"

int main()
{
    setlocale(LC_CTYPE, "Portuguese");
    system("cls");
    int opcao = 0;
    Armazem armazem;
    printf("     CÓDIGO  |   OPÇÃO\n\t1\tProdutos\n\t2\tVendas\n\t3\tSair\n\nDigite um código: ");
    do
    {
        scanf("%d", &opcao);

        if(opcao == 1)
        {
            system("cls");
            armazem = leitura_arquivo();
            funcao_produto(armazem);
        }

        else if(opcao == 2)
        {
            system("cls");
            armazem = leitura_arquivo();
            vendas(armazem);
        }

        else if(opcao == 3)
        {
            system("cls");
            printf("Obrigado por usar nosso programa!\n");
            exit(0);
        }

        else
            printf("\nCódigo inválido\n\nDigite um código válido: ");

        fflush(stdin);
    }
    while(opcao < 1 || opcao > 3);
    return 0;
}
