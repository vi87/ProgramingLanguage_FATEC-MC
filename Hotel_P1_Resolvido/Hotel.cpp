// Hotel.cpp - Programa de Hotel para prova de Linguagem de Programa��o - 28/09/2016
// FATEC - Mogi das Cruzes
#include "Hotel.h"
//
// Fun��o principal
//
void main(void)
{
	int  i, j, k,							// indices gen�ricos 
		iIndQuarto,							// para calcular o �ndice do quarto em fun��o do
											//  andar e o quarto dentro do andar
		nQtdeAndares,						// para receber a quantidade de andares do hotel
		nQtdeQuartosPorAndar,				// para receber a quantidade de quartos por andar
		nQtdeTotalQuartos,					// para receber a quantidade total de quartos do hotel
		nAndarHotel,						// para receber o n�mero do andar
		nQuartoHotel;						// para receber o n�mero do quarto dentro do andar
	char cOpcaoOper,						// local para receber a op��o escolhida do menu
		cNomeHospede[41],					// local para receber o nome do h�spede do hotel
		cWork[200],							// para formata��o de sprintf
		cNomeAluno[] = "Jos� Carlos Bortot";
	double dTotalDiarias;					// para a somat�ria de todas as di�rias lan�adas 
	//
	// vetores do sistema de hotel
	//
	// o vetor abaixo indica quando o quarto dentro de um andar  est� livre ou ocupado
	//		true - indica que o quarto est� ocupado
	bool vetLivreOcupado[QUANTIDADE_MAXIMA_ANDARES * QUANTIDADE_MAXIMA_QUARTOS];
	// o vetor bi-dimensional abaixo indica o nome do hospede que est� ocupando o quarto
	char vetNomeHospede[QUANTIDADE_MAXIMA_ANDARES * QUANTIDADE_MAXIMA_QUARTOS][EXTEN_NOME + 1];
	// o vetor abaixo indica o valor da di�ria do quarto
	double vetVlrDiaria[QUANTIDADE_MAXIMA_ANDARES * QUANTIDADE_MAXIMA_QUARTOS];
	// o vetor abaixo indica o valor total de di�rias do quarto
	double vetTotalDiarias[QUANTIDADE_MAXIMA_ANDARES * QUANTIDADE_MAXIMA_QUARTOS];
	SYSTEMTIME stTime;						// para buscar data e hora

	setlocale(LC_ALL, "portuguese_brazil");
	// comandos para estabelecer o numero de casas decimais
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);						// duas casas decimais
	// <<<<<<0>>>>>>> - Antes de entregar o Pen drive - renomear o diret�rio principal do projeto que
	// est� LP_ProvaN1_28_09_2016_Tarde para LP_ProvaN1_SeuNomeComLetrasMai�sculasMin�sculas

	// <<<< 01 >>>>
	// Pedir a quantidade de andares e quartos por andares do hotel ou zeros para cancelar a
	//	execu��o do programa
	// A quantidade de andares n�o pode ser menor que QTDE_MINIMA_ANDARES e n�o pode ser maior
	//	que a QUANTIDADE_MAXIMA_ANDARES. Se for informado zeros cancelar a execu��o do programa
	// A quantidade de quartos por andar n�o pode ser menor que QTDE_MINIMA_QUARTOS_ANDAR
	//  ou maior que QUANTIDADE_MAXIMA_QUARTOS. Se for informado zeros cancelar a execu��o do
	//	programa.
	//
	// loop para pedir uma quantidade v�lida de andares
	do
	{
		cout << "Informe quantidade de andares entre " << QTDE_MINIMA_ANDARES << " e " <<
			QUANTIDADE_MAXIMA_ANDARES << endl <<
			"Ou zero para cancelar a execu��o do programa: ";
		cin >> nQtdeAndares;
		if(nQtdeAndares == 0)						// cancelar a execu��o do programa?
			return;									// retorna ao Sistema Operacional
	} while(nQtdeAndares < QTDE_MINIMA_ANDARES ||
		nQtdeAndares > QUANTIDADE_MAXIMA_ANDARES);
	// loop para pedir uma quantidade v�lida de quartos por andar
	do
	{
		cout << "Informe a quantidade de quartos por andar entre " << QTDE_MINIMA_QUARTOS_ANDAR <<
			" e " << QUANTIDADE_MAXIMA_QUARTOS << endl <<
			"Ou zero para cancelar a execu��o do programa: ";
		cin >> nQtdeQuartosPorAndar;
		if(nQtdeQuartosPorAndar == 0)				// cancelar?
			return;									// retorna ao S.O.
	} while(nQtdeQuartosPorAndar < QTDE_MINIMA_QUARTOS_ANDAR ||
		nQtdeQuartosPorAndar > QUANTIDADE_MAXIMA_QUARTOS);

	// Inicializar o vetor vetLivreOcupado fazendo com que todos os quartos estejam livres e 
	//		associar a cada quarto o valor correspondente da di�ria de acordo com o andar do
	//		mesmo de acordo com que foi definido no Hotel.h
	//		Zerar o total de di�rias de cada quarto.
	nQtdeTotalQuartos = nQtdeAndares * nQtdeQuartosPorAndar;		// total de quartos
	// loop para inicializar os vetores
	for(i = 1, k = 0; k < nQtdeTotalQuartos; i++ )			// i = andar e k = indice dos quartos
	{
		for(j = 0; j < nQtdeQuartosPorAndar; j++, k++)		// j = 0 quarto por andar
		{
			vetLivreOcupado[k] = false;						// quarto livre
			vetTotalDiarias[k] = 0.0;						// zerar o total de di�rias
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
			"\n\tFATEC-MC - Sistema de Hotel %02d/%02d/%04d �s %02d:%02d:%02d\n\t\tOperador: %s Turma: noite",
			stTime.wDay, stTime.wMonth, stTime.wYear,
			stTime.wHour, stTime.wMinute, stTime.wSecond,
			cNomeAluno);
		cout << cWork << endl;
		// Mostrar o menu de op��es para o operador
		cout << FAZER_CHECK_IN << " - Check-in de um hospede" << endl;
		cout << FAZER_CHECK_OUT << " - Check-out de um hospede" << endl;
		cout << LANCAR_DIARIA << " - Lancar diarias em todos os quartos ocupados" << endl;
		cout << LISTAR_UM_QUARTO << " - Listar um quarto" << endl;
		cout << EXIBIR_QUARTOS_LIVRES_ANDAR << " -  Exibir os quartos livres de um andar" << endl;
		cout << SAIR_DO_PROGRAMA << " - Sair do programa" << endl;
		cout << "\tSelecione: ";
		cin	 >> cOpcaoOper;					// op��o escolhida pelo operador
		cOpcaoOper = toupper(cOpcaoOper);	// converte para upper case a op��o escolhida
		switch(cOpcaoOper)					// avaliar a op��o que foi escolhida pelo operador
		{
			case FAZER_CHECK_IN:
				// <<<< 02 >>>>
				// 1 - Chamar a fun��o PedirAndarQuarto passando os endere�o de nAndarHotel para receber
				//		o n�mero do andar e o endere�o de nQuartoHotel para receber o n�mero do quarto no
				//			andar, quantidade de andares e quartos por andar que foram configurados e
				//			indicar que a transa��o � "Check-in de h�spede"
				//		Se retornar false cancelar a transa��o e voltar ao menu
				// 2 - Se retornou true indicando que foram informados andar e quarto no andar v�lido
				//		calcular o iIndQuarto em fun��o do andar e quarto no andar informados.
				// 3 - Verificar se o quarto j� est� ocupado e se estiver exibir ao operador que o
				//		quarto est� ocupado e o nome do h�spede que est� ocupando o quarto, dar uma
				//		pausa para o operador poder ler e voltar ao menu.
				// 4 - Pedir o nome do h�spede considerando que tem nome e sobrenome
				// 5 - Zerar o total de di�rias do quarto que est� sendo ocupado
				// 6 - Indicar que este quarto est� ocupado e voltar ao menu
				if(!PedirAndarQuarto(&nAndarHotel, &nQuartoHotel, nQtdeAndares, nQtdeQuartosPorAndar,
					"Check-in de um h�spede"))				// cancelou a transa��o?
					break;									// cai fora do switch e volta ao menu
				// calcular o indice deste quarto
				iIndQuarto = ((nAndarHotel - 1) * nQtdeQuartosPorAndar) + (nQuartoHotel - 1);
				// verificar se o quarto est� ocupado
				if(vetLivreOcupado[iIndQuarto] == true)		// quarto ocupado?
				{	// quarto est� ocupado
					sprintf_s(cWork, sizeof(cWork), 
						"\nAndar:%2d Quarto:%2d H�spede:%-30s\nQuarto est� ocupado!",
						nAndarHotel, nQuartoHotel, vetNomeHospede[iIndQuarto]);
					cout << cWork << endl;
					PAUSA;
					break;									// volta ao menu
				}
				// pedir o nome do h�spede
				cin.ignore(1, EOF);							// ignorar a tecla Enter anterior
				cout << "Nome do h�spede: ";
				cin.getline(vetNomeHospede[iIndQuarto], EXTEN_NOME, '\n'); // aceita nome e sobrenome
				vetLivreOcupado[iIndQuarto] = true;			// ocupa o quarto
				vetTotalDiarias[iIndQuarto] = 0.0;			// zerar as di�rias de um h�spede anterior
				sprintf_s(cWork, sizeof(cWork), 
					"\nAndar:%2d Quarto:%2d H�spede:%-30s\nDi�ria:%9.2f",
						nAndarHotel, nQuartoHotel, vetNomeHospede[iIndQuarto],
						vetVlrDiaria[iIndQuarto]);
				cout << cWork << endl;
				PAUSA;
				break;						// para sair do switch e voltar ao menu
			case FAZER_CHECK_OUT:
				// <<<< 03 >>>>
				// 1 - Pedir o andar e o quarto da mesma forma que no item anterior indicando que a transa��o 
				//		� "Check-out"
				// 2 - Verificar se a transa��o foi cancelada e voltar ao menu
				// 3 - Verificar se o quarto est� ocupado e se estiver exibir o nome do h�spede e
				//		o total de di�rias do quarto
				// 4 - Pedir a confirma��o do operador com um S ou N
				//		Se for indicado 'S' ou 's' desocupar o quarto e qualquer outro caractere 
				//		 voltar ao menu. Para desocupar o quarto basta indicar false no vetLivreOcupado
				// 5 - Se o quarto n�o estiver ocupado avisar ao operador e voltar ao menu
				break;						// para sair do switch e voltar ao menu
			case LANCAR_DIARIA:
				// <<<< 05 >>>> 
				// 1 - Pedir a data e hora do sistema e apresentar ao operador
				// 2 - Confirmar com o operador se ele realmente deseja lan�ar as di�rias no hor�rio
				//		apresentado
				// 3 - Se o operador confirmar percorrer o vetor de quartos livres e ocupados e 
				//			somar uma di�ria a mais no total de di�rias deste quarto.
				// 4 - Caso o operador n�o confirme voltar ao menu.
				//		Lan�ar di�ria significa pegar o valor da di�ria que foi associada ao quarto e
				//			somar no total das di�rias e do quarto.
				// Para buscar a data e hora do sistema utilizar o seguinte comando:
				//		GetLocalTime(&stTime);
				//		stTime.wDay, stTime.wHour e etc. tem o valores correspondentes a data e hora
				dTotalDiarias = 0.0;			// para acumular o total de di�rias lan�adas
				GetLocalTime(&stTime);			// data e hora do sistema
				sprintf_s(cWork, sizeof(cWork),
					"\nLan�ar di�ria em %02d/%02d/%04d �s %02d:%02d Confirma (S ou N): ",
					stTime.wDay, stTime.wMonth, stTime.wYear,
					stTime.wHour, stTime.wMinute);
				cout << cWork;
				cin >> cOpcaoOper;			// confirma��o ou n�o do operador
				if(cOpcaoOper == 's' || cOpcaoOper ==  'S')		// confirmou?
				{	// vai lan�ar di�rias em todos os quarto ocupados
					for(i = 0; i < nQtdeTotalQuartos; i++)	// loop de todos os quartos do hotel
					{
						if(vetLivreOcupado[i])				// quarto ocupado?
						{	// quarto est� ocupado
							vetTotalDiarias[i] += vetVlrDiaria[i]; // mais uma di�ria no quarto
							dTotalDiarias += vetVlrDiaria[i];	   // acumula na somat�ria
						}
					} // for i
				}
				else break;					// volta ao menu se o operador n�o disse sim
				sprintf_s(cWork, sizeof(cWork),
					"\n\t\tTotal de di�rias lan�ado:%10.2f", dTotalDiarias);
				cout << cWork << endl;
				PAUSA;
				break;						// para sair do switch e voltar ao menu
			case LISTAR_UM_QUARTO:
				// <<<< 06 >>>> 
				// 1 - Pedir Andar e Quarto conforme itens anteriores
				// 2 - Verificar se o quarto est� ocupado e se n�o estiver, avisar ao operador e voltar ao menu
				// 3 - Se estiver ocupado listar os dados do quarto indicando nome do h�spede e valor da
				//		di�ria do quarto e o total de di�rias utilizando o sprintf_s
				//		Formato: Andar Quarto H�spede            Vlr.Di�ria Tot.Di�rias
				//				  A      Q    XXXXXXXXXXXXXXXXX  DDDDD.DD   TTTTTT.TT
				//
				break;						// para sair do switch e voltar ao menu
			case EXIBIR_QUARTOS_LIVRES_ANDAR:
				// pedir um andar v�lido
				// loop para listar os quarto que est�o livres
				break;
			case SAIR_DO_PROGRAMA:
				cout << "\nDeseja sair realmente? (S ou N): ";
				cin >> cOpcaoOper;
				if(cOpcaoOper == 'S' || cOpcaoOper == 's')		// sair realmente?
					return;
				break;						// para sair do switch e decidir se vai sair realmente
			default:
				// Avisar que foi escolhida uma op��o errada
				cout << "\nOpcao inv�lida!" << endl;
				PAUSA;
		} // switch
	} // while(true)
} // main
