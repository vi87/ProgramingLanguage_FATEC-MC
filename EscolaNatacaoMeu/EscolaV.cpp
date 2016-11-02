// Programa Escola de Natação - Prova B1 - 17/09/2014 - Turma da Tarde
//
#include "Escola.h"
//	Entry point do programa
//
void main(void)
{
	int nPeriodo,								// periodo da aula de natação
		nRaia,									// raia da piscina
		nQtdeRaiasDaPiscina,					// quantidade de raias da piscina
		nQtdeTotalDeRaias,						// qtde total de raias nos três períodos
		i, j;									// índices genéricos
	char cOpcao,								// opcao do operador
		cNomeAluno[] = "Victor Drulis Oliveira",
		cRA_Aluno[] = "1840481613015",
		cWork[200];								// para sprintf_s
	SYSTEMTIME stTime;							// para data e hora do sistema
	// vetores dos periodos e raias das piscinas
	bool vetRaiasLivres[QTDE_RAIAS_DA_PISCINA * QTDE_PERIODOS];	// vetor que indica se raia livre ou ocupada
												// true - indica ocupada e false indica livre
	char vetSobrenomes[QTDE_RAIAS_DA_PISCINA * QTDE_PERIODOS][TAMANHO_SOBRENOME],
			vetAuxSobrenomes[1][TAMANHO_SOBRENOME];	// vetor de sobrenomes
	double vetMensalidades[QTDE_RAIAS_DA_PISCINA * QTDE_PERIODOS];	// vetor mensalidades
	// para duas casas decimais nos valores
	setlocale(LC_ALL, "portuguese_brazil");		// para acentuação brasileira
	// <<<1>>> - Preencher as variáveis com seu nome e RA
	// <<<2>>> - Fazer um loop indicando que todas as raias de todos os períodos estão desocupadas
	//			 
	//			 Não se esquecer do seguinte:
	//				No período da manhã temos a raia 1 até Qtde de Raias da Piscina, no período da tarde de
	//				1 até a Qtde de Raias da Piscina, idem no período da noite.
	//
	//	Loop Infinito
	for (i = 0 ; i < QTDE_PERIODOS * QTDE_RAIAS_DA_PISCINA ; i++)
	{
		vetRaiasLivres[i] = false;
		stpcpy_s(vetSobrenomes[i], "");
	}
	
	while(true)
	{
		LIMPAR_TELA;
		GetLocalTime(&stTime);						// data e hora do sistema
		sprintf(cWork, 
			"\tFATEC-Escola de Natação %02d/%02d/%04d às %02d:%02d:%02d\n\tOperador: %s Matrícula: %s",
			stTime.wDay, stTime.wMonth, stTime.wYear, 
			stTime.wHour, stTime.wMinute, stTime.wSecond,
			cNomeAluno, cRA_Aluno);
		cout << cWork << endl;
		// exibir o menu
		cout << MATRICULAR_ALUNO << " - Matricular aluno em um período desejado" << endl
			<< CANCELAR_MATRICULA << " - Cancelar a matrícula de um aluno" << endl
			<< LANCAR_DESPESA << " - Lançar despesas em um aluno matriculado" << endl
			<< LISTAR_PERIODO << " - Listar os alunos de um dado período" << endl
			<< SAIR_DO_PROGRAMA << " - Sair do programa" << endl
			<< "\tSelecione: ";
		cin  >> cOpcao;
		cOpcao = toupper(cOpcao);					// converte para maiúscula
		switch(cOpcao)								// avalia a opção escolhida
		{
			case MATRICULAR_ALUNO:
				// <<<5>>> - pedir um período válido (desejado pelo aluno) através da função 
				//				BuscarPeriodo
				if (BuscarPeriodo(&nPeriodo, QTDE_PERIODOS, "Escolha um período:") == true)
				{
					nRaia = BuscarRaiaLivreNoPeriodo(vetRaiasLivres, nPeriodo, QTDE_RAIAS_DA_PISCINA);
					if(nRaia == 0 && vetRaiasLivres[0] == true)
					{
						cout << "Não há raias disponíveis." << endl;
						PAUSA;
						break;
					}
					else if (nRaia >= 0 && vetRaiasLivres[nRaia] != true)
					{
						cout << "Cadastrar aluno." << endl << endl
						<< "Digite o sobrenome: ";
						cin >> vetAuxSobrenome[0];
						
						
					}
				}
				else
				{
					cout << "ERRO!" << endl;
					PAUSA;
					break;
				}
				// <<<6>>> - chamar a função que verifica se tem uma raia livre no
				//			 período desejado e se não houver uma livre, esta função, devolve zero e
				//			 caso contrário, devolve o número da raia livre no período desejado
				//			 Se não houver uma raia livre cancelar esta ação de matricular aluno
				//				(volta ao menu principal)
				
				// <<<7>>> - pedir o sobrenome do aluno sendo matriculado.
				//			 verificar se existe o mesmo sobrenome nas raias ocupadas. Para
				//			 cada parente encontrado será dado um desconto de 10% limitado ao
				//			 máximo de 40%.
				//			 Assim: Se houver um só ou o primeiro aluno a mensalidade é cheia (100%); 
				//			  se houver mais um 10% de desconto, se houver
				//				mais um 20%; mais um 30% e apartir quarto todos terão 40% de desconto
				// <<<8>>>	Associar este aluno ao período e à raia desejada (ocupar a raia com a bool true
				//			no vetor de livre/ocupada, sobrenome que está nesta raia, valor da mensalidade
				//			Indicar a raia e o período onde o aluno foi matriculado
				//			Dar uma pausa e
				//			Voltar ao menu 
				//
				break;								// cai fora do switch
			case CANCELAR_MATRICULA:				
				// <<<9>>>  Chamar a função que pede o periodo e a raia indicando que a ação é
				//			Cancelamento de Matrícula
				// <<<10>>> Verificar se a raia está ocupada e se estiver livre avisar ao operador e
				//			cancelar está ação voltando ao menu
				//			Se a raia estiver ocupada exibir o sobrenome, valor da matrícula
				// <<<11>>> Pedir a confirmação do cancelamento da matrícula e havendo a confirmação
				//			apenas indicar que está raia deste periodo está livre. Caso contrário
				//			voltar ao menu principal
				break;								// cai fora do switch
			case LANCAR_DESPESA:
				// Não codificar ????????????????????????????????????????????
				// <<<12>>> Chamar a função que pede o periodo e a raia indicando que a ação é
				//			Lançamento de Despesa
				// <<<13>>> Verificar se a raia está ocupada e se estiver livre avisar ao operador e
				//			cancelar está ação voltando ao menu
				// <<<14>>> Se a raia estiver ocupada exibir o Sobrenome e as despesas até o momento
				//			Pedir o valor da despesa
				//			Somar o valor informado às despesas anteriores deste aluno
				//			Voltar ao menu
				break;								// cai fora do switch
			case LISTAR_PERIODO:				
				// <<<15>>> Pedir um período válido ou zero para cancelar a ação de listar
				//			Se foi informado um período válido listar todos as raias ocupadas
				//			no seguinte formato:
				//				Listagem das raias do periodo: ppppppp
				//			Raia Sobrenome  Mensalidade 
				//			 RR  SSSSSSSSS  MMMMMM,MM	
				//			.....
				//			.....
				//					       Total Mensalidades: TTTTTT,TT
				//			Onde: PPPPPPP - periodo: "Manhã", "Tarde" ou "Noite"
				//				  RR - raia ocupada ( 1 a Qtde de Raias da Piscina)
				//				  SSSSSSSSS - sobrenome do aluno
				//				  MMMMM - valor da mensalidade
				//				  TTTTTT,TT - valor total de todas as mensalidades
				//	<<<16>>> Pausa para visualização e voltar ao menu
				break;								// cai fora do switch
			case SAIR_DO_PROGRAMA:					
				cout << "Vai sair realmente? (S ou N): ";
				cin >> cOpcao;
				if(cOpcao == 's' || cOpcao == 'S')	// sair realmente?
					return;			
				break;								// cai fora do switch
			default:
				cout << "Opção inválida!" << endl;
				PAUSA;
		} // switch
	} // while
} // main
// 
// Funções do Programa
//
// Função que pede um período válido e uma raia da piscina válida
// Parâmetros:
//	Entrada: int *ptrPeriodo - ponteiro para receber o período desejado
//			 int *ptrRaia - ponteiro para receber a raia da piscina desejada
//			 int nQtdePeriodos - quantidade de períodos da Escola de Natação
//			 int nQtRaiasPiscina - quantidade de raias que tem a piscina da Escola de Natação
//			 char *ptrAcao - ponteiro de um string que contém a ação que está sendo executada
//	Retorno: bool - true - indica que foi informado um período e uma raia válidos
//					false - indica que o operador desistiu da ação que iria executar
//							digitando periodo zero
bool PedirPeriodoRaia(int *ptrPeriodo, int *ptrRaia, 
					  int nQtdePeriodos, int nQtRaiasPiscina, char *ptrAcao)
{

	return true;							// ???? para não dar erro de compilação
}
//
// Função que verifica se tem uma raia livre no período desejado
//	Parâmetros:
//		Entrada: bool *ptrVetLivreOcup - ponteiro do vetor de bool que indica se a raia está 
//										 livre ou ocupada
//				 int nPeriodo - período desejado
//				 int nQtRaiasPiscina - quantidade de raia que a piscina te´m
//		Retorno: int - Número da raia que está livre ou zero se não existir nenhuma
//						raia livre no período desejado
int BuscarRaiaLivreNoPeriodo(bool *ptrVetLivreOcup, int nPeriodo, int nQtRaiasPiscina)
{
	int i;
	for(i = (nPeriodo-1)*nQtRaiasPiscina; 
	i < ((nPeriodo-1)*nQtRaiasPiscina) + QTDE_RAIAS_DA_PISCINA || *ptrVetLivreOcup == true ; 
	i++, ptrVetLivreOcup++)
	{
		cout << i << "\t";
		cout << "Raia " << i - ((nPeriodo-1)*nQtRaiasPiscina) + 1;
		if(*ptrVetLivreOcup == false)
		{
			cout << ": LIVRE" << endl;
			return i;
		}
		else
		{
			cout << ": OCUPADO" << endl;
			return 0;
		}
	}
								// ???? para não dar erro de compilação
}
// Parâmetros:
//	Entrada: int *ptrPeriodo - endereço de uma inteira que receberá o periodo desejado
//			 int nQtdePeriodos - quantidade de periodos
//			 char *ptrAcao - ponteiro de um string que contém a ação em execução
//	Retorno: bool - true - foi indicado um período válido
//					false - foi indicado um periodo zero que indica cancelar a ação desejada
bool BuscarPeriodo(int *ptrPeriodo, int nQtdePeriodos, char *ptrAcao)
{
	LIMPAR_TELA;
	do
	{
		cout << ptrAcao << endl << endl
			<< "manhã = 1" << endl
			<< "tarde = 2" << endl
			<< "noite = 3" << endl
			<< "cancelar = 0" << endl;
		cin >> *ptrPeriodo;
	} while (*ptrPeriodo < 0 || *ptrPeriodo > 3);
	cout << "Selecionado -> ";
	if (*ptrPeriodo == 0)
	{
		return false;
	}
	else if (*ptrPeriodo == 1)
	{
		cout << "Manhã" << endl;
		return true;
		PAUSA;
	}
	else if (*ptrPeriodo == 2)
	{
		cout << "Tarde" << endl;
		return true;
		PAUSA;
	}
	else if (*ptrPeriodo == 3)
	{
		cout << "Noite" << endl;
		return true;
		PAUSA;
	}
	else
	{
		cout << "Opção inválida." << endl;
		PAUSA;
	}
	}while(*ptrPeriodo < 0 || *ptrPeriodo > 3);
}

BuscarSobrenome (char *vetNomes, char *vetAuxNomes)
{
	int i;
	for (i = 0 ; i < QTDE_PERIODOS * QTDE_RAIAS_DA_PISCINA ; i++ , vetNomes++)
	{
		if (strcmp_s(*vetNomes, *vetAuxNomes))
		{
			
		}
	}
}
