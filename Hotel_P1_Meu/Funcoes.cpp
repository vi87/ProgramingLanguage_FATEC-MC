// Funções do programa de Hotel
#include "Hotel.h"
//---[PedirAndarQuarto]--------------------------------------------------------------------
// Função para pedir o andar e o número do quarto no andar
//		
//	Parâmetros:
//		Entrada: 
//			int *ptrAndar - ponteiro para receber o número do andar de 1 a nQtAndares ou
//							zero para cancelar a transação
//			int *ptrQuarto - ponteiro para receber o número do quarto por andar de 1 a
//							  nQtQuartos ou zero para cancelar a transação
//			int nQtAndares - quantidade de andares que foi configurada no início do programa
//			int nQtQuartos - idem quantidade de quartos por andar
//			char *ptrTransacao - ponteiro da transação que está sendo realizada
//		Retorno: bool = true - indica que o andar e quarto foram informados
//				 bool = false - indica que a transação foi cancelada porque foi informado
//								andar zero ou quarto zero
bool	PedirAndarQuarto(int *ptrAndar, int *ptrQuarto, int nQtAndares, int nQtQuartos, char *ptrTransacao)
{
	// <<<< 08 >>>>
	// 1 - Ficar em loop pedindo o número do andar ou zero para cancelar a transação.
	//		O número do andar tem que ser de 1 a nQtAndares
	// 2 - Ficar em loop pedindo o número do quarto ou zeros para cancelar a transação
	//		O número do quarto tem que ser de 1 a nQtQuartos

	cout << "\n\t" << ptrTransacao << endl;
	// loop para pedir um anadar válido
	do
	{
		cout << "\nAndar entre 1 e " << nQtAndares << endl <<
			"Ou 0 para cancelar a transação: ";
		cin >> *ptrAndar;
		if(*ptrAndar == 0 )										// cancelar a transação?
			return false;										// avisa que cancelou a transação.

	}while(*ptrAndar < 1 || *ptrAndar > nQtAndares);
	// loop para pedir um quarto válido
	do
	{
		cout << "\nQuarto entre 1 e " << nQtQuartos << endl <<
			"Ou 0 para cancelar a transação: ";
		cin >> *ptrQuarto;
		if(*ptrQuarto == 0 )										// cancelar a transação?
			return false;										// avisa que cancelou a transação.

	}while(*ptrQuarto < 1 || *ptrQuarto > nQtQuartos);
	return true;									// Indica que foi informado um andar e quarto
} 
