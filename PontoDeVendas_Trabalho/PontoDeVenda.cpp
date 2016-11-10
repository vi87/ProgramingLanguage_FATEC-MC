// Programa de Ponto de Venda
// FATEC-MC - Sigla do Aluno - 22-10-2014 Vers�o 0.0
#include "PDV.h"
//
// entry point do programa
//
void main(void)
{
	int nCodigo,					// para receber o c�digo do produto
		i;							// indice gen�rico
	PRODUTO stProduto;				// struct para um produto
	FILE *fdProduto;				// file descriptor do produto
	SYSTEMTIME stTime;				// para data e hora
	char cWork[200],				// para sprintf
		cOpcao;						// op��o de escolha do operador
	setlocale(LC_ALL, "portuguese_brazil"); // para acentua��o brasileira
	// abrir o arquivo em modo leitura e grava��o e bin�ria e
	// precisa existir
	if(fopen_s(&fdProduto, CAMINHO_ARQ_PRODUTO, "r+b") != 0)	// erro de abertura?
	{
		if(fopen_s(&fdProduto, CAMINHO_ARQ_PRODUTO, "w+b") != 0) // erro de abertura?
		{
			cout << "Problema na abertura do arquivo "
				<< CAMINHO_ARQ_PRODUTO << endl;
			PAUSA;
			return;					// volta ao sistema operacional
		}
		// vamos iniciar o arquivo 
		for(i = 0; i < QTDE_MAXIMA_PRODUTOS; i++)
		{
			stProduto.nCodigo = i + 1;		// 1, 2, 3, .......QTDE_MAXIMA_PRODUTOS
			stProduto.flgAtivo = false;		// produto inativo
			if(fwrite(&stProduto, TAM_PROD, 1, fdProduto) == 0)
			{	// erro de grava��o
				fclose(fdProduto);		// fechar o arquivo
				cout << "Erro de grava��o!" << endl;
				PAUSA;
				return;					// volta ao Sistema Operacional
			}
		} // for i
	} // if arquivo n�o existe
	// temos um arquivo de produto aberto em leitura ou grava��o
	while(true)							// loop infinito
	{
		LIMPAR_TELA;
		GetLocalTime(&stTime);			// data e hora do sistema
		sprintf_s(cWork, "\n\tFATEC-MC - Ponto de Venda %02d/%02d/%04d �s %02d:%02d:%02d",
			stTime.wDay, stTime.wMonth, stTime.wYear,
			stTime.wHour, stTime.wMinute, stTime.wSecond);
		cout << "\t" << cWork << endl;
		// exibir o menu de op��es
		cout << CADASTRAR_NOVO_PRODUTO 
			<< " - Cadastrar um novo produto" << endl;
		cout << EXCLUIR_PRODUTO_EXISTENTE
			<< " - Excluir um produto existente" << endl;
		cout << VENDER_UM_PRODUTO
			<< " - Vender um produto" << endl;
		cout << DAR_ENTRADA_UM_PRODUTO
			<< " - Dar entrada de um produto" << endl;
		cout << DAR_SAIDA_VENCIDO
			<< " - Dar saida de um produto vencido" << endl;
		cout << MOSTRAR_DADOS_PRODUTO
			<< " - Mostrar os dados de um produto" << endl;
		cout << LISTAR_APARTIR_DE
			<< " - Listar cadastro de produtos a partir de um c�digo"
			<< endl;
		cout << SAIR_DO_PROGRAMA << " - Sair do programa" << endl;
		cout << "\tSelecione: ";
		cin >> cOpcao;					// escolha do operador
		cOpcao = toupper(cOpcao);		// para caixa alta (upper case)
		switch(cOpcao)
		{
			case CADASTRAR_NOVO_PRODUTO:
				break;
			case EXCLUIR_PRODUTO_EXISTENTE:
				break;
			case VENDER_UM_PRODUTO:
				break;
			case DAR_ENTRADA_UM_PRODUTO:
				break;
			case DAR_SAIDA_VENCIDO:
				break;
			case MOSTRAR_DADOS_PRODUTO:
				break;
			case LISTAR_APARTIR_DE:
				break;
			case SAIR_DO_PROGRAMA:
				cout << "Deseja sair realmente? (S ou N): ";
				cin >> cOpcao;	
				if(cOpcao == 'S' || cOpcao == 's') // sair realmente?
				{	// vai encerrar o programa
					fclose(fdProduto);				// fechar arquivo
					return;							// cai fora 
				}
				break;
			default:
				cout << "Op��o errada!" << endl;
				PAUSA;
				break;
		}// switch
	} // while
} // main
