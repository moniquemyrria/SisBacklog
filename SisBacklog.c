#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Estrutura Usuario
typedef struct Usuario{
       int id;
	   char nome[50];
       int senha;
       int tipoAcesso;
}cadUsuario;

// Estrutura Sprint
typedef struct Sprint{
       int sp;
	   char dtInicial[20];
	   char dtFinal[20];
}cadSprint;

// Estrutura Projeto
typedef struct Projeto{
       int id;
	   char nome[50];
}cadProjeto;

// Estrutura Tipo Atividade
typedef struct TipoAtividade{
       int id;
	   char nome[50];
}cadTipoAtividade;

// Estrutura Atividades - Backlog
typedef struct ProductBacklog{
	int id;
	char descricao[200];
    int prioridade; //(sendo 1 para alta, 2 média e 3 para baixa)
    struct Projeto cadProj;  
	struct TipoAtividade cadTipoAtiv;
}cadAtividade;

// Estrutura Programador
typedef struct Programador{
       int id;
	   char nome[50];
}cadProgramador;

// Estrutura Gerenciar Sprint
typedef struct GerenciarSprint{
	char status[50];
	int pontuacao;
	float percentualDesenvolvimento;
	struct Sprint cadSprint;
	struct Programador cadProg;
	struct ProductBacklog cadAtiv;
}GerSprint;

//Menus
void menuProgramador();
void menuUsuario();
void menuAtividade();
void menuProjeto();
void menuTipoAtividade();
void menuSprint();
void menuGerenciarSprint();
void menuPrincipal();
void menuSprintPrgramador(char nomeProgrmador[50]);
void menuRelatorio();

//Crud - Cadastrar
void cadastrarAtividade();
void cadastrarUsuario();
void cadastrarProgramador();
void cadastrarProjeto();
void cadastrarTipoAtividade();
void cadastrarSprint();

//Crud - Listar
void listarProgramador();
void listarUsuario();
void listarAtividade();
void listarProjeto();
void listarTipoAtividade();
void listarSprint();

//Crud - Alterar
void alterarProgramador();
void alterarUsuario();
void alterarAtividade();
void alterarProjeto();
void alterarTipoAtividade();
void alterarSprint();

//Crud - Excluir
void excluirProgramador();
void excluirUsuario();
void excluirAtividade();
void excluirProjeto();
void excluirTipoAtividade();
void excluirSprint();

//Funções
int verificaProgramadorCadastro();
int verificaProjetoCadastro();
int verificaSprintCadastro();
int verificaTipoAtividadeCadastro();
int verificaUsuarioCadastro();
int verificaAtividadeCadastro();

//Gerenciamento do Sprint
void selecionarAtividadesSprint();
void listarAtividadesDoSprint();
void listarAtividadesDoProgramador(char nomeProgramador[50]);
void listarAtividadesPorStatus(char Status[50]);
void dailyMeeting();
void validaAcesso();
void helpSobre();
void layoutHeader();

void helpSobre(){
	layoutHeader();
	printf("\n--------------------------------------------------\n COMO UTILIZAR O SISBACKLOG\n--------------------------------------------------\n");
	printf("\n\n 1. PARA  CADASTRO DAS  ATIVIDADES  DO  BACKLOG E'\n    NECESSARIO  QUE  DOS  PROJETOS  E  ATIVIDADES\n    ESTEJAM CADASTRADAS.");
	printf("\n\n 2. PARA O  GERENCIAMENTO DO  SPRINT E' NECESSARIO\n    A   DATA  DOS   SPRINTS,  OS  PROGRAMADORES  E\n    ATIVIDADES DO PRODUCT BACKLOG CADASTRADOS.");
	printf("\n\n\n--------------------------------------------------\n SOBRE O SISBACKLOG\n--------------------------------------------------\n");
	printf("\n DESENVOLVEDORES:\n\n 1. ADRIANA KARLA SANTANA\n 2. EDUARDO OLIVEIRA\n 3. GABRIELLE MACIEL\n 4. IGOR FERNANDES\n 5. MONIQUE ROCHA\n 6. RICARDO CHAMY\n\n ");
	system("pause");
}

void layoutHeader(){
	system("cls");
	printf("\n--------------------------------------------------\n\n\t\tS I S B A C K L O G\n\n\t     GERENCIADOR DE ATIVIDADES\n");	
}

void validaAcesso(){
	char longinAdmin[20] = "ADMIN"; // login e senha inicializado
	char login[20];
	int i=0, verificaLogin = 0,senha, senhaAdmin = 123; // 0 não existe.
	FILE *pUsu;
	cadUsuario cadUsu;
	
	do{
		layoutHeader();
		printf("\n\t\t HOJE: ");
		system("date/t");
		printf("\t\t HORA: ");
		system("time/t");
		printf("\n--------------------------------------------------\n");
		printf("\n\n\t\tLOGIN: ");
		fflush(stdin);
		gets(login);
		strupr(login);
		printf("\n\n\t\tSENHA: ");
		scanf("%d",&senha);
			
		if (strcmp(login, "ADMIN") == 0){ 
			if(senha == senhaAdmin){
				verificaLogin = 1; // validou senha
				menuPrincipal(); //Menu Administrador
			}
			else{
				verificaLogin = 0;
				printf("\n\n\t\tSENHA INVALIDA!\n\n     ");
				system("pause");
			}
		}
		
		if(strcmp(login, "ADMIN") == 1){
			pUsu=fopen("Usuario.txt","r+b");
			rewind(pUsu);
			fread(&cadUsu, sizeof(cadUsuario), 1, pUsu);
			while(!feof(pUsu)){
				if(!feof(pUsu)){
					if (strcmp(strupr(login), strupr(cadUsu.nome)) == 0){
						if(senha == cadUsu.senha){	
							verificaLogin=1;
							if (cadUsu.tipoAcesso == 1){
								verificaLogin = 1;
								menuPrincipal();
							}
							if (cadUsu.tipoAcesso == 2){
								menuSprintPrgramador(cadUsu.nome);
							}	
						}
						else{
							verificaLogin = 0;
						}
					}
					else{
						verificaLogin = 0;
					}
					fread(&cadUsu, sizeof(cadUsuario), 1, pUsu);
				}
			}
			fclose(pUsu);
			if (verificaLogin == 0){
				printf("\n\n\t   USUARIO OU SENHA INCORRETOS!\n\n     ");
				system("pause");
			}
		}
	}while(verificaLogin != 1);
}

//M E N U   P R I N C I P A L
void menuPrincipal(){
	int Op;
	do{
		layoutHeader();
		printf("\n--------------------------------------------------\n OPCOES DO MENU PRINCIPAL\n--------------------------------------------------\n");
		printf("\n\n [ 1] - GERENCIAR SPRINTS");
		printf("\n [ 2] - ATIVIDADES DO BACKLOG");
		printf("\n [ 3] - DEFINIR DATAS DE SPRINTS");
		printf("\n [ 4] - PROJETOS");
		printf("\n [ 5] - PROGRAMADORES");
		printf("\n [ 6] - TIPO DE ATIVIDADES");
		printf("\n [ 7] - USUARIOS E ACESSOS");
		printf("\n [ 8] - RELATORIOS");
		printf("\n [ 9] - REALIZAR NOVO LOGIN");
		printf("\n [10] - COMO UTILIZAR / SOBRE");
		printf("\n [ 0] - SAIR\n");		
		printf("\n INFORME OPCAO: ");
	    scanf("%d",&Op);
		switch(Op){
			case 1: menuGerenciarSprint();
					break;
			case 2: menuAtividade();
					break;
			case 3: menuSprint();
					break;
			case 4: menuProjeto();
					break;
			case 5: menuProgramador();
					break;
			case 6: menuTipoAtividade();
					break;
			case 7: menuUsuario();
					break;
			case 8: menuRelatorio();
					break;
			case 9: validaAcesso();
					break;
			case 10:helpSobre();
					break;
			case 0: exit(0);
					break;
		}
		if ((Op < 0) || (Op > 10)){
          	printf("\n OPCAO INVALIDA!\n ");
			system("pause");
		}
	}while (Op != 0);
}

//MENU - PROGRAMADOR
void menuProgramador(){
	int Op, verificaRegistro=0;
	do{
		layoutHeader();
	    printf("\n--------------------------------------------------\n OPCOES DE PROGRAMADORES\n--------------------------------------------------\n");
		printf("\n\n [1] - LISTAR");
		printf("\n [2] - CADASTRAR");
		printf("\n [3] - ALTERAR");
		printf("\n [4] - EXCLUIR");
		printf("\n [0] - VOLTAR MENU PRINCIPAL\n");		
		printf("\n INFORME OPCAO: ");
        verificaRegistro = verificaProgramadorCadastro();
		scanf("%d",&Op);
        switch(Op){
			case 1: if (verificaRegistro > 0)
						listarProgramador();
					else{
						printf("\n\n SEM REGISTRO CADASTRADO! \n ");
						system("pause");
					}
					break;
					
			case 2: cadastrarProgramador();
					break;
					
			case 3: if (verificaRegistro > 0)
						alterarProgramador();
					else{
						printf("\n\n SEM REGISTRO CADASTRADO! \n ");
						system("pause");
					}
					break;
					
			case 4: if (verificaRegistro > 0)
						excluirProgramador();
					else{
						printf("\n\n SEM REGISTRO CADASTRADO! \n ");
						system("pause");
					}
					break;
		
		} 
		
		if ((Op < 0) || (Op > 4)){
          	printf("\n OPCAO INVALIDA!\n ");
			system("pause");
		}
	}while(Op!=0);
}

//MENU - SPRINT
void menuSprint(){
	int Op, verificaRegistro=0;
	do{
		layoutHeader();
	    printf("\n--------------------------------------------------\n OPCOES DE SPRINT\n--------------------------------------------------\n");
		printf("\n\n [1] - LISTAR");
		printf("\n [2] - CADASTRAR");
		printf("\n [3] - ALTERAR");
		printf("\n [4] - EXCLUIR");
		printf("\n [0] - VOLTAR MENU PRINCIPAL\n");		
		printf("\n INFORME OPCAO: ");
        verificaRegistro = verificaSprintCadastro();
		scanf("%d",&Op);
        switch(Op){
			case 1: if (verificaRegistro > 0)
						listarSprint();
					else{
						printf("\n\n SEM REGISTRO CADASTRADO! \n ");
						system("pause");
					}
					break;
					
			case 2: cadastrarSprint();
					break;
					
			case 3: if (verificaRegistro > 0)
						alterarSprint();
					else{
						printf("\n\n SEM REGISTRO CADASTRADO! \n ");
						system("pause");
					}
					break;
					
			case 4: if (verificaRegistro > 0)
						excluirSprint();
					else{
						printf("\n\n SEM REGISTRO CADASTRADO! \n ");
						system("pause");
					}
					break;
		
		} 
		
		if ((Op < 0) || (Op > 4)){
          	printf("\n OPCAO INVALIDA!\n ");
			system("pause");
		}
	}while(Op!=0);	
}

//MENU - USUARIO
void menuUsuario(){
	int Op, verificaRegistro=0;
	do{
		layoutHeader();
	    printf("\n--------------------------------------------------\n OPCOES DE USUARIOS\n--------------------------------------------------\n");
		printf("\n\n [1] - LISTAR");
		printf("\n [2] - CADASTRAR");
		printf("\n [3] - ALTERAR");
		printf("\n [4] - EXCLUIR");
		printf("\n [0] - VOLTAR MENU PRINCIPAL\n");		
		printf("\n INFORME OPCAO: ");
        verificaRegistro = verificaUsuarioCadastro();
		scanf("%d",&Op);
        switch(Op){
			case 1: if (verificaRegistro > 0)
						listarUsuario();
					else{
						printf("\n\n SEM REGISTRO CADASTRADO! \n ");
						system("pause");
					}
					break;
					
			case 2: cadastrarUsuario();
					break;
					
			case 3: if (verificaRegistro > 0)
						alterarUsuario();
					else{
						printf("\n\n SEM REGISTRO CADASTRADO! \n ");
						system("pause");
					}
					break;
					
			case 4: if (verificaRegistro > 0)
						excluirUsuario();
					else{
						printf("\n\n SEM REGISTRO CADASTRADO! \n ");
						system("pause");
					}
					break;
		
		} 
		
		if ((Op < 0) || (Op > 4)){
          	printf("\n OPCAO INVALIDA!\n ");
			system("pause");
		}
	}while(Op!=0);	
}

//MENU - TIPO DE ATIVIDADE
void menuTipoAtividade(){
	int Op, verificaRegistro=0;
	do{
		layoutHeader();
	    printf("\n--------------------------------------------------\n OPCOES DE TIPO DE ATIVIDADE\n--------------------------------------------------\n");
		printf("\n\n [1] - LISTAR");
		printf("\n [2] - CADASTRAR");
		printf("\n [3] - ALTERAR");
		printf("\n [4] - EXCLUIR");
		printf("\n [0] - VOLTAR MENU PRINCIPAL\n");		
		printf("\n INFORME OPCAO: ");
        verificaRegistro = verificaTipoAtividadeCadastro();
		scanf("%d",&Op);
        switch(Op){
			case 1: if (verificaRegistro > 0)
						listarTipoAtividade();
					else{
						printf("\n\n SEM REGISTRO CADASTRADO! \n ");
						system("pause");
					}
					break;
					
			case 2: cadastrarTipoAtividade();
					break;
					
			case 3: if (verificaRegistro > 0)
						alterarTipoAtividade();
					else{
						printf("\n\n SEM REGISTRO CADASTRADO! \n ");
						system("pause");
					}
					break;
					
			case 4: if (verificaRegistro > 0)
						excluirTipoAtividade();
					else{
						printf("\n\n SEM REGISTRO CADASTRADO! \n ");
						system("pause");
					}
					break;
		
		} 
		
		if ((Op < 0) || (Op > 4)){
          	printf("\n OPCAO INVALIDA!\n ");
			system("pause");
		}
	}while(Op!=0);	
}

//MENU - PROJETO
void menuProjeto(){
	int Op, verificaRegistro=0;
	do{
		layoutHeader();
	    printf("\n--------------------------------------------------\n OPCOES DE PROJETOS\n--------------------------------------------------\n");
		printf("\n\n [1] - LISTAR");
		printf("\n [2] - CADASTRAR");
		printf("\n [3] - ALTERAR");
		printf("\n [4] - EXCLUIR");
		printf("\n [0] - VOLTAR MENU PRINCIPAL\n");		
		printf("\n INFORME OPCAO: ");
        verificaRegistro = verificaProjetoCadastro();
		scanf("%d",&Op);
        switch(Op){
			case 1: if (verificaRegistro > 0)
						listarProjeto();
					else{
						printf("\n\n SEM REGISTRO CADASTRADO! \n ");
						system("pause");
					}
					break;
					
			case 2: cadastrarProjeto();
					break;
					
			case 3: if (verificaRegistro > 0)
						alterarProjeto();
					else{
						printf("\n\n SEM REGISTRO CADASTRADO! \n ");
						system("pause");
					}
					break;
					
			case 4: if (verificaRegistro > 0)
						excluirProjeto();
					else{
						printf("\n\n SEM REGISTRO CADASTRADO! \n ");
						system("pause");
					}
					break;
		
		} 
		
		if ((Op < 0) || (Op > 4)){
          	printf("\n OPCAO INVALIDA!\n ");
			system("pause");
		}
	}while(Op!=0);	
}

//MENU - ATIVIDADE BACKLOG
void menuAtividade(){
	int Op, verificaRegistroProj=0,verificaRegistroTipoAtiv;
	do{
		layoutHeader();
	    printf("\n--------------------------------------------------\n OPCOES DE ATIVIDADES DO BACKLOG\n--------------------------------------------------\n");
		printf("\n\n [1] - LISTAR");
		printf("\n [2] - CADASTRAR");
		printf("\n [3] - ALTERAR");
		printf("\n [4] - EXCLUIR");
		printf("\n [0] - VOLTAR MENU PRINCIPAL\n");		
		printf("\n INFORME OPCAO: ");
		scanf("%d",&Op);
		if ((Op > 0)  && (((verificaRegistroProj = verificaProjetoCadastro()) == 0) && ((verificaRegistroTipoAtiv = verificaTipoAtividadeCadastro()) == 0))){
			printf("\n\n PARA INSERIR, VISUALIZAR, ALTERAR OU EXCLUIR UMA ATIVIDADES DO BACKLOG \n E' NECESSARIO QUE PROJETOS E TIPO DE ATIVIDADES ESTEJAM CADASTRADOS.\n ");
			system("pause");	
		}
		else{			
			switch(Op){
				case 1: listarAtividade();
						break;
				case 2: cadastrarAtividade();
						break;
				case 3: alterarAtividade();
						break;
				case 4: excluirAtividade();
						break;
			} 
			if ((Op < 0) || (Op > 4)){
				printf("\n OPCAO INVALIDA!\n ");
				system("pause");
			}
		}
		
	}while(Op!=0);
}

//MENU - GERENCIAR SPRINT
void menuGerenciarSprint(){
	int Op, verificaRegistroSp=0, verificaRegistroProg=0, verificaRegistroAtiv=0;
	do{
		layoutHeader();
	    printf("\n--------------------------------------------------\n GERENCIAMENTO DE SPRINTS\n--------------------------------------------------\n");
		printf("\n\n [1] - LISTAR ATIVIDADES POR SPRINT");
		printf("\n [2] - SELECIONAR ATIVIDADES PARA SPRINT (SPRINT PLANNING)");
		printf("\n [3] - PERCENTUAL DE ATIVIDADES (DAILY MEETING)");
		printf("\n [0] - VOLTAR MENU PRINCIPAL\n");		
		printf("\n INFORME OPCAO: ");
        scanf("%d",&Op);
        if ((Op > 0)  && (((verificaRegistroSp = verificaSprintCadastro()) == 0) || ((verificaRegistroProg = verificaProgramadorCadastro()) == 0) || ((verificaRegistroAtiv = verificaAtividadeCadastro()) ==  0))){
			printf("\n\n PARA GERENCIAR OS SPRINTS E' NECESSARIO QUE\n DATAS DOS SPRINTS, PROGRAMADORES, E ATIVIDADES DO BACKLOG\n ESTEJAM CADASTRADOS.\n ");
			system("pause");	
		}
		else{			
	        switch(Op){
				case 1: listarAtividadesDoSprint();
						break;
				case 2: selecionarAtividadesSprint();
						break;
				case 3: dailyMeeting();
						break;
			}
			if ((Op < 0) || (Op > 3)){
          		printf("\n OPCAO INVALIDA!\n ");
				system("pause");
			}
		}
	}while(Op!=0);	
}

//MENU - ATIVIDADES PROGRAMADOR
void menuSprintPrgramador(char nomeProgramador[50]){
	int Op, verificaRegistroSp=0, verificaRegistroProg=0, verificaRegistroAtiv=0;
	do{
		layoutHeader();
	    printf("\n--------------------------------------------------\n MENU DE OPCOES DO PROGRAMADOR\n--------------------------------------------------\n");
		printf("\n\n [1] - LISTAR ATIVIDADES POR SPRINT");
		printf("\n [2] - REALIZAR NOVO LOGIN");
		printf("\n [0] - SAIR\n");		
		printf("\n INFORME OPCAO: ");
        scanf("%d",&Op);
        if (((verificaRegistroSp = verificaSprintCadastro()) == 0) || ((verificaRegistroProg = verificaProgramadorCadastro()) == 0) || ((verificaRegistroAtiv = verificaAtividadeCadastro()) ==  0)){
			printf("\n\n SO E' PERMITIDA A VISUALIZACAO DE SUAS ATIVIDADES\n APOS O GERENTE DE PROJETOS ATRIBUILAS A VOCE.\n ");
			system("pause");	
		}
		else{			
	        switch(Op){
				case 1: listarAtividadesDoProgramador(nomeProgramador);
						break;
				case 2: validaAcesso();
						break;
				case 0: exit(0);
						break;
			}
			if ((Op < 0) || (Op > 3)){
          		printf("\n OPCAO INVALIDA!\n ");
				system("pause");
			}
		}
	}while(Op!=0);	
}

//MENU - ATIVIDADES PROGRAMADOR
void menuRelatorio(){
	int Op, verificaRegistroSp=0, verificaRegistroProg=0, verificaRegistroAtiv=0;
	do{
		layoutHeader();
	    printf("\n--------------------------------------------------\n OPCOES DE RELATORIOS\n--------------------------------------------------\n");
		printf("\n\n [1] - ATIVIDADES CONCLUIDAS");
		printf("\n [2] - ATIVIDADES EM DESENVOLVIMENTO");
		printf("\n [3] - ATIVIDADES EM NAO REALIZADAS");
		printf("\n [0] - VOLTAR AO MENU PRINCIPAL\n");		
		printf("\n INFORME OPCAO: ");
        scanf("%d",&Op);
        if (((verificaRegistroSp = verificaSprintCadastro()) == 0) || ((verificaRegistroProg = verificaProgramadorCadastro()) == 0) || ((verificaRegistroAtiv = verificaAtividadeCadastro()) ==  0)){
			printf("\n\n SO E' PERMITIDA A VISUALIZACAO DE RELATORIOS\n APOS O SELECAO DE ATIVIDADES DOS SPRINTS.\n ");
			system("pause");	
		}
		else{			
	        switch(Op){
				case 1: listarAtividadesPorStatus("CONCLUIDA");
						break;
				case 2: listarAtividadesPorStatus("EM DESENVOLVIMENTO");
						break;
				case 3: listarAtividadesPorStatus("NAO REALIZADA");
						break;
				case 0: break;
			}
			if ((Op < 0) || (Op > 3)){
          		printf("\n OPCAO INVALIDA!\n ");
				system("pause");
			}
		}
	}while(Op!=0);	
}

//VALIDAÇÃO - VERIFICA SE EXISTE PROGRAMADOR CADASTRADO
int verificaProgramadorCadastro(){
	FILE *pProg;
	long verificaRegistros=0;
	cadProgramador cadProg;
	pProg=fopen("Programador.txt","r");
	if(pProg == NULL){
		verificaRegistros = 0;
	}
	else{
		fseek(pProg, 0, SEEK_END);
    	verificaRegistros = ftell(pProg);
		fclose(pProg);
	}
	return verificaRegistros;
}

//VALIDAÇÃO - VERIFICA SE EXISTE PROGRAMADOR CADASTRADO
int verificaProjetoCadastro(){
	FILE *pProj;
	long verificaRegistros=0;
	cadProjeto cadProj;
	pProj=fopen("Projeto.txt","r");
	if(pProj == NULL){
		verificaRegistros = 0;
	}
	else{
		fseek(pProj, 0, SEEK_END);
    	verificaRegistros = ftell(pProj);
		fclose(pProj);
	}
	return verificaRegistros;
}

//VALIDAÇÃO - VERIFICA SE EXISTE SPRINT CADASTRADO
int verificaSprintCadastro(){
	FILE *pSp;
	long verificaRegistros=0;
	cadSprint cadSp;
	pSp=fopen("Sprint.txt","r");
	if(pSp == NULL){
		verificaRegistros = 0;
	}
	else{
		fseek(pSp, 0, SEEK_END);
    	verificaRegistros = ftell(pSp);
		fclose(pSp);
	}
	return verificaRegistros;
}

//VALIDAÇÃO - VERIFICA SE EXISTE SPRINT CADASTRADO
int verificaTipoAtividadeCadastro(){
	FILE *pTipoAtiv;
	long verificaRegistros=0;
	cadTipoAtividade cadTipoAtiv;
	pTipoAtiv=fopen("TipoAtividade.txt","r");
	if(pTipoAtiv == NULL){
		verificaRegistros = 0;
	}
	else{
		fseek(pTipoAtiv, 0, SEEK_END);
    	verificaRegistros = ftell(pTipoAtiv);
		fclose(pTipoAtiv);
	}
	return verificaRegistros;
}

//VALIDAÇÃO - VERIFICA SE EXISTE  USUARIO CADASTRADO
int verificaUsuarioCadastro(){
	FILE *pUsu;
	long verificaRegistros=0;
	cadUsuario cadUsu;
	pUsu=fopen("Usuario.txt","r");
	if(pUsu == NULL){
		verificaRegistros = 0;
	}
	else{
		fseek(pUsu, 0, SEEK_END);
    	verificaRegistros = ftell(pUsu);
		fclose(pUsu);
	}
	return verificaRegistros;
}

//VALIDAÇÃO - VERIFICA SE EXISTE ATIVIDADES DO BACKLOG CADASTRADO
int verificaAtividadeCadastro(){
	FILE *pAtiv;
	long verificaRegistros=0;
	cadAtividade cadAtiv;
	pAtiv=fopen("Atividade.txt","r");
	if(pAtiv == NULL){
		verificaRegistros = 0;
	}
	else{
		fseek(pAtiv, 0, SEEK_END);
    	verificaRegistros = ftell(pAtiv);
		fclose(pAtiv);
	}
	return verificaRegistros;
}

//********************* C R U D   U S U Á R I O *********************
//Cadastrar
void cadastrarUsuario(){
    int Op, tipoAcesso;
    cadUsuario cadUsu;
    FILE *pUsu;
    pUsu=fopen("Usuario.txt","a+");
    if(pUsu==NULL)
    {
		layoutHeader();
		printf("\n--------------------------------------------------\n CADASTRO DE USUARIOS\n--------------------------------------------------\n");
		printf("\n\n ERRO, NAO FOI POSSIVEL ABRIR O ARQUIVO. ARQUIVO SEM REGISTRO.\n");
		system("pause");
	}
    else{
        do{
			layoutHeader();
            printf("\n--------------------------------------------------\n CADASTRO DE USUARIOS\n--------------------------------------------------\n");
			printf("\n INFORME OS DADOS");
            printf("\n\n ID: ");
            scanf("%d",&cadUsu.id);
            printf("\n NOME: ");
            fflush(stdin);
            gets(cadUsu.nome);
            strupr(cadUsu.nome);
            printf("\n SENHA [APENAS NUMEROS]: ");
           	scanf("%d",&cadUsu.senha);
           	printf("\n TIPO DE USUARIO [1] ADMINISTRADOR OU  [2] PROGRAMADOR: ");
           	scanf("%d",&tipoAcesso);
           	do{
				if ((tipoAcesso < 1) || (tipoAcesso > 2)){
					printf("\n\n OPCAO INVALIDA!\n ");
					system("pause");
					printf("\n TIPO DE USUARIO [1] ADMINISTRADOR OU  [2] PROGRAMADOR: ");
           			scanf("%d",&tipoAcesso);
				}
			}while((tipoAcesso < 1) || (tipoAcesso > 2));
			cadUsu.tipoAcesso = tipoAcesso;
			
            fwrite(&cadUsu, sizeof(cadUsu), 1, pUsu);

			do{ 
				layoutHeader();
				printf("\n--------------------------------------------------\n CADASTRO DE USUARIOS\n--------------------------------------------------\n");
				printf("\n\n DESEJA REALIZAR UM NOVO CADASTRO?\n\n [1] SIM\n [0] NAO\n\n INFORME OPCAO: ");
            	scanf("%d",&Op);
          		if ((Op < 0) || (Op > 1)){
          			printf("\n OPCAO INVALIDA!\n");
					system("pause");
				}
			}while((Op < 0) || (Op > 1));
		}while(Op!=0);
    }
    fclose(pUsu);
}
//Listar
void listarUsuario(){
	FILE *pUsu;
	cadUsuario cadUsu;
	pUsu=fopen("Usuario.txt","r+b");
	if(pUsu == NULL){
		layoutHeader();
		printf("\n--------------------------------------------------\n LISTAGEM DE USUARIOS CADASTRADOS\n--------------------------------------------------\n");
		printf("\n\n ERRO, NAO FOI POSSIVEL ABRIR O ARQUIVO. ARQUIVO SEM REGISTRO.\n\n ");
		system("pause");
	}
	else{
		layoutHeader();
		rewind(pUsu);
		fread(&cadUsu, sizeof(cadUsuario), 1, pUsu);
		printf("\n--------------------------------------------------\n LISTAGEM DE USUARIOS CADASTRADOS\n--------------------------------------------------\n");
		printf("\n\n ID\t NOME\t\t TIPO DE USUARIO\n--------------------------------------------------");
		while(!feof(pUsu)){
			if(!feof(pUsu)){
				if (cadUsu.tipoAcesso == 1)
					printf("\n %d\t %s\t\t ADMINISTRADOR\n",cadUsu.id,cadUsu.nome);
				if (cadUsu.tipoAcesso == 2) 
					printf("\n %d\t %s\t\t PROGRAMADOR\n",cadUsu.id,cadUsu.nome);
				
				fread(&cadUsu, sizeof(cadUsuario), 1, pUsu);
			}
		}
		printf("\n\n");
		system("pause");
		fclose(pUsu);
	}
}
//Alterar
void alterarUsuario(){
    cadUsuario cadUsu;
	int i=0,Op, tipoAcesso;
	char nome[50];
	FILE *pUsu;
	int verificaCadastro = 0; //Boleana para verificar se registro esta cadastrado ou não
	
	pUsu=fopen("Usuario.txt","rb+");
	
	if(pUsu == NULL){
		layoutHeader();
		printf("\n--------------------------------------------------\n ALTERACAO DE DADOS USUARIO CADASTRADO\n--------------------------------------------------\n");	
		printf("\n\n ERRO, NAO FOI POSSIVEL ABRIR O ARQUIVO. ARQUIVO SEM REGISTRO.\n\n ");
		system("pause");
	}
	else{
		layoutHeader();
		printf("\n--------------------------------------------------\n ALTERACAO DE DADOS USUARIO CADASTRADO\n--------------------------------------------------\n");	
		printf(" \n\n INFORME O NOME DO USUARIO QUE DESEJA ALTERAR: ");
	    fflush(stdin);
	    gets(nome);
	    verificaCadastro = 0;
	    rewind(pUsu);
		while(!feof(pUsu)){
			fread(&cadUsu,sizeof(cadUsuario),1,pUsu);
	        if(!feof(pUsu)){
				if(strcmp(cadUsu.nome,strupr(nome))==0){
	            	printf("\n DADOS ATUAIS\n--------------------------------------------------\n");
	            	printf(" ID: %d\n", cadUsu.id);
		        	printf(" NOME: %s\n", cadUsu.nome);   
		        	printf(" SENHA: %d\n", cadUsu.senha);
					if (cadUsu.tipoAcesso == 1)
						printf(" TIPO DE USUARIO: ADMINISTRADOR\n--------------------------------------------------");   
					if (cadUsu.tipoAcesso == 2)
						printf(" TIPO DE USUARIO: PROGRAMADOR\n--------------------------------------------------");   
					verificaCadastro = 1;
					printf("\n\n INFORME NOVOS DADOS\n");
		        	printf("\n ID: ");
		        	scanf("%d",&cadUsu.id);
		        	printf(" \n NOME: ");
					fflush(stdin);
		        	gets(cadUsu.nome);
		        	strupr(cadUsu.nome);
		        	printf("\n SENHA [APENAS NUMEROS]: ");
		           	scanf("%d",&cadUsu.senha);
		           	printf("\n TIPO DE USUARIO [1] ADMINISTRADOR OU  [2] PROGRAMADOR: ");
		           	scanf("%d",&tipoAcesso);
		           	do{
						if ((tipoAcesso < 1) || (tipoAcesso > 2)){
							printf("\n\n OPCAO INVALIDA!\n ");
							system("pause");
							printf("\n TIPO DE USUARIO [1] ADMINISTRADOR OU  [2] PROGRAMADOR: ");
		           			scanf("%d",&tipoAcesso);
						}
					}while((tipoAcesso < 1) || (tipoAcesso > 2));
					cadUsu.tipoAcesso = tipoAcesso;
		        	fseek(pUsu,i*sizeof(cadUsuario), SEEK_SET);
		        	fwrite(&cadUsu, sizeof(cadUsuario),1,pUsu);
					break;
	        	}
			}
			i++;		
		}
		if (verificaCadastro == 0){
		    printf("\n REGISTRO NAO ENCONTRADO!\n ");
		    system("pause");
		}  
		fclose(pUsu);
		
		do{ 
			layoutHeader();
			printf("\n--------------------------------------------------\n ALTERACAO DE DADOS USUARIO CADASTRADO\n--------------------------------------------------\n");	
			printf("\n\n DESEJA REALIZAR UMA NOVA NOVA BUSCAR?\n\n [1] SIM\n [0] NAO\n\n INFORME OPCAO: ");
	        scanf("%d",&Op);
	        if ((Op < 0) || (Op > 1)){
	          	printf("\n OPCAO INVALIDA!\n");
				system("pause");
			}
		}while((Op < 0) || (Op > 1));
		if (Op == 1)
			alterarUsuario();
	}
}
//Excluir
void excluirUsuario(){
	char nome[50];
	FILE *pUsu;
	cadUsuario cadUsu, *vetUsu;
	    
	int cont=0,i=0,verificaCadastro=0, Op;
	vetUsu=(cadUsuario*)malloc(1000*sizeof(cadUsuario));
	pUsu=fopen("Usuario.txt","rb+");
	if(pUsu == NULL){
		layoutHeader();
		printf("\n--------------------------------------------------\n EXCLUSAO DE REGISTROS DO USUARIO \n--------------------------------------------------\n");	
		printf("\n\n ERRO, NAO FOI POSSIVEL ABRIR O ARQUIVO. ARQUIVO SEM REGISTRO.\n\n ");
		system("pause");
	}
	else{
		layoutHeader();
		printf("\n--------------------------------------------------\n EXCLUSAO DE REGISTROS DO USUARIO \n--------------------------------------------------\n");	
		printf(" \n\n INFORME O NOME DO USUARIO QUE DESEJA EXCLUIR: ");
	    fflush(stdin);
	    gets(nome);
		rewind(pUsu);
		while(!feof(pUsu)){
			fread(&cadUsu,sizeof(cadUsuario),1,pUsu);
			if(!feof(pUsu)){
				if(strcmp(strupr(cadUsu.nome),strupr(nome))==0){
					printf("\n DADOS EXCLUIDOS COM SUCESSO!\n ");
					verificaCadastro=1;
					system("pause");		
				}
				else{
					strcpy(strupr(vetUsu[i].nome),strupr(cadUsu.nome));
					(vetUsu[i].id = cadUsu.id);
					(vetUsu[i].senha = cadUsu.senha);
					(vetUsu[i].tipoAcesso = cadUsu.tipoAcesso);
					i++;
					cont++;				
			    }
			}
		}
		fclose(pUsu);
		pUsu=fopen("Usuario.txt","wb");
		fwrite(vetUsu,sizeof(cadUsuario),i,pUsu);
		fclose(pUsu);
		free(vetUsu);  
		
		if (verificaCadastro == 0){
		    printf("\n REGISTRO NAO ENCONTRADO!\n ");
		    system("pause");
		}  
		
		do{ 
			layoutHeader();
			printf("\n--------------------------------------------------\n EXCLUSAO DE REGISTROS DO USUARIO \n--------------------------------------------------\n");	
			printf("\n\n DESEJA REALIZAR UMA NOVA NOVA BUSCA?\n\n [1] SIM\n [0] NAO\n\n INFORME OPCAO: ");
	        scanf("%d",&Op);
	        if ((Op < 0) || (Op > 1)){
	          	printf("\n OPCAO INVALIDA!\n");
				system("pause");
			}
		}while((Op < 0) || (Op > 1));
		if (Op == 1)
			excluirUsuario();
	}             
}

//********************* C R U D   A T I V I D A D E   B A C K L O G *********************
//Cadastrar
void cadastrarAtividade(){
    int Op, OpAux=0, nivelPrioridade,i,verificaAux=0;
    cadAtividade cadAtiv;
    cadProjeto cadProj;
    cadTipoAtividade cadTipoAtiv;
    
	FILE *pAtiv,*pProj,*pTipoAtiv;
    pAtiv=fopen("Atividade.txt","a+");
	if(pAtiv==NULL)
    {
		layoutHeader();
		printf("\n--------------------------------------------------\n CADASTRO DE ATIVIDADES(PRODUCT BACKLOG)\n--------------------------------------------------\n");
		printf("\n\n ERRO, NAO FOI POSSIVEL ABRIR O ARQUIVO. ARQUIVO SEM REGISTRO.\n");
		system("pause");
	}
    else{
        do{
			layoutHeader();
            printf("\n--------------------------------------------------\n CADASTRO DE ATIVIDADES(PRODUCT BACKLOG)\n--------------------------------------------------\n");
			printf("\n INFORME OS DADOS DA ATIVIDADE");
            printf("\n\n ID: ");
            scanf("%d",&cadAtiv.id);
            printf("\n DESCRICAO DETALHADA: \n ");
            fflush(stdin);
            gets(cadAtiv.descricao);
            strupr(cadAtiv.descricao);
            
			//Lista Tipo de Atividades
			OpAux=0;
			pTipoAtiv=fopen("TipoAtividade.txt","r+b");
			rewind(pTipoAtiv);
			fread(&cadTipoAtiv, sizeof(cadTipoAtividade), 1, pTipoAtiv);
			printf("\n LISTAGEM DE TIPO DE ATIVIDADES\n ID\t NOME\n--------------------------------------------------\n");
			while(!feof(pTipoAtiv)){
				if(!feof(pTipoAtiv)){
					printf(" %d\t %s\n", cadTipoAtiv.id,cadTipoAtiv.nome);
					fread(&cadTipoAtiv, sizeof(cadTipoAtividade), 1, pTipoAtiv);
				}
			}
			do{
				printf("\n ESCOLHA O ID DO TIPO DE ATIVIDADE: ");
				scanf("%d",&OpAux);
				verificaAux = 0;
			    pTipoAtiv=fopen("TipoAtividade.txt","r+b");
				rewind(pTipoAtiv);
				while(!feof(pTipoAtiv)){
					fread(&cadTipoAtiv,sizeof(cadTipoAtividade),1,pTipoAtiv);
			        if(!feof(pTipoAtiv)){
						if(cadTipoAtiv.id == OpAux){
			            	verificaAux = 1;
							strcpy(cadAtiv.cadTipoAtiv.nome,strupr(cadTipoAtiv.nome));
							fclose(pTipoAtiv);
							break;
			        	}
					}
					i++;
				}
				if (verificaAux == 0){
				    printf("\n OPCAO INVALIDA!\n ");
				    system("pause");
				}  
				fclose(pTipoAtiv);
			}while(verificaAux == 0);
			
			
			do{
				printf("\n NIVEIS DE PRIORIDADE\n [1] ALTA\n [2] MEDIA\n [3] BAIXA \n ESCOLHA O NIVEL: ");
           		scanf("%d",&nivelPrioridade);
				if ((nivelPrioridade < 1) || (nivelPrioridade > 3)){
					printf("\n\n OPCAO INVALIDA!\n ");
					system("pause");
				}
			}while((nivelPrioridade < 1) || (nivelPrioridade > 3));
			cadAtiv.prioridade = nivelPrioridade;
			
			//Lista Projetos
			OpAux=0;
			pProj=fopen("Projeto.txt","r+b");
			rewind(pProj);
			fread(&cadProj, sizeof(cadProjeto), 1, pProj);
			printf("\n LISTAGEM DE PROJETOS\n ID\t NOME\n--------------------------------------------------\n");
			while(!feof(pProj)){
				if(!feof(pProj)){
					printf(" %d\t %s\n", cadProj.id,cadProj.nome);
					fread(&cadProj, sizeof(cadProjeto), 1, pProj);
				}
			}
			fclose(pProj);
			
			do{
				printf("\n ESCOLHA O ID DO PROJETO: ");
				scanf("%d",&OpAux);
				verificaAux = 0;
			    pProj=fopen("Projeto.txt","r+b");
				rewind(pProj);
				while(!feof(pProj)){
					fread(&cadProj,sizeof(cadProjeto),1,pProj);
			        if(!feof(pProj)){
						if(cadProj.id == OpAux){
			            	verificaAux = 1;
							strcpy(cadAtiv.cadProj.nome,strupr(cadProj.nome));
							fclose(pProj);
							break;
			        	}
					}
					i++;
				}
				if (verificaAux == 0){
				    printf("\n OPCAO INVALIDA!\n ");
				    system("pause");
				}  
				fclose(pProj);
			}while(verificaAux == 0);
			
						
	        fwrite(&cadAtiv, sizeof(cadAtiv), 1, pAtiv);
			printf("\n\n ATIVIDADE CADASTRADA COM SUCESSO!\n\n ");
			system("pause");
			do{ 
				layoutHeader();
				printf("\n--------------------------------------------------\n CADASTRO DE ATIVIDADES(PRODUCT BACKLOG)\n--------------------------------------------------\n");
				printf("\n\n DESEJA REALIZAR UM NOVO CADASTRO?\n\n [1] SIM\n [0] NAO\n\n INFORME OPCAO: ");
	            scanf("%d",&Op);
	          	if ((Op < 0) || (Op > 1)){
	          		printf("\n OPCAO INVALIDA!\n");
					system("pause");
				}
			}while((Op < 0) || (Op > 1));
		}while(Op!=0);
    }
    fclose(pAtiv);
}
//Listar
void listarAtividade(){
	FILE *pAtiv;
	cadAtividade cadAtiv;
	pAtiv=fopen("Atividade.txt","r+b");
	if(pAtiv == NULL){
		layoutHeader();
		printf("\n--------------------------------------------------\n BACKLOG DE ATIVIDADES\n--------------------------------------------------\n");
		printf("\n\n ERRO, NAO FOI POSSIVEL ABRIR O ARQUIVO. ARQUIVO SEM REGISTRO.\n\n ");
		system("pause");
	}
	else{
		layoutHeader();
		rewind(pAtiv);
		fread(&cadAtiv, sizeof(cadAtividade), 1, pAtiv);
		printf("\n--------------------------------------------------\n BACKLOG DE ATIVIDADES\n--------------------------------------------------\n\n");
		while(!feof(pAtiv)){
			if(!feof(pAtiv)){
				printf("\n ATIVIDADE ID [%d]", cadAtiv.id);
				printf("\n\n PROJETO: %s", cadAtiv.cadProj.nome);
				printf("\n\n DESCRICAO: \n %s", cadAtiv.descricao);
				printf("\n\n PRIORIDADE: %d", cadAtiv.prioridade);
				printf("\n\n TIPO DE ATIVIDADE: %s\n--------------------------------------------------\n", cadAtiv.cadTipoAtiv.nome);
				fread(&cadAtiv, sizeof(cadAtividade), 1, pAtiv);
			}
		}
		printf("\n\n");
		system("pause");
		fclose(pAtiv);
	}
}
//Alterar
void alterarAtividade(){
    cadAtividade cadAtiv;
	cadProjeto cadProj;
    cadTipoAtividade cadTipoAtiv;
    
	int i=0,Op,id,nivelPrioridade,OpAux=0,verificaAux=0;;
	FILE *pAtiv,*pProj,*pTipoAtiv;;
	int verificaCadastro = 0; //Boleana para verificar se registro esta cadastrado ou não
	
	pAtiv=fopen("Atividade.txt","rb+");
	
	if(pAtiv == NULL){
		layoutHeader();
		printf("\n--------------------------------------------------\n ALTERACAO DE DADOS DE ATIVIDADE CADASTRADA\n--------------------------------------------------\n");	
		printf("\n\n ERRO, NAO FOI POSSIVEL ABRIR O ARQUIVO. ARQUIVO SEM REGISTRO.\n\n ");
		system("pause");
	}
	else{
		layoutHeader();
		printf("\n--------------------------------------------------\n ALTERACAO DE DADOS DE ATIVIDADE CADASTRADA\n--------------------------------------------------\n");	
		printf(" \n\n INFORME O ID DA ATIVIDADE QUE DESEJA ALTERAR: ");
	    fflush(stdin);
	    scanf("%d",&id);
	    verificaCadastro = 0;
	    rewind(pAtiv);
		while(!feof(pAtiv)){
			fread(&cadAtiv,sizeof(cadAtividade),1,pAtiv);
	        if(!feof(pAtiv)){
				if(cadAtiv.id == id){
	            	printf("\n ATIVIDADE ID [%d]", cadAtiv.id);
					printf("\n\n PROJETO: \n %s", cadAtiv.cadProj.nome);
					printf("\n\n DESCRICAO: \n %s", cadAtiv.descricao);
					printf("\n\n PRIORIDADE: %d", cadAtiv.prioridade);
					printf("\n\n TIPO ATIVIDADE: \n %s\n--------------------------------------------------\n\n", cadAtiv.cadTipoAtiv.nome);
		
		        	verificaCadastro = 1;
					printf("\n INFORME NOVOS DADOS\n");
					printf("\n\n ATIVIDADE ID [%d]\n",cadAtiv.id);
		            (cadAtiv.id = cadAtiv.id);
		            
					printf("\n DESCRICAO DETALHADA: \n ");
		            fflush(stdin);
		            gets(cadAtiv.descricao);
		            strupr(cadAtiv.descricao);
		            
		            //Lista Projetos
					OpAux=0;
					pProj=fopen("Projeto.txt","r+b");
					rewind(pProj);
					fread(&cadProj, sizeof(cadProjeto), 1, pProj);
					printf("\n LISTAGEM DE PROJETOS\n ID\t NOME\n--------------------------------------------------\n");
					while(!feof(pProj)){
						if(!feof(pProj)){
							printf(" %d\t %s\n", cadProj.id,cadProj.nome);
							fread(&cadProj, sizeof(cadProjeto), 1, pProj);
						}
					}
					fclose(pProj);
					
					do{
						printf("\n ESCOLHA O ID DO PROJETO: ");
						scanf("%d",&OpAux);
						verificaAux = 0;
					    pProj=fopen("Projeto.txt","r+b");
						rewind(pProj);
						while(!feof(pProj)){
							fread(&cadProj,sizeof(cadProjeto),1,pProj);
					        if(!feof(pProj)){
								if(cadProj.id == OpAux){
					            	verificaAux = 1;
									strcpy(cadAtiv.cadProj.nome,strupr(cadProj.nome));
									fclose(pProj);
									break;
					        	}
							}
						}
						if (verificaAux == 0){
						    printf("\n OPCAO INVALIDA!\n ");
						    system("pause");
						}  
						fclose(pProj);
					}while(verificaAux == 0);
					
					//Lista Tipo de Atividades
					OpAux=0;
					pTipoAtiv=fopen("TipoAtividade.txt","r+b");
					rewind(pTipoAtiv);
					fread(&cadTipoAtiv, sizeof(cadTipoAtividade), 1, pTipoAtiv);
					printf("\n LISTAGEM DE TIPO DE ATIVIDADES\n ID\t NOME\n--------------------------------------------------\n");
					while(!feof(pTipoAtiv)){
						if(!feof(pTipoAtiv)){
							printf(" %d\t %s\n", cadTipoAtiv.id,cadTipoAtiv.nome);
							fread(&cadTipoAtiv, sizeof(cadTipoAtividade), 1, pTipoAtiv);
						}
					}
					do{
						printf("\n ESCOLHA O ID DO TIPO DE ATIVIDADE: ");
						scanf("%d",&OpAux);
						verificaAux = 0;
					    pTipoAtiv=fopen("TipoAtividade.txt","r+b");
						rewind(pTipoAtiv);
						while(!feof(pTipoAtiv)){
							fread(&cadTipoAtiv,sizeof(cadTipoAtividade),1,pTipoAtiv);
					        if(!feof(pTipoAtiv)){
								if(cadTipoAtiv.id == OpAux){
					            	verificaAux = 1;
									strcpy(cadAtiv.cadTipoAtiv.nome,strupr(cadTipoAtiv.nome));
									fclose(pTipoAtiv);
									break;
					        	}
							}
						}
						if (verificaAux == 0){
						    printf("\n OPCAO INVALIDA!\n ");
						    system("pause");
						}  
						fclose(pTipoAtiv);
					}while(verificaAux == 0);
					
					
					do{
						printf("\n NIVEIS DE PRIORIDADE\n [1] ALTA\n [2] MEDIA\n [3] BAIXA \n ESCOLHA O NIVEL: ");
		           		scanf("%d",&nivelPrioridade);
						if ((nivelPrioridade < 1) || (nivelPrioridade > 3)){
							printf("\n\n OPCAO INVALIDA!\n ");
							system("pause");
						}
					}while((nivelPrioridade < 1) || (nivelPrioridade > 3));
					cadAtiv.prioridade = nivelPrioridade;
		        	//cadProg.situacaoAtivo = 1;
		        	fseek(pAtiv,i*sizeof(cadAtividade), SEEK_SET);
		        	fwrite(&cadAtiv, sizeof(cadAtividade),1,pAtiv);
					break;
		        
	        	}
			}
			i++;
		}
		if (verificaCadastro == 0){
		    printf("\n REGISTRO NAO ENCONTRADO!\n ");
		    system("pause");
		}  
		fclose(pAtiv);
		
		do{ 
			layoutHeader();
			printf("\n--------------------------------------------------\n ALTERACAO DE DADOS DE ATIVIDADE CADASTRADA\n--------------------------------------------------\n");	
			printf("\n\n DESEJA REALIZAR UMA NOVA NOVA BUSCAR?\n\n [1] SIM\n [0] NAO\n\n INFORME OPCAO: ");
	        scanf("%d",&Op);
	        if ((Op < 0) || (Op > 1)){
	          	printf("\n OPCAO INVALIDA!\n");
				system("pause");
			}
		}while((Op < 0) || (Op > 1));
		if (Op == 1)
			alterarAtividade();
	}
}
//Excluir
void excluirAtividade(){
	FILE *pAtiv;
	cadAtividade cadAtiv, *vetAtiv;
	    
	int cont=0,i=0,verificaCadastro=0, Op, id;
	vetAtiv=(cadAtividade*)malloc(1000*sizeof(cadAtividade));
	pAtiv=fopen("Atividade.txt","rb+");
	if(pAtiv == NULL){
		layoutHeader();
		printf("\n--------------------------------------------------\n EXCLUSAO DE REGISTROS DE ATIVIDADE \n--------------------------------------------------\n");	
		printf("\n\n ERRO, NAO FOI POSSIVEL ABRIR O ARQUIVO. ARQUIVO SEM REGISTRO.\n\n ");
		system("pause");
	}
	else{
		layoutHeader();
		printf("\n--------------------------------------------------\n EXCLUSAO DE REGISTROS DE ATIVIDADE \n--------------------------------------------------\n");	
		printf(" \n\n INFORME O ID DA ATIVIDADE QUE DESEJA EXCLUIR: ");
		scanf("%d",&id);
	    rewind(pAtiv);
		while(!feof(pAtiv)){
			fread(&cadAtiv,sizeof(cadAtividade),1,pAtiv);
			if(!feof(pAtiv)){
				if(cadAtiv.id == id){
					printf("\n DADOS EXCLUIDOS COM SUCESSO!\n ");
					verificaCadastro=1;
					system("pause");		
				}
				else{
					strcpy(strupr(vetAtiv[i].descricao),strupr(cadAtiv.descricao));
					strcpy(strupr(vetAtiv[i].cadProj.nome),strupr(cadAtiv.cadProj.nome));
					strcpy(strupr(vetAtiv[i].cadTipoAtiv.nome),strupr(cadAtiv.cadTipoAtiv.nome));
					(vetAtiv[i].id = cadAtiv.id);
					(vetAtiv[i].prioridade = cadAtiv.prioridade);
					i++;
					cont++;				
			    }
			}
		}
		fclose(pAtiv);
		pAtiv=fopen("Atividade.txt","wb");
		fwrite(vetAtiv,sizeof(cadAtividade),i,pAtiv);
		fclose(pAtiv);
		free(vetAtiv);  
		
		if (verificaCadastro == 0){
		    printf("\n REGISTRO NAO ENCONTRADO!\n ");
		    system("pause");
		}  
		
		do{ 
			layoutHeader();
			printf("\n--------------------------------------------------\n EXCLUSAO DE REGISTROS DO PROGRAMADOR \n--------------------------------------------------\n");	
			printf("\n\n DESEJA REALIZAR UMA NOVA NOVA BUSCA?\n\n [1] SIM\n [0] NAO\n\n INFORME OPCAO: ");
	        scanf("%d",&Op);
	        if ((Op < 0) || (Op > 1)){
	          	printf("\n OPCAO INVALIDA!\n");
				system("pause");
			}
		}while((Op < 0) || (Op > 1));
		if (Op == 1)
			excluirAtividade();
	}             
}

//********************* C R U D   P R O J E T O *********************
//Cadastrar
void cadastrarProjeto(){
    int Op;
    cadProjeto cadProj;
    FILE *pProj;
    pProj=fopen("Projeto.txt","a+");
    if(pProj==NULL)
    {
		layoutHeader();
		printf("\n--------------------------------------------------\n CADASTRO DE PROJETO\n--------------------------------------------------\n");
		printf("\n\n ERRO, NAO FOI POSSIVEL ABRIR O ARQUIVO. ARQUIVO SEM REGISTRO.\n");
		system("pause");
	}
    else{
        do{
			layoutHeader();
            printf("\n--------------------------------------------------\n CADASTRO DE PROJETO\n--------------------------------------------------\n");
			printf("\n INFORME OS DADOS");
            printf("\n\n ID: ");
            scanf("%d",&cadProj.id);
            printf("\n NOME: ");
            fflush(stdin);
            gets(cadProj.nome);
            strupr(cadProj.nome);;
            fwrite(&cadProj, sizeof(cadProj), 1, pProj);
            
			do{ 
				layoutHeader();
				printf("\n--------------------------------------------------\n CADASTRO DE PROJETO\n--------------------------------------------------\n");
				printf("\n\n DESEJA REALIZAR UM NOVO CADASTRO?\n\n [1] SIM\n [0] NAO\n\n INFORME OPCAO: ");
            	scanf("%d",&Op);
          		if ((Op < 0) || (Op > 1)){
          			printf("\n OPCAO INVALIDA!\n");
					system("pause");
				}
			}while((Op < 0) || (Op > 1));
		}while(Op!=0);
    }
    fclose(pProj);
}
//Listar
void listarProjeto(){
	FILE *pProj;
	cadProjeto cadProj;
	pProj=fopen("Projeto.txt","r+b");
	if(pProj == NULL){
		layoutHeader();
		printf("\n--------------------------------------------------\n LISTAGEM DE PROJETOS CADASTRADOS\n--------------------------------------------------\n");
		printf("\n\n ERRO, NAO FOI POSSIVEL ABRIR O ARQUIVO. ARQUIVO SEM REGISTRO.\n\n ");
		system("pause");
	}
	else{
		layoutHeader();
		rewind(pProj);
		fread(&cadProj, sizeof(cadProjeto), 1, pProj);
		printf("\n--------------------------------------------------\n LISTAGEM DE PROJETOS CADASTRADOS\n--------------------------------------------------\n");
		printf("\n\n ID\t NOME\n--------------------------------------------------");
		while(!feof(pProj)){
			if(!feof(pProj)){
				printf("\n %d\t %s\n", cadProj.id,cadProj.nome);
				fread(&cadProj, sizeof(cadProjeto), 1, pProj);
			}
		}
		printf("\n\n");
		system("pause");
		fclose(pProj);
	}
}
//Alterar
void alterarProjeto(){
    cadProjeto cadProj;
	int i=0,Op;
	char nome[50];
	FILE *pProj;
	int verificaCadastro = 0; //Boleana para verificar se registro esta cadastrado ou não
	
	pProj=fopen("Projeto.txt","rb+");
	
	if(pProj == NULL){
		layoutHeader();
		printf("\n--------------------------------------------------\n ALTERACAO DE DADOS PROGRAMADOR CADASTRADO\n--------------------------------------------------\n");	
		printf("\n\n ERRO, NAO FOI POSSIVEL ABRIR O ARQUIVO. ARQUIVO SEM REGISTRO.\n\n ");
		system("pause");
	}
	else{
		layoutHeader();
		printf("\n--------------------------------------------------\n ALTERACAO DE DADOS PROJETO CADASTRADO\n--------------------------------------------------\n");	
		printf(" \n\n INFORME O NOME DO PROJETO QUE DESEJA ALTERAR: ");
	    fflush(stdin);
	    gets(nome);
	    verificaCadastro = 0;
	    rewind(pProj);
		while(!feof(pProj)){
			fread(&cadProj,sizeof(cadProjeto),1,pProj);
	        if(!feof(pProj)){
				if(strcmp(cadProj.nome,strupr(nome))==0){
	            	printf("\n DADOS ATUAIS\n--------------------------------------------------\n");
	            	printf(" ID: %d\n", cadProj.id);
		        	printf(" NOME: %s\n--------------------------------------------------", cadProj.nome);   
		        	verificaCadastro = 1;
					printf("\n\n INFORME NOVOS DADOS\n");
		        	printf("\n ID: ");
		        	scanf("%d",&cadProj.id);
		        	printf(" \n NOME: ");
		        	fflush(stdin);
		        	gets(cadProj.nome);
		        	strupr(cadProj.nome);
		        	//cadProj.situacaoAtivo = 1;
		        	fseek(pProj,i*sizeof(cadProjeto), SEEK_SET);
		        	fwrite(&cadProj, sizeof(cadProjeto),1,pProj);
					break;
		        
	        	}
			}
			i++;
				
		}
		if (verificaCadastro == 0){
		    printf("\n REGISTRO NAO ENCONTRADO!\n ");
		    system("pause");
		}  
		fclose(pProj);
		
		do{ 
			layoutHeader();
			printf("\n--------------------------------------------------\n ALTERACAO DE DADOS PROJETO CADASTRADO\n--------------------------------------------------\n");	
			printf("\n\n DESEJA REALIZAR UMA NOVA NOVA BUSCAR?\n\n [1] SIM\n [0] NAO\n\n INFORME OPCAO: ");
	        scanf("%d",&Op);
	        if ((Op < 0) || (Op > 1)){
	          	printf("\n OPCAO INVALIDA!\n");
				system("pause");
			}
		}while((Op < 0) || (Op > 1));
		if (Op == 1)
			alterarProjeto();
	}
}
//Excluir
void excluirProjeto(){
char nome[50];
	FILE *pProj;
	cadProjeto cadProj, *vetProg;
	    
	int cont=0,i=0,verificaCadastro=0, Op;
	vetProg=(cadProjeto*)malloc(1000*sizeof(cadProjeto));
	pProj=fopen("Projeto.txt","rb+");
	if(pProj == NULL){
		layoutHeader();
		printf("\n--------------------------------------------------\n EXCLUSAO DE REGISTROS DO PROJETO \n--------------------------------------------------\n");	
		printf("\n\n ERRO, NAO FOI POSSIVEL ABRIR O ARQUIVO. ARQUIVO SEM REGISTRO.\n\n ");
		system("pause");
	}
	else{
		layoutHeader();
		printf("\n--------------------------------------------------\n EXCLUSAO DE REGISTROS DO PROJETO \n--------------------------------------------------\n");	
		printf(" \n\n INFORME O NOME DO PROJETO QUE DESEJA EXCLUIR: ");
	    fflush(stdin);
	    gets(nome);
		rewind(pProj);
		while(!feof(pProj)){
			fread(&cadProj,sizeof(cadProjeto),1,pProj);
			if(!feof(pProj)){
				if(strcmp(strupr(cadProj.nome),strupr(nome))==0){
					printf("\n DADOS EXCLUIDOS COM SUCESSO!\n ");
					verificaCadastro=1;
					system("pause");		
				}
				else{
					strcpy(strupr(vetProg[i].nome),strupr(cadProj.nome));
					(vetProg[i].id = cadProj.id);
					i++;
					cont++;				
			    }
			}
		}
		fclose(pProj);
		pProj=fopen("Projeto.txt","wb");
		fwrite(vetProg,sizeof(cadProjeto),i,pProj);
		fclose(pProj);
		free(vetProg);  
		
		if (verificaCadastro == 0){
		    printf("\n REGISTRO NAO ENCONTRADO!\n ");
		    system("pause");
		}  
		
		do{ 
			layoutHeader();
			printf("\n--------------------------------------------------\n EXCLUSAO DE REGISTROS DO PROJETO \n--------------------------------------------------\n");	
			printf("\n\n DESEJA REALIZAR UMA NOVA NOVA BUSCA?\n\n [1] SIM\n [0] NAO\n\n INFORME OPCAO: ");
	        scanf("%d",&Op);
	        if ((Op < 0) || (Op > 1)){
	          	printf("\n OPCAO INVALIDA!\n");
				system("pause");
			}
		}while((Op < 0) || (Op > 1));
		if (Op == 1)
			excluirProjeto();
	}             
}


//********************* C R U D   T I P O  A T I V I D A D E *********************
//Cadastrar
void cadastrarTipoAtividade(){
    int Op;
    cadTipoAtividade cadTipoAtiv;
    FILE *pTipoAtiv;
    pTipoAtiv=fopen("TipoAtividade.txt","a+");
    if(pTipoAtiv==NULL)
    {
		layoutHeader();
		printf("\n--------------------------------------------------\n CADASTRO DE TIPO DE ATIVIDADE\n--------------------------------------------------\n");
		printf("\n\n ERRO, NAO FOI POSSIVEL ABRIR O ARQUIVO. ARQUIVO SEM REGISTRO.\n");
		system("pause");
	}
    else{
        do{
			layoutHeader();
            printf("\n--------------------------------------------------\n CADASTRO DE TIPO DE ATIVIDADE\n--------------------------------------------------\n");
			printf("\n INFORME OS DADOS");
            printf("\n\n ID: ");
            scanf("%d",&cadTipoAtiv.id);
            printf("\n NOME: ");
            fflush(stdin);
            gets(cadTipoAtiv.nome);
            strupr(cadTipoAtiv.nome);;
            fwrite(&cadTipoAtiv, sizeof(cadTipoAtiv), 1, pTipoAtiv);
            
			do{ 
				layoutHeader();
				printf("\n--------------------------------------------------\n CADASTRO DE TIPO DE ATIVIDADE\n--------------------------------------------------\n");
				printf("\n\n DESEJA REALIZAR UM NOVO CADASTRO?\n\n [1] SIM\n [0] NAO\n\n INFORME OPCAO: ");
            	scanf("%d",&Op);
          		if ((Op < 0) || (Op > 1)){
          			printf("\n OPCAO INVALIDA!\n");
					system("pause");
				}
			}while((Op < 0) || (Op > 1));
		}while(Op!=0);
    }
    fclose(pTipoAtiv);
}
//Listar
void listarTipoAtividade(){
	FILE *pTipoAtiv;
	cadTipoAtividade cadTipoAtiv;
	pTipoAtiv=fopen("TipoAtividade.txt","r+b");
	if(pTipoAtiv == NULL){
		layoutHeader();
		printf("\n--------------------------------------------------\n LISTAGEM DE TIPO DE ATIVIDADES CADASTRADOS\n--------------------------------------------------\n");
		printf("\n\n ERRO, NAO FOI POSSIVEL ABRIR O ARQUIVO. ARQUIVO SEM REGISTRO.\n\n ");
		system("pause");
	}
	else{
		layoutHeader();
		rewind(pTipoAtiv);
		fread(&cadTipoAtiv, sizeof(cadTipoAtividade), 1, pTipoAtiv);
		printf("\n--------------------------------------------------\n LISTAGEM DE TIPO DE ATIVIDADES CADASTRADOS\n--------------------------------------------------\n");
		printf("\n\n ID\t NOME\n--------------------------------------------------");
		while(!feof(pTipoAtiv)){
			if(!feof(pTipoAtiv)){
				printf("\n %d\t %s\n", cadTipoAtiv.id,cadTipoAtiv.nome);
				fread(&cadTipoAtiv, sizeof(cadTipoAtividade), 1, pTipoAtiv);
			}
		}
		printf("\n\n");
		system("pause");
		fclose(pTipoAtiv);
	}
}
//Alterar
void alterarTipoAtividade(){
    cadTipoAtividade cadTipoAtiv;
	int i=0,Op;
	char nome[50];
	FILE *pTipoAtiv;
	int verificaCadastro = 0; //Boleana para verificar se registro esta cadastrado ou não
	
	pTipoAtiv=fopen("TipoAtividade.txt","rb+");
	
	if(pTipoAtiv == NULL){
		layoutHeader();
		printf("\n--------------------------------------------------\n ALTERACAO DE DADOS TIPO DE ATIVIDADE CADASTRADO\n--------------------------------------------------\n");	
		printf("\n\n ERRO, NAO FOI POSSIVEL ABRIR O ARQUIVO. ARQUIVO SEM REGISTRO.\n\n ");
		system("pause");
	}
	else{
		layoutHeader();
		printf("\n--------------------------------------------------\n ALTERACAO DE DADOS TIPO DE ATIVIDADE CADASTRADO\n--------------------------------------------------\n");	
		printf(" \n\n INFORME O NOME DO TIPO DE ATIVIDADE QUE DESEJA ALTERAR: ");
	    fflush(stdin);
	    gets(nome);
	    verificaCadastro = 0;
	    rewind(pTipoAtiv);
		while(!feof(pTipoAtiv)){
			fread(&cadTipoAtiv,sizeof(cadTipoAtividade),1,pTipoAtiv);
	        if(!feof(pTipoAtiv)){
				if(strcmp(cadTipoAtiv.nome,strupr(nome))==0){
	            	printf("\n DADOS ATUAIS\n--------------------------------------------------\n");
	            	printf(" ID: %d\n", cadTipoAtiv.id);
		        	printf(" NOME: %s\n--------------------------------------------------", cadTipoAtiv.nome);   
		        	verificaCadastro = 1;
					printf("\n\n INFORME NOVOS DADOS\n");
		        	printf("\n ID: ");
		        	scanf("%d",&cadTipoAtiv.id);
		        	printf(" \n NOME: ");
		        	fflush(stdin);
		        	gets(cadTipoAtiv.nome);
		        	strupr(cadTipoAtiv.nome);
		        	//cadTipoAtiv.situacaoAtivo = 1;
		        	fseek(pTipoAtiv,i*sizeof(cadTipoAtividade), SEEK_SET);
		        	fwrite(&cadTipoAtiv, sizeof(cadTipoAtividade),1,pTipoAtiv);
					break;
		        
	        	}
			}
			i++;
				
		}
		if (verificaCadastro == 0){
		    printf("\n REGISTRO NAO ENCONTRADO!\n ");
		    system("pause");
		}  
		fclose(pTipoAtiv);
		
		do{ 
			layoutHeader();
			printf("\n--------------------------------------------------\n ALTERACAO DE DADOS TIPO DE ATIVIDADE CADASTRADO\n--------------------------------------------------\n");	
			printf("\n\n DESEJA REALIZAR UMA NOVA NOVA BUSCAR?\n\n [1] SIM\n [0] NAO\n\n INFORME OPCAO: ");
	        scanf("%d",&Op);
	        if ((Op < 0) || (Op > 1)){
	          	printf("\n OPCAO INVALIDA!\n");
				system("pause");
			}
		}while((Op < 0) || (Op > 1));
		if (Op == 1)
			alterarTipoAtividade();
	}
}
//Excluir
void excluirTipoAtividade(){
char nome[50];
	FILE *pTipoAtiv;
	cadTipoAtividade cadTipoAtiv, *vetTipoAtiv;
	    
	int cont=0,i=0,verificaCadastro=0, Op;
	vetTipoAtiv=(cadTipoAtividade*)malloc(1000*sizeof(cadTipoAtividade));
	pTipoAtiv=fopen("TipoAtividade.txt","rb+");
	if(pTipoAtiv == NULL){
		layoutHeader();
		printf("\n--------------------------------------------------\n EXCLUSAO DE REGISTROS DO TIPO DE ATIVIDADE \n--------------------------------------------------\n");	
		printf("\n\n ERRO, NAO FOI POSSIVEL ABRIR O ARQUIVO. ARQUIVO SEM REGISTRO.\n\n ");
		system("pause");
	}
	else{
		layoutHeader();
		printf("\n--------------------------------------------------\n EXCLUSAO DE REGISTROS DO TIPO DE ATIVIDADE \n--------------------------------------------------\n");	
		printf(" \n\n INFORME O NOME DO TIPO DE ATIVIDADE QUE DESEJA EXCLUIR: ");
	    fflush(stdin);
	    gets(nome);
		rewind(pTipoAtiv);
		while(!feof(pTipoAtiv)){
			fread(&cadTipoAtiv,sizeof(cadTipoAtividade),1,pTipoAtiv);
			if(!feof(pTipoAtiv)){
				if(strcmp(strupr(cadTipoAtiv.nome),strupr(nome))==0){
					printf("\n DADOS EXCLUIDOS COM SUCESSO!\n ");
					verificaCadastro=1;
					system("pause");		
				}
				else{
					strcpy(strupr(vetTipoAtiv[i].nome),strupr(cadTipoAtiv.nome));
					(vetTipoAtiv[i].id = cadTipoAtiv.id);
					i++;
					cont++;				
			    }
			}
		}
		fclose(pTipoAtiv);
		pTipoAtiv=fopen("TipoAtividade.txt","wb");
		fwrite(vetTipoAtiv,sizeof(cadTipoAtividade),i,pTipoAtiv);
		fclose(pTipoAtiv);
		free(vetTipoAtiv);  
		
		if (verificaCadastro == 0){
		    printf("\n REGISTRO NAO ENCONTRADO!\n ");
		    system("pause");
		}  
		
		do{ 
			layoutHeader();
			printf("\n--------------------------------------------------\n EXCLUSAO DE REGISTROS DO TIPO DE ATIVIDADE \n--------------------------------------------------\n");	
			printf("\n\n DESEJA REALIZAR UMA NOVA NOVA BUSCA?\n\n [1] SIM\n [0] NAO\n\n INFORME OPCAO: ");
	        scanf("%d",&Op);
	        if ((Op < 0) || (Op > 1)){
	          	printf("\n OPCAO INVALIDA!\n");
				system("pause");
			}
		}while((Op < 0) || (Op > 1));
		if (Op == 1)
			excluirTipoAtividade();
	}             
}

//********************* C R U D   S P R I N T *********************
//Cadastrar
void cadastrarSprint(){
    int Op;
    cadSprint cadSp;
    FILE *pSp;
    pSp=fopen("Sprint.txt","a+");
    if(pSp==NULL)
    {
		layoutHeader();
		printf("\n--------------------------------------------------\n CADASTRO DE SPRINT\n--------------------------------------------------\n");
		printf("\n\n ERRO, NAO FOI POSSIVEL ABRIR O ARQUIVO. ARQUIVO SEM REGISTRO.\n");
		system("pause");
	}
    else{
        do{
			layoutHeader();
            printf("\n--------------------------------------------------\n CADASTRO DE SPRINT\n--------------------------------------------------\n");
			printf("\n INFORME OS DADOS");
            printf("\n\n #SP: ");
            scanf("%d",&cadSp.sp);
            printf("\n DATA INICIAL: ");
            fflush(stdin);
            gets(cadSp.dtInicial);
            printf("\n DATA FINAL: ");
            fflush(stdin);
            gets(cadSp.dtFinal);
            
			fwrite(&cadSp, sizeof(cadSprint), 1, pSp);
            
			do{ 
				layoutHeader();
				printf("\n--------------------------------------------------\n CADASTRO DE SPRINT\n--------------------------------------------------\n");
				printf("\n\n DESEJA REALIZAR UM NOVO CADASTRO?\n\n [1] SIM\n [0] NAO\n\n INFORME OPCAO: ");
            	scanf("%d",&Op);
          		if ((Op < 0) || (Op > 1)){
          			printf("\n OPCAO INVALIDA!\n");
					system("pause");
				}
			}while((Op < 0) || (Op > 1));
		}while(Op!=0);
    }
    fclose(pSp);
}
//Listar
void listarSprint(){
	FILE *pSp;
	cadSprint cadSp;
	pSp=fopen("Sprint.txt","r+b");
	if(pSp == NULL){
		layoutHeader();
		printf("\n--------------------------------------------------\n DATAS DE SPRINTS\n--------------------------------------------------\n");
		printf("\n\n ERRO, NAO FOI POSSIVEL ABRIR O ARQUIVO. ARQUIVO SEM REGISTRO.\n\n ");
		system("pause");
	}
	else{
		layoutHeader();
		rewind(pSp);
		fread(&cadSp, sizeof(cadSprint), 1, pSp);
		printf("\n--------------------------------------------------\n DATAS DE SPRINTS\n--------------------------------------------------\n");
		printf("\n\n #SP\t DATA INICIAL\t DATA FINAL\n--------------------------------------------------");
		while(!feof(pSp)){
			if(!feof(pSp)){
				printf("\n %d\t %s%\t %s\n",cadSp.sp,cadSp.dtInicial,cadSp.dtFinal);
				fread(&cadSp, sizeof(cadSprint), 1, pSp);
			}
		}
		printf("\n\n");
		system("pause");
		fclose(pSp);
	}
}
//Alterar
void alterarSprint(){
    cadSprint cadSp;
	int i=0,Op, Sp;
	FILE *pSp;
	int verificaCadastro = 0; //Boleana para verificar se registro esta cadastrado ou não
	
	pSp=fopen("Sprint.txt","rb+");
	
	if(pSp == NULL){
		layoutHeader();
		printf("\n--------------------------------------------------\n ALTERACAO DE DADOS PROGRAMADOR CADASTRADO\n--------------------------------------------------\n");	
		printf("\n\n ERRO, NAO FOI POSSIVEL ABRIR O ARQUIVO. ARQUIVO SEM REGISTRO.\n\n ");
		system("pause");
	}
	else{
		layoutHeader();
		printf("\n--------------------------------------------------\n ALTERACAO DE DATAS DO SRINT\n--------------------------------------------------\n");	
		printf(" \n\n INFORME O NUMERO DO SPRINT QUE DESEJA ALTERAR: ");
	    scanf("%d",&Sp);
		verificaCadastro = 0;
	    rewind(pSp);
		while(!feof(pSp)){
			fread(&cadSp,sizeof(cadSprint),1,pSp);
	        if(!feof(pSp)){
				if(cadSp.sp == Sp){
	            	printf("\n DADOS ATUAIS\n--------------------------------------------------\n");
	            	printf(" #SP: %d\n", cadSp.sp);
		        	printf("\n DATA INICIAL: %s\n", cadSp.dtInicial);   
					printf("\n DATA FINAL: %s\n--------------------------------------------------", cadSp.dtFinal);   
		        	
					verificaCadastro = 1;
					printf("\n\n INFORME NOVOS DADOS\n");
		        	printf("\n #SP: [%d]\n",cadSp.sp);
		        	cadSp.sp = cadSp.sp;
		        	printf(" \n DATA INICIAL: ");
		        	fflush(stdin);
		        	gets(cadSp.dtInicial);
		        	printf(" \n DATA FINAL: ");
					fflush(stdin);
		        	gets(cadSp.dtFinal);
		        	
					
		        	fseek(pSp,i*sizeof(cadSprint), SEEK_SET);
		        	fwrite(&cadSp, sizeof(cadSprint),1,pSp);
					break;
		        }
			}
			i++;
		}
		if (verificaCadastro == 0){
		    printf("\n REGISTRO NAO ENCONTRADO!\n ");
		    system("pause");
		}  
		fclose(pSp);
		
		do{ 
			layoutHeader();
			printf("\n--------------------------------------------------\n ALTERACAO DE DATAS DO SRINT\n--------------------------------------------------\n");	
			printf("\n\n DESEJA REALIZAR UMA NOVA NOVA BUSCAR?\n\n [1] SIM\n [0] NAO\n\n INFORME OPCAO: ");
	        scanf("%d",&Op);
	        if ((Op < 0) || (Op > 1)){
	          	printf("\n OPCAO INVALIDA!\n");
				system("pause");
			}
		}while((Op < 0) || (Op > 1));
		if (Op == 1)
			alterarSprint();
	}
}
//Excluir
void excluirSprint(){
	FILE *pSp;
	cadSprint cadSp, *vetSp;
	    
	int sp,cont=0,i=0,verificaCadastro=0, Op;
	vetSp=(cadSprint*)malloc(1000*sizeof(cadSprint));
	pSp=fopen("Sprint.txt","rb+");
	if(pSp == NULL){
		layoutHeader();
		printf("\n--------------------------------------------------\n EXCLUSAO DE REGISTROS DO SPRINT \n--------------------------------------------------\n");	
		printf("\n\n ERRO, NAO FOI POSSIVEL ABRIR O ARQUIVO. ARQUIVO SEM REGISTRO.\n\n ");
		system("pause");
	}
	else{
		layoutHeader();
		printf("\n--------------------------------------------------\n EXCLUSAO DE REGISTROS DO SPRINT \n--------------------------------------------------\n");	
		printf(" \n\n INFORME O NUMERO DO SPRINT QUE DESEJA EXCLUIR: ");
	    scanf("%d",&sp);
		rewind(pSp);
		while(!feof(pSp)){
			fread(&cadSp,sizeof(cadSprint),1,pSp);
			if(!feof(pSp)){
				if(cadSp.sp == sp){
					printf("\n DADOS EXCLUIDOS COM SUCESSO!\n ");
					verificaCadastro=1;
					system("pause");		
				}
				else{
					strcpy(vetSp[i].dtInicial, cadSp.dtInicial);
					strcpy(vetSp[i].dtFinal, cadSp.dtFinal);
					(vetSp[i].sp = cadSp.sp);
					i++;
					cont++;				
			    }
			}
		}
		fclose(pSp);
		pSp=fopen("Sprint.txt","wb");
		fwrite(vetSp,sizeof(cadSprint),i,pSp);
		fclose(pSp);
		free(vetSp);  
		
		if (verificaCadastro == 0){
		    printf("\n REGISTRO NAO ENCONTRADO!\n ");
		    system("pause");
		}  
		
		do{ 
			layoutHeader();
			printf("\n--------------------------------------------------\n EXCLUSAO DE REGISTROS DO SPRINT \n--------------------------------------------------\n");	
			printf("\n\n DESEJA REALIZAR UMA NOVA NOVA BUSCA?\n\n [1] SIM\n [0] NAO\n\n INFORME OPCAO: ");
	        scanf("%d",&Op);
	        if ((Op < 0) || (Op > 1)){
	          	printf("\n OPCAO INVALIDA!\n");
				system("pause");
			}
		}while((Op < 0) || (Op > 1));
		if (Op == 1)
			excluirSprint();
	}             
}



//********************* C R U D   P R O G R A M A D O R *********************
//Cadastrar
void cadastrarProgramador(){
    int Op;
    cadProgramador cadProg;
    FILE *pProg;
    pProg=fopen("Programador.txt","a+");
    if(pProg==NULL)
    {
		layoutHeader();
		printf("\n--------------------------------------------------\n CADASTRO DE PROGRAMADOR\n--------------------------------------------------\n");
		printf("\n\n ERRO, NAO FOI POSSIVEL ABRIR O ARQUIVO. ARQUIVO SEM REGISTRO.\n");
		system("pause");
	}
    else{
        do{
			layoutHeader();
            printf("\n--------------------------------------------------\n CADASTRO DE PROGRAMADOR\n--------------------------------------------------\n");
			printf("\n INFORME OS DADOS");
            printf("\n\n ID: ");
            scanf("%d",&cadProg.id);
            printf("\n NOME: ");
            fflush(stdin);
            gets(cadProg.nome);
            strupr(cadProg.nome);;
            fwrite(&cadProg, sizeof(cadProg), 1, pProg);
            
			do{ 
				layoutHeader();
				printf("\n--------------------------------------------------\n CADASTRO DE PROGRAMADOR\n--------------------------------------------------\n");
				printf("\n\n DESEJA REALIZAR UM NOVO CADASTRO?\n\n [1] SIM\n [0] NAO\n\n INFORME OPCAO: ");
            	scanf("%d",&Op);
          		if ((Op < 0) || (Op > 1)){
          			printf("\n OPCAO INVALIDA!\n");
					system("pause");
				}
			}while((Op < 0) || (Op > 1));
		}while(Op!=0);
    }
    fclose(pProg);
}
//Listar
void listarProgramador(){
	FILE *pProg;
	cadProgramador cadProg;
	pProg=fopen("Programador.txt","r+b");
	if(pProg == NULL){
		layoutHeader();
		printf("\n--------------------------------------------------\n LISTAGEM DE PROGRAMADORES CADASTRADOS\n--------------------------------------------------\n");
		printf("\n\n ERRO, NAO FOI POSSIVEL ABRIR O ARQUIVO. ARQUIVO SEM REGISTRO.\n\n ");
		system("pause");
	}
	else{
		layoutHeader();
		rewind(pProg);
		fread(&cadProg, sizeof(cadProgramador), 1, pProg);
		printf("\n--------------------------------------------------\n LISTAGEM DE PROGRAMADORES CADASTRADOS\n--------------------------------------------------\n");
		printf("\n\n ID\t NOME\n--------------------------------------------------");
		while(!feof(pProg)){
			if(!feof(pProg)){
				printf("\n %d\t %s\n", cadProg.id,cadProg.nome);
				fread(&cadProg, sizeof(cadProgramador), 1, pProg);
			}
		}
		printf("\n\n");
		system("pause");
		fclose(pProg);
	}
}
//Alterar
void alterarProgramador(){
    cadProgramador cadProg;
	int i=0,Op;
	char nome[50];
	FILE *pProg;
	int verificaCadastro = 0; //Boleana para verificar se registro esta cadastrado ou não
	
	pProg=fopen("Programador.txt","rb+");
	
	if(pProg == NULL){
		layoutHeader();
		printf("\n--------------------------------------------------\n ALTERACAO DE DADOS PROGRAMADOR CADASTRADO\n--------------------------------------------------\n");	
		printf("\n\n ERRO, NAO FOI POSSIVEL ABRIR O ARQUIVO. ARQUIVO SEM REGISTRO.\n\n ");
		system("pause");
	}
	else{
		layoutHeader();
		printf("\n--------------------------------------------------\n ALTERACAO DE DADOS PROGRAMADOR CADASTRADO\n--------------------------------------------------\n");	
		printf(" \n\n INFORME O NOME DO PROGRAMADOR QUE DESEJA ALTERAR: ");
	    fflush(stdin);
	    gets(nome);
	    verificaCadastro = 0;
	    rewind(pProg);
		while(!feof(pProg)){
			fread(&cadProg,sizeof(cadProgramador),1,pProg);
	        if(!feof(pProg)){
				if(strcmp(cadProg.nome,strupr(nome))==0){
	            	printf("\n DADOS ATUAIS\n--------------------------------------------------\n");
	            	printf(" ID: %d\n", cadProg.id);
		        	printf(" NOME: %s\n--------------------------------------------------", cadProg.nome);   
		        	verificaCadastro = 1;
					printf("\n\n INFORME NOVOS DADOS\n");
		        	printf("\n ID: ");
		        	scanf("%d",&cadProg.id);
		        	printf(" \n NOME: ");
		        	fflush(stdin);
		        	gets(cadProg.nome);
		        	strupr(cadProg.nome);
		        	fseek(pProg,i*sizeof(cadProgramador), SEEK_SET);
		        	fwrite(&cadProg, sizeof(cadProgramador),1,pProg);
					break;
		        
	        	}
			}
			i++;
				
		}
		if (verificaCadastro == 0){
		    printf("\n REGISTRO NAO ENCONTRADO!\n ");
		    system("pause");
		}  
		fclose(pProg);
		
		do{ 
			layoutHeader();
			printf("\n--------------------------------------------------\n ALTERACAO DE DADOS PROGRAMADOR CADASTRADO\n--------------------------------------------------\n");	
			printf("\n\n DESEJA REALIZAR UMA NOVA NOVA BUSCAR?\n\n [1] SIM\n [0] NAO\n\n INFORME OPCAO: ");
	        scanf("%d",&Op);
	        if ((Op < 0) || (Op > 1)){
	          	printf("\n OPCAO INVALIDA!\n");
				system("pause");
			}
		}while((Op < 0) || (Op > 1));
		if (Op == 1)
			alterarProgramador();
	}
}
//Excluir
void excluirProgramador(){
char nome[50];
	FILE *pProg;
	cadProgramador cadProg, *vetProg;
	    
	int cont=0,i=0,verificaCadastro=0, Op;
	vetProg=(cadProgramador*)malloc(1000*sizeof(cadProgramador));
	pProg=fopen("Programador.txt","rb+");
	if(pProg == NULL){
		layoutHeader();
		printf("\n--------------------------------------------------\n EXCLUSAO DE REGISTROS DO PROGRAMADOR \n--------------------------------------------------\n");	
		printf("\n\n ERRO, NAO FOI POSSIVEL ABRIR O ARQUIVO. ARQUIVO SEM REGISTRO.\n\n ");
		system("pause");
	}
	else{
		layoutHeader();
		printf("\n--------------------------------------------------\n EXCLUSAO DE REGISTROS DO PROGRAMADOR \n--------------------------------------------------\n");	
		printf(" \n\n INFORME O NOME DO PROGRAMADOR QUE DESEJA EXCLUIR: ");
	    fflush(stdin);
	    gets(nome);
		rewind(pProg);
		while(!feof(pProg)){
			fread(&cadProg,sizeof(cadProgramador),1,pProg);
			if(!feof(pProg)){
				if(strcmp(strupr(cadProg.nome),strupr(nome))==0){
					printf("\n DADOS EXCLUIDOS COM SUCESSO!\n ");
					verificaCadastro=1;
					system("pause");		
				}
				else{
					strcpy(strupr(vetProg[i].nome),strupr(cadProg.nome));
					(vetProg[i].id = cadProg.id);
					i++;
					cont++;				
			    }
			}
		}
		fclose(pProg);
		pProg=fopen("Programador.txt","wb");
		fwrite(vetProg,sizeof(cadProgramador),i,pProg);
		fclose(pProg);
		free(vetProg);  
		
		if (verificaCadastro == 0){
		    printf("\n REGISTRO NAO ENCONTRADO!\n ");
		    system("pause");
		}  
		
		do{ 
			layoutHeader();
			printf("\n--------------------------------------------------\n EXCLUSAO DE REGISTROS DO PROGRAMADOR \n--------------------------------------------------\n");	
			printf("\n\n DESEJA REALIZAR UMA NOVA NOVA BUSCA?\n\n [1] SIM\n [0] NAO\n\n INFORME OPCAO: ");
	        scanf("%d",&Op);
	        if ((Op < 0) || (Op > 1)){
	          	printf("\n OPCAO INVALIDA!\n");
				system("pause");
			}
		}while((Op < 0) || (Op > 1));
		if (Op == 1)
			excluirProgramador();
	}             
}


//********************* G E R E N C I A R   S P R I N T *********************
//Selecionar Atividades
void selecionarAtividadesSprint(){
    int Op,OpAux=0,verificaAux=0;
    GerSprint GerSp;
	cadProgramador cadProg;
    cadAtividade cadAtiv;
    cadSprint cadSp;
	
	FILE *pGerSp, *pProg, *pAtiv, *pSp;
    pGerSp=fopen("GerenciarSprint.txt","a+");
    if(pProg==NULL)
    {
		layoutHeader();
		printf("\n--------------------------------------------------\n SELECAO DE ATIVIDADES DO SPRINT\n--------------------------------------------------\n");
		printf("\n\n ERRO, NAO FOI POSSIVEL ABRIR O ARQUIVO. ARQUIVO SEM REGISTRO.\n");
		system("pause");
	}
    else{
        
		layoutHeader();
        printf("\n--------------------------------------------------\n SELECAO DE ATIVIDADES DO SPRINT\n--------------------------------------------------\n");
		
        //Selecionando Numero do Sprint
		OpAux=0;
		pSp=fopen("Sprint.txt","r+b");
		rewind(pSp);
		fread(&cadSp, sizeof(cadSprint), 1, pSp);
		printf("\n DATA DOS SPRINT\n #SP\t DATA INICIAL\t DATA FINAL\n--------------------------------------------------\n");
		while(!feof(pSp)){
			if(!feof(pSp)){
			printf(" %d\t %s\t %s\n", cadSp.sp,cadSp.dtInicial,cadSp.dtFinal);
			fread(&cadSp, sizeof(cadSprint), 1, pSp);
			}
		}
		do{
			printf("\n ESCOLHA O NUMERO DO SPRINT: ");
			scanf("%d",&OpAux);
			verificaAux = 0;
			pSp=fopen("Sprint.txt","r+b");
			rewind(pSp);
			while(!feof(pSp)){
				fread(&cadSp,sizeof(cadSprint),1,pSp);
				if(!feof(pSp)){
					if(cadSp.sp == OpAux){
						verificaAux = 1;
						GerSp.cadSprint.sp = cadSp.sp;
						fclose(pSp);
						break;
					}
				}
			}
			if (verificaAux == 0){
				printf("\n OPCAO INVALIDA!\n ");
				system("pause");
			}  
			fclose(pSp);
		}while(verificaAux == 0);	
        
        do{
        	//Selecionando Atividades do Sprint
			OpAux=0;
			pAtiv=fopen("Atividade.txt","r+b");
			rewind(pAtiv);
			fread(&cadAtiv, sizeof(cadAtividade), 1, pAtiv);
			printf("\n LISTA DE ATIVIDADES DO BACKLOG\n --------------------------------------------------\n");
			while(!feof(pAtiv)){
				if(!feof(pAtiv)){
					printf("\n ID: %d",cadAtiv.id);
					printf("\n DESCRICAO:\n %s",cadAtiv.descricao);
					printf("\n PROJETO: %s",cadAtiv.cadProj.nome);
					printf("\n TIPO DE ATIVIDADE: %s",cadAtiv.cadTipoAtiv.nome);
					printf("\n PRIORIDADE: %D\n",cadAtiv.prioridade);
					fread(&cadAtiv, sizeof(cadAtividade), 1, pAtiv);
				}
			}
			printf("\n --------------------------------------------------\n");
			
			do{
				printf("\n ESCOLHA O ID DA ATIVIDADE: ");
				scanf("%d",&OpAux);
				verificaAux = 0;
				pSp=fopen("Atividade.txt","r+b");
				rewind(pAtiv);
				while(!feof(pAtiv)){
					fread(&cadAtiv,sizeof(cadAtividade),1,pAtiv);
					if(!feof(pAtiv)){
						if(cadAtiv.id == OpAux){
							verificaAux = 1;
							GerSp.cadAtiv.id = cadAtiv.id;
							strcpy(GerSp.cadAtiv.descricao, cadAtiv.descricao);
							strcpy(GerSp.cadAtiv.cadProj.nome, cadAtiv.cadProj.nome);
							strcpy(GerSp.cadAtiv.cadTipoAtiv.nome, cadAtiv.cadTipoAtiv.nome);
							fclose(pAtiv);
							break;
						}
					}
				}
				if (verificaAux == 0){
					printf("\n OPCAO INVALIDA!\n ");
					system("pause");
				}  
				fclose(pAtiv);
			}while(verificaAux == 0);
			
			//Selecionando o Prgramador
			OpAux=0;
			pProg=fopen("Programador.txt","r+b");
			rewind(pProg);
			fread(&cadProg, sizeof(cadProgramador), 1, pProg);
			printf("\n LISTAGEM DE PROGRAMADORES\n ID\t NOME\n--------------------------------------------------\n");
			while(!feof(pProg)){
				if(!feof(pProg)){
				printf(" %d\t %s\n", cadProg.id,cadProg.nome);
					fread(&cadProg, sizeof(cadProgramador), 1, pProg);
				}
			}
			do{
				printf("\n ESCOLHA O ID DO PROGRAMADOR QUE IRA DESENVOLVER A ATIVIDADE: ");
				scanf("%d",&OpAux);
				verificaAux = 0;
				pProg=fopen("Programador.txt","r+b");
				rewind(pProg);
				while(!feof(pProg)){
					fread(&cadProg,sizeof(cadProgramador),1,pProg);
					if(!feof(pProg)){
						if(cadProg.id == OpAux){
							verificaAux = 1;
							strcpy(GerSp.cadProg.nome, cadProg.nome);
							fclose(pProg);
							break;
						}
					}
				}
				if (verificaAux == 0){
					printf("\n OPCAO INVALIDA!\n ");
					system("pause");
				}  
				fclose(pProg);
			}while(verificaAux == 0);
			
			strcpy(GerSp.status, "NAO REALIZADA");
			OpAux=0;
			
			do{
				printf("\n\n PONTUACAOES: \n [1],[2],[5],[8],[13],[20],[100]\n ESCOLHA A PONTUACAO: ");
				scanf("%d",&OpAux);
				if ((OpAux != 1) && (OpAux != 2) && (OpAux != 5) && (OpAux != 8) && (OpAux != 13) && (OpAux != 20) && (OpAux != 100)){
	          		printf("\n OPCAO INVALIDA!\n ");
					system("pause");
				}
			}while((OpAux != 1) && (OpAux != 2) && (OpAux != 5) &&(OpAux != 8) &&(OpAux != 13) &&(OpAux != 20) &&(OpAux != 100));
			
			GerSp.pontuacao = OpAux;
			GerSp.percentualDesenvolvimento = 0;
			 
			do{ 
				printf("\n\n DESEJA INSERIR OUTRA ATIVIDADE NO SPRINT #%d?\n\n [1] SIM\n [0] NAO\n\n INFORME OPCAO: ",GerSp.cadSprint.sp);
	            scanf("%d",&Op);
	          	if ((Op < 0) || (Op > 1)){
	          		printf("\n OPCAO INVALIDA!\n");
					system("pause");
				}
			}while((Op < 0) || (Op > 1));
			if (Op == 1){
				GerSp.cadSprint.sp = GerSp.cadSprint.sp;
			}
			fwrite(&GerSp, sizeof(GerSprint), 1, pGerSp);
				
		}while(Op != 0);	
            
    }
    fclose(pGerSp);
}
//Listar Atividades por Sprint
void listarAtividadesDoSprint(){
	FILE *pGerSp;
	GerSprint GerSp;
	int OpSp, registrosEncontrados=0, Op;
	pGerSp=fopen("GerenciarSprint.txt","r+b");
	if(pGerSp == NULL){
		layoutHeader();
		printf("\n--------------------------------------------------\n ATIVIDADES DO SPRINT\n--------------------------------------------------\n");
		printf("\n\n ERRO, NAO FOI POSSIVEL ABRIR O ARQUIVO. ARQUIVO SEM REGISTRO.\n\n ");
		system("pause");
	}
	else{
		do{
			layoutHeader();
			rewind(pGerSp);
			fread(&GerSp, sizeof(GerSprint), 1, pGerSp);
			printf("\n--------------------------------------------------\n ATIVIDADES DO SPRINT\n--------------------------------------------------\n");
			printf(" \n INFORME O NUMERO DO SPRINT QUE DESEJA \n VISUALIZAR AS ATIVIDADES: ");
			scanf("%d",&OpSp);
			while(!feof(pGerSp)){
				if(!feof(pGerSp)){
					if (GerSp.cadSprint.sp == OpSp){
						printf("\n--------------------------------------------------\n ID: %d", GerSp.cadAtiv.id);		
						printf("\n DESCRICAO:\n %s", GerSp.cadAtiv.descricao);		
						printf("\n PROJETO: %s", GerSp.cadAtiv.cadProj.nome);
						printf("\n PROGRAMADOR: %s", GerSp.cadProg.nome);
						printf("\n TIPO DE ATIVIDADE: %s", GerSp.cadAtiv.cadTipoAtiv.nome);
						printf("\n PONTUACAO: %d", GerSp.pontuacao);
						printf("\n PERCENTUAL EM DESENVOLVIMENTO: %.2f%", GerSp.percentualDesenvolvimento);
						printf("\n STATUS: %s\n--------------------------------------------------", GerSp.status);
						registrosEncontrados=1;
					}
					else{
						registrosEncontrados=0;
					}
							
					fread(&GerSp, sizeof(GerSprint), 1, pGerSp);
				}
			}
			if (registrosEncontrados == 1){
				printf("\n ");
				system("pause");
				
			}
			
			if (registrosEncontrados == 0){
				printf("\n SEM REGISTROS DE ATIVIDADES PARA O SPRINT INFORMADO.\n ");
				system("pause");
			}
			
			do{ 
				layoutHeader();
				printf("\n--------------------------------------------------\n ATIVIDADES DO SPRINT\n--------------------------------------------------\n");			
				printf("\n\n DESEJA REALIZAR UMA NOVA BUSCA ?\n\n [1] SIM\n [0] NAO\n\n INFORME OPCAO: ");
	            scanf("%d",&Op);
	          	if ((Op < 0) || (Op > 1)){
	          		printf("\n OPCAO INVALIDA!\n ");
					system("pause");
				}
			}while((Op < 0) || (Op > 1));
			
		}while(Op != 0);
	}
	printf("\n\n");
	
	fclose(pGerSp);			
}

//LISTA - ATIVIDADES PRO PROGRAMADOR
void listarAtividadesDoProgramador(char nomeProgramador[50]){
	FILE *pGerSp;
	GerSprint GerSp;
	int OpSp, registrosEncontrados=0, Op;
	pGerSp=fopen("GerenciarSprint.txt","r+b");
	if(pGerSp == NULL){
		layoutHeader();
		printf("\n--------------------------------------------------\n ATIVIDADES DO SPRINT POR PROGRAMADOR\n--------------------------------------------------\n");
		printf("\n\n ERRO, NAO FOI POSSIVEL ABRIR O ARQUIVO. ARQUIVO SEM REGISTRO.\n\n ");
		system("pause");
	}
	else{
		do{
			layoutHeader();
			rewind(pGerSp);
			fread(&GerSp, sizeof(GerSprint), 1, pGerSp);
			printf("\n--------------------------------------------------\n ATIVIDADES DO SPRINT POR PROGRAMADOR\n--------------------------------------------------\n");
			printf(" \n INFORME O NUMERO DO SPRINT QUE DESEJA \n VISUALIZAR AS ATIVIDADES: ");
			scanf("%d",&OpSp);
			while(!feof(pGerSp)){
				if(!feof(pGerSp)){
					if (GerSp.cadSprint.sp == OpSp){
						if(strcmp(strupr(nomeProgramador),strupr(GerSp.cadProg.nome))==0){
							printf("\n--------------------------------------------------\n ID: %d", GerSp.cadAtiv.id);		
							printf("\n DESCRICAO:\n %s", GerSp.cadAtiv.descricao);		
							printf("\n PROJETO: %s", GerSp.cadAtiv.cadProj.nome);
							printf("\n PROGRAMADOR: %s", GerSp.cadProg.nome);
							printf("\n TIPO DE ATIVIDADE: %s", GerSp.cadAtiv.cadTipoAtiv.nome);
							printf("\n PONTUACAO: %d", GerSp.pontuacao);
							printf("\n PERCENTUAL EM DESENVOLVIMENTO: %.2f%", GerSp.percentualDesenvolvimento);
							printf("\n STATUS: %s\n--------------------------------------------------", GerSp.status);
							registrosEncontrados=1;
						}
					}
					else{
						registrosEncontrados=0;
					}
							
					fread(&GerSp, sizeof(GerSprint), 1, pGerSp);
				}
			}
			if (registrosEncontrados == 1){
				printf("\n ");
				system("pause");
				
			}
			
			if (registrosEncontrados == 0){
				printf("\n SEM REGISTROS DE ATIVIDADES PARA O SPRINT INFORMADO.\n ");
				system("pause");
			}
			
			do{ 
				layoutHeader();
				printf("\n--------------------------------------------------\n ATIVIDADES DO SPRINT POR PROGRAMADOR\n--------------------------------------------------\n");			
				printf("\n\n DESEJA REALIZAR UMA NOVA BUSCA ?\n\n [1] SIM\n [0] NAO\n\n INFORME OPCAO: ");
	            scanf("%d",&Op);
	          	if ((Op < 0) || (Op > 1)){
	          		printf("\n OPCAO INVALIDA!\n ");
					system("pause");
				}
			}while((Op < 0) || (Op > 1));
			
		}while(Op != 0);
	}
	printf("\n\n");
	
	fclose(pGerSp);			
}

//LISTA - POR STATUS
void listarAtividadesPorStatus(char Status[50]){
	FILE *pGerSp;
	GerSprint GerSp;
	int OpSp, registrosEncontrados=0, Op;
	pGerSp=fopen("GerenciarSprint.txt","r+b");
	if(pGerSp == NULL){
		layoutHeader();
		printf("\n--------------------------------------------------\n ATIVIDADES DO SPRINT - %s\n--------------------------------------------------\n",Status);
		printf("\n\n ERRO, NAO FOI POSSIVEL ABRIR O ARQUIVO. ARQUIVO SEM REGISTRO.\n\n ");
		system("pause");
	}
	else{
		do{
			layoutHeader();
			rewind(pGerSp);
			fread(&GerSp, sizeof(GerSprint), 1, pGerSp);
			printf("\n--------------------------------------------------\n ATIVIDADES DO SPRINT - %s\n--------------------------------------------------\n",Status);
			printf(" \n INFORME O NUMERO DO SPRINT QUE DESEJA \n VISUALIZAR AS ATIVIDADES %s: ",Status);
			scanf("%d",&OpSp);
			while(!feof(pGerSp)){
				if(!feof(pGerSp)){
					if (GerSp.cadSprint.sp == OpSp){
						if(strcmp(strupr(Status),strupr(GerSp.status))==0){
							printf("\n--------------------------------------------------\n ID: %d", GerSp.cadAtiv.id);		
							printf("\n DESCRICAO:\n %s", GerSp.cadAtiv.descricao);		
							printf("\n PROJETO: %s", GerSp.cadAtiv.cadProj.nome);
							printf("\n PROGRAMADOR: %s", GerSp.cadProg.nome);
							printf("\n TIPO DE ATIVIDADE: %s", GerSp.cadAtiv.cadTipoAtiv.nome);
							printf("\n PONTUACAO: %d", GerSp.pontuacao);
							printf("\n PERCENTUAL EM DESENVOLVIMENTO: %.2f%", GerSp.percentualDesenvolvimento);
							printf("\n STATUS: %s\n--------------------------------------------------", GerSp.status);
							registrosEncontrados=1;
						}
					}
					else{
						registrosEncontrados=0;
					}
							
					fread(&GerSp, sizeof(GerSprint), 1, pGerSp);
				}
			}
			if (registrosEncontrados == 1){
				printf("\n ");
				system("pause");
				
			}
			
			if (registrosEncontrados == 0){
				printf("\n SEM REGISTROS DE ATIVIDADES %s PARA O SPRINT INFORMADO.\n ",Status);
				system("pause");
			}
			
			do{ 
				layoutHeader();
				printf("\n--------------------------------------------------\n ATIVIDADES DO SPRINT - %s\n--------------------------------------------------\n",Status);
				printf("\n\n DESEJA REALIZAR UMA NOVA BUSCA ?\n\n [1] SIM\n [0] NAO\n\n INFORME OPCAO: ");
	            scanf("%d",&Op);
	          	if ((Op < 0) || (Op > 1)){
	          		printf("\n OPCAO INVALIDA!\n ");
					system("pause");
				}
			}while((Op < 0) || (Op > 1));
			
		}while(Op != 0);
	}
	printf("\n\n");
	
	fclose(pGerSp);			
}


//Percentual de Atividade
void dailyMeeting(){
    GerSprint GerSp;
    
	int i=0,OpSp,OpAtiv,Op;
	float Percentual=0;
	FILE *pGerSp,pAtiv;
	int verificaCadastro = 0,verificaAtivSprint=0,verificaAtivSel=0; //Boleana para verificar se registro esta cadastrado ou não
	
	//pGerSp=fopen("GerenciarSprint.txt","rb+");
	if(pGerSp == NULL){
		layoutHeader();
		printf("\n--------------------------------------------------\n PERCENTUAL DE DESNVOLVIMENTO DE ATIVIDADES DO SPRINT\n--------------------------------------------------\n");	
		printf("\n\n ERRO, NAO FOI POSSIVEL ABRIR O ARQUIVO. ARQUIVO SEM REGISTRO.\n\n ");
		system("pause");
		fclose(pGerSp);
	}
	else{
		do{
			layoutHeader();
			printf("\n--------------------------------------------------\n PERCENTUAL DE DESNVOLVIMENTO DE ATIVIDADES \n DO SPRINT\n--------------------------------------------------\n");	
			printf(" \n\n INFORME O NUMERO DO SPRINT: ");
		    scanf("%d",&OpSp);
		    
			//Listando Atividades do Sprint
			pGerSp=fopen("GerenciarSprint.txt","r+b");
			rewind(pGerSp);
			fread(&GerSp, sizeof(GerSprint), 1, pGerSp);
			printf("\n--------------------------------------------------\n ATIVIDADES DO SPRINT\n--------------------------------------------------\n");
			while(!feof(pGerSp)){
				if(!feof(pGerSp)){
					if (GerSp.cadSprint.sp == OpSp){
						printf("\n ID: %d", GerSp.cadAtiv.id);		
						printf("\n DESCRICAO:\n %s", GerSp.cadAtiv.descricao);		
						printf("\n PROJETO: %s", GerSp.cadAtiv.cadProj.nome);
						printf("\n PROGRAMADOR: %s", GerSp.cadProg.nome);
						printf("\n PONTUACAO: %d", GerSp.pontuacao);
						printf("\n PERCENTUAL EM DESENVOLVIMENTO: %.2f%", GerSp.percentualDesenvolvimento);
						printf("\n STATUS: %s\n", GerSp.status);
						verificaAtivSprint=1;
					}
							
					fread(&GerSp, sizeof(GerSprint), 1, pGerSp);
				}
			}
			printf("\n--------------------------------------------------\n ", GerSp.status);
			fclose(pGerSp);
		
			if (verificaAtivSprint == 0){
				layoutHeader();
				printf("\n--------------------------------------------------\n PERCENTUAL DE DESNVOLVIMENTO DE ATIVIDADES \n DO SPRINT\n--------------------------------------------------\n");	
				printf("\n SEM REGISTROS DE ATIVIDADES PARA O SPRINT INFORMADO.\n ");
				system("pause");
			}
			
			if (verificaAtivSprint == 1){
				pGerSp=fopen("GerenciarSprint.txt","rb+");
				printf("\n ");
				//system("pause");
				do{
					printf("\n ESCOLHA O ID DA ATIVIDADE PARA INFORMAR PERCENTUAL DE DESENVOLVIMENTO: ");
					scanf("%d",&OpAtiv);
					verificaAtivSel = 0;
					pGerSp=fopen("GerenciarSprint.txt","r+b");
					rewind(pGerSp);
						while(!feof(pGerSp)){
							fread(&GerSp,sizeof(GerSprint),1,pGerSp);
							if(!feof(pGerSp)){
								if((GerSp.cadSprint.sp == OpSp) &&(GerSp.cadAtiv.id == OpAtiv)){
									verificaAtivSel = 1;
									fclose(pGerSp);
									break;
								}
							}
						}
						if (verificaAtivSel == 0){
							printf("\n OPCAO INVALIDA!\n ");
							system("pause");
						}  
						
				}while(verificaAtivSel == 0);
				fclose(pGerSp);
				
				if(verificaAtivSel == 1){
				    pGerSp=fopen("GerenciarSprint.txt","rb+");
					rewind(pGerSp);
					while(!feof(pGerSp)){
						fread(&GerSp,sizeof(GerSprint),1,pGerSp);
				        if(!feof(pGerSp)){
							if(GerSp.cadAtiv.id == OpAtiv){
				            	do{
									printf("\n INFORME PERCENTUAL DE DESENVOLVIMENTO DA ATIVIDADE\n [0] A [100]: ");
					        		scanf("%f",&Percentual);
									if ((Percentual < 0) || (Percentual > 100)){
										printf("\n PERCENTUAL INVALIDO!\n ");
									}
								}while((Percentual < 0) || (Percentual > 100));
								GerSp.percentualDesenvolvimento = Percentual;
								if ((Percentual > 0) || (Percentual < 100)) {
									strcpy(GerSp.status, "EM DESENVOLVIMENTO");
								if (GerSp.percentualDesenvolvimento == 100){
									strcpy(GerSp.status, "CONCLUIDA");
								}
								fseek(pGerSp,i*sizeof(GerSprint), SEEK_SET);
					        	fwrite(&GerSp, sizeof(GerSprint),1,pGerSp);
					        	
								break;
				        		}
							}
							i++;
						}
					}
				}
			}
			fclose(pGerSp);
			do{ 
				layoutHeader();
				printf("\n--------------------------------------------------\n PERCENTUAL DE DESNVOLVIMENTO DE ATIVIDADES \n DO SPRINT\n--------------------------------------------------\n");	
				printf("\n\n DESEJA INFORMMAR O PERCENTUAL PARA OUTRA ATIVIDADE?\n\n [1] SIM\n [0] NAO\n\n INFORME OPCAO: ");
		        scanf("%d",&Op);
		        if ((Op < 0) || (Op > 1)){
		          	printf("\n OPCAO INVALIDA!\n");
					system("pause");
				}
			}while((Op < 0) && (Op > 1));
			if (Op == 1){
				dailyMeeting();
			}
		}while(Op != 0);
	}
}

//M A I N
main()
{	
	validaAcesso();
	
}

