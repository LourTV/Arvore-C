#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MAXFILHOS 20

struct arvore
{
	int valor, TemValor;
	struct arvore* filho[MAXFILHOS];
	struct arvore* pai;
};

typedef struct arvore ARVORE;
typedef ARVORE* POINTERARVORE;

POINTERARVORE CriarElemento(int valor, int TemValor) //Criar qualquer elemento
{
	int n;
	POINTERARVORE Novo = malloc(sizeof(ARVORE));
	Novo->valor = valor;
	Novo->TemValor = TemValor;
	for(n = 0; n<MAXFILHOS;n++)
		Novo->filho[n] = NULL;
		
	return Novo;
}

POINTERARVORE CriarFilho(POINTERARVORE Pai, POINTERARVORE NovoNo)
{
	int i;
	for(i=0 ; Pai->filho[i] != NULL && i<MAXFILHOS;i++); //ANALISAR EM QUE POSIÇÃO FICA O NOVO FILHO
	if(Pai->filho[i] == NULL)
	{
		Pai->filho[i] = NovoNo;
		NovoNo->pai = Pai;
	}
	else
		printf("[ERRO DE FILHOS] - Não existem slots de filhos suficientes");
	 
	return NovoNo;
}



void desenhaArvore(POINTERARVORE root) //PRINT DA ÀRVORE DA MESMA MANEIRA QUE ESTÁ ESCRITA NO FICHEIRO
{
	if(root->TemValor == 1) //Se Tiver valor, imprime o valor
	{
		printf("%d", root->valor);
	}
	int i = 0;
	while(root->filho[i]!=NULL)
		{
			printf("(");
			desenhaArvore(root->filho[i]);
			i++;
			printf(")");
		}
}

main()
{
	setlocale(LC_ALL, "Portuguese");
	POINTERARVORE Raiz = NULL;
	POINTERARVORE NovoNo = NULL;
	POINTERARVORE ElemAtual = Raiz;
	FILE* FicheiroLeitura;
	int valor_filho;
	char chess[200];
	int i;
	int valor;
	
	
	FicheiroLeitura = fopen("arvore.txt", "r");
	fscanf(FicheiroLeitura, "%s", &chess);
	fclose(FicheiroLeitura);
	
	
	printf("conteúdo do ficheiro: %s\n", chess);
	
	for(i=0;chess[i] != '\0'; i++)
	{
		if(i==0 && Raiz == NULL) //CRIAR A RAIZ
		{
			if(chess[i] =='(') //CRIAR RAIZ SEM VALOR
			{
				Raiz = CriarElemento(0,329);
				ElemAtual = Raiz;
				Raiz->pai = NULL;
				i--;
			}
			else //CRIAR RAIZ COM VALOR
			{
			valor = chess[i] - 48;
			while(chess[i+1] != '(' && chess[i+1] != ')') //Inserir valores > 9
			{
				valor = (valor * 10) + chess[i+1] - 48;
				i++; 
			}
			Raiz = CriarElemento(valor, 1);
			ElemAtual = Raiz;
			Raiz->pai = NULL;
			}
		}
		else if(chess[i] == '(')
		{
			if(chess[i+1] == '(') //INSERIR ELEMENTO SEM VALOR
			{
				NovoNo = CriarElemento(0, 0);
				ElemAtual = CriarFilho(ElemAtual, NovoNo);
			}
			else
			{
			valor = chess[i+1] - 48; //Obter o Valor do Prox elemento
			while(chess[i+2] != '(' && chess[i+2] != ')') //Inserir valores > 9
			{
				valor = (valor * 10) + chess[i+2] - 48;
				i++; 
			}
			NovoNo = CriarElemento(valor, 1);
			i++;
			ElemAtual = CriarFilho(ElemAtual, NovoNo);
			}
		}
		else if(chess[i] == ')')
		{
			ElemAtual = ElemAtual->pai;
		}
	}
	printf("\n\n ----- Resultado -----\n\n");
	desenhaArvore(Raiz);	
}
