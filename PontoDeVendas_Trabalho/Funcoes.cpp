// Funções do programa
#include "PDV.h"
// Função que pede um código de produto ou zero para cancelar
//	Parâmetros:
//		Entrada: char *ptrTransacao - ponteiro para um string que 
//									  indica a transação sendo executada
//		Retorno: int - 0 - indica que cancelou a transação ou
//						um código válido de produto
int PedirCodigoProduto(char *ptrTransacao)
{
	int nCodigo;					// para receber o código
	do
	{
		cout << "\n\t" << ptrTransacao << endl
			<< "\tInforme o código do produto entre 1 e "
			<< QTDE_MAXIMA_PRODUTOS << endl
			<< "Ou zero para cancelar a transação: ";
		cin >> nCodigo;
		if(nCodigo == 0)			// cancelar?
			return 0;				// indica cancelar
	} while(nCodigo < 1 || nCodigo > QTDE_MAXIMA_PRODUTOS);
	return nCodigo;					// devolve o código do produto
}
// Função que lê um produto sendo dado o seu código
//	Parâmetros:
//		Entrada: int nCodigo - código posicional do produto
//				 FILE *ptrFdProduto - ponteiro do ponteiro do file descriptor
//				 PRODUTO *ptrStProduto - ponteiro de uma struct para
//										receber os dados do produto
//		Retorno: bool - true - o produto foi lido OK
//						false - erro de leitura ou de fseek
bool LerUmProduto(int nCodigo, FILE *ptrFdProduto, PRODUTO *ptrStProduto)
{
	if(fseek(ptrFdProduto, (nCodigo - 1) * TAM_PROD, SEEK_SET) != 0)
	{	// erro de seek
		return false;				// avisa o erro
	}
	if(fread_s(ptrStProduto, TAM_PROD, TAM_PROD, 1, ptrFdProduto) == 0)
	{	// erro de leitura
		return false;				// avisa o erro
	}
	return true;					// indica tudo OK
}
