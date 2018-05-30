/***************************************\
| TRABALHO DE LABORATÓRIO DE COMPUTAÇÃO |
|      MARCELO TOMIO HAMA - 1° ANO      |
\***************************************/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct fichario
{
    int codigo;
    char nome[21];
    char endereco[31];
    char bairro[21];
    char estado[3];
    char cidade[21];
    char email[31];
    char cep[10];
    char telefone[11];
    char celular[11];
} ficha;

int pega_espaco(FILE *arq)
{
    int aux=0;
    fseek(arq,0,SEEK_SET);
    while(!feof(arq))
    {
        if(fread(&ficha,sizeof(ficha),1,arq)==1)
        {
            if(ficha.nome[0]=='\0')
                return aux;
            aux++;
        }
    }
    return aux;
}

void menu()
{
    int i;
    printf("\n\n\n\n\n\n\n             ");
	putchar(201); for(i=0;i<31;i++) printf("%c",205); putchar(187);
	printf("\n             %c        AGENDA  VIRTUAL        %c   \n             ",186,186);
	putchar(204); for(i=0;i<31;i++) printf("%c",205); putchar(185);
	printf("\n             %cMENU PRINCIPAL                 %c",186,186);
	printf("\n             %c<1> Inclusao                   %c",186,186);
	printf("\n             %c<2> Exclusao                   %c",186,186);
	printf("\n             %c<3> Pesquisa                   %c",186,186);
	printf("\n             %c<4> Relatorio                  %c",186,186);
	printf("\n             %c<5> Alteracao                  %c",186,186);
	printf("\n             %c<6> Sair                       %c\n             ",186,186);
	putchar(200); for(i=0;i<31;i++) printf("%c",205); putchar(188);    
}

void inclusao(FILE *arq)
{
    system("cls");
    printf("|----------|\n| Inclusao |\n|----------|\n\n");
    ficha.codigo=pega_espaco(arq);
    printf("Codigo %d\n",ficha.codigo);
    fflush(stdin);
    do{
        printf("Nome: ");
        gets(ficha.nome);
        if(strlen(ficha.nome)>20)
           printf("maximo 20 caracteres\n");
    }while(strlen(ficha.nome)>20);
    fflush(stdin);
    do{
        printf("Endereco: ");
        gets(ficha.endereco);
        if(strlen(ficha.endereco)>30)
           printf("maximo 30 caracteres\n");
    }while(strlen(ficha.endereco)>30);
    fflush(stdin);
    do{
        printf("Bairro: ");
        gets(ficha.bairro);
        if(strlen(ficha.bairro)>20)
           printf("maximo 20 caracteres\n");
    }while(strlen(ficha.bairro)>20);
    fflush(stdin);
    do{
        printf("Estado: ");
        gets(ficha.estado);
        if(strlen(ficha.estado)!=2)
           printf("maximo 2 caracteres\n");
    }while(strlen(ficha.estado)!=2);
    fflush(stdin);
    do{
        printf("Cidade: ");
        gets(ficha.cidade);
        if(strlen(ficha.cidade)>20)
           printf("maximo 20 caracteres\n");
    }while(strlen(ficha.cidade)>20);
    fflush(stdin);
    do{
        printf("E-mail: ");
        gets(ficha.email);
        if(strlen(ficha.email)>30)
           printf("maximo 30 caracteres\n");
    }while(strlen(ficha.email)>30);
    fflush(stdin);
    do{
        printf("CEP: ");
        gets(ficha.cep);
        if(strlen(ficha.cep)>9)
           printf("maximo 9 caracteres\n");
    }while(strlen(ficha.cep)>9);
    fflush(stdin);
    do{
        printf("Tel: ");
        gets(ficha.telefone);
        if(strlen(ficha.telefone)>10)
           printf("maximo 10 caracteres\n");
    }while(strlen(ficha.telefone)>10);
    fflush(stdin);
    do{
        printf("Cel: ");
        gets(ficha.celular);
        if(strlen(ficha.celular)>10)
           printf("maximo 10 caracteres\n");
    }while(strlen(ficha.celular)>10);
    fseek(arq,ficha.codigo*sizeof(ficha),SEEK_SET);
    if(fwrite(&ficha,sizeof(ficha),1,arq)!=1)
    {
        printf("\nerro no cadastramento");
        getch();
        exit(0);
    }
    fflush(arq);
}

void exclusao(FILE *arq)
{
    system("cls");
    printf("|----------|\n| Exclusao |\n|----------|\n\n");
    int cod;
    char resp;
    printf("Codigo a ser excluido: "); scanf("%d",&cod);
    fseek(arq,cod*sizeof(ficha),SEEK_SET);
    if(fread(&ficha,sizeof(ficha),1,arq)==1)
    {
        if(cod<0||ficha.nome[0]=='\0')
        {
            printf("\nCodigo nao cadastrado ou invalido");
            getch();
            return;
        }
        else
        {
            printf("\nNome ------- %s",ficha.nome);
            printf("\nEndereco --- %s",ficha.endereco);
            printf("\nCidade ----- %s",ficha.cidade);
            printf("\nE-Mail ----- %s",ficha.email);
            printf("\nTel -------- %s",ficha.telefone);
            printf("\n\nDeseja exclui este cadastro? s/n"); resp=getch();
            if(resp=='s'||resp=='S')
                ficha.nome[0]='\0';
            fseek(arq,cod*sizeof(ficha),SEEK_SET);
            if(fwrite(&ficha,sizeof(ficha),1,arq)!=1)
            {
                printf("\nerro na exclusao");
                getch();
                exit(0);
            }
        }
        fflush(arq);
    }
}

void pesquisa(FILE *arq)
{
    system("cls");
    printf("|----------|\n| Pesquisa |\n|----------|\n\n");
    int pes;
    printf("Codigo a ser mostrado: ");
    scanf("%d",&pes);
    fseek(arq,pes*sizeof(ficha),SEEK_SET);
    if(fread(&ficha,sizeof(ficha),1,arq)==1)
    {
        if(ficha.nome[0]=='\0'||pes<0)
        {
            printf("\nCodigo nao cadastrado ou invalido");
            getch();
            return;
        }
        else
        {
            printf("\nNome ------- %s",ficha.nome);
            printf("\nEndereco --- %s",ficha.endereco);
            printf("\nBairro ----- %s",ficha.bairro);
            printf("\nEstado ----- %s",ficha.estado);
            printf("\nCidade ----- %s",ficha.cidade);
            printf("\nE-Mail ----- %s",ficha.email);
            printf("\nCEP -------- %s",ficha.cep);
            printf("\nTel -------- %s",ficha.telefone);
            printf("\nCel -------- %s",ficha.celular);
            getch();
        }
    }
    fflush(arq);
}

void relatorio_codigo(FILE *arq)
{
    system("cls");
    printf("|---------------|\n| Relatorio/Cod |\n|---------------|\n\n");
    int aux=0;
    fseek(arq,0,SEEK_SET);
    printf("Cod   Nome\n");
    while(!feof(arq))
    {
        if(fread(&ficha,sizeof(ficha),1,arq)==1)
            if(ficha.nome[0]!='\0')
            {
                printf("%3.1d   %s\n",ficha.codigo,ficha.nome);
                aux++;
            }
    }
    if(aux==0) printf("Nenhum cadastro feito");
    fflush(arq);
}

void relatorio_nome(FILE *arq)
{
    system("cls");
    printf("|----------------|\n| Relatorio/Nome |\n|----------------|\n\n");
    int j,i=0,aux=0;
    char str[21];
    fseek(arq,0,SEEK_SET);
    while(!feof(arq))
    {
        if(fread(&ficha,sizeof(ficha),1,arq)==1)
            if(ficha.nome[0]!='\0')
                aux++;
    }
    if(aux==0)
    {
        printf("Nenhum cadastro feito");
        return;
    }
    struct vet
    {
        int pos;
        char nome[20];
    } vetor[aux];
    fseek(arq,0,SEEK_SET);
    while(!feof(arq))
    {
        if(fread(&ficha,sizeof(ficha),1,arq)==1)
        {
            if(ficha.nome[0]!='\0')
            {
                vetor[i].pos=ficha.codigo;
                strcpy(vetor[i].nome,ficha.nome);
                i++;
            }
        }       
    }
    i=0;
    while(i<aux-1)
    {
        if(strcmp(vetor[i].nome,vetor[i+1].nome)>0)
        {
            strcpy(str,vetor[i].nome);
            strcpy(vetor[i].nome,vetor[i+1].nome);
            strcpy(vetor[i+1].nome,str);
            j=vetor[i].pos;
            vetor[i].pos=vetor[i+1].pos;
            vetor[i+1].pos=j;
            i=0;
        }
        i++;
    }
    i=0;
    while(i<aux-1)
    {
        if(strcmp(vetor[i].nome,vetor[i+1].nome)>0)
        {
            strcpy(str,vetor[i].nome);
            strcpy(vetor[i].nome,vetor[i+1].nome);
            strcpy(vetor[i+1].nome,str);
            j=vetor[i].pos;
            vetor[i].pos=vetor[i+1].pos;
            vetor[i+1].pos=j;
            i=0;
        }
        i++;
    }
    printf("Cod   Nome\n");
    for(i=0;i<aux;i++)
        printf("%3.1d   %s\n",vetor[i].pos,vetor[i].nome);
    fflush(arq);
}

void relatorio(FILE *arq)
{
    system("cls");
    printf("|-----------|\n| Relatorio |\n|-----------|\n\n");
    char resp;
    printf("<1> Por codigo\n<2> Por nome");
    resp=getch();
    switch(resp)
    {
        case 49: relatorio_codigo(arq); break;
        case 50: relatorio_nome(arq); break;
        default: ;
    }
    fflush(arq);
    getch();
}

void alteracao(FILE *arq)
{
    system("cls");
    printf("|-----------|\n| Alteracao |\n|-----------|\n\n");
    char str[31],resp;
    int alt;
    printf("Codigo a ser alterado: "); scanf("%d",&alt);
    fseek(arq,alt*sizeof(ficha),SEEK_SET);
    if(fread(&ficha,sizeof(ficha),1,arq)==1)
    {
        if(alt<0||ficha.nome[0]=='\0')
        {
            printf("\nCodigo nao cadastrado ou invalido");
            getch();
            return;
        }
        while(resp!=48)
        {
            system("cls");
            printf("|-----------|\n| Alteracao |\n|-----------|\n\n");
            printf("Ficha %d",ficha.codigo);
            printf("\n<1> para alterar nome ------- %s",ficha.nome);
            printf("\n<2> para alterar endereco --- %s",ficha.endereco);
            printf("\n<3> para alterar bairro ----- %s",ficha.bairro);
            printf("\n<4> para alterar estado ----- %s",ficha.estado);
            printf("\n<5> para alterar cidade ----- %s",ficha.cidade);
            printf("\n<6> para alterar e-mail ----- %s",ficha.email);
            printf("\n<7> para alterar CEP -------- %s",ficha.cep);
            printf("\n<8> para alterar telefone --- %s",ficha.telefone);
            printf("\n<9> para alterar celular ---- %s",ficha.celular);
            printf("\n<0> para voltar");
            resp=getch();
            switch(resp)
            {
                case 49: printf("\nNovo nome: ");
                         fflush(stdin);
                         gets(str);
                         strcpy(ficha.nome,str);
                         break;
                case 50: printf("\nNovo endereco: ");
                         fflush(stdin);
                         gets(str);
                         strcpy(ficha.endereco,str);
                         break;
                case 51: printf("\nNovo bairro: ");
                         fflush(stdin);
                         gets(str);
                         strcpy(ficha.bairro,str);
                         break;
                case 52: printf("\nNovo estado: ");
                         fflush(stdin);
                         gets(str);
                         strcpy(ficha.estado,str);
                         break;
                case 53: printf("\nNovo cidade: ");
                         fflush(stdin);
                         gets(str);
                         strcpy(ficha.cidade,str);
                         break;
                case 54: printf("\nNovo email: ");
                         fflush(stdin);
                         gets(str);
                         strcpy(ficha.email,str);
                         break;
                case 55: printf("\nNovo cep: ");
                         fflush(stdin);
                         gets(str);
                         strcpy(ficha.cep,str);
                         break;
                case 56: printf("\nNovo telefone: ");
                         fflush(stdin);
                         gets(str);
                         strcpy(ficha.telefone,str);
                         break;
                case 57: printf("\nNovo celular: ");
                         fflush(stdin);
                         gets(str);
                         strcpy(ficha.celular,str);
                         break;
                case 48: fseek(arq,alt*sizeof(ficha),SEEK_SET);
                         fwrite(&ficha,sizeof(ficha),1,arq);
                         break;
                default: ;
            }
        }
    }
    fflush(arq);
}

int main()
{
    FILE *fp;
    char resp;
    fp=fopen("dados.dat","rb+");
    if(fp==NULL)
    {
        printf("arquivo de dados inexistente\ncriando arquivo...");
        fp=fopen("dados.dat","wb");
        fclose(fp);
        fp=fopen("dados.dat","rb+");
    }
    for(;;)
    {
        system("cls");
        menu();
        resp=getch();
        switch(resp)
        {
            case 49 : inclusao(fp); break;
            case 50 : exclusao(fp); break;
            case 51 : pesquisa(fp); break;
            case 52 : relatorio(fp); break;
            case 53 : alteracao(fp); break;
            case 54 : fclose(fp); exit(0);
            default : ;
        }
    }
}
