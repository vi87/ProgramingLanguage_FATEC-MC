// Declarações da prova de LP - N1 - 28/09/2016
#include <iostream>
#include <Windows.h>
using namespace std;
#define PAUSA							system("pause")
#define LIMPAR_TELA						system("cls")
#define EXTEN_NOME						30			// extensão do nome do hóspede
// opções do menu
#define FAZER_CHECK_IN					'I'			// fazer o check-in do hóspede
#define FAZER_CHECK_OUT					'O'			// fazer o check-out do hóspede
#define LISTAR_UM_QUARTO				'L'			// listar os dados de um dado quarto
#define LANCAR_DIARIA					'D'			// lançar diárias nos quartos que estão ocupados
#define EXIBIR_QUARTOS_LIVRES_ANDAR		'E'			// exibir os quartos livres de um andar
#define SAIR_DO_PROGRAMA				'S'			// sair do programa		

// Valores das diárias para cada quarto de acordo com o andar em que está
#define DIARIA_QUARTO_SIMPLES			165.00		// Diária do quarto simples
#define DIARIA_QUARTO_MEDIO				308.00		// Diária do quarto do tipo médio
#define DIARIA_QUARTO_SUPER				610.00		// Diária do quarto do tipo super
#define DIARIA_QUARTO_SUITE				990.00		// Diária do quarto do tipo suite
// Observações:
// 1 - Os quartos dos andares 1º ao 2º - são quartos do tipo simples
// 2 - Os quartos dos andares 3º ao 4º - são quartos do tipo médio
// 3 - Os quartos dos andares 5º ao 8º - são quartos do tipo super
// 4 - Os quartos dos andares 9º e acima - são quartos do tipo suite
#define ANDAR_1							1
#define ANDAR_2							2
#define ANDAR_3							3
#define ANDAR_4							4
#define ANDAR_5							5
#define ANDAR_6							6
#define ANDAR_7							7
#define ANDAR_8							8
#define ANDAR_9							9

// Limitações do programa
#define QUANTIDADE_MAXIMA_ANDARES		35			// quantidade máxima de andares do hotel
#define QTDE_MINIMA_ANDARES				10			// quantidade mínima de andares
#define QUANTIDADE_MAXIMA_QUARTOS		20			// quantidade máxima de quartos por andar
#define QTDE_MINIMA_QUARTOS_ANDAR		10			// quantidade mínima de quartos por andar

// definições de tipos de serviços
#define DIARIA							1			// transação de diária
#define RESTAURANTE						2			// transação de restaurante
#define BAR								3			// transação de bar
#define PISCINA							4			// transação de bar da piscina
#define BOATE							5			// transação de bar da boate
// protótipos das funções
bool	PedirAndarQuarto(int *ptrAndar, int *ptrQuarto, int nQtAndares, int nQtQuartos, char *ptrTransacao);
