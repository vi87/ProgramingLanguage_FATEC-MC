// Declaração do programa
#include <iostream>
#include <Windows.h>
using namespace std;
#define PAUSA				system("pause")
#define LIMPAR_TELA			system("cls")
// definições do programa
#define QTDE_MAX_CALOUROS			30
#define QTDE_MIN_CALOUROS			5
#define EXTENSAO_NOME				30
#define MASCULINO					'M'
#define FEMININO					'F'
#define CARACTER					1
// Protótipos das funções do programa
void ListarCalouros(char vetCalouros[][EXTENSAO_NOME + 1], char vetSexos[], int vetNotas[], int nQtdeCalouros);
void BubbleSort(char vetNomes[][EXTENSAO_NOME + 1], char VetSexo[], int vetNotas[], int nQtde);
void BubbleAlfa(char vetCalouros[][EXTENSAO_NOME + 1], char vetSexos[], int vetNotas[], int nQtde);