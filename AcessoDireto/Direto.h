// Declarações do programa de acesso direto em disco
#include <iostream>
#include <Windows.h>
using namespace std;
// definições do programa
#define PAUSA				system("pause")
#define LIMPAR_TELA			system("cls")
#define CAMINHO_ARQUIVO		"..\\Produto.cad"
#define QTDE_PRODUTOS		3000
// Opções do menu
#define CADASTRAR_PRODUTO	'C'
#define EXCLUIR_PRODUTO		'E'
#define	MOSTRAR_PRODUTO		'M'
#define	SAIR_DO_PROGRAMA	'S'
// struct do produto
typedef struct tagPRODUTO
{
	int nCodigo;		// 1, 2, 3, ..... QTDE_PRODUTOS
	char cAtivo,			// 'A' - ativo e 'I' - inativo ou excluido
		cDescricao[41];			// descricao do produto
	double dPrecoUnit;		// Preço unitário do produto
} PRODUTO;
