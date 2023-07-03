#include <stdio.h>
#include <stdlib.h>
#include "produtos.h"

float realizar_vendas(Armazem armazem)
{
    int item = -1, quant_item = 0, counter = 0, num_vendas = 0, repete = 0, menu;
    unsigned long int codigo;
    float valor_total = 0;
    struct Vendidos *vendidos;

    do
    {
        do
        {
            item = -1;
            system("cls");
            printf("        CÓDIGO       |           NOME           |    VALOR    |    ESTOQUE\n");
            for(int i = 0; i < armazem.quant_produtos; i++)
                printf("\t%-10lu     %-25s     %4.2f\t    %3d\n", armazem.produtos[i].codigo, armazem.produtos[i].nome, armazem.produtos[i].valor_unit, armazem.produtos[i].quant_estoque);

            printf("\nDigite o código do item escolhido: ");
            do
            {
                scanf("%lu", &codigo);
                for(int i = 0; i < armazem.quant_produtos; i++)
                    if(codigo == armazem.produtos[i].codigo)
                        item = i;

                if(item >= 0)
                    counter = 0;
                else
                {
                    printf("\nCódigo inválido\n\nDigite novamente: ");
                    counter = 1;
                }
                fflush(stdin);
            }
            while(counter == 1);
            counter = 0;
            printf("\nDigite a quantidade que deseja comprar: ");
            scanf("%d", &quant_item);
            if(quant_item > armazem.produtos[item].quant_estoque)
            {
                printf("\nQuantidade de item indisponível no estoque\n");
                counter = 1;
                printf("\nPressione [ENTER] para voltar");
                getch();
            }
            else if(quant_item < 0)
            {
                printf("\nQuantidade inválida\n");
                counter = 1;
                printf("\nPressione [ENTER] para voltar");
                getch();
            }

            if(counter == 1)
            {
                system("cls");
                printf("     CÓDIGO  |   OPÇÃO\n\t1\tFinalizar compra\n\t2\tComprar outro item\n\t3\tCancelar compra\n\nDigite o código: ");
                do
                {
                    scanf("%d", &menu);
                    switch(menu)
                    {
                    case 1:
                        counter = 0;
                        break;

                    case 2:
                        counter = 1;
                        break;

                    case 3:
                        leitura_arquivo(armazem);
                        vendas(armazem);
                        break;

                    default:
                        printf("Código inválido\nDigite o código novamente: ");
                    }
                    fflush(stdin);
                }
                while(menu < 1 || menu > 3);
            }
        }
        while(counter == 1);

        if((quant_item > 0) && (quant_item <= armazem.produtos[item].quant_estoque))
        {
            num_vendas++;
            armazem.produtos[item].quant_estoque -= quant_item;
            armazem.produtos[item].quant_vendida += quant_item;

            valor_total += armazem.produtos[item].valor_unit * quant_item;

            vendidos = (struct Vendidos *) realloc(vendidos, sizeof(struct Vendidos) * num_vendas);

            if (vendidos == NULL)
            {
                printf("erro ao alocar");
                exit(1);
            }

            vendidos[num_vendas - 1].item = item;
            vendidos[num_vendas - 1].quantidade = quant_item;
            vendidos[num_vendas - 1].subtotal = armazem.produtos[item].valor_unit * quant_item;
        }

        system("cls");
        printf("Deseja realizar outra venda?\n\n     CÓDIGO  |   OPÇÃO\n\t1\t  Sim\n\t2\t  Não\n\nDigite o código: ");
        do
        {
            scanf("%d", &menu);
            if(menu == 1)
                repete = 1;

            else if(menu == 2)
                repete = 0;

            else
                printf("\nCódigo inválido\n\nDigite o código novamente: ");

            fflush(stdin);
        }
        while((menu > 2) || (menu < 1));
    }
    while(repete == 1);

    for(int i = 0; i < num_vendas - 1; i++)
    {
        for(int j = num_vendas - 1; j > i; j--)
            if(vendidos[j].subtotal > vendidos[j - 1].subtotal)
            {
                int aux = vendidos[j].item;
                vendidos[j].item = vendidos[j - 1].item;
                vendidos[j - 1].item = aux;

                int aux1 = vendidos[j].quantidade;
                vendidos[j].quantidade = vendidos[j - 1].quantidade;
                vendidos[j - 1].quantidade = aux1;

                float aux2 = vendidos[j].subtotal;
                vendidos[j].subtotal = vendidos[j - 1].subtotal;
                vendidos[j - 1].subtotal = aux2;
            }
    }

    system("cls");
    printf("   ITEM   |      CÓDIGO      |           NOME           |    VALOR    |    QUANTIDADE    |   SUBTOTAL\n");

    for(int i = 0; i < num_vendas; i++)
    {
        printf("    %2d\t         %lu\t       %-25s    R$%4.2f\t       %2d\t     R$%4.2f\n",
               i + 1, armazem.produtos[vendidos[i].item].codigo,armazem.produtos[vendidos[i].item].nome, armazem.produtos[vendidos[i].item].valor_unit, vendidos[i].quantidade, vendidos[i].subtotal);
    }
    printf("                                                                                TOTAL:   |   R$%.2f\n", valor_total);

    printf("\nPressione [ENTER] para continuar");
    getch();

    return(valor_total);
    vendas(armazem);
}

void valor_troco(float valor_total, Armazem armazem)
{
    float valor_pago, troco;
    system("cls");

    printf("\nValor total: %.2f\n", valor_total);

    printf("Digite o valor pago: ");
    scanf("%f", &valor_pago);
    troco = valor_pago - valor_total;

    if (troco >= 0)
        printf("\nTroco: %.2f\n", troco);
    else
    {
        printf("\nValor insuficiente\n");
        printf("\nPressione [ENTER] para continuar");
        getch();
        valor_troco(valor_total, armazem);
    }
    printf("\nCompra finalizada\n");

    printf("\nPressione [ENTER] para continuar");
    getch();

    salvamento_data(armazem);
    salvamento_arquivo(armazem);
    vendas(armazem);
}

void vista(float valor_total, Armazem armazem)
{
    int troco;
    float diferenca = 0;
    system("cls");

    if (valor_total < 50)
    {
        printf ("Desconto de 5%%\n");
        diferenca = valor_total * 0.05;
    }

    else if (valor_total >= 50 && valor_total < 100)
    {
        printf ("Desconto de 10%%\n");
        diferenca = valor_total * 0.1;
    }

    else
    {
        printf ("Desconto de 18%%\n");
        diferenca = valor_total * 0.18;
    }

    valor_total -= diferenca;
    printf("\nValor total: %.2f\n", valor_total);

    do
    {
        printf("\nTroco é necessário?\n\n     CÓDIGO  |   OPÇÃO\n\t1\t  Sim\n\t2\t  Não\n\nDigite o código: ");
        scanf("%d", &troco);

        if(troco == 1)
            valor_troco(valor_total, armazem);

        else if(troco == 2)
        {
            printf("\nCompra finalizada\n");

            printf("\nPressione [ENTER] para continuar");
            getch();
        }

        else
            printf("\nCódigo incorreto\n");

        fflush(stdin);
    }
    while(troco < 1 || troco > 2);

    salvamento_data(armazem);
    salvamento_arquivo(armazem);
    vendas(armazem);
}

void prazo(float valor_total, Armazem armazem)
{
    int parcela;
    float diferenca = 0, valor_mensal;
    system("cls");

    printf("Digite quantas parcelas: ");
    do
    {
        scanf("%d", &parcela);
        system("cls");

        if ((parcela >= 1)&&(parcela <= 3))
        {
            printf ("Acréscimo de 5%%\n");
            diferenca = valor_total * 0.05;

            valor_total += diferenca;
            valor_mensal = valor_total / parcela;

            printf ("\nValor total: %.2f\n", valor_total);
            printf ("Valor parcela: %.2f\n", valor_mensal);
        }

        else if (parcela > 3)
        {
            printf ("Acréscimo de 8%%\n");
            diferenca = valor_total * 0.08;

            valor_total += diferenca;
            valor_mensal = valor_total / parcela;

            printf ("\nValor total: %.2f\n", valor_total);
            printf ("Valor parcela: %.2f\n", valor_mensal);
        }
        else
            printf("\nNúmero de parcelas inválido\n\nDigite um valor igual ou acima de 1 parcela: ");

        fflush(stdin);
    }
    while(parcela < 1);

    printf("\nCompra finalizada\n");

    printf("\nPressione [ENTER] para continuar");
    getch();

    salvamento_data(armazem);
    salvamento_arquivo(armazem);
    vendas(armazem);
}

void pagamento(float valor_total, Armazem armazem)
{
    system("cls");
    int modo_pagamento;

    printf("Formas de pagamento:\n\n     CÓDIGO  |   OPÇÃO\n\t1\tÀ vista\n\t2\tA prazo\n\nDigite o código: ");
    scanf("%d", &modo_pagamento);

    if (modo_pagamento == 1)
    {
        printf("\nPagamento à vista\n");
        vista(valor_total, armazem);
    }

    else if (modo_pagamento == 2)
    {
        printf("\nPagamento a prazo\n");
        prazo(valor_total, armazem);
    }
    else
    {
        printf("\nOpção de pagamento inválida\n");
        printf("\nPressione [ENTER] para continuar");
        getch();
        pagamento(valor_total, armazem);
    }
}

void relatorio_vendas(Armazem armazem)
{
    system("cls");
    printf("        CÓDIGO       |           NOME           |    ESTOQUE    |    VENDIDOS\n");
    for(int i = 0; i < armazem.quant_produtos; i++)
        printf("\t%-10lu     %-25s       %3d\t       %3d\n", armazem.produtos[i].codigo, armazem.produtos[i].nome, armazem.produtos[i].quant_estoque, armazem.produtos[i].quant_vendida);

    printf("\nPressione [ENTER] para voltar");
    getch();

    vendas(armazem);
}

void vendas(Armazem armazem)
{
    system("cls");
    int opcao = 0;
    float valor_troco;
    printf("     CÓDIGO  |   OPÇÃO\n\t1\tRealizar vendas\n\t2\tRelatório de vendas\n\t3\tVoltar\n\nDigite um código: ");
    do
    {
        scanf("%d", &opcao);

        if(opcao == 1)
        {
            valor_troco = realizar_vendas(armazem);
            pagamento(valor_troco, armazem);
        }

        else if(opcao == 2)
            relatorio_vendas(armazem);

        else if(opcao == 3)
            main();

        else
            printf("\nCódigo inválido\n\nDigite um código válido: ");

        fflush(stdin);
    }
    while(opcao < 1 || opcao > 3);

    vendas(armazem);
}
