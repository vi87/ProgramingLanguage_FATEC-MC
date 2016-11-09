// Programa teste de acesso direto
// FATEC-MC - JCB - 26/10/2016 - Vers�o 0.0
#include "Direto.h"
// Fun��o que pede c�digo de produto v�lido
//	Par�metros:
//		Entradas:	int *ptrCodigo - Ponteiro de uma inteira que receber� o c�digo digitado
//					char *ptrTransacao - Ponteiro de uma string que cont�m a transa��o sendo realizada
//		Retorno:	bool - True - Foi digitado um c�digo v�lido
//							false - foi cancelada a transa��o pela digita��o de um c�digo zero
bool PedirCodigoProduto(int *ptrCodigo, char *ptrTransacao)
{
	cout << "\n\t " << ptrTransacao << endl;			// transa��o sendo executada
	do
	{
		cout << "Digite o c�digo do produto de 1 a " << QTDE_PRODUTOS << endl
			<< "Ou zero para cancelar a transa��o: ";
		cin >> *ptrCodigo;
		if (*ptrCodigo == 0)				// cancelar?
			return false;
	} while (*ptrCodigo < 1 || *ptrCodigo > QTDE_PRODUTOS);
	return true;							// indica que tem um c�digo v�lido
}
// Fun��o que l� um registro de produto de forma posicional
//	Par�metros:
//		Entradas:	 int nCodigo - C�digo do produto 1, 2, 3 ..... QTDE_PRODUTO  a ser buscado
//					PRODUTO *ptrStProduto - Ponteiro de um struct do chamador da fun��o a receber os dados do produto
//					FILE *fdProduto - File descriptor do arquivo produtos
//		Retorno:	bool - True - leitura foi realizada OK!
//							false - erro no fseek ou fred
//					
bool LerProdutoPosicional(int nCodigo, PRODUTO *ptrStProduto, FILE *fdProduto)
{
	if (fseek(fdProduto, (nCodigo - 1) * sizeof(PRODUTO), SEEK_SET) != 0)		// erro de SEEK?
		return false;			// avisa o erro
	if (fread_s(ptrStProduto, sizeof(PRODUTO), sizeof(PRODUTO), 1, fdProduto) == 0)			// erro de leitura?
		return false;
	return true;		// foi lido tudo ok
}
// Fun��o que grava um registro de produto de forma posicional
//	Par�metros:
//		Entradas:	PRODUTO *ptrStProduto - Ponteiro de um struct do chamador da fun��o e que cont�m os dados de um produto a ser gravado
//					FILE *fdProduto - File descriptor do arquivo produtos
//					
//		Retorno:	bool - True - grava��o foi realizada OK!
//							false - erro no fseek ou de grava��o
bool GravarProdutoPosicional(PRODUTO *ptrStProduto, FILE *fdProduto)
{
	if (fseek(fdProduto, (ptrStProduto->nCodigo - 1) * sizeof(PRODUTO), SEEK_SET) != 0)		// erro de SEEK?
		return false;			// avisa o erro
	if (fwrite(ptrStProduto, sizeof(PRODUTO), 1, fdProduto) == 0)		// erro de grava��o
		return false;
	return true;		// grava��o tudo OK
}
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
	setlocale(LC_ALL, "portuguese_brazil");		// acentua��o brasileira
	// abrir o arquivo em modo r+b, ele precisa existir
	if (fopen_s(&fdProduto, CAMINHO_ARQUIVO, "r+b") != 0)		// arquivo n�o existe?
	{ // vamos formatar o arquivo com todos os produtos inativos - primeira vez
		if (fopen_s(&fdProduto, CAMINHO_ARQUIVO, "w+b") != 0)		// erro irrecuper�vel?
		{ // erro irrecuperavel
			cout << "Erro irrecuper�vel na abertura do arquivo." << endl;
			PAUSA;
			return;			// volta ao S.O.
		}
		// formatar o produto com produtos inativos em uma grava��o sequencial
		for (i = 0; i < QTDE_PRODUTOS; i++)
		{
			stProduto.cAtivo = 'I';		// produto inativo
			stProduto.nCodigo = i + 1;		// 1, 2, 3 ....
			stProduto.cDescricao[0] = NULL;	// descricao vazia
			stProduto.dPrecoUnit = 0.0;		// pre�o unitario zerado
			if (fwrite(&stProduto, sizeof(PRODUTO), 1, fdProduto) == 0)		// erro de grava��o?
			{ // erro irrecuperavel
				fclose(fdProduto);		// fechar o cadastro
				cout << "Erro de grava��o." << endl;
				PAUSA;
				return;		// volta ao S.O.
			} 
		} // for i
	} // arquivo existe
	// loop infinito com as op��es do menu
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
		switch (cOpcao)			// avalia a op�~cao escolhida
		{
		case CADASTRAR_PRODUTO:
			if (!PedirCodigoProduto(&stProduto.nCodigo, "Cadastrar produto"))	// cancelou?
				break;				// retorna ao menu
			// verificar se o produto j� est� cadastrado
			if (!LerProdutoPosicional(stProduto.nCodigo, &stProduto, fdProduto))		// erro?
			{	// erro de seek ou leitura
				cout << "Erro de leitura!" << endl;
				PAUSA;
				break;					// volta ao menu
			}
			if (stProduto.cAtivo == 'A')		// produto cadastrado??
			{	// produto j� cadastrado
				sprintf_s(cWork, "\nC�digo: %d Descri��o: %-40s\nPre�o Unit�rio: %9.2f j� est� cadastrado!",
					stProduto.nCodigo, stProduto.cDescricao, stProduto.dPrecoUnit);
				cout << cWork << endl;
				PAUSA;
				break;			// volta ao menu
			}
			cin.ignore(1, EOF);				// ignorar tecla enter
			cout << "Descri��o: ";
			cin.getline(stProduto.cDescricao, 40, '\n');
			cout << "Pre�o unit�rio: ";
			cin >> stProduto.dPrecoUnit;
			stProduto.cAtivo = 'A';			// produto cadastrado.
			// gravar este produto de forma posicional
			if (!GravarProdutoPosicional(&stProduto, fdProduto)) // erro de grava��o?
			{	// erro de grava��o
				cout << "Erro de grava��o!" << endl;
				PAUSA;
			}
			break;
		case EXCLUIR_PRODUTO:
			if (!PedirCodigoProduto(&stProduto.nCodigo, "Excluir produto"))	// cancelou?
				break;				// retorna ao menu
									// verificar se o produto j� est� cadastrado
			if (!LerProdutoPosicional(stProduto.nCodigo, &stProduto, fdProduto))		// erro?
			{	// erro de seek ou leitura
				cout << "Erro de leitura!" << endl;
				PAUSA;
				break;					// volta ao menu
			}
			if (stProduto.cAtivo != 'A')		// produto n�o cadastrado??
			{
				cout << "Produto n�o cadastrado!" << endl;
				PAUSA;
				break;			// volta ao menu
			}
			sprintf_s(cWork, "\nC�digo: %d Descri��o: %-40s\nPre�o Unit�rio: %9.2f confirma exclus�o (S ou N): ",
				stProduto.nCodigo, stProduto.cDescricao, stProduto.dPrecoUnit);
			cout << cWork << endl;
			cin >> cOpcao;
			if (cOpcao == 's' || cOpcao == 'S')		// excluir realmente?
			{
				stProduto.cAtivo = 'I';		// torna produto exclu�do
				if (!GravarProdutoPosicional(&stProduto, fdProduto))		// erro de grava��o?
				{
					cout << "Erro de grava��o!" << endl;
					PAUSA;
				}
			}
			break;			// volta ao menu
		case MOSTRAR_PRODUTO:
			if (!PedirCodigoProduto(&stProduto.nCodigo, "Mostrar produto"))	// cancelou?
				break;				// retorna ao menu
									// verificar se o produto j� est� cadastrado
			if (!LerProdutoPosicional(stProduto.nCodigo, &stProduto, fdProduto))		// erro?
			{	// erro de seek ou leitura
				cout << "Erro de leitura!" << endl;
				PAUSA;
				break;					// volta ao menu
			}
			if (stProduto.cAtivo != 'A')		// produto n�o cadastrado??
			{
				cout << "Produto n�o cadastrado!" << endl;
				PAUSA;
				break;			// volta ao menu
			}
			sprintf_s(cWork, "\nC�digo: %d Descri��o: %-40s\nPre�o Unit�rio: %9.2f",
				stProduto.nCodigo, stProduto.cDescricao, stProduto.dPrecoUnit);
			cout << cWork << endl;
			PAUSA;
			break;
		case SAIR_DO_PROGRAMA:
			cout << "Deseja sair realmente? (S ou N): ";
			cin >> cOpcao;
			if (cOpcao == 's' || cOpcao == 'S')
			{
				fclose(fdProduto);			// fechar o arquivo
				return;						// volta ao sistema operacional
			}
			break;			// volta para o menu
		default:
			cout << "Op��o inv�lida!\n" << endl;
			PAUSA;
		} // switch
	} // while
} // main