#ifndef PRODUTOS_H_INCLUDED
#define PRODUTOS_H_INCLUDED

typedef struct produto
{
    unsigned long int codigo;
    char nome[25];
    float valor_unit;
    int quant_estoque;
    int quant_vendida;
}Produto;

typedef struct armazem
{
    int quant_produtos;
    Produto *produtos;
}Armazem;

struct Vendidos
{
    int item;
    int quantidade;
    float subtotal;
};

struct Vendidos *vendidos;

Armazem leitura_arquivo();
void funcao_produto(Armazem armazem);
void vendas(Armazem armazem);
void salvamento_arquivo(Armazem armazem);
void salvamento_data(Armazem armazem);

#endif // PRODUTOS_H_INCLUDED
