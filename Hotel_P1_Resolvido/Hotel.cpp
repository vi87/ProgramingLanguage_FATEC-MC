// Hotel.cpp - Programa de Hotel para prova de Linguagem de Programação - 28/09/2016
// FATEC - Mogi das Cruzes
#include "Hotel.h"
//
// Função principal
//
void main(void)
{
	int  i, j, k,							// indices genéricos 
		iIndQuarto,							// para calcular o índice do quarto em função do
											//  andar e o quarto dentro do andar
		nQtdeAndares,						// para receber a quantidade de andares do hotel
		nQtdeQuartosPorAndar,				// para receber a quantidade de quartos por andar
		nQtdeTotalQuartos,					// para receber a quantidade total de quartos do hotel
		nAndarHotel,						// para receber o número do andar
		nQuartoHotel;						// para receber o número do quarto dentro do andar
	char cOpcaoOper,						// local para receber a opção escolhida do menu
		cNomeHospede[41],					// local para receber o nome do hóspede do hotel
		cWork[200],							// para formatação de sprintf
		cNomeAluno[] = "José Carlos Bortot";
	double dTotalDiarias;					// para a somatória de todas as diárias lançadas 
	//
	// vetores do sistema de hotel
	//
	// o vetor abaixo indica quando o quarto dentro de um andar  está livre ou ocupado
	//		true - indica que o quarto está ocupado
	bool vetLivreOcupado[QUANTIDADE_MAXIMA_ANDARES * QUANTIDADE_MAXIMA_QUARTOS];
	// o vetor bi-dimensional abaixo indica o nome do hospede que está ocupando o quarto
	char vetNomeHospede[QUANTIDADE_MAXIMA_ANDARES * QUANTIDADE_MAXIMA_QUARTOS][EXTEN_NOME + 1];
	// o vetor abaixo indica o valor da diária do quarto
	double vetVlrDiaria[QUANTIDADE_MAXIMA_ANDARES * QUANTIDADE_MAXIMA_QUARTOS];
	// o vetor abaixo indica o valor total de diárias do quarto
	double vetTotalDiarias[QUANTIDADE_MAXIMA_ANDARES * QUANTIDADE_MAXIMA_QUARTOS];
	SYSTEMTIME stTime;						// para buscar data e hora

	setlocale(LC_ALL, "portuguese_brazil");
	// comandos para estabelecer o numero de casas decimais
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);						// duas casas decimais
	// <<<<<<0>>>>>>> - Antes de entregar o Pen drive - renomear o diretório principal do projeto que
	// está LP_ProvaN1_28_09_2016_Tarde para LP_ProvaN1_SeuNomeComLetrasMaiúsculasMinúsculas

	// <<<< 01 >>>>
	// Pedir a quantidade de andares e quartos por andares do hotel ou zeros para cancelar a
	//	execução do programa
	// A quantidade de andares não pode ser menor que QTDE_MINIMA_ANDARES e não pode ser maior
	//	que a QUANTIDADE_MAXIMA_ANDARES. Se for informado zeros cancelar a execução do programa
	// A quantidade de quartos por andar não pode ser menor que QTDE_MINIMA_QUARTOS_ANDAR
	//  ou maior que QUANTIDADE_MAXIMA_QUARTOS. Se for informado zeros cancelar a execução do
	//	programa.
	//
	// loop para pedir uma quantidade válida de andares
	do
	{
		cout << "Informe quantidade de andares entre " << QTDE_MINIMA_ANDARES << " e " <<
			QUANTIDADE_MAXIMA_ANDARES << endl <<
			"Ou zero para cancelar a execução do programa: ";
		cin >> nQtdeAndares;
		if(nQtdeAndares == 0)						// cancelar a execução do programa?
			return;									// retorna ao Sistema Operacional
	} while(nQtdeAndares < QTDE_MINIMA_ANDARES ||
		nQtdeAndares > QUANTIDADE_MAXIMA_ANDARES);
	// loop para pedir uma quantidade válida de quartos por andar
	do
	{
		cout << "Informe a quantidade de quartos por andar entre " << QTDE_MINIMA_QUARTOS_ANDAR <<
			" e " << QUANTIDADE_MAXIMA_QUARTOS << endl <<
			"Ou zero para cancelar a execução do programa: ";
		cin >> nQtdeQuartosPorAndar;
		if(nQtdeQuartosPorAndar == 0)				// cancelar?
			return;									// retorna ao S.O.
	} while(nQtdeQuartosPorAndar < QTDE_MINIMA_QUARTOS_ANDAR ||
		nQtdeQuartosPorAndar > QUANTIDADE_MAXIMA_QUARTOS);

	// Inicializar o vetor vetLivreOcupado fazendo com que todos os quartos estejam livres e 
	//		associar a cada quarto o valor correspondente da diária de acordo com o andar do
	//		mesmo de acordo com que foi definido no Hotel.h
	//		Zerar o total de diárias de cada quarto.
	nQtdeTotalQuartos = nQtdeAndares * nQtdeQuartosPorAndar;		// total de quartos
	// loop para inicializar os vetores
	for(i = 1, k = 0; k < nQtdeTotalQuartos; i++ )			// i = andar e k = indice dos quartos
	{
		for(j = 0; j < nQtdeQuartosPorAndar; j++, k++)		// j = 0 quarto por andar
		{
			vetLivreOcupado[k] = false;						// quarto livre
			vetTotalDiarias[k] = 0.0;						// zerar o total de diárias
			switch(i)										// avaliar o andar em que estamos
			{
				case ANDAR_1:
				case ANDAR_2:
					vetVlrDiaria[k] = DIARIA_QUARTO_SIMPLES;
					break;									// sai fora do switch
				case ANDAR_3:
				case ANDAR_4:
					vetVlrDiaria[k] = DIARIA_QUARTO_MEDIO;
					break;									// sai fora do switch
				case ANDAR_5:
				case ANDAR_6:
				case ANDAR_7:
				case ANDAR_8:
					vetVlrDiaria[k] = DIARIA_QUARTO_SUPER;
					break;
				case ANDAR_9:
					vetVlrDiaria[k] = DIARIA_QUARTO_SUITE;
					break;
				default:
					vetVlrDiaria[k] = DIARIA_QUARTO_SUITE;
			} // switch do andar
		} // for j
	} // for k
	while(true)								// loop infinito
	{
		LIMPAR_TELA;
		GetLocalTime(&stTime);
		sprintf_s(cWork, sizeof(cWork), 
			"\n\tFATEC-MC - Sistema de Hotel %02d/%02d/%04d às %02d:%02d:%02d\n\t\tOperador: %s Turma: noite",
			stTime.wDay, stTime.wMonth, stTime.wYear,
			stTime.wHour, stTime.wMinute, stTime.wSecond,
			cNomeAluno);
		cout << cWork << endl;
		// Mostrar o menu de opções para o operador
		cout << FAZER_CHECK_IN << " - Check-in de um hospede" << endl;
		cout << FAZER_CHECK_OUT << " - Check-out de um hospede" << endl;
		cout << LANCAR_DIARIA << " - Lancar diarias em todos os quartos ocupados" << endl;
		cout << LISTAR_UM_QUARTO << " - Listar um quarto" << endl;
		cout << EXIBIR_QUARTOS_LIVRES_ANDAR << " -  Exibir os quartos livres de um andar" << endl;
		cout << SAIR_DO_PROGRAMA << " - Sair do programa" << endl;
		cout << "\tSelecione: ";
		cin	 >> cOpcaoOper;					// opção escolhida pelo operador
		cOpcaoOper = toupper(cOpcaoOper);	// converte para upper case a opção escolhida
		switch(cOpcaoOper)					// avaliar a opção que foi escolhida pelo operador
		{
			case FAZER_CHECK_IN:
				// <<<< 02 >>>>
				// 1 - Chamar a função PedirAndarQuarto passando os endereço de nAndarHotel para receber
				//		o número do andar e o endereço de nQuartoHotel para receber o número do quarto no
				//			andar, quantidade de andares e quartos por andar que foram configurados e
				//			indicar que a transação é "Check-in de hóspede"
				//		Se retornar false cancelar a transação e voltar ao menu
				// 2 - Se retornou true indicando que foram informados andar e quarto no andar válido
				//		calcular o iIndQuarto em função do andar e quarto no andar informados.
				// 3 - Verificar se o quarto já está ocupado e se estiver exibir ao operador que o
				//		quarto está ocupado e o nome do hóspede que está ocupando o quarto, dar uma
				//		pausa para o operador poder ler e voltar ao menu.
				// 4 - Pedir o nome do hóspede considerando que tem nome e sobrenome
				// 5 - Zerar o total de diárias do quarto que está sendo ocupado
				// 6 - Indicar que este quarto está ocupado e voltar ao menu
				if(!PedirAndarQuarto(&nAndarHotel, &nQuartoHotel, nQtdeAndares, nQtdeQuartosPorAndar,
					"Check-in de um hóspede"))				// cancelou a transação?
					break;									// cai fora do switch e volta ao menu
				// calcular o indice deste quarto
				iIndQuarto = ((nAndarHotel - 1) * nQtdeQuartosPorAndar) + (nQuartoHotel - 1);
				// verificar se o quarto está ocupado
				if(vetLivreOcupado[iIndQuarto] == true)		// quarto ocupado?
				{	// quarto está ocupado
					sprintf_s(cWork, sizeof(cWork), 
						"\nAndar:%2d Quarto:%2d Hóspede:%-30s\nQuarto está ocupado!",
						nAndarHotel, nQuartoHotel, vetNomeHospede[iIndQuarto]);
					cout << cWork << endl;
					PAUSA;
					break;									// volta ao menu
				}
				// pedir o nome do hóspede
				cin.ignore(1, EOF);							// ignorar a tecla Enter anterior
				cout << "Nome do hóspede: ";
				cin.getline(vetNomeHospede[iIndQuarto], EXTEN_NOME, '\n'); // aceita nome e sobrenome
				vetLivreOcupado[iIndQuarto] = true;			// ocupa o quarto
				vetTotalDiarias[iIndQuarto] = 0.0;			// zerar as diárias de um hóspede anterior
				sprintf_s(cWork, sizeof(cWork), 
					"\nAndar:%2d Quarto:%2d Hóspede:%-30s\nDiária:%9.2f",
						nAndarHotel, nQuartoHotel, vetNomeHospede[iIndQuarto],
						vetVlrDiaria[iIndQuarto]);
				cout << cWork << endl;
				PAUSA;
				break;						// para sair do switch e voltar ao menu
			case FAZER_CHECK_OUT:
				// <<<< 03 >>>>
				// 1 - Pedir o andar e o quarto da mesma forma que no item anterior indicando que a transação 
				//		é "Check-out"
				// 2 - Verificar se a transação foi cancelada e voltar ao menu
				// 3 - Verificar se o quarto está ocupado e se estiver exibir o nome do hóspede e
				//		o total de diárias do quarto
				// 4 - Pedir a confirmação do operador com um S ou N
				//		Se for indicado 'S' ou 's' desocupar o quarto e qualquer outro caractere 
				//		 voltar ao menu. Para desocupar o quarto basta indicar false no vetLivreOcupado
				// 5 - Se o quarto não estiver ocupado avisar ao operador e voltar ao menu
				break;						// para sair do switch e voltar ao menu
			case LANCAR_DIARIA:
				// <<<< 05 >>>> 
				// 1 - Pedir a data e hora do sistema e apresentar ao operador
				// 2 - Confirmar com o operador se ele realmente deseja lançar as diárias no horário
				//		apresentado
				// 3 - Se o operador confirmar percorrer o vetor de quartos livres e ocupados e 
				//			somar uma diária a mais no total de diárias deste quarto.
				// 4 - Caso o operador não confirme voltar ao menu.
				//		Lançar diária significa pegar o valor da diária que foi associada ao quarto e
				//			somar no total das diárias e do quarto.
				// Para buscar a data e hora do sistema utilizar o seguinte comando:
				//		GetLocalTime(&stTime);
				//		stTime.wDay, stTime.wHour e etc. tem o valores correspondentes a data e hora
				dTotalDiarias = 0.0;			// para acumular o total de diárias lançadas
				GetLocalTime(&stTime);			// data e hora do sistema
				sprintf_s(cWork, sizeof(cWork),
					"\nLançar diária em %02d/%02d/%04d às %02d:%02d Confirma (S ou N): ",
					stTime.wDay, stTime.wMonth, stTime.wYear,
					stTime.wHour, stTime.wMinute);
				cout << cWork;
				cin >> cOpcaoOper;			// confirmação ou não do operador
				if(cOpcaoOper == 's' || cOpcaoOper ==  'S')		// confirmou?
				{	// vai lançar diárias em todos os quarto ocupados
					for(i = 0; i < nQtdeTotalQuartos; i++)	// loop de todos os quartos do hotel
					{
						if(vetLivreOcupado[i])				// quarto ocupado?
						{	// quarto está ocupado
							vetTotalDiarias[i] += vetVlrDiaria[i]; // mais uma diária no quarto
							dTotalDiarias += vetVlrDiaria[i];	   // acumula na somatória
						}
					} // for i
				}
				else break;					// volta ao menu se o operador não disse sim
				sprintf_s(cWork, sizeof(cWork),
					"\n\t\tTotal de diárias lançado:%10.2f", dTotalDiarias);
				cout << cWork << endl;
				PAUSA;
				break;						// para sair do switch e voltar ao menu
			case LISTAR_UM_QUARTO:
				// <<<< 06 >>>> 
				// 1 - Pedir Andar e Quarto conforme itens anteriores
				// 2 - Verificar se o quarto está ocupado e se não estiver, avisar ao operador e voltar ao menu
				// 3 - Se estiver ocupado listar os dados do quarto indicando nome do hóspede e valor da
				//		diária do quarto e o total de diárias utilizando o sprintf_s
				//		Formato: Andar Quarto Hóspede            Vlr.Diária Tot.Diárias
				//				  A      Q    XXXXXXXXXXXXXXXXX  DDDDD.DD   TTTTTT.TT
				//
				break;						// para sair do switch e voltar ao menu
			case EXIBIR_QUARTOS_LIVRES_ANDAR:
				// pedir um andar válido
				// loop para listar os quarto que estão livres
				break;
			case SAIR_DO_PROGRAMA:
				cout << "\nDeseja sair realmente? (S ou N): ";
				cin >> cOpcaoOper;
				if(cOpcaoOper == 'S' || cOpcaoOper == 's')		// sair realmente?
					return;
				break;						// para sair do switch e decidir se vai sair realmente
			default:
				// Avisar que foi escolhida uma opção errada
				cout << "\nOpcao inválida!" << endl;
				PAUSA;
		} // switch
	} // while(true)
} // main
