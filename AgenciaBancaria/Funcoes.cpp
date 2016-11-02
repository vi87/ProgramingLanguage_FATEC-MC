// Fun��es do programa de Agencia Banc�ria
#include "Agencia.h"
// Fun��o que pede o c�digo de um cliente v�lido
//	ou zero para cancelar a transa��o
//	Par�metros:
//		Entrada: char *ptrAcao - ponteiro para um string que contem a a��o
//								que est� sendo executada
//		Retorno: int - c�digo de cliente v�lido ou zero para cancelar a a��o
int PedirCodigoCliente(char *ptrAcao)
{
	int nCodigo;					// para receber o c�digo
	cout << "\n\t" << ptrAcao << endl;
	do
	{
		cout << "C�digo do cliente entre 1 e " << QTDE_CLIENTES << endl
			<< "Ou zero para cancelar a transa��o: ";
		cin >> nCodigo;				// recebe o c�digo
		if(nCodigo == 0)			// cancelar a transa��o?
			return 0;				// indica que cancelou a transa��o
	} while(nCodigo < 1 || nCodigo > QTDE_CLIENTES);
	return nCodigo;					// devolve o c�digo v�lido
}
// Fun��o que l� um cliente de forma posicional (acesso direto)
// Par�metros:
//	Entrada: int nCodigo - c�digo do cliente desejado
//			 CLIENTE *ptrCliente - ponteiro de uma struct para receber os
//									dados do cliente
//			 FILE *fdArquivo - ponteiro do file descriptor do cadastro
//	Retorno: bool - true - leitura foi Ok
//					false - erro de seek ou de leitura
bool LerClientePosicional(int nCodigo, CLIENTE *ptrCliente, FILE *fdArquivo)
{
	if(fseek(fdArquivo, (nCodigo - 1) * sizeof(CLIENTE), SEEK_SET) != 0) // erro?
	{
		return false;					// indica que houve erro
	}
	if(fread_s(ptrCliente, sizeof(CLIENTE), sizeof(CLIENTE),
		1, fdArquivo) == 0)				// erro de leitura?
		return false;					// indica erro
	return true;						// indica tudo OK
}
// Fun��o que grava um cliente posicional (acesso direto)
//	Entrada: int nCodigo - c�digo do cliente a ser gravado
//			 CLIENTE *ptrCliente - ponteiro de uma struct que contem os 
//									dados do cliente
//			 FILE *fdArquivo - ponteiro do file descriptor do cadastro
//	Retorno: bool - true - grava��o foi Ok
//					false - erro de seek ou de grava��o
bool GravarClientePosicional(int nCodigo, CLIENTE *ptrCliente, FILE *fdArquivo)
{
	if(fseek(fdArquivo, (nCodigo - 1) * sizeof(CLIENTE), SEEK_SET) != 0) // erro?
		return false;					// indica que houve erro
	if(fwrite(ptrCliente, sizeof(CLIENTE), 1, fdArquivo) == 0) // erro grava��o?
		return false;					// indica o erro
	return true;						// indica que grava��o foi OK
}
