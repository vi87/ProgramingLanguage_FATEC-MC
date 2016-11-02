// Agencia Bancária - Trabalho para entrega na P2
// FATEC - MC - JCB - 20/04/2016 - Versão 0.0
#include "Agencia.h"
//
// entry point do programa
//
void main(void)
{
	int i,									// indice e contador
		nCodCliente;						// recebe o código do cliente
	char cOpcao,							// opção do operador
		szOperador[] = "José Carlos Bortot",// nome do operador
		cTrabalho[200];						// sprintf_s
	CLIENTE stCliente;						// para conter os dados de um cliente
	SYSTEMTIME stTime;						// para data e hora do sistema
	FILE *fdCadastro;						// file descriptor do cadastro cliente

	setlocale(LC_ALL, "portuguese_brazil");	// acentuação brasileira
	// abrir o arquivo em modo leitura/gravação e binário - precisa existir
	if(fopen_s(&fdCadastro, CAMINHO_ARQUIVO, "r+b") != 0)	// erro de abertura?
	{	// o arquivo não existe porque é a primeira vez que o programa é executado
		if(fopen_s(&fdCadastro, CAMINHO_ARQUIVO, "w+b") != 0) // erro de abertura?
		{	// erro irrecuperável
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
				sizeof(CLIENTE), 1, fdCadastro) == 0) // erro gravação?
			{	// erro irrecuperável
				fclose(fdCadastro);		// fechar com o que está gravado
				cout << "Erro na inicialização do cadastro de clientes!"
					<< endl;
				PAUSA;
				return;								// volta ao sistema operacional
			}
		} // for
	} // arquivo não existe
	// o arquivo existe ou foi criado um novo
	// loop infinito
	while(true)
	{
		LIMPAR_TELA;				
		GetLocalTime(&stTime);					// data e hora do sistema
		sprintf_s(cTrabalho, sizeof(cTrabalho), 
		"\n\tFATEC-MC - Agência Bancária %02d/%02d/%04d às %02d:%02d:%02d\n\tOperador: %s",
		stTime.wDay, stTime.wMonth, stTime.wYear,
		stTime.wHour, stTime.wMinute, stTime.wSecond,
		szOperador);
		cout << cTrabalho << endl;
		// editar o menu
		cout << CADASTRAR_CLIENTE << " - Cadastrar novo cliente" << endl;
		cout << EXCLUIR_CLIENTE << " - Excluir cliente existente" << endl;
		cout << MOSTRAR_CLIENTE << " - Mostrar dados do cliente" << endl;
		cout << DEBITAR_CHEQUE << " - Debitar um cheque de cliente" << endl;
		cout << CREDITAR_DEPOSITO << " - Creditar depósito de cliente" << endl;
		cout << LISTAR_CADASTRO << " - Listar cadastro a partir de um cliente" << endl;
		cout << EXIBIR_SALDO_TOTAL << " - Exibir o total da contas da agência" << endl;
		cout << SAIR_DO_PROGRAMA << " - Sair do programa" << endl;
		cout << "\tSelecione: ";
		cin >> cOpcao;					// opção do operador
		cOpcao = toupper(cOpcao);		// converte para maiúscula
		switch(cOpcao)					// avaliar a opção escolhida
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
				if(stCliente.cAtivo == ATIVO)	// cliente já existe?
				{	// cliente já existe
					cout << "\nCliente: " << stCliente.nCodigo
						<< " Nome: " << stCliente.cNome << endl
						<< "Já foi cadastrado!" << endl;
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
					&stCliente, fdCadastro))	// erro de gravação?
				{	// erro de gravação
					cout << "Erro de gravação do cliente: " << nCodCliente
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
				cout << "Opção inválida!" << endl;
				PAUSA;
		} // switch
	} // while
} // main

