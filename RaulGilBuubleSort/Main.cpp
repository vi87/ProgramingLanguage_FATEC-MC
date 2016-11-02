//Programa de calouros Raul Gil
// FATEC - MC - JCB - 31/08/16 - VERS�O 0.0
#include "Meu.h"
//
// Entry point do programa
//
void main(void)
{
	int i,											//�ndice e contador gen�rico
		nNotaTrono = -1,									// Nota do melhor calouro at� o momento
		nQtdeCalouros = 0,								// quantidade de calouros que ir� cantar hoje
		vetNotas[QTDE_MAX_CALOUROS];					// Vetor de notas dos calouros
	char vetNomes[QTDE_MAX_CALOUROS][EXTENSAO_NOME + 1],
		vetSexo[QTDE_MAX_CALOUROS],						// Vetor de sexo dos calouros
		szNomeTrono[EXTENSAO_NOME + 1],					// Guarda o nome do melhor calouro at� o momento
		cSexoTrono;										// Guarda o sexo do melhor calouro at� o momento
	setlocale(LC_ALL, "portuguese_brazil");				// aceita tabela ASCII do Brasil
														// perguntar ao Raul Gil quantos calouros ir�o cantar hoje
														// dentro de limites v�lidos
	do
	{
		cout << "Informe a quantidade de calouros entre " << QTDE_MIN_CALOUROS
			<< " e " << QTDE_MAX_CALOUROS << endl
			<< " ou zero para cancelar a execu��o do programa";
		cin >> nQtdeCalouros;
		if (nQtdeCalouros == 0)			// cancelar?
			return;						// volta ao Sistema Operacional
	} while (nQtdeCalouros < QTDE_MIN_CALOUROS || nQtdeCalouros > QTDE_MAX_CALOUROS);			// Loop enquanto quantidade fora dos limites
																								// Temos uma quantidade v�lida
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
			vetSexo[i] = toupper(vetSexo[i]);							// converte para ma�scula
		} while (vetSexo[i] != MASCULINO && vetSexo[i] != FEMININO);
		// pedir uma nota v�lida
		do
		{
			cout << "Nota entre 0 e 10: ";
			cin >> vetNotas[i];
		} while (vetNotas[i] < 0 || vetNotas[i] > 10);
		// averiguar se o calouro ir� para o trono
		if (vetNotas[i] > nNotaTrono)								// vai ou n�o vai para o trono?
		{// o calouro vai para o trono
			nNotaTrono = vetNotas[i];								// melhor nota at� o momento
			strcpy_s(szNomeTrono, EXTENSAO_NOME + 1, vetNomes[i]);	// nome do melhor at� o momento
			cSexoTrono = vetSexo[i];								// sexo do melhor calouro at� o momento
		}

	}
	// todos os calouros j� cantaram
	cout << "Vencedor: " << szNomeTrono << " Sexo: " << cSexoTrono << " Nota: " << nNotaTrono << endl;
	PAUSA;
	// Listar calouros por ondem de nota
	BubbleSort(vetNomes, vetSexo, vetNotas, nQtdeCalouros);
	ListarCalouros(vetNomes, vetSexo, vetNotas, nQtdeCalouros);
	PAUSA;
	//Listar calouros por ordem alfab�tica
	BubbleAlfa(vetNomes, vetSexo, vetNotas, nQtdeCalouros);
	ListarCalouros(vetNomes, vetSexo, vetNotas, nQtdeCalouros);
}//main