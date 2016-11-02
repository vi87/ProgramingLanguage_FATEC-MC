// Programa teste de acesso direto
// FATEC-MC - JCB - 26/10/2016 - Versão 0.0
#include "Direto.h"
//
// entry point do programa
//
void main(void)
{
	int i,				// indice generico
		nCodigo;		// para receber o codigo digitado
	char cWork[200],		// para o uso do sprintf
		cOpcao;				// para opcao do operador
	PRODUTO stProduto;		// struct para receber os dados de um produto (buffer)
	FILE *fdProduto;		// file descriptor do cadastro de produtos
	setlocale(LC_ALL, "portuguese_brazil");		// acentuação brasileira
	// abrir o arquivo em modo r+b, ele precisa existir
	if (fopen_s(&fdProduto, CAMINHO_ARQUIVO, "r+b") != 0)		// arquivo não existe?
	{ // vamos formatar o arquivo com todos os produtos inativos - primeira vez
		if (fopen_s(&fdProduto, CAMINHO_ARQUIVO, "w+b") != 0)		// erro irrecuperável?
		{ // erro irrecuperavel
			cout << "Erro irrecuperável na abertura do arquivo." << endl;
			PAUSA;
			return;			// volta ao S.O.
		}
		// formatar o produto com produtos inativos em uma gravação sequencial
		for (i = 0; i < QTDE_PRODUTOS; i++)
		{
			stProduto.cAtivo = 'I';		// produto inativo
			stProduto.nCodigo = i + 1;		// 1, 2, 3 ....
			stProduto.cDescricao[0] = NULL;	// descricao vazia
			stProduto.dPrecoUnit = 0.0;		// preço unitario zerado
			if (fwrite(&stProduto, sizeof(PRODUTO), 1, fdProduto) == 0)		// erro de gravação?
			{ // erro irrecuperavel
				fclose(fdProduto);		// fechar o cadastro
				cout << "Erro de gravação." << endl;
				PAUSA;
				return;		// volta ao S.O.
			} 
		} // for i
	}
	// loop infinito com as opções do menu
	while (true)
	{
		LIMPAR_TELA;
		cout << "Programa de teste de acesso direto" << endl;
		cout << CADASTRAR_PRODUTO << " - Cadastrar novo produto" << endl;
		cout << EXCLUIR_PRODUTO << " - Excluir produto existente" << endl;
		cout << MOSTRAR_PRODUTO << " - Mostrar os dados de um produto" << endl;
		cout << SAIR_DO_PROGRAMA << " - Sair do programa" << endl;
		cout << "\n Selecione um: ";
		cin >> cOpcao;				// recebe opcao do operador
		cOpcao = toupper(cOpcao);	// Converte para maiuscula
		switch (cOpcao)			// avalia a opç~cao escolhida
		{
		case CADASTRAR_PRODUTO:
			break;
		case EXCLUIR_PRODUTO:
			break;
		case MOSTRAR_PRODUTO:
			break;
		case SAIR_DO_PROGRAMA:
			return;
		default:
			cout << "Opção inválida!\n" << endl;
			PAUSA;
		} // switch
	} // while
} // main