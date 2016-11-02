// Fun��es do programa Raul Gil
#include "Meu.h"
// Fun��o que lista o vetor de calouros
// Par�metros
// Entrada: char vetCalouros[][EXTENSAO_NOME + 1] - endere�o do primeiro calouro do vetor
//			char vetSexos[] - endere�o do sexo do primeiro calouro do vetor
//			int vetNotas - endere�o da nota do primeiro calouro do vetor
//			int nQtdeCalouros - quantidade de calouros que cantou hoje
void ListarCalouros(char vetCalouros[][EXTENSAO_NOME + 1], char vetSexos[], int vetNotas[], int nQtdeCalouros)
{
	int i;
	char cWork[150];
	LIMPAR_TELA;
	sprintf_s(cWork, // destino do string
		sizeof(cWork), // tamanho do vetor do char de trabalho
		"Nome                                Sexo Nota"); // m�scara de edi��o n�o puxando nada
	cout << cWork << endl;
	for (i = 0; i < nQtdeCalouros; i++) // loop pra exibir tabela
	{
		sprintf_s(cWork, sizeof(cWork), // destino do string que ser� formatado
			"%-40s %c   %2d", // m�scara de edi��o
							  // %-30 atrai um string de 30 bytes alinhado pela esquerda e preenchido com brancos � direita
							  // %c atrai un char
							  // %2d atrai uma inteira e se tiver apenas um digito, preenche com um branco a esquerda

			vetCalouros[i],			// ser� atra�do para %-40 nesta ordem	
			vetSexos[i],			// ser� atra�do %c
			vetNotas[i]);			// ser� atra�do para %2d
									// Se fosse um double ou float na mascara colocar %10.2f
									// significa 10 d�gitos inclusive com o ponto decimal
		cout << cWork << endl;
	};
	PAUSA;
};
void BubbleSort(char vetCalouros[][EXTENSAO_NOME + 1], char vetSexos[], int vetNotas[], int nQtde)
{
	int i,
		auxNotas;														// auxiliar que receber� a nota maior entre 2
	char auxSexo,														// auxiliar que receber� o sexo referente a nota maior comparada
		 auxNome[QTDE_MAX_CALOUROS][EXTENSAO_NOME + 1];					// auxiliar que receber� o nome referente a nota maior comparada
	bool flgHouveTroca;
	do
	{
		flgHouveTroca = false;											// come�a com falso para n�o repetir sem necessidade
		for (i = 0; i < nQtde - 1; i++)									// loop que verifica todas as posi��es do vetor
		{
			if (vetNotas[i] > vetNotas[i + 1])							// verifica se i > i+1 e se for, come�a a ordena��o
			{
				//Troca das notas
				auxNotas = vetNotas[i];									// auxiliar recebe a nota maior
				vetNotas[i] = vetNotas[i + 1];							// vetor [i] recebe o valor do vetor [i+1]
				vetNotas[i + 1] = auxNotas;								// vetor[i+1] recebe o antigo valor de [i] que estava na auxiliar
				// Troca das strings
				strcpy_s(auxNome[i], EXTENSAO_NOME + 1, vetCalouros[i]);			// auxiliar recebe o nome correspondente a nota trocada
				strcpy_s(vetCalouros[i], EXTENSAO_NOME + 1, vetCalouros[i+1]);		 // vetor [i] recebe o valor do vetor [i+1]
				strcpy_s(vetCalouros[i + 1], EXTENSAO_NOME + 1, auxNome[i]);		// vetor[i+1] recebe o antigo valor de [i] que estava na auxiliar
				// troca dos sexos
				auxSexo = vetSexos[i];
				vetSexos[i] = vetSexos[i + 1];
				vetSexos[i + 1] = auxSexo;
				flgHouveTroca = true;
			}
		}
	} while (flgHouveTroca == true);
};

void BubbleAlfa(char vetCalouros[][EXTENSAO_NOME + 1], char vetSexos[], int vetNotas[], int nQtde)
{
	int i,
		auxNotas;														// auxiliar que receber� a nota maior entre 2
	char auxSexo,														// auxiliar que receber� o sexo referente a nota maior comparada
		auxNome[QTDE_MAX_CALOUROS][EXTENSAO_NOME + 1];					// auxiliar que receber� o nome referente a nota maior comparada
	bool flgHouveTroca;

	do
	{
		flgHouveTroca = false;
		for (i = 0; i < nQtde-1; i++)
		{
			if (strcmp(vetCalouros[i], vetCalouros[i + 1]) > 0)
			{
				//Troca das notas
				auxNotas = vetNotas[i];									// auxiliar recebe a nota maior
				vetNotas[i] = vetNotas[i + 1];							// vetor [i] recebe o valor do vetor [i+1]
				vetNotas[i + 1] = auxNotas;								// vetor[i+1] recebe o antigo valor de [i] que estava na auxiliar
				// Troca das strings
				strcpy_s(auxNome[i], EXTENSAO_NOME + 1, vetCalouros[i]);			// auxiliar recebe o nome correspondente a nota trocada
				strcpy_s(vetCalouros[i], EXTENSAO_NOME + 1, vetCalouros[i + 1]);		 // vetor [i] recebe o valor do vetor [i+1]
				strcpy_s(vetCalouros[i + 1], EXTENSAO_NOME + 1, auxNome[i]);		// vetor[i+1] recebe o antigo valor de [i] que estava na auxiliar
				// troca dos sexos
				auxSexo = vetSexos[i];
				vetSexos[i] = vetSexos[i + 1];
				vetSexos[i + 1] = auxSexo;
				flgHouveTroca = true;
			}
		}
	} while (flgHouveTroca);
};