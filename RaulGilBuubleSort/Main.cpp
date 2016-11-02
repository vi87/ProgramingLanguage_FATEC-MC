//Programa de calouros Raul Gil
// FATEC - MC - JCB - 31/08/16 - VERSÃO 0.0
#include "Meu.h"
//
// Entry point do programa
//
void main(void)
{
	int i,											//índice e contador genérico
		nNotaTrono = -1,									// Nota do melhor calouro até o momento
		nQtdeCalouros = 0,								// quantidade de calouros que irá cantar hoje
		vetNotas[QTDE_MAX_CALOUROS];					// Vetor de notas dos calouros
	char vetNomes[QTDE_MAX_CALOUROS][EXTENSAO_NOME + 1],
		vetSexo[QTDE_MAX_CALOUROS],						// Vetor de sexo dos calouros
		szNomeTrono[EXTENSAO_NOME + 1],					// Guarda o nome do melhor calouro até o momento
		cSexoTrono;										// Guarda o sexo do melhor calouro até o momento
	setlocale(LC_ALL, "portuguese_brazil");				// aceita tabela ASCII do Brasil
														// perguntar ao Raul Gil quantos calouros irão cantar hoje
														// dentro de limites válidos
	do
	{
		cout << "Informe a quantidade de calouros entre " << QTDE_MIN_CALOUROS
			<< " e " << QTDE_MAX_CALOUROS << endl
			<< " ou zero para cancelar a execução do programa";
		cin >> nQtdeCalouros;
		if (nQtdeCalouros == 0)			// cancelar?
			return;						// volta ao Sistema Operacional
	} while (nQtdeCalouros < QTDE_MIN_CALOUROS || nQtdeCalouros > QTDE_MAX_CALOUROS);			// Loop enquanto quantidade fora dos limites
																								// Temos uma quantidade válida
																								// loop para tratar a quantidade armazenada em nQtdeCalouros
	for (i = 0; i < nQtdeCalouros; i++)
	{
		cin.ignore(1, EOF);
		cout << "Nome do calouro de ordem " << i + 1 << " de " << nQtdeCalouros << ": ";
		cin.getline(vetNomes[i], EXTENSAO_NOME, '\n');
		// pedir o sexo
		do
		{
			cout << "Sexo do calouro " << vetNomes[i] << " (" << MASCULINO
				<< "-Masculino ou " << FEMININO << "-Feminino): ";
			cin >> vetSexo[i];
			vetSexo[i] = toupper(vetSexo[i]);							// converte para maíscula
		} while (vetSexo[i] != MASCULINO && vetSexo[i] != FEMININO);
		// pedir uma nota válida
		do
		{
			cout << "Nota entre 0 e 10: ";
			cin >> vetNotas[i];
		} while (vetNotas[i] < 0 || vetNotas[i] > 10);
		// averiguar se o calouro irá para o trono
		if (vetNotas[i] > nNotaTrono)								// vai ou não vai para o trono?
		{// o calouro vai para o trono
			nNotaTrono = vetNotas[i];								// melhor nota até o momento
			strcpy_s(szNomeTrono, EXTENSAO_NOME + 1, vetNomes[i]);	// nome do melhor até o momento
			cSexoTrono = vetSexo[i];								// sexo do melhor calouro até o momento
		}

	}
	// todos os calouros já cantaram
	cout << "Vencedor: " << szNomeTrono << " Sexo: " << cSexoTrono << " Nota: " << nNotaTrono << endl;
	PAUSA;
	// Listar calouros por ondem de nota
	BubbleSort(vetNomes, vetSexo, vetNotas, nQtdeCalouros);
	ListarCalouros(vetNomes, vetSexo, vetNotas, nQtdeCalouros);
	PAUSA;
	//Listar calouros por ordem alfabética
	BubbleAlfa(vetNomes, vetSexo, vetNotas, nQtdeCalouros);
	ListarCalouros(vetNomes, vetSexo, vetNotas, nQtdeCalouros);
}//main