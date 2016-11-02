// Programa de teste de disco
// FATEC-MC - JCB - 26/10/2016 - Vers�o 0.0
#include "Texto.h"
//
// Entry point do programa
//
void main(void)
{
	int i;							// indice gen�rico
	char cLinha[200], 				// para cada linha digitada
		cBuffer;					// Buffer de leitura de apenas um byte
	FILE *fdTexto;					// file descriptor do arquivo texto
	setlocale(LC_ALL, "portuguese_brazil");		// acentua��o brasileira
	// abrir o arquivo em modo grava��o e destrutivo
	if (fopen_s(&fdTexto, CAMINHO_ARQUIVO, "w") != 0)	// erro irrecuper�vel?
	{
		cout << "Erro irrecuper�vel na abertura do arquivo: " << CAMINHO_ARQUIVO << endl;
		PAUSA;
		return;				// volta ao sistema operacional
	}
	// loop infinito de grava��o
	while (true)
	{
		cout << "Digite um texto e tecle Enter ou ###### para encerrar a grava��o" << endl;
		cin.getline(cLinha, sizeof(cLinha), '\n');
		if (strcmp(cLinha, "######") == 0)		// fim de grava��o?
		{
			fclose(fdTexto);				// fecha arquivo
			break;							// cai fora do while
			//return;							// volta ao S.O.
		}
		strcat_s(cLinha, sizeof(cLinha), "\n");				// de string vira uma linha
		if (fwrite(cLinha, strlen(cLinha), 1, fdTexto) == 0)			// Erro de grava��o?
		{ // Erro irrecuper�vel de grava��o
			fclose(fdTexto);		// fecha arquivo
			cout << "Erro de grava��o." << endl;
			PAUSA;
			return;			// volta ao S.O.
		}
	} // While
	// abrir o arquivo em modo leiura e vamos listar as linhas digitadas na grava��o
	if (fopen_s(&fdTexto, CAMINHO_ARQUIVO, "r") != 0)		// erro de abertura?
	{ // erro de abertura
		cout << "Erro de abertura!" << endl;
		PAUSA;
		return;			// volta ao S.O.
	}
	i = 0;
	while (true)				// loop infinito de listagem de arqivo
	{
		if (fread_s(&cBuffer, sizeof(cBuffer), 1, 1, fdTexto) == 0)		// fim de arquivo?
		{
			fclose(fdTexto);
			cout << "\nFim da listagem!" << endl;
			PAUSA;
			return;			// retorna ao S.O.
		}
		cLinha[i++] = cBuffer;			// copia o Buffer em cLinha
		if (cBuffer == '\n')			// complpetou uma linha?
		{
			cLinha[i] = NULL;			// torna uma linha um string
			cout << cLinha;
			i = 0;
		}
	} // While
} // main

