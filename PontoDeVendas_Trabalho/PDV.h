// Declarações do Programa de Ponto de Venda
#include <iostream>
#include <Windows.h>
using namespace std;
// Definições do Programa
#define PAUSA					system("pause")
#define LIMPAR_TELA				system("cls")
// Dimensionamento do programa
#define QTDE_MAXIMA_PRODUTOS	5000
#define CAMINHO_ARQ_PRODUTO		"..\\Produtos.arq"
// struct do produto
typedef struct tagPRODUTO
{
	int nCodigo;				// código que vai de 1, 2, 3.... a QTDE_MAXIMA_PRODUTOS
	bool flgAtivo;				// true - indica ativo e false - inativo ou
								//	      excluido
	char cEAN_13[14],			// Código Nacional de Produto
		cDescricao[41];			// descrição do produto
	double dPrecoUnit,			// preço unitário
		dQtdeEstoque,			// qtde em estoque com 3 casas decimais
		dQtdeVendida,			// qtde vendida total
		dQtdeUltCompra,			// qtde da última compra
		dQtdeVencida;			// qtde total com data vencida ou roubo
}PRODUTO;
#define TAM_PROD				sizeof(PRODUTO)
// Opções do menu do operador
#define CADASTRAR_NOVO_PRODUTO		'C'
#define EXCLUIR_PRODUTO_EXISTENTE	'E'
#define VENDER_UM_PRODUTO			'V'
#define DAR_ENTRADA_UM_PRODUTO		'D'
#define DAR_SAIDA_VENCIDO			'S'
#define MOSTRAR_DADOS_PRODUTO		'M'
#define LISTAR_APARTIR_DE			'L'
#define SAIR_DO_PROGRAMA			'X'
// Protótipos do programa
int PedirCodigoProduto(char *ptrTransacao);
bool LerUmProduto(int nCodigo, FILE *ptrFdProduto, PRODUTO *ptrStProduto);
