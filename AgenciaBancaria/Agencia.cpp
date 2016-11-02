// Agencia Banc�ria - Trabalho para entrega na P2
// FATEC - MC - JCB - 20/04/2016 - Vers�o 0.0
#include "Agencia.h"
//
// entry point do programa
//
void main(void)
{
	int i,									// indice e contador
		nCodCliente;						// recebe o c�digo do cliente
	char cOpcao,							// op��o do operador
		szOperador[] = "Jos� Carlos Bortot",// nome do operador
		cTrabalho[200];						// sprintf_s
	CLIENTE stCliente;						// para conter os dados de um cliente
	SYSTEMTIME stTime;						// para data e hora do sistema
	FILE *fdCadastro;						// file descriptor do cadastro cliente

	setlocale(LC_ALL, "portuguese_brazil");	// acentua��o brasileira
	// abrir o arquivo em modo leitura/grava��o e bin�rio - precisa existir
	if(fopen_s(&fdCadastro, CAMINHO_ARQUIVO, "r+b") != 0)	// erro de abertura?
	{	// o arquivo n�o existe porque � a primeira vez que o programa � executado
		if(fopen_s(&fdCadastro, CAMINHO_ARQUIVO, "w+b") != 0) // erro de abertura?
		{	// erro irrecuper�vel
			cout << "Erro de abertura do arquivo: " << CAMINHO_ARQUIVO << endl;
			PAUSA;
			return;							// volta ao sistema operacional
		}
		// aberto com sucesso - vamos incializar o arquivo com todos os
		//	clientes inativos
		for(i = 0; i < QTDE_CLIENTES; i++)
		{
			stCliente.nCodigo = i + 1;	// 1, 2, 3, .......QTDE_CLIENTES
			stCliente.cAtivo = INATIVO; // cliente inativo
			// gravar esse cliente em modo sequencial
			if(fwrite(&stCliente,
				sizeof(CLIENTE), 1, fdCadastro) == 0) // erro grava��o?
			{	// erro irrecuper�vel
				fclose(fdCadastro);		// fechar com o que est� gravado
				cout << "Erro na inicializa��o do cadastro de clientes!"
					<< endl;
				PAUSA;
				return;								// volta ao sistema operacional
			}
		} // for
	} // arquivo n�o existe
	// o arquivo existe ou foi criado um novo
	// loop infinito
	while(true)
	{
		LIMPAR_TELA;				
		GetLocalTime(&stTime);					// data e hora do sistema
		sprintf_s(cTrabalho, sizeof(cTrabalho), 
		"\n\tFATEC-MC - Ag�ncia Banc�ria %02d/%02d/%04d �s %02d:%02d:%02d\n\tOperador: %s",
		stTime.wDay, stTime.wMonth, stTime.wYear,
		stTime.wHour, stTime.wMinute, stTime.wSecond,
		szOperador);
		cout << cTrabalho << endl;
		// editar o menu
		cout << CADASTRAR_CLIENTE << " - Cadastrar novo cliente" << endl;
		cout << EXCLUIR_CLIENTE << " - Excluir cliente existente" << endl;
		cout << MOSTRAR_CLIENTE << " - Mostrar dados do cliente" << endl;
		cout << DEBITAR_CHEQUE << " - Debitar um cheque de cliente" << endl;
		cout << CREDITAR_DEPOSITO << " - Creditar dep�sito de cliente" << endl;
		cout << LISTAR_CADASTRO << " - Listar cadastro a partir de um cliente" << endl;
		cout << EXIBIR_SALDO_TOTAL << " - Exibir o total da contas da ag�ncia" << endl;
		cout << SAIR_DO_PROGRAMA << " - Sair do programa" << endl;
		cout << "\tSelecione: ";
		cin >> cOpcao;					// op��o do operador
		cOpcao = toupper(cOpcao);		// converte para mai�scula
		switch(cOpcao)					// avaliar a op��o escolhida
		{
			case CADASTRAR_CLIENTE:
				nCodCliente = PedirCodigoCliente("Cadastrar cliente");
				if(nCodCliente == 0)	// cancelar?
					break;				// volta ao menu
				// ler um cliente posicional
				if(!LerClientePosicional(nCodCliente, 
					&stCliente, fdCadastro))		// erro de leitura
				{
					cout << "Erro de leitura do cliente: " << nCodCliente << endl;
					PAUSA;
					break;				// volta ao menu
				}
				// o cliente foi lido
				if(stCliente.cAtivo == ATIVO)	// cliente j� existe?
				{	// cliente j� existe
					cout << "\nCliente: " << stCliente.nCodigo
						<< " Nome: " << stCliente.cNome << endl
						<< "J� foi cadastrado!" << endl;
					PAUSA;
					break;						// volta ao menu
				}
				// cliente vai ser cadastrado
				cin.ignore(1, EOF);				// ignorar a tecla enter
				cout << "Nome: ";
				cin.getline(stCliente.cNome, EXTENSAO_NOME, '\n');
				cout << "Saldo: ";
				cin >> stCliente.dSaldo;
				stCliente.dTotalCreditos =
					stCliente.dTotalDebitos = 0.0;
				stCliente.stDataUltimoAcesso.nDia = stTime.wDay;
				stCliente.stDataUltimoAcesso.nMes = stTime.wMonth;
				stCliente.stDataUltimoAcesso.nAno = stTime.wYear;
				stCliente.cAtivo = ATIVO;		// cliente ativo
				// gravar o cliente posicional
				if(!GravarClientePosicional(nCodCliente, 
					&stCliente, fdCadastro))	// erro de grava��o?
				{	// erro de grava��o
					cout << "Erro de grava��o do cliente: " << nCodCliente
						<< endl;
					PAUSA;
				}
				break;					// volta ao menu
			case EXCLUIR_CLIENTE:
				break;					// volta ao menu
			case MOSTRAR_CLIENTE:
				break;					// volta ao menu
			case DEBITAR_CHEQUE:
				break;					// volta ao menu
			case CREDITAR_DEPOSITO:		
				break;					// volta ao menu
			case LISTAR_CADASTRO:
				break;					// volta ao menu
			case EXIBIR_SALDO_TOTAL:
				break;					// volta ao menu
			case SAIR_DO_PROGRAMA:
				cout << "Sair realmente? (S ou N): ";
				cin >> cOpcao;
				if(cOpcao == 's' || cOpcao == 'S')	// sair realmente?
				{
					fclose(fdCadastro);		// fechar o cadastro
					return;					// volta ao sistema operacional
				}
				break;						// volta ao menu
			default:
				cout << "Op��o inv�lida!" << endl;
				PAUSA;
		} // switch
	} // while
} // main

