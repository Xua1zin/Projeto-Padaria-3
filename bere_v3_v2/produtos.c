#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produtos.h"

void exibir(Armazem armazem)
{
    system("cls");
    printf("        CÓDIGO       |           NOME           |    VALOR    |    ESTOQUE\n");
    for(int i = 0; i < armazem.quant_produtos; i++)
        printf("\t%-10lu     %-25s     %4.2f\t    %3d\n", armazem.produtos[i].codigo, armazem.produtos[i].nome, armazem.produtos[i].valor_unit, armazem.produtos[i].quant_estoque);

    printf("\nPressione [ENTER] para voltar");
    getch();
}

void cadastrar(Armazem armazem)
{
    system("cls");
    int quant = 0, tamanho_str = 0;
    int ultimo_item = armazem.quant_produtos;
    printf("Digite a quantidade de novos itens: ");
    do
    {
        scanf("%d", &quant);

        if(quant <= 0)
            printf("\nEstá tentando adicionar zero ou menos itens\nDigite um valor maior que zero: ");

        fflush(stdin);
    }
    while(quant <= 0);


    armazem.produtos = (Produto *) realloc(armazem.produtos, sizeof(Produto) * (quant + armazem.quant_produtos));
    armazem.quant_produtos += quant;

    for(int i = ultimo_item; i < armazem.quant_produtos; i++)
    {
        system("cls");
        int counter;
        printf("Digite o código do item: ");
        do
        {
            counter = 0;
            scanf("%lu", &armazem.produtos[i].codigo);
            for(int j = 0; j < i; j++)
                if(armazem.produtos[i].codigo == armazem.produtos[j].codigo)
                {
                    counter = 1;
                    printf("\nCódigo já em uso\nDigite um código novo: ");
                }
        }
        while(counter == 1);

        printf("\nDigite o nome do item: ");
        do
        {
            counter = 0;
            fflush(stdin);
            gets(armazem.produtos[i].nome);
            tamanho_str = strlen(armazem.produtos[i].nome);


            for(int j = 0; j < strlen(armazem.produtos[i].nome); j++)
            {
                if(isspace(armazem.produtos[i].nome[j]) == 0)
                {
                    counter = 0;
                    break;
                }
                else
                    counter = 1;
            }
            if(strlen(armazem.produtos[i].nome) == 0)
                counter = 1;

            else if(tamanho_str > 25)
            {
                printf("\nNome do item muito grande");
                counter = 1;
            }

            if(counter == 1)
                printf("\nDigite novamente: ");
            fflush(stdin);
        }
        while(counter == 1);

        while(isspace(armazem.produtos[i].nome[0]))
            for(int j = 0; j < strlen(armazem.produtos[i].nome); j++)
            {
                int aux = armazem.produtos[i].nome[j];
                armazem.produtos[i].nome[j] = armazem.produtos[i].nome[j + 1];
                armazem.produtos[i].nome[j + 1] = aux;
            }
        printf("\nDigite o preço do item: ");
        do
        {
            counter = 0;
            scanf("%f", &armazem.produtos[i].valor_unit);
            if(armazem.produtos[i].valor_unit < 0)
            {
                counter = 1;
                printf("\nValor menor que zero\nDigite um valor maior ou igual a zero: ");
            }
            fflush(stdin);
        }
        while(counter == 1);

        printf("\nDigite a quantidade de estoque do item: ");
        do
        {
            counter = 0;
            scanf("%d", &armazem.produtos[i].quant_estoque);
            if(armazem.produtos[i].quant_estoque < 0)
            {
                counter = 1;
                printf("\nEstoque menor que zero\nDigite um número maior ou igual a zero: ");
            }
            fflush(stdin);
        }
        while(counter == 1);
        armazem.produtos[i].quant_vendida = 0;
    }

    system("cls");
    printf("Itens cadastrados com sucesso!\n");
    printf("        CÓDIGO       |           NOME           |    VALOR    |    ESTOQUE\n");
    for(int i = ultimo_item; i < armazem.quant_produtos; i++)
        printf("\t%-10lu     %-25s     %4.2f\t    %3d\n", armazem.produtos[i].codigo, armazem.produtos[i].nome, armazem.produtos[i].valor_unit, armazem.produtos[i].quant_estoque);

    printf("\nPressione [ENTER] para voltar");
    getch();
    funcao_produto(armazem);
}

void atualizar(Armazem armazem)
{
    int item = -1, estoque = 0, opcao;
    unsigned long int codigo;
    float preco = 0;
    system("cls");
    printf("        CÓDIGO       |           NOME           |    VALOR    |    ESTOQUE\n");
    for(int i = 0; i < armazem.quant_produtos; i++)
        printf("\t%-10lu     %-25s     %4.2f\t    %3d\n", armazem.produtos[i].codigo, armazem.produtos[i].nome, armazem.produtos[i].valor_unit, armazem.produtos[i].quant_estoque);
    printf("Digite o código do item que deseja atualizar: ");
    scanf("%lu", &codigo);
    for(int i = 0; i < armazem.quant_produtos; i++)
        if(codigo == armazem.produtos[i].codigo)
            item = i;
    if(item >= 0)
    {
        printf("\nDigite a nova quantidade no estoque: ");
        scanf("%d", &estoque);
        printf("\nDigite o novo preço do produto: ");
        scanf("%f", &preco);
        system("cls");
        printf("        CÓDIGO       |           NOME           |    VALOR    |    ESTOQUE\n");
        printf("ANTES:\t%-10lu     %-25s     %4.2f\t    %3d\n\n", armazem.produtos[item].codigo, armazem.produtos[item].nome, armazem.produtos[item].valor_unit, armazem.produtos[item].quant_estoque);
        printf("DEPOIS:\t%-10lu     %-25s     %4.2f\t    %3d\n",armazem.produtos[item].codigo, armazem.produtos[item].nome, preco, estoque);
        printf("\nDeseja confirmar alteração?\n\n     CÓDIGO  |   OPÇÃO\n\t1\tConfirmar\n\t2\tCancelar\n\nEscolha uma opção: ");
        do
        {
            scanf("%d", &opcao);
            if(opcao == 1)
            {
                armazem.produtos[item].valor_unit = preco;
                armazem.produtos[item].quant_estoque = estoque;
            }
            else if(opcao == 2) {}
            else
                printf("\nEscolha uma opção válida\nDigite novamente: ");

            fflush(stdin);
        }
        while(opcao < 1 || opcao > 2);
    }
    else
        printf("\nProduto não encontrado\n");

    printf("\nPressione [ENTER] para voltar");
    getch();
    funcao_produto(armazem);
}

void excluir(Armazem armazem)
{
    system("cls");
    int item = -1, opcao;
    unsigned long int codigo;
    printf("        CÓDIGO       |           NOME           |    VALOR    |    ESTOQUE\n");
    for(int i = 0; i < armazem.quant_produtos; i++)
        printf("\t%-10lu     %-25s     %4.2f           %3d\n", armazem.produtos[i].codigo, armazem.produtos[i].nome, armazem.produtos[i].valor_unit, armazem.produtos[i].quant_estoque);

    printf("\nDigite o código do item que deseja excluir: ");
    scanf("%lu", &codigo);
    for(int i = 0; i < armazem.quant_produtos; i++)
        if(codigo == armazem.produtos[i].codigo)
            item = i;

    if(item >= 0)
    {
        system("cls");
        printf("        CÓDIGO       |           NOME           |    VALOR    |    ESTOQUE\n");
        printf("\t%-10lu     %-25s     %4.2f           %3d\n",armazem.produtos[item].codigo, armazem.produtos[item].nome, armazem.produtos[item].valor_unit, armazem.produtos[item].quant_estoque);
        printf("\nDeseja excluir este item?\n\n     CÓDIGO  |   OPÇÃO\n\t1\tConfirmar\n\t2\tCancelar\n\nEscolha uma opção: ");
        do
        {
            scanf("%d", &opcao);
            if(opcao == 1)
            {
                for(int i = item; i < armazem.quant_produtos; i++)
                    armazem.produtos[i] = armazem.produtos[i + 1];

                armazem.quant_produtos--;
                armazem.produtos = (Produto *) realloc(armazem.produtos, sizeof(Produto) * (armazem.quant_produtos));
            }
            else if(opcao == 2) {}
            else
                printf("\nEscolha uma opção válida\nDigite novamente: ");

            fflush(stdin);
        }
        while(opcao < 1 || opcao > 2);
    }
    else
        printf("\nProduto não encontrado\n");

    printf("\nPressione [ENTER] para voltar");
    getch();
    funcao_produto(armazem);
}

void salvar(Armazem armazem)
{
    salvamento_arquivo(armazem);
    printf("Salvo com sucesso!\n\nPressione [ENTER] para continuar");
    getch();
}

void ler(Armazem armazem)
{
    system("cls");
    armazem = leitura_arquivo();
    printf("Lido com sucesso!\n\nPressione [ENTER] para voltar");
    getch();
    funcao_produto(armazem);
}

void funcao_produto(Armazem armazem)
{
    system("cls");
    int opcao = 0, salvo = 1, opcao_salvar = 0;

    printf("     CÓDIGO  |   OPÇÃO\n\t1\tExibir\n\t2\tCadastrar\n\t3\tAtualizar\n\t4\tExcluir\n\t5\tSalvar\n\t6\tLer\n\t7\tVoltar\n\nDigite um código: ");
    do
    {
        scanf("%d", &opcao);

        switch(opcao)
        {

        case 1:
            exibir(armazem);
            break;

        case 2:
            salvo = 0;
            cadastrar(armazem);
            break;

        case 3:
            salvo = 0;
            atualizar(armazem);
            break;

        case 4:
            salvo = 0;
            excluir(armazem);
            break;

        case 5:
            salvo = 1;
            salvar(armazem);
            break;

        case 6:
            salvo = 1;
            ler(armazem);
            break;

        case 7:
            if(salvo == 1)
            {
                system("cls");
                printf("Deseja salvar antes de sair?\n\n     CÓDIGO  |   OPÇÃO\n\t1\tConfirmar\n\t2\tCancelar\n\nEscolha uma opção: ");
                do
                {
                    scanf("%d", &opcao_salvar);
                    if(opcao_salvar == 1)
                        salvar(armazem);
                    else if(opcao_salvar == 2){}
                    else
                    printf("\nCódigo inválido\nDigite novamente: ");
                }
                while(opcao_salvar < 1 || opcao_salvar > 2);
            }
            main();
            break;

        default:
            printf("\nCódigo inválido\n\nDigite um código válido: ");
        }
        fflush(stdin);
    }
    while(opcao < 1 || opcao > 7);

    funcao_produto(armazem);
}
