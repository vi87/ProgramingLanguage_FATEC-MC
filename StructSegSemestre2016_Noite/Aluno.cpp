// Programa de teste de struct
// FATEC-MC JCB - 19/10/2016 - Versão 0.0
#include "Struc.h"
// entry point do programa
void main(void)
{
	bool flgSegundo = false;				// true - Indica segundo passo do programa
	int i, j;								// indices genéricos
	ALUNO stAluno,							// struct para conter aluno
		vetAlunos[QTDE_ALUNOS],				// vetor de alunos
		*ptrStAluno = &stAluno,				// ponteiro apontado para struct stAluno
		*ptrVetAluno;						// ponteiro que não aponta pra ninguém
	SYSTEMTIME stTime;						// para receber a data e hora do sistema
	char cWork[200];						// para uso do sprintf
	ACENTUACAO_BRASILEIRA;
	// inicializar o vetor de alunos com todos inativos
	// no código 1, 2, 3, ........ QTDE_ALUNOS
	for (i = 0; i < QTDE_ALUNOS; i++)
	{
		vetAlunos[i].cAtivo = 'I';		// aluno inativo;
		vetAlunos[i].nCodAluno = i + 1;		// código 1, 2, 3, ...... 
	}
	GetLocalTime(&stTime);					// busca a data e hora do sistema
	sprintf_s(cWork, sizeof(cWork),
		"\n\tPrograma para matricular alunos em %02d/%02d%04d às %02d:%02d",
		stTime.wDay, stTime.wMonth, stTime.wYear,
		stTime.wHour, stTime.wMinute);
	cout << cWork << endl;
	while (true)								// for (;;) loop infinito
	{
		do
		{
			cout << "Código de aluno entre 1 e " << QTDE_ALUNOS << endl
				<< " ou 0 para encerrar o programa: ";
			cin >> stAluno.nCodAluno;			// código do aluno
			if (stAluno.nCodAluno == 0)			// encerrar?
			{
				flgSegundo = true;				// indica para ir ao segundio passo do programa
				break;							// cai fora do while
			}
				//return;							// retorna ao S.O.
		} while (stAluno.nCodAluno < 1 || stAluno.nCodAluno > QTDE_ALUNOS);
		if (flgSegundo)							// flgSegundo = true?
			break;								// cai fora do while infinito
		// temos um código válido - será que o aluno está inativo?
		if (vetAlunos[stAluno.nCodAluno - 1].cAtivo == 'A')	// aluno já cadastrado?
		{// aluno já cadastrado
			sprintf_s(cWork, sizeof(cWork),
				"Código: %6d Nome: %-30s já matriculado",
				vetAlunos[stAluno.nCodAluno - 1].nCodAluno,
				vetAlunos[stAluno.nCodAluno - 1].szNomeAluno);
			cout << cWork << endl;
			PAUSA;
			continue;							// continua no while
		}
		cin.ignore(1, EOF);						// Retira a tecla enter do buffer do teclado
		cout << "Nome: ";
		cin.getline(stAluno.szNomeAluno, EXTENSAO_NOME, '\n');	// nome com sobrenome
		stAluno.cAtivo = 'A';					// aluno matriculado
		cout << "Mensalidade: ";
		cin >> stAluno.dVlrMensalidade;			// mensalidade do aluno;
		stAluno.stDtMatricula.nDia = stTime.wDay;
		stAluno.stDtMatricula.nMes = stTime.wMonth;
		stAluno.stDtMatricula.nAno = stTime.wYear;
		// copiar a struct do aluno dentro da sua posição no vetor
		memcpy_s(&vetAlunos[stAluno.nCodAluno - 1],sizeof(ALUNO),&stAluno, sizeof(ALUNO));
	}// while
	// segundo passo do programa
	ptrVetAluno = vetAlunos;					// o ponteiro aponta para o primeiro aluno
	flgSegundo = false;
	LIMPAR_TELA;
	while (true)
	{
		do
		{
			cout << "Código de aluno entre 1 e " << QTDE_ALUNOS << endl
				<< " ou 0 para encerrar o programa: ";
			cin >> ptrStAluno->nCodAluno;			// código do aluno
			if (ptrStAluno->nCodAluno == 0)			// encerrar?
			{
				flgSegundo = true;					// para ir para o terceiro passo
				break;								// cai fora do do..while
			}
		} while (ptrStAluno->nCodAluno < 1 || ptrStAluno->nCodAluno > QTDE_ALUNOS);
		if (flgSegundo)								// flag é true?
			break;									// vai para o terceiro passo
		if ((ptrVetAluno + (ptrStAluno->nCodAluno - 1))->cAtivo == 'A') // já cadastrado?
		{// exibir o aluno já cadastrado
			sprintf_s(cWork, sizeof(cWork),
				"Código: %6d Nome: %-30s já cadastrado.",
				(ptrVetAluno + (ptrStAluno->nCodAluno - 1))->nCodAluno,
				(ptrVetAluno + (ptrStAluno->nCodAluno - 1))->szNomeAluno);
			cout << cWork << endl;
			PAUSA;
			continue;						// continua no while
		}
		// pedir nome e sobrenome
		cin.ignore(1, EOF);							// ignorar a tecla enter anterior
		cout << "Nome: ";
		cin.getline(ptrStAluno->szNomeAluno, EXTENSAO_NOME, '\n');	// nome e sobrenome
		cout << "Mensalidade: ";
		cin >> ptrStAluno->dVlrMensalidade;
		ptrStAluno->stDtMatricula.nDia = stTime.wDay;
		ptrStAluno->stDtMatricula.nMes = stTime.wMonth;
		ptrStAluno->stDtMatricula.nAno = stTime.wYear;
		// copiar a struct no vetor na posição do aluno
		memcpy_s((ptrVetAluno + (ptrStAluno->nCodAluno - 1)), sizeof(ALUNO), ptrStAluno, sizeof(ALUNO));
	}// while
	// terceiro passo listar todos os alunos matriculados
	LIMPAR_TELA;
	cout << "\n\tListagem dos alunos matriculados." << endl;
	// ponteiro direto
	for (i = 0; i < QTDE_ALUNOS; i++, ptrVetAluno++)					// loop de todos os alunos
	{
		if (ptrVetAluno->cAtivo == 'A')					// aluno cadastrado?
		{
			sprintf_s(cWork, sizeof(cWork),
				"Código: %6d Nome: %-30s Matricula: %9.2f\nDt.Matricula: %02d/%02d/%04d",
				ptrVetAluno->nCodAluno,
				ptrVetAluno->szNomeAluno,
				ptrVetAluno->dVlrMensalidade,
				ptrVetAluno->stDtMatricula.nDia,
				ptrVetAluno->stDtMatricula.nMes,
				ptrVetAluno->stDtMatricula.nAno);
			cout << cWork << endl;
		}
	}// for i
	cout << "\n\tFim da listagem." << endl;
	PAUSA;
	LIMPAR_TELA;
	cout << "\n\tListagem dos não matriculados." << endl;
	for (i = 0, ptrVetAluno = vetAlunos ; i < QTDE_ALUNOS; i++)					// loop de todos os alunos
	{
		for (j = 0; j < 8; j++, i++, ptrVetAluno++)
		{
			if (ptrVetAluno->cAtivo == 'A')					// aluno cadastrado?
			{
				sprintf_s(cWork, sizeof(cWork), "%06d", ptrVetAluno->nCodAluno);
				cout << cWork;
				/*
				cout << ptrVetAluno->nCodAluno << "\t";		// lista um codigo
				sprintf_s(cWork, sizeof(cWork),
					"Código: %6d Nome: %-30s Matricula: %9.2f\nDt.Matricula: %02d/%02d/%04d",
					ptrVetAluno->nCodAluno,
					ptrVetAluno->szNomeAluno,
					ptrVetAluno->dVlrMensalidade,
					ptrVetAluno->stDtMatricula.nDia,
					ptrVetAluno->stDtMatricula.nMes,
					ptrVetAluno->stDtMatricula.nAno);
				cout << cWork << endl;
				*/
			}
			else
			{
				j--;						// um a menos
				continue;
			}
		}
	}// for i
	cout << "\n\tFim da listagem." << endl;
	PAUSA;
}