// Programa de teste de disco
// FATEC-MC - JCB - 26/10/2016 - Versão 0.0
#include "Texto.h"
//
// Entry point do programa
//
void main(void)
{
	int i;							// indice genérico
	char cLinha[200], 				// para cada linha digitada
		cBuffer;					// Buffer de leitura de apenas um byte
	FILE *fdTexto;					// file descriptor do arquivo texto
	setlocale(LC_ALL, "portuguese_brazil");		// acentuação brasileira
	// abrir o arquivo em modo gravação e destrutivo
	if (fopen_s(&fdTexto, CAMINHO_ARQUIVO, "w") != 0)	// erro irrecuperável?
	{
		cout << "Erro irrecuperável na abertura do arquivo: " << CAMINHO_ARQUIVO << endl;
		PAUSA;
		return;				// volta ao sistema operacional
	}
	// loop infinito de gravação
	while (true)
	{
		cout << "Digite um texto e tecle Enter ou ###### para encerrar a gravação" << endl;
		cin.getline(cLinha, sizeof(cLinha), '\n');
		if (strcmp(cLinha, "######") == 0)		// fim de gravação?
		{
			fclose(fdTexto);				// fecha arquivo
			break;							// cai fora do while
			//return;							// volta ao S.O.
		}
		strcat_s(cLinha, sizeof(cLinha), "\n");				// de string vira uma linha
		if (fwrite(cLinha, strlen(cLinha), 1, fdTexto) == 0)			// Erro de gravação?
		{ // Erro irrecuperável de gravação
			fclose(fdTexto);		// fecha arquivo
			cout << "Erro de gravação." << endl;
			PAUSA;
			return;			// volta ao S.O.
		}
	} // While
	// abrir o arquivo em modo leiura e vamos listar as linhas digitadas na gravação
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

