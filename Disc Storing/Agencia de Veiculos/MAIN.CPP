#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

/**********************************************************\
| DEFININDO A ESTRUTURA CARRO E SUAS CARACTERÍSTICAS       |
\**********************************************************/
struct carro
{
	int ano;
	int codigo;
	char marca[25];
	char modelo[25];
	char placa[10];
	float preco;
} veiculo[MAX];

/**********************************************************\
| FUNÇÃO PARA RENOVA A LISTA, APAGANDO TODOS OS REGISTROS  |
\**********************************************************/
void inicia_lista()
{
	system("cls");
	char escolha;
	int i;
	// PERGUNTA FINAL ANTES DE DELETAR TUDO
	printf("\nDeseja renovar a lista? s/n");
	escolha=getch();
	if(escolha=='s')
	{
		// DELETANDO TODOS OS REGISTROS
		for(i=0;i<MAX;i++)
 		{
  			veiculo[i].marca[0] = '\0';
  			veiculo[i].preco = 0;
		}
	}
}

/**********************************************************\
| FUNÇÃO PARA BUSCAR UM ESPAÇO LIVRE PARA REALIZAR NOVOS   |
| CADASTROS                                                |
\**********************************************************/
int busca_espaco()
{
	int i;
	// RETORNA O PRIMEIRO ESPAÇO QUE CONTIVER NULO NO REGISTRO NOME[0]
	for(i=0;veiculo[i].marca[0]&&i<MAX;i++);
	if(i==MAX) return -1;
	return i;
}

/**********************************************************\
| FUNÇÃO QUE DESENHA O MENU INICIAL E SUAS OPÇÕES          |
\**********************************************************/
void menu_inicial()
{
	system("cls");
	char escolha;
	int i;
	// EXIBIÇÃO DO MENU DE ESCOLHAS
	printf("\n\n\n\n\n\n\n             ");
	putchar(201); for(i=0;i<31;i++) printf("%c",205); putchar(187);
	printf("\n             %c    AGENCIA DE VEICULOS AV     %c   \n             ",186,186);
	putchar(204); for(i=0;i<31;i++) printf("%c",205); putchar(185);
	printf("\n             %cMENU PRINCIPAL                 %c",186,186);
	printf("\n             %c<1> Cadastro                   %c",186,186);
	printf("\n             %c<2> Exclusao                   %c",186,186);
	printf("\n             %c<3> Alteracao                  %c",186,186);
	printf("\n             %c<4> Relatorio                  %c",186,186);
	printf("\n             %c<5> Sair                       %c",186,186);
	printf("\n             %c<6> Renovar lista              %c\n             ",186,186);
	putchar(200); for(i=0;i<31;i++) printf("%c",205); putchar(188);
	// DESENHA UM CAMINHÃOZINHO TOSCO
	printf("\n\n\n             ");
	printf("     _________________\n             ");
	printf("    |                 ||__\n             ");
	printf("    |   VEICULOS AV   ||  \\__\n             ");
	printf("    |                 ||     \\\n             ");
	printf("    |_________________||  _  |\n             ");
	printf("    /=/ \\=/ \\======/ \\==\\/ \\/=\\\n             ");
	printf("      \\_/ \\_/      \\_/   \\_/");
}

/**********************************************************\
| FUNÇÃO PARA CADASTRAR NOVOS VEÍCULOS                     |
\**********************************************************/
void cadastrar()
{
	system("cls");
    printf("|----------------------|\n");
    printf("| CADASTRO DE VEICULOS |\n");
    printf("|----------------------|\n\n");
	int posicao;
	char escolha;
	// VERIFICA SE HÁ ESPAÇO PARA UM NOVO CADASTRO
	posicao=busca_espaco();
	if(posicao==-1)
	{
		printf("\nLista cheia");
		getch();
		return;
	}
	// ATRIBUI AUTOMATICAMENTE O CÓDIGO
	veiculo[posicao].codigo = posicao+1;
	// RECEBENDO A MARCA
	printf("Digite a marca: ");
	do{
		gets(veiculo[posicao].marca);
		if(strlen(veiculo[posicao].marca)>20)
			printf("maximo 20 caracteres e minimo 1\n");
	}while(strlen(veiculo[posicao].marca)>20||strlen(veiculo[posicao].marca)<1);
	// RECEBENDO O MODELO
	printf("Digite o modelo: ");
	do{
		gets(veiculo[posicao].modelo);
		if(strlen(veiculo[posicao].marca)>20)
			printf("maximo 20 caracteres e minimo 1\n");
	}while(strlen(veiculo[posicao].marca)>20||strlen(veiculo[posicao].marca)<1);
	// RECEBENDO A PLACA
	printf("Digite a placa: ");
	do{
		gets(veiculo[posicao].placa);
		if(strlen(veiculo[posicao].placa)!=8)
  			printf("placas tem 8 caracteres\n");
	}while(strlen(veiculo[posicao].placa)!=8);
	// RECEBENDO O ANO
	printf("Digite o ano: ");
	do{
		scanf("%d",&veiculo[posicao].ano);
		if(veiculo[posicao].ano<1900||veiculo[posicao].ano>3000)
  			printf("data desatualizada\n");
	}while(veiculo[posicao].ano<1900||veiculo[posicao].ano>3000);
	// RECEBENDO O PREÇO
	printf("Digite o preco: ");
	do{
		scanf("%f",&veiculo[posicao].preco);
		if(veiculo[posicao].preco<=0||veiculo[posicao].preco>999999)
  			printf("fora de escala\n");
	}while(veiculo[posicao].preco<=0||veiculo[posicao].preco>999999);
	// PERGUNTANDO SOBRE UM NOVO CADASTRAMENTO
	printf("\nDeseja cadastrar outro veiculo? s/n");
	escolha=getch();
	if(escolha=='s'||escolha=='S')
		cadastrar();
}

/**********************************************************\
| FUNÇÃO PARA EXCLUIR VEÍCULOS JÁ CADASTRADOS              |
\**********************************************************/
void excluir()
{
	system("cls");
	printf("|----------------------|\n");
    printf("| EXCLUSAO DE VEICULOS |\n");
    printf("|----------------------|\n\n");
 	int posicao;
	char escolha;
	// RECEBENDO O CÓDIGO DO VEÍCULO A SER EXCLUÍDO E VERIFICANDO-O
	printf("Digite o codigo do veiculo a ser excluido: ");
	scanf("%d",&posicao);
	if(posicao<=0||posicao>MAX||veiculo[posicao-1].marca[0]=='\0')
	{
	    printf("\nveiculo nao consta nos cadastros");
	    getch();
    }
    else
    {
    	// MOSTRANDO OS DADOS DO VEÍCULO SELECIONADO PARA SER EXCLUÍDO
	    printf("\nMARCA ---> %s\n",veiculo[posicao-1].marca);
	    printf("MODELO --> %s\n",veiculo[posicao-1].modelo);
	    printf("PLACA ---> %s\n",veiculo[posicao-1].placa);
	    printf("ANO -----> %d\n",veiculo[posicao-1].ano);
	    printf("PRECO ---> %.2f\n",veiculo[posicao-1].preco);
	    printf("\nDeseja excluir esse veiculo? s/n");
	    escolha=getch();
	    // PERGUNTA FINAL ANTES DA EXCLUSÃO
	    if(escolha=='s'||escolha=='S')
	    {
	         veiculo[posicao-1].marca[0]='\0';
	         veiculo[posicao-1].preco=0;
      	}
     }
}

/**********************************************************\
| FUNÇÃO PARA ALTERAR VEÍCULOS JÁ CADASTRADOS              |
\**********************************************************/
void alteracao()
{
	system("cls");
	printf("|-----------------------|\n");
    printf("| ALTERACAO DE VEICULOS |\n");
    printf("|-----------------------|\n\n");
	int posicao;
	// RECEBENDO O CÓDIGO DO VEÍCULO A SER ALTERADO E VERIFICANDO-O
	printf("Digite o codigo do veiculo a ser alterado: ");
	scanf("%d",&posicao); posicao--;
	if(posicao<0||posicao>MAX||veiculo[posicao].marca[0]=='\0')
	{
	    printf("\nveiculo nao consta nos cadastros");
	    getch();
    }
    else
    {
    	// RECEBENDO OS NOVOS DADOS
		printf("Insira os novos dados: \n\n");
		printf("Digite a placa: ");
		do{
			scanf("%s",&veiculo[posicao].placa);
			if(strlen(veiculo[posicao].placa)!=8)
   				printf("placas tem 8 caracteres\n");
		}while(strlen(veiculo[posicao].placa)!=8);
		printf("Digite o preco: ");
		do{
			scanf("%f",&veiculo[posicao].preco);
			if(veiculo[posicao].preco<=0||veiculo[posicao].preco>999999)
   				printf("fora de escala\n");
		}while(veiculo[posicao].preco<=0||veiculo[posicao].preco>999999);
	}
}

/**********************************************************\
| FUNÇÃO PARA LISTAR OS VEÍCULOS PELO CÓDIGO               |
\**********************************************************/
void listagem_codigo()
{
	system("cls");
	printf("|---------------------|\n");
    printf("| LISTAGEM POR CODIGO |\n");
    printf("|---------------------|\n\n");
	int i,j,k=0;
	printf("COD   MARCA               MODELO              PLACA      ANO    PRECO\n");
	// LISTANDO TODOS OS VEÍCULOS POR CÓDIGO
	for(i=0;i<MAX;i++)
	{
		if(veiculo[i].marca[0]!='\0')
		{
			k++;
			printf("%.3d   ", veiculo[i].codigo);
			printf("%s", veiculo[i].marca);
			for(j=0;j<20-strlen(veiculo[i].marca);j++) printf(" ");
			printf("%s", veiculo[i].modelo);
			for(j=0;j<20-strlen(veiculo[i].modelo);j++) printf(" ");
			printf("%s", veiculo[i].placa);
			printf("   %d   ", veiculo[i].ano);
			printf("RS %.2f\n", veiculo[i].preco);
		}
		// ESPERANDO UMA TECLA QUALQUER PARA DAR TEMPO DA LISTAGEM
		if((k+1)%25==0)
  		{
  			k=0;
    		getch();
		}
	}
	getch();
}

/**********************************************************\
| FUNÇÃO PARA LISTAR OS VEÍCULOS PELO PREÇO                |
\**********************************************************/
void listagem_preco()
{
	system("cls");
	printf("|--------------------|\n");
    printf("| LISTAGEM POR PRECO |\n");
    printf("|--------------------|\n\n");
	int aux=0,i,j=0,k=0,vetor[MAX];
	for(i=0;i<MAX;i++) vetor[i]=i;
	// ORGANIZANDO UM VETOR PARA SERVIR DE BASE PARA A LISTAGEM
	for(i=0;i<MAX-1;i++)
	{
		if(veiculo[vetor[i]].preco<veiculo[vetor[i+1]].preco)
 	    {
            if(i!=MAX)
            {
				aux=vetor[i];
				vetor[i]=vetor[i+1];
				vetor[i+1]=aux;
				i=0;
				j=0;
			}
			else
            {
                if(veiculo[vetor[i]].preco>veiculo[vetor[i-1]].preco)
                aux=vetor[i];
				vetor[i]=vetor[i+1];
				vetor[i+1]=aux;
				i=0;
				j=0;
			}
		}
	}
	printf("COD   MARCA               MODELO              PLACA      ANO    PRECO\n");
	// LISTANDO TODOS OS VEÍCULOS POR PREÇO
	for(i=0;i<MAX;i++)
	{
		if(veiculo[vetor[i]].marca[0]!='\0')
		{	
			k++;
			printf("%.3d   ", veiculo[vetor[i]].codigo);
			printf("%s", veiculo[vetor[i]].marca);
			for(j=0;j<20-strlen(veiculo[vetor[i]].marca);j++) printf(" ");
			printf("%s", veiculo[vetor[i]].modelo);
			for(j=0;j<20-strlen(veiculo[vetor[i]].modelo);j++) printf(" ");
			printf("%s", veiculo[vetor[i]].placa);
			printf("   %d   ", veiculo[vetor[i]].ano);
			printf("RS %.2f\n", veiculo[vetor[i]].preco);
		}
		// ESPERANDO UMA TECLA QUALQUER PARA DAR TEMPO DA LISTAGEM
		if((k+1)%25==0)
  		{
    		getch();
    		k=0;
		}
	}
	getch();
}

/**********************************************************\
| FUNÇÃO PARA ABRIR O MENU DE LISTAGENS                    |
\**********************************************************/
void relatorio()
{
	system("cls");
	printf("|------------|\n");
    printf("| RELATORIOS |\n");
    printf("|------------|\n\n");
    char opcao;
    // MOSTRA AS POSSÍVEIS LISTAGENS E SELECIONA-A
	printf("Escolha o tipo de listagem\n");
	printf("<1> - Listagem por codigo\n");
	printf("<2> - Listagem por preco\n");
 	opcao=getch();
	switch(opcao)
	{
		case 49: listagem_codigo(); break;
		case 50: listagem_preco(); break;
		default: relatorio();
	}
}

/**********************************************************\
| FUNÇÃO QUE GRAVA OS DADOS E SAI DO PROGRAMA              |
\**********************************************************/
void sair(FILE *arquivo)
{
	int i;
	// VERIFICANDO A ABERTURA DE ARQUIVO, SALVANDO DADOS E GRAVANDO-OS
	arquivo=fopen("dados.dat","wb");
	if(arquivo==NULL)
	{
		printf("\nerro na gravacao");
		getch();
		exit(0);
	}
	fwrite(veiculo,sizeof(veiculo),1,arquivo);
	fclose(arquivo);
	exit(0);
}

/**********************************************************\
| MAIN(), LÊ OS DADOS JÁ GRAVADOS ANTERIORMENTE, CHAMA AS  |
| DEMAIS FUNÇÕES, ETC...                                   |
\**********************************************************/
int main()
{
	// ABRINDO O ARQUIVO, VERIFICANDO-O E DEPOIS LENDO-O
	FILE *arq;
	arq=fopen("dados.dat","rb");
	if(arq==NULL)
	{
		printf("\nerro na abertura de dados");
		getch();
		exit(0);
	}
	fread(veiculo,sizeof(veiculo),1,arq);
	fclose(arq);
	char escolha;
	// LAÇO PRINCIPAL DO PROGRAMA
	for(;;)
	{
		menu_inicial();
		escolha=getch();
		switch(escolha)
		{
			case 49: cadastrar(); break;
			case 50: excluir(); break;
			case 51: alteracao(); break;
			case 52: relatorio(); break;
			case 53: sair(arq); break;
			case 54: inicia_lista(); break;
			default: system("cls");
		}
	}
	return 0;
}
