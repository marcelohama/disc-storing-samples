#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100

/**********************************************************************\
| FUNÇÃO QUE ANALIZA SE UMA STRING ESTÁ CONTIDA EM OUTRA, QUE É USADA  |
| NAS PESQUISAS E RELATÓRIOS                                           |
\**********************************************************************/
int str_em_str(char s1[], char s2[])
{
	int pos1=0,pos2,aux=0;
	while(s1[pos1]!='\0')
	{
		pos2=0;
		while(s2[pos2]!='\0')
		{
			if(s1[pos1+pos2]!=s2[pos2]) break;
			pos2++;
  		}
  		if(s2[pos2]=='\0') aux=1;
    	pos1++;
	}
	return aux;
}

/**********************************************************************\
| DEFININDO A ESTRUTURA DOS PRODUTOS, SUAS CARACTERÍSTICAS             |
\**********************************************************************/
struct mercadoria
{
	int estoque;
	int codigo;
	char descricao[31];
	float custo;
	float venda;
} produto[MAX];

/**********************************************************************\
| DEFININDO A ESTRUTURA DOS NEGÓCIOS, SUAS CARACTERÍSTICAS             |
\**********************************************************************/
struct negocios
{
	int codigo;
	char negociante[41];
	char data[11];
	int quantidade;
} compra[MAX],venda[MAX];

/**********************************************************************\
| FUNÇÃO QUE EXIBE O MENU INICIAL, MOSTRANDO AS OPÇÕES E REFERENCIANDO |
| AS DEMAIS FUNÇÕES DO PROGRAMA                                        |
\**********************************************************************/
void menu()
{   system("cls");
	printf("\n");
	printf("********************************************************************************\n");
	printf("*                                                                              *\n");
	printf("*                          CONTROLE COMPRA & VENDA                             *\n");
	printf("*                                                                              *\n");
	printf("********************************************************************************\n");
	printf("*                                                                              *\n");
	printf("*   	MENU PRINCIPAL                                                         *\n");
	printf("*   	Pressione <1> para CADASTRAR NOVO PRODUTO                              *\n");
	printf("*   	Pressione <2> para EXCLUIR PRODUTO                                     *\n");
	printf("*   	Pressione <3> para ALTERAR PRODUTO                                     *\n");
	printf("*   	Pressione <4> para PESQUISA POR NOME                                   *\n");
	printf("*   	Pressione <5> para EFETUAR COMPRA                                      *\n");
	printf("*   	Pressione <6> para EFETUAR VENDA                                       *\n");
	printf("*   	Pressione <7> para RELATORIO                                           *\n");
	printf("*   	Pressione <8> para SAIR                                                *\n");
	printf("*   	Pressione <9> para RENOVAR LISTA                                       *\n");
	printf("*                                                                              *\n");
	printf("*                                                                              *\n");
	printf("*                                                                              *\n");
	printf("*                                                                              *\n");
	printf("*                                                                              *\n");
	printf("*                                                                              *\n");
	printf("*                                                                              *\n");
	printf("********************************************************************************\n");
}

/**********************************************************************\
| FUNÇÕES PARA BUSCAR ESPAÇOS LIVRES PARA NOVOS CADASTROS OU NEGÒCIOS  |
\**********************************************************************/
int busca_mercadoria()
{
	int i;
	for(i=0;produto[i].descricao[0]!='\0'&&i<MAX;++i);
	if(i==MAX) return -1;
	else return i;
}
int busca_compra()
{
	int i;
	for(i=0;compra[i].negociante[0]!='\0'&&i<MAX;++i);
	if(i==MAX) return -1;
	else return i;
}
int busca_venda()
{
	int i;
	for(i=0;venda[i].negociante[0]!='\0'&&i<MAX;++i);
	if(i==MAX) return -1;
	else return i;
}

/**********************************************************************\
| FUNÇÃO PARA LIMPAR A LISTA DE REGISTROS, APAGANDO-A TODA             |
\**********************************************************************/
void limpar()
{
	system("cls");
	printf("|-----------|\n");
	printf("| DELETADOR |\n");
	printf("|-----------|\n\n");
	int i;
	char escolha,tecla;
	printf("<1> Renovar a lista de produtos\n<2> Renovar a agenda\n");
	tecla=getch();
	switch(tecla)
	{
	    case '1':
	         // AVISO FINAL ANTES DE LIMPAR OS REGISTROS
	         printf("Deseja realmente limpar a lista e apagar todos os registros? s/n");
	         escolha=getch();
	         // APAGANDO OS PRODUTOS CADASTRADOS
	         if(escolha=='s'||escolha=='S')
	         {
	             for(i=0;i<MAX;i++)
	             {
	                 produto[i].estoque=0;
	                 produto[i].descricao[0]='\0';
                 }
             }
             break;
	    case '2':
	         // AVISO FINAL ANTES DE LIMPAR OS REGISTROS
	         printf("Deseja realmente limpar a lista e apagar todos os registros? s/n");
	         escolha=getch();
	         // APAGANDO TODA A AGENDA
	         if(escolha=='s'||escolha=='S')
	         {
                 for(i=0;i<MAX;i++)
                 {
                     venda[i].negociante[0]='\0';
                     compra[i].negociante[0]='\0';
	        	 }
        	 }
        	 break;
	    default : menu();
    }
}

/**********************************************************************\
| FUNÇÃO PARA CADASTRAR UM NOVO PRODUTO (SÓ É POSSÍVEL REALIZAR COMPRA |
| E VENDA COM PRODUTOS JÁ CADASTRADOS ANTERIORMENTE)                   |
\**********************************************************************/
void cadastro()
{
	system("cls");
	printf("|---------------|\n");
	printf("| CADASTRAMENTO |\n");
	printf("|---------------|\n\n");
	int i,posicao;
	char escolha;
	// BUSCANDO UM ESPAÇO LIVRE PARA CADASTRAR E VERIFICANDO SUA VALIDEZ
	posicao=busca_mercadoria();
	if(posicao==-1)
	{
		printf("\nLista cheia");
		getch();
	}
	else
	{
		// ATRIBUINDO O CÓDIGO DO PRODUTO AUTOMATICAMENTE
		produto[posicao].codigo=posicao;
		// INSERINDO UM NOME OU DESCRIÇÃO PARA O PRODUTO
		printf("Insira a descricao do produto: ");
		do{
			gets(produto[posicao].descricao);
			if(strlen(produto[posicao].descricao)>30)
				printf("maximo de 30 caracteres\n");
		}while(strlen(produto[posicao].descricao)>30);
		// INSERINDO O PREÇO DE CUSTO
		printf("Insira o preco de custo: ");
		do{
			scanf("%f",&produto[posicao].custo);
			if(produto[posicao].custo<=0||produto[posicao].custo>=10000)
				printf("valores menores que 10000, estritamente positivos\n");
		}while(produto[posicao].custo<=0||produto[posicao].custo>=10000);
		// INSERINDO O PREÇO DE VENDA
		printf("Insira o preco de venda: ");
		do{
			scanf("%f",&produto[posicao].venda);
			if(produto[posicao].venda<=0||produto[posicao].custo>=10000)
				printf("valores menores que 10000, estritamente positivos\n");
		}while(produto[posicao].custo<=0||produto[posicao].custo>=10000);
	}
	printf("\n\nDeseja cadastrar outro produto? s/n");
	escolha=getch();
	if(escolha=='s'||escolha=='S') cadastro();
}

/**********************************************************************\
| FUNÇÃO PARA EXCLUIR UM PRODUTO JÁ CADASTRADO                         |
\**********************************************************************/
void exclusao()
{
	system("cls");
	printf("|----------|\n");
	printf("| EXCLUSAO |\n");
	printf("|----------|\n\n");
	int posicao;
	char escolha;
	// RECEBENDO O CÓDIGO DO PRODUTO A SER EXCLUÍDO E VERIFICANDO SUA VALIDEZ
	printf("Digite o codigo do produto a ser excluido: ");
	scanf("%d",&posicao);
	if(posicao<0||posicao>=MAX||produto[posicao].descricao[0]=='\0')
	{
		printf("\ncodigo nao cadastrado ou inexistente");
		getch();
	}
	else
	{
		// MOSTRANDO OS DADOS DO PRODUTO A SER EXCLUÍDO E DANDO O AVISO FINAL
		printf("\nCodigo --------> %3.d\n",produto[posicao].codigo);
		printf("Estoque -------> %3.d\n",produto[posicao].estoque);
		printf("Descricao -----> %s\n",produto[posicao].descricao);
		printf("Preco/custo ---> RS %5.2f\n",produto[posicao].custo);
		printf("Preco/venda ---> RS %5.2f\n",produto[posicao].venda);
		printf("\nDeseja realmente excluir este produto? s/n");
		escolha=getch();
		if(escolha=='s'||escolha=='S')
 			produto[posicao].descricao[0]='\0';
	}
}

/**********************************************************************\
| FUNÇÃO PARA ALTERAR UM PRODUTO JÁ CADASTRADO                         |
\**********************************************************************/
void alteracao()
{
	system("cls");
	printf("|-----------|\n");
	printf("| ALTERACAO |\n");
	printf("|-----------|\n\n");
	int posicao;
	// RECEBENDO O CÓDIGO DO PRODUTO A SER ALTERADO E VERIFICANDO SUA VALIDEZ
	printf("Digite o codigo do produto a ser excluido: ");
	scanf("%d",&posicao);
	if(posicao<0||posicao>=MAX||produto[posicao].descricao[0]=='\0')
	{
		printf("\ncodigo nao cadastrado ou inexistente");
		getch();
	}
	else
	{
		printf("Insira os novos dados: \n\n");
		// INSERINDO O PREÇO DE CUSTO
		printf("Insira o preco de custo: ");
		do{
			scanf("%f",&produto[posicao].custo);
			if(produto[posicao].custo<=0||produto[posicao].custo>=10000)
				printf("valores menores que 10000, estritamente positivos\n");
		}while(produto[posicao].custo<=0||produto[posicao].custo>=10000);
		// INSERINDO O PREÇO DE VENDA
		printf("Insira o preco de venda: ");
		do{
			scanf("%f",&produto[posicao].venda);
			if(produto[posicao].venda<=0||produto[posicao].custo>=10000)
				printf("valores menores que 10000, estritamente positivos\n");
		}while(produto[posicao].custo<=0||produto[posicao].custo>=10000);
	}
}

/**********************************************************************\
| FUNÇÃO PARA PESQUISAR POR NOME OU PARTE DO NOME UM DADO PRODUTO      |
\**********************************************************************/
void pesquisa()
{
	system("cls");
	printf("|----------|\n");
	printf("| PESQUISA |\n");
	printf("|----------|\n\n");
	char str[31];
	int i,j=0;
	// RECEBENDO O NOME OU PARTE DELE PARA PESQUISÁ-LO
	printf("Insira o nome ou parte do nome do produto a ser pesquisado: ");
	scanf("%s",&str);
	// EXIBINDO OS RESULTADOS ENCONTRADOS
	printf("\n\nCOD   DESCRICAO                      PRECO CUSTO      PRECO VENDA       \n");
	for(i=0;i<MAX;i++)
	{
		if(str_em_str(produto[i].descricao,str)!=0&&produto[i].descricao[0]!='\0')
		{
			printf("%.3d   ", produto[i].codigo);
			printf("%s", produto[i].descricao);
			for(j=0;j<31-strlen(produto[i].descricao);j++) printf(" ");
			printf("RS %5.2f         ", produto[i].custo);
			printf("RS %5.2f\n", produto[i].venda);
		}
	}
	getch();
}

/**********************************************************************\
| FUNÇÃO PARA A REALIZAÇÃO DE COMPRAS, PODENDO SOMENTE SER REALIZADA   |
| COM PRODUTOS JÁ ANTERIORMENTE CADASTRADOS                            |
\**********************************************************************/
void gasto()
{
	system("cls");
	printf("|--------|\n");
	printf("| COMPRA |\n");
	printf("|--------|\n\n");
	int cod,posicao;
	char escolha;
	// RECEBENDO O CÓDIGO DO PRODUTO A SER COMPRADO E VERIFICANDO-O
	printf("Insira o codigo do produto: ");
	scanf("%d",&cod);
	if(produto[cod].descricao[0]=='\0')
	{
		printf("\ncodigo nao cadastrado ou nao valido");
		getch();
	}
	else
	{
		// BUSCANDO UM ESPAÇO LIVRE PARA MARCAR NO RELATÓRIO
		posicao=busca_compra();
		compra[posicao].codigo=cod;
		// INSERINDO O NOME DO FORNECEDOR
		printf("\nInsira o nome do fornecedor: ");
		do{
			scanf("%s",&compra[posicao].negociante);
			if(strlen(compra[posicao].negociante)>40)
				printf("maximo de 40 caracteres\n");
		}while(strlen(compra[posicao].negociante)>40);
		// INSERINDO A DATA DA COMPRA
		printf("\nInsira a data da compra: ");
		do{
		    scanf("%s",&compra[posicao].data);
			if(strlen(compra[posicao].data)!=10)
				printf("10 caracteres\n");
		}while((int)strlen(compra[posicao].data)!=10);
		// INSERINDO A QUANTIA COMPRADA
		printf("\nInsira a quantidade comprada: ");
		do{
			scanf("%d",&compra[posicao].quantidade);
			if(compra[posicao].quantidade<=0||compra[posicao].quantidade>=10000)
				printf("valores menores que 10000, estritamente positivos\n");
		}while(compra[posicao].quantidade<=0||compra[posicao].quantidade>=10000);
		// MOSTRANDO OS DADOS DA COMPRA A SER FEITA
		printf("\nProduto ------> %s",produto[cod].descricao);
		printf("\nFornecedor ---> %s",compra[posicao].negociante);
		printf("\nData ---------> %s",compra[posicao].data);
		printf("\nQuantidade ---> %d",compra[posicao].quantidade);
		// ADICIONANDO AO ESTOQUE OU NÃO EM FUNÇÃO DA ESCOLHA
		printf("\n\nDeseja efetivar a compra? s/n");
		escolha=getch();
		if(escolha=='s'||escolha=='S')
			produto[cod].estoque+=compra[posicao].quantidade;
		else compra[posicao].negociante[0]='\0';
	}
}

/**********************************************************************\
| FUNÇÃO PARA A REALIZAÇÃO DE VENDAS, PODENDO SOMENTE SER REALIZADA    |
| COM PRODUTOS JÁ ANTERIORMENTE CADASTRADOS                            |
\**********************************************************************/
void lucro()
{
	system("cls");
	printf("|-------|\n");
	printf("| VENDA |\n");
	printf("|-------|\n\n");
	int cod,posicao;
	char escolha;
	// RECEBENDO O CÓDIGO DO PRODUTO A SER VENDIDO E VERIFICANDO-O
	printf("Insira o codigo do produto: ");
	scanf("%d",&cod);
	if(produto[cod].descricao[0]=='\0')
	{
		printf("\ncodigo nao cadastrado ou nao valido");
		getch();
	}
	else
	{
		// BUSCANDO UM ESPAÇO LIVRE PARA MARCAR NO RELATÓRIO
		posicao=busca_venda();
		venda[posicao].codigo=cod;
		// INSERINDO O NOME DO CLIENTE
		printf("\nInsira o nome do cliente: ");
		do{
			scanf("%s",&venda[posicao].negociante);
			if(strlen(venda[posicao].negociante)>40)
				printf("maximo de 40 caracteres\n");
		}while(strlen(venda[posicao].negociante)>40);
		// INSERINDO A DATA DA VENDA
		printf("\nInsira a data da venda: ");
		do{
			scanf("%s",&venda[posicao].data);
			if((int)strlen(venda[posicao].data)!=10)
				printf("10 caracteres\n");
		}while(strlen(venda[posicao].data)!=10);
		// INSERINDO A QUANTIA VENDIDA
		printf("\nInsira a quantidade vendida: ");
		do{
			scanf("%d",&venda[posicao].quantidade);
			if(venda[posicao].quantidade<=0||venda[posicao].quantidade>=10000)
				printf("valores menores que 10000, estritamente positivos\n");
		}while(venda[posicao].quantidade<=0||venda[posicao].quantidade>=10000);
		// MOSTRANDO OS DADOS DA COMPRA A SER FEITA
		printf("\nProduto ------> %s",produto[cod].descricao);
		printf("\nCliente ------> %s",venda[posicao].negociante);
		printf("\nData ---------> %s",venda[posicao].data);
		printf("\nQuantidade ---> %d",venda[posicao].quantidade);
		// RETIRANDO DO ESTOQUE OU NÃO EM FUNÇÃO DA ESCOLHA E DA VALIDEZ
		printf("\n\nDeseja efetivar a compra? s/n");
		escolha=getch();
		if((escolha=='s'||escolha=='S')&&produto[cod].estoque-venda[posicao].quantidade>=0)
			produto[cod].estoque-=venda[posicao].quantidade;
		else
		{
			if(produto[cod].estoque-venda[posicao].quantidade<0)
			{
				printf("\ncompra cancelada por falta de produto no estoque");
				getch();
			}
			venda[posicao].negociante[0]='\0';
		}
	}
}

/**********************************************************************\
| FUNÇÃO PARA A EXIBIÇÃO DE RELATÓRIOS DAS COMPRAS, VENDAS E PRODUTOS  |
\**********************************************************************/
void relatorio()
{
	system("cls");
	printf("|------------|\n");
	printf("| RELATORIOS |\n");
	printf("|------------|\n\n");
	int i,j;
	char str[40],escolha;
	printf("<1> Produtos cadastrados\n<2> Produtos em estoque\n");
	printf("<3> Vendas\n<4> Vendas de um produto\n");
	printf("<5> Compras\n<6> Compras de um produto\n");
	printf("<7> Vendas por mes\n<8> Compras por mes\n");
	escolha=getch();
	switch(escolha)
	{
		case 49:
				system("cls");
				j=0;
  				printf("PRODUTOS CADASTRADOS\nCod   Preco/custo   Preco/venda    Descricao\n");
  				for(i=0;i<MAX;i++)
				{
					if(produto[i].descricao[0]!='\0')
					{
						printf("%3.1d   RS %5.2f      RS %5.2f       %s\n",i,produto[i].custo,produto[i].venda,produto[i].descricao);
						j++;
					}
     				if(j==30)
					{
						getch();
						j=0;
					}
				}
				getch();
				break;
		case 50:
				system("cls");
				j=0;
				printf("PRODUTOS EM ESTOQUE\nCod   Estoque   Descricao\n");
				for(i=0;i<MAX;i++)
				{
					if(produto[i].descricao[0]!='\0'&&produto[i].estoque!=0)
					{
						printf("%3.1d   %3.d       %s\n",i,produto[i].estoque,produto[i].descricao);
						j++;
					}
     				if(j==30)
					{
						getch();
						j=0;
					}
				}
				getch();
				break;
		case 51:
				system("cls");
				j=0;
				printf("VENDAS\nCod   Data         Quantia   Cliente\n");
				for(i=0;i<MAX;i++)
				{
					if(venda[i].negociante[0]!='\0')
					{
						printf("%3.1d   %s   %3.d       %s\n",venda[i].codigo,venda[i].data,venda[i].quantidade,venda[i].negociante);
						j++;
					}
					if(j==30)
					{
						getch();
						j=0;
					}
				}
				getch();
				break;
		case 52:
				system("cls");
				j=0;
				printf("VENDAS DE UM PRODUTO\n");
				printf("Insira o nome ou parte do nome do produto a ser pesquisado: ");
				gets(str);
				printf("Cod   Data         Quantia   Cliente\n");
				for(i=0;i<MAX;i++)
				{
					if(str_em_str(produto[i].descricao,str)!=0&&venda[i].negociante[0]!='\0')
					{
						printf("%3.1d   %s   %3.d       %s\n",venda[i].codigo,venda[i].data,venda[i].quantidade,venda[i].negociante);
						j++;
					}
     				if(j==30)
     				{
						getch();
						j=0;
					}
				}
				getch();
				break;
		case 53:
				system("cls");
				j=0;
				printf("COMPRAS\nCod   Data         Quantia   Fornecedor\n");
				for(i=0;i<MAX;i++)
				{
					if(compra[i].negociante[0]!='\0')
					{
						printf("%3.1d   %s   %3.d       %s\n",compra[i].codigo,compra[i].data,compra[i].quantidade,compra[i].negociante);
						j++;
					}
     				if(j==30)
					{
						getch();
						j=0;
					}
				}
				getch();
				break;
		case 54:
				system("cls");
				j=0;
				printf("COMPRAS DE UM PRODUTO\n");
				printf("Insira o nome ou parte do nome do produto a ser pesquisado: ");
				gets(str);
				printf("Cod   Data         Quantia   Fornecedor\n");
				for(i=0;i<MAX;i++)
				{
					if(str_em_str(produto[i].descricao,str)!=0&&compra[i].negociante[0]!='\0')
					{
						printf("%3.1d   %s   %3.d       %s\n",compra[i].codigo,compra[i].data,compra[i].quantidade,compra[i].negociante);
						j++;
					}
					if(j==30)
					{
						j=0;
						getch();
					}
				}
				getch();
				break;
		case 55:
				system("cls");
				printf("VENDAS POR MES\n");
				printf("Insira o mes a ser pesquisado: ");
				scanf("%d",&j);
				if(j<1||j>12)
				{
				    printf("\nmes incompativel");
				    getch();
                }
                else
				printf("Cod   Quantia   Cliente\n");
				for(i=0;i<MAX;i++)
				{
				    if((((int)venda[i].data[3]-48)*10+((int)venda[i].data[4]-48)==j)&&(produto[i].descricao[0]!='\0'))
				    printf("%3.1d   %3.d       %s\n",venda[i].codigo,venda[i].quantidade,venda[i].negociante);
                }
                getch();
                break;
		case 56:
                system("cls");
				printf("COMPRAS POR MES\n");
				printf("Insira o mes a ser pesquisado: ");
				scanf("%d",&j);
				if(j<1||j>12)
				{
				    printf("\nmes incompativel");
				    getch();
                }
                else
				printf("Cod   Quantia   Cliente\n");
				for(i=0;i<MAX;i++)
				{
				    if((((int)compra[i].data[3]-48)*10+((int)compra[i].data[4]-48)==j)&&(produto[i].descricao[0]!='\0'))
				    printf("%3.1d   %3.d       %s\n",compra[i].codigo,compra[i].quantidade,compra[i].negociante);
                }
                getch();
                break;
		default: break;
	}
}

/************************************************************************\
| CARREGANDO DADOS RECEBIDOS PELO PROGRAMA E SALVANDO-OS COMO REGISTROS  |
| EM ARQUIVOS BINÁRIOS                                                   |
\************************************************************************/
void carregador(FILE *arq)
{
	arq=fopen("mercadoria.dat","rb");
	if(arq==NULL)
	{
		printf("\nerro na gravacao");
		getch();
		exit(0);
	}
	fread(produto,sizeof(produto),1,arq);
	fclose(arq);
	arq=fopen("compra.dat","rb");
	if(arq==NULL)
	{
		printf("\nerro na gravacao");
		getch();
		exit(0);
	}
	fread(compra,sizeof(compra),1,arq);
	fclose(arq);
	arq=fopen("venda.dat","rb");
	if(arq==NULL)
	{
		printf("\nerro na gravacao");
		getch();
		exit(0);
	}
	fread(venda,sizeof(venda),1,arq);
	fclose(arq);
}

/**********************************************************************\
| GRAVANDO DADOS RECEBIDOS PELO PROGRAMA E SALVANDO-OS COMO REGISTROS  |
| EM ARQUIVOS BINÁRIOS                                                 |
\**********************************************************************/
void gravacao(FILE *arq)
{
	arq=fopen("mercadoria.dat","wb");
	if(arq==NULL)
	{
		printf("\nerro na gravacao");
		getch();
		exit(0);
	}
	fwrite(produto,sizeof(produto),1,arq);
	fclose(arq);
	arq=fopen("compra.dat","wb");
	if(arq==NULL)
	{
		printf("\nerro na gravacao");
		getch();
		exit(0);
	}
	fwrite(compra,sizeof(compra),1,arq);
	fclose(arq);
	arq=fopen("venda.dat","wb");
	if(arq==NULL)
	{
		printf("\nerro na gravacao");
		getch();
		exit(0);
	}
	fwrite(venda,sizeof(venda),1,arq);
	fclose(arq);
	exit(0);
}

/**********************************************************************\
| A TODA PODEROSA MAIN(), CHAMANDO AS DEMAIS FUNÇÕES DO PROGRAMA       |
\**********************************************************************/
int main()
{
	FILE *dados;
	carregador(dados);
	char escolha;
	for(;;)
	{
		menu();
		escolha=getch();
		switch(escolha)
		{
			case 49: cadastro(); break;
			case 50: exclusao(); break;
			case 51: alteracao(); break;
			case 52: pesquisa(); break;
			case 53: gasto(); break;
			case 54: lucro(); break;
			case 55: relatorio(); break;
			case 56: gravacao(dados); break;
			case 57: limpar(); break;
			default: menu();
		}
	}
	return 0;
}
