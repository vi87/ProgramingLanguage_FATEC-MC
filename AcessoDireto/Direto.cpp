// Programa teste de acesso direto
// FATEC-MC - JCB - 26/10/2016 - Versão 0.0
#include "Direto.h"
// Função que pede código de produto válido
//	Parâmetros:
//		Entradas:	int *ptrCodigo - Ponteiro de uma inteira que receberá o código digitado
//					char *ptrTransacao - Ponteiro de uma string que contém a transação sendo realizada
//		Retorno:	bool - True - Foi digitado um código válido
//							false - foi cancelada a transação pela digitação de um código zero
bool PedirCodigoProduto(int *ptrCodigo, char *ptrTransacao)
{
	cout << "\n\t " << ptrTransacao << endl;			// transação sendo executada
	do
	{
		cout << "Digite o código do produto de 1 a " << QTDE_PRODUTOS << endl
			<< "Ou zero para cancelar a transação: ";
		cin >> *ptrCodigo;
		if (*ptrCodigo == 0)				// cancelar?
			return false;
	} while (*ptrCodigo < 1 || *ptrCodigo > QTDE_PRODUTOS);
	return true;							// indica que tem um código válido
}
// Função que lê um registro de produto de forma posicional
//	Parâmetros:
//		Entradas:	 int nCodigo - Código do produto 1, 2, 3 ..... QTDE_PRODUTO  a ser buscado
//					PRODUTO *ptrStProduto - Ponteiro de um struct do chamador da função a receber os dados do produto
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
// Função que grava um registro de produto de forma posicional
//	Parâmetros:
//		Entradas:	PRODUTO *ptrStProduto - Ponteiro de um struct do chamador da função e que contém os dados de um produto a ser gravado
//					FILE *fdProduto - File descriptor do arquivo produtos
//					
//		Retorno:	bool - True - gravação foi realizada OK!
//							false - erro no fseek ou de gravação
bool GravarProdutoPosicional(PRODUTO *ptrStProduto, FILE *fdProduto)
{
	if (fseek(fdProduto, (ptrStProduto->nCodigo - 1) * sizeof(PRODUTO), SEEK_SET) != 0)		// erro de SEEK?
		return false;			// avisa o erro
	if (fwrite(ptrStProduto, sizeof(PRODUTO), 1, fdProduto) == 0)		// erro de gravação
		return false;
	return true;		// gravação tudo OK
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
	} // arquivo existe
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
			if (!PedirCodigoProduto(&stProduto.nCodigo, "Cadastrar produto"))	// cancelou?
				break;				// retorna ao menu
			// verificar se o produto já está cadastrado
			if (!LerProdutoPosicional(stProduto.nCodigo, &stProduto, fdProduto))		// erro?
			{	// erro de seek ou leitura
				cout << "Erro de leitura!" << endl;
				PAUSA;
				break;					// volta ao menu
			}
			if (stProduto.cAtivo == 'A')		// produto cadastrado??
			{	// produto já cadastrado
				sprintf_s(cWork, "\nCódigo: %d Descrição: %-40s\nPreço Unitário: %9.2f já está cadastrado!",
					stProduto.nCodigo, stProduto.cDescricao, stProduto.dPrecoUnit);
				cout << cWork << endl;
				PAUSA;
				break;			// volta ao menu
			}
			cin.ignore(1, EOF);				// ignorar tecla enter
			cout << "Descrição: ";
			cin.getline(stProduto.cDescricao, 40, '\n');
			cout << "Preço unitário: ";
			cin >> stProduto.dPrecoUnit;
			stProduto.cAtivo = 'A';			// produto cadastrado.
			// gravar este produto de forma posicional
			if (!GravarProdutoPosicional(&stProduto, fdProduto)) // erro de gravação?
			{	// erro de gravação
				cout << "Erro de gravação!" << endl;
				PAUSA;
			}
			break;
		case EXCLUIR_PRODUTO:
			if (!PedirCodigoProduto(&stProduto.nCodigo, "Excluir produto"))	// cancelou?
				break;				// retorna ao menu
									// verificar se o produto já está cadastrado
			if (!LerProdutoPosicional(stProduto.nCodigo, &stProduto, fdProduto))		// erro?
			{	// erro de seek ou leitura
				cout << "Erro de leitura!" << endl;
				PAUSA;
				break;					// volta ao menu
			}
			if (stProduto.cAtivo != 'A')		// produto não cadastrado??
			{
				cout << "Produto não cadastrado!" << endl;
				PAUSA;
				break;			// volta ao menu
			}
			sprintf_s(cWork, "\nCódigo: %d Descrição: %-40s\nPreço Unitário: %9.2f confirma exclusão (S ou N): ",
				stProduto.nCodigo, stProduto.cDescricao, stProduto.dPrecoUnit);
			cout << cWork << endl;
			cin >> cOpcao;
			if (cOpcao == 's' || cOpcao == 'S')		// excluir realmente?
			{
				stProduto.cAtivo = 'I';		// torna produto excluído
				if (!GravarProdutoPosicional(&stProduto, fdProduto))		// erro de gravação?
				{
					cout << "Erro de gravação!" << endl;
					PAUSA;
				}
			}
			break;			// volta ao menu
		case MOSTRAR_PRODUTO:
			if (!PedirCodigoProduto(&stProduto.nCodigo, "Mostrar produto"))	// cancelou?
				break;				// retorna ao menu
									// verificar se o produto já está cadastrado
			if (!LerProdutoPosicional(stProduto.nCodigo, &stProduto, fdProduto))		// erro?
			{	// erro de seek ou leitura
				cout << "Erro de leitura!" << endl;
				PAUSA;
				break;					// volta ao menu
			}
			if (stProduto.cAtivo != 'A')		// produto não cadastrado??
			{
				cout << "Produto não cadastrado!" << endl;
				PAUSA;
				break;			// volta ao menu
			}
			sprintf_s(cWork, "\nCódigo: %d Descrição: %-40s\nPreço Unitário: %9.2f",
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
			cout << "Opção inválida!\n" << endl;
			PAUSA;
		} // switch
	} // while
} // main