// Declara��es da prova de LP - N1 - 28/09/2016
#include <iostream>
#include <Windows.h>
using namespace std;
#define PAUSA							system("pause")
#define LIMPAR_TELA						system("cls")
#define EXTEN_NOME						30			// extens�o do nome do h�spede
// op��es do menu
#define FAZER_CHECK_IN					'I'			// fazer o check-in do h�spede
#define FAZER_CHECK_OUT					'O'			// fazer o check-out do h�spede
#define LISTAR_UM_QUARTO				'L'			// listar os dados de um dado quarto
#define LANCAR_DIARIA					'D'			// lan�ar di�rias nos quartos que est�o ocupados
#define EXIBIR_QUARTOS_LIVRES_ANDAR		'E'			// exibir os quartos livres de um andar
#define SAIR_DO_PROGRAMA				'S'			// sair do programa		

// Valores das di�rias para cada quarto de acordo com o andar em que est�
#define DIARIA_QUARTO_SIMPLES			165.00		// Di�ria do quarto simples
#define DIARIA_QUARTO_MEDIO				308.00		// Di�ria do quarto do tipo m�dio
#define DIARIA_QUARTO_SUPER				610.00		// Di�ria do quarto do tipo super
#define DIARIA_QUARTO_SUITE				990.00		// Di�ria do quarto do tipo suite
// Observa��es:
// 1 - Os quartos dos andares 1� ao 2� - s�o quartos do tipo simples
// 2 - Os quartos dos andares 3� ao 4� - s�o quartos do tipo m�dio
// 3 - Os quartos dos andares 5� ao 8� - s�o quartos do tipo super
// 4 - Os quartos dos andares 9� e acima - s�o quartos do tipo suite
#define ANDAR_1							1
#define ANDAR_2							2
#define ANDAR_3							3
#define ANDAR_4							4
#define ANDAR_5							5
#define ANDAR_6							6
#define ANDAR_7							7
#define ANDAR_8							8
#define ANDAR_9							9

// Limita��es do programa
#define QUANTIDADE_MAXIMA_ANDARES		35			// quantidade m�xima de andares do hotel
#define QTDE_MINIMA_ANDARES				10			// quantidade m�nima de andares
#define QUANTIDADE_MAXIMA_QUARTOS		20			// quantidade m�xima de quartos por andar
#define QTDE_MINIMA_QUARTOS_ANDAR		10			// quantidade m�nima de quartos por andar

// defini��es de tipos de servi�os
#define DIARIA							1			// transa��o de di�ria
#define RESTAURANTE						2			// transa��o de restaurante
#define BAR								3			// transa��o de bar
#define PISCINA							4			// transa��o de bar da piscina
#define BOATE							5			// transa��o de bar da boate
// prot�tipos das fun��es
bool	PedirAndarQuarto(int *ptrAndar, int *ptrQuarto, int nQtAndares, int nQtQuartos, char *ptrTransacao);
