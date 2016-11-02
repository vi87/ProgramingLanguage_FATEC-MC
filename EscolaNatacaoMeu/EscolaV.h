// Declara��es do programa Escola de Nata��o
#include <iostream>
#include <windows.h>
using namespace std;
// Defini��es
#define PAUSA				system("pause")
#define LIMPAR_TELA			system("cls")
// Delimita��o do programa
#define QTDE_PERIODOS		3			// quantidade de per�odos (1 - manh�, 2 - tarde e 3 - noite)
#define QTDE_RAIAS_DA_PISCINA	10			// quantidade m�xima de raias da piscina
#define PERIODO_MANHA		1			// per�odo da manh�
#define PERIODO_TARDE		2			// per�odo da tarde
#define PERIODO_NOITE		3			// per�odo da noite
#define TAMANHO_SOBRENOME	15			// tamanho do sobrenome sem o delimitador
// op��es do menu
#define MATRICULAR_ALUNO		'M'			
#define CANCELAR_MATRICULA		'C'
#define LANCAR_DESPESA			'D'
#define LISTAR_PERIODO			'P'
#define SAIR_DO_PROGRAMA		'S'
// valores e descontos de mensalidade
#define VALOR_MENSALIDADE			130.00	// valor da mensalidade do primeiro da fam�lia
#define VALOR_DESCONTO_POR_PARENTE	10		// valor para cada parente com o mesmo sobrenome
// limite de descontos at� quatro parentes
// prot�tipos das fun��es
bool PedirPeriodoRaia(int *ptrPeriodo, int *ptrRaia, 
					  int nQtdePeriodos, int nQtRaiasPiscina, char *ptrAcao);
int BuscarRaiaLivreNoPeriodo(bool *ptrVetLivreOcup, int nPeriodo, int nQtRaiasPiscina);
bool BuscarPeriodo(int *ptrPeriodo, int nQtdePeriodos, char *ptrAcao);
