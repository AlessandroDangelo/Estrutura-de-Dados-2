#ifndef LIB_H
#define LIB_H

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <iomanip>
#include <vector>
#include <algorithm> // PARA ORDENAR OS DADOS 

//DETECTING OPERATIVE SISTEM 
#ifdef _WIN32
#define cls system("cls")
#endif

#ifdef linux
#define cls system("clear")
#endif
// ATALHOS 
#define sizePage 100
#define tab cout<<"\t\t\t\t"
#define br2 cout<<"\n\n"
#define br1 cout<<"\n"

using namespace std;

//ORDEM DA ARVORE
#define M 2
#define MM M*2



// DEFINIÇÃO DAS ESTRUTURAS

struct {//TIPO INDICE PARA CONSTRUÇÃO DE TABELA DE INDICE NA BUSCA SEQUENCIAL INDEXADA
	int position;
	long Chave;
}typedef TypeIndex;


struct { // TIPO ITEM 
	long Chave;
	long long data1;
	char data2[500];
}typedef DataType;


typedef struct TipoRegistro{ 

	DataType Registro;

}TipoRegistro;


typedef struct TipoPagina* TipoApontador;

typedef struct TipoPagina{
	short n;
	TipoRegistro r[MM];
	TipoApontador p[MM+1];
}TipoPagina;


struct { // ESTRUTURA PARA CALCULAR COMPLEXIDADE TEMPO, NUM DE TRANSFERENCIAS E COMP;

	clock_t start, end;
	double time;
	int comparation;
	int numOfTrans;
}typedef Complexity;

//----------------------------------ESTRUTURA PARA ARVORE BINARIA ------------------------------------------------//

typedef struct binaryTree{
  TipoRegistro Registro;
  long chaveEs;
  long chaveDi;
  
} BinaryTree;


void insereChaveArquivoBinario(FILE* , FILE* , long* );
void atualizaFilhoArquivoBinario(FILE* , TipoRegistro , BinaryTree , long* );
void pesquisaArvoreBinaria(FILE*, TipoRegistro, BinaryTree);

//----------------------------------TERMINAL DISPLAY ------------------------------------------------
void menuPrincipal(int, int, int);
void displayOptions(string option, double i = -1, bool should = false);
//----------------------------------ACESSO SEQUENCIAL INDEXADO ------------------------------------------------
void sequentalIndexedSearch(TipoRegistro *Reg, long indexSize, TypeIndex *Index, char* file,Complexity *T, bool);
int seqSearch(TipoRegistro* onePage, long size, long key,Complexity *T);
void index_builder(char* fileName, TypeIndex*,Complexity *T);
void randomSeqSearch(TipoRegistro *Reg, char* fileName, Complexity *T);

//----------------------------------ARVORE B ------------------------------------------------
//DEFINIÇOES DAS FUNCÇOES

void tree_starter(TipoApontador *Tree);
void display(TipoApontador Tree);
void insert_into_page(TipoApontador Ap, TipoRegistro Reg, TipoApontador ApDir);
void inser(TipoRegistro Reg, TipoApontador Ap, short *grow, TipoRegistro *RegRetorno, TipoApontador *ApRetorno);
void push(TipoRegistro Reg, TipoApontador *Ap);
void bTreeSearch(TipoRegistro *Reg, TipoApontador Tree, Complexity *T);

//GERADORES DE DADOS E CARREGADORES
void datasGenerator(long long int dataQnt, int order, char* fileName);
void dataLoader(TipoApontador *Tree, char* fileName);


//----------------------------------COMPLEXIDADE ------------------------------------------------

void complexityDiscription(Complexity *T, TipoRegistro Reg);
//----------------------------------ARVORE B* ------------------------------------------------

/*
// DEFINIÇÕES DAS ESTRUTURAS
typedef long TipoChave;


typedef enum{Interna, Externa} TipoIntExt;



typedef struct TipoPaginaEstrela {
	TipoIntExt Pt;
	union {
		struct {
			int ni;
			TipoChave ri[MM];
			TipoApontador pi[MM + 1];
		} U0;

		struct {
			int ne;
			TipoRegistro re[MM];
		} U1;
	}UU;
}TipoPaginaEstrela;

//DEFINIÇÕES DAS FUNÇÕES

void Pesquisa(TipoRegistro *x, TipoApontador *Ap);
//
*/
#endif 