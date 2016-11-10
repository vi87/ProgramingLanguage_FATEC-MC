// Fun��es do programa
#include "PDV.h"
// Fun��o que pede um c�digo de produto ou zero para cancelar
//	Par�metros:
//		Entrada: char *ptrTransacao - ponteiro para um string que 
//									  indica a transa��o sendo executada
//		Retorno: int - 0 - indica que cancelou a transa��o ou
//						um c�digo v�lido de produto
int PedirCodigoProduto(char *ptrTransacao)
{
	int nCodigo;					// para receber o c�digo
	do
	{
		cout << "\n\t" << ptrTransacao << endl
			<< "\tInforme o c�digo do produto entre 1 e "
			<< QTDE_MAXIMA_PRODUTOS << endl
			<< "Ou zero para cancelar a transa��o: ";
		cin >> nCodigo;
		if(nCodigo == 0)			// cancelar?
			return 0;				// indica cancelar
	} while(nCodigo < 1 || nCodigo > QTDE_MAXIMA_PRODUTOS);
	return nCodigo;					// devolve o c�digo do produto
}
// Fun��o que l� um produto sendo dado o seu c�digo
//	Par�metros:
//		Entrada: int nCodigo - c�digo posicional do produto
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
