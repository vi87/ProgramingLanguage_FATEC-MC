// Funções do programa Raul Gil
#include "Meu.h"
// Função que lista o vetor de calouros
// Parâmetros
// Entrada: char vetCalouros[][EXTENSAO_NOME + 1] - endereço do primeiro calouro do vetor
//			char vetSexos[] - endereço do sexo do primeiro calouro do vetor
//			int vetNotas - endereço da nota do primeiro calouro do vetor
//			int nQtdeCalouros - quantidade de calouros que cantou hoje
void ListarCalouros(char vetCalouros[][EXTENSAO_NOME + 1], char vetSexos[], int vetNotas[], int nQtdeCalouros)
{
	int i;
	char cWork[150];
	LIMPAR_TELA;
	sprintf_s(cWork, // destino do string
		sizeof(cWork), // tamanho do vetor do char de trabalho
		"Nome                                Sexo Nota"); // máscara de edição não puxando nada
	cout << cWork << endl;
	for (i = 0; i < nQtdeCalouros; i++) // loop pra exibir tabela
	{
		sprintf_s(cWork, sizeof(cWork), // destino do string que será formatado
			"%-40s %c   %2d", // máscara de edição
							  // %-30 atrai um string de 30 bytes alinhado pela esquerda e preenchido com brancos à direita
							  // %c atrai un char
							  // %2d atrai uma inteira e se tiver apenas um digito, preenche com um branco a esquerda

			vetCalouros[i],			// será atraído para %-40 nesta ordem	
			vetSexos[i],			// será atraído %c
			vetNotas[i]);			// será atraído para %2d
									// Se fosse um double ou float na mascara colocar %10.2f
									// significa 10 dígitos inclusive com o ponto decimal
		cout << cWork << endl;
	};
	PAUSA;
};
void BubbleSort(char vetCalouros[][EXTENSAO_NOME + 1], char vetSexos[], int vetNotas[], int nQtde)
{
	int i,
		auxNotas;														// auxiliar que receberá a nota maior entre 2
	char auxSexo,														// auxiliar que receberá o sexo referente a nota maior comparada
		 auxNome[QTDE_MAX_CALOUROS][EXTENSAO_NOME + 1];					// auxiliar que receberá o nome referente a nota maior comparada
	bool flgHouveTroca;
	do
	{
		flgHouveTroca = false;											// começa com falso para não repetir sem necessidade
		for (i = 0; i < nQtde - 1; i++)									// loop que verifica todas as posições do vetor
		{
			if (vetNotas[i] > vetNotas[i + 1])							// verifica se i > i+1 e se for, começa a ordenação
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
		auxNotas;														// auxiliar que receberá a nota maior entre 2
	char auxSexo,														// auxiliar que receberá o sexo referente a nota maior comparada
		auxNome[QTDE_MAX_CALOUROS][EXTENSAO_NOME + 1];					// auxiliar que receberá o nome referente a nota maior comparada
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