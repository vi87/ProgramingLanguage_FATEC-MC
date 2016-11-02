// DEclarações do programa de teste de struct
#include <iostream>
#include <Windows.h>
using namespace std;
// definições
#define PAUSA									system("pause")
#define LIMPAR_TELA								system("cls")
#define QTDE_ALUNOS								1000
#define EXTENSAO_NOME							30
#define ACENTUACAO_BRASILEIRA					setlocale(LC_ALL, "portuguese_brazil")
// struct para data
typedef struct tagDATA
{
	short int nDia, nMes, nAno;				//dia/mês/ano

} DATA, DATA_DO_DIA;
//struct para o aluno
typedef struct tagALUNO
{
	int nCodAluno;							// código do aluno
	char cAtivo,							// 'A' = ativo e 'I' = inativo
		szNomeAluno[EXTENSAO_NOME+1];		// nome do aluno
	DATA StDtMAtricula;						// data da matrícula
	double dVlrMensalidade;					// valor da mensalidade
} ALUNO;