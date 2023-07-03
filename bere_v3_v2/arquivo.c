#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "produtos.h"

void salvamento_data(Armazem armazem)
{
    FILE *arq_data = NULL;
    char data[23];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(data, sizeof(data), "%d-%d-%d_%d-%d-%d.txt", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    arq_data = fopen(data, "w");

    if (arq_data == NULL)
    {
        printf("Erro ao abrir o arquivo de dados.\n");
        exit(1);
    }

    fprintf(arq_data, "        CÓDIGO       |           NOME           |    VENDIDOS\n");
        for(int i = 0; i < armazem.quant_produtos; i++)
            fprintf(arq_data,"\t%-10lu     %-25s       %3d\n", armazem.produtos[i].codigo, armazem.produtos[i].nome, armazem.produtos[i].quant_vendida);

    fclose(arq_data);
}

void salvamento_arquivo(Armazem armazem)
{
    FILE *arq_produtos = NULL;
    arq_produtos = fopen("produtos.bin", "wb");

    if (arq_produtos == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    fwrite(&armazem.quant_produtos, sizeof(int), 1, arq_produtos);
    for(int i = 0; i < armazem.quant_produtos; i++)
        fwrite(&armazem.produtos[i], sizeof(Produto), 1, arq_produtos);

    if(arq_produtos == NULL)
    {
        printf("Erro ao abrir");
        exit(1);
    }

    fclose(arq_produtos);
}

Armazem leitura_arquivo()
{
    FILE *arq_prod = NULL;
    Armazem armazem;
    arq_prod = fopen("produtos.bin", "rb");

    if (arq_prod == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    fread(&armazem.quant_produtos, sizeof(int), 1, arq_prod);

    armazem.produtos = NULL;
    armazem.produtos = (Produto *) calloc(armazem.quant_produtos, sizeof(Produto));

    if(armazem.produtos == NULL)
    {
        printf("ERRO AO ALOCAR\n");
        exit(1);
    }

    for(int i = 0; i < armazem.quant_produtos; i++)
        fread(&(armazem.produtos[i]), sizeof(Produto), 1, arq_prod);

    fclose(arq_prod);

    return armazem;
}

