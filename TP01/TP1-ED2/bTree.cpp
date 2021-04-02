#include "lib.h"

void tree_starter(TipoApontador *Tree){ //INICIALIZANDO ARVORE

	*Tree = NULL;
}


void display(TipoApontador Tree){ //CAMINHAMENTO IN-ORDEM

	// cout<<"Display";
	if (Tree != NULL) {
       for (int i=0; i < Tree->n; i++){
           display(Tree->p[i]);
	 		cout<<"Chave: "<<Tree->r[i].Registro.Chave<<" - Dado1: "<<Tree->r[i].Registro.data1<<" - "<<Tree->r[i].Registro.data2<<"\n\n";
       }
       display(Tree->p[Tree->n]);
   }
}

//---------------------------------------------------INSERTION------------------------------------------------

void insert_into_page(TipoApontador Ap, TipoRegistro Reg, TipoApontador ApDir){ // INSERE NA PAGINA

	short positon;
	int k;
	k=  Ap->n;
	positon = (k>0);

	while(positon){

		if(Reg.Registro.Chave >= Ap->r[k-1].Registro.Chave){
			positon = false;
			break;
		}

		Ap->r[k] = Ap->r[k-1];
		Ap->p[k+1] = Ap->p[k];
		k--;

		if(k < 1)
			positon = false;
	}

	Ap->r[k] = Reg;
	Ap->p[k+1] = ApDir;
	Ap->n++;
}

void inser(TipoRegistro Reg, TipoApontador Ap, short *grow, TipoRegistro *RegRetorno, TipoApontador *ApRetorno){

	long i=1, j;

	TipoApontador ApTemp;

	if(Ap == NULL){
		*grow = true;
		(*RegRetorno) = Reg;
		(*ApRetorno) = NULL;
		return ;
	}

	while(i < Ap->n && Reg.Registro.Chave > Ap->r[i-1].Registro.Chave)
		i++;

	if(Reg.Registro.Chave == Ap->r[i-1].Registro.Chave){
		return;
	}

	if(Reg.Registro.Chave < Ap->r[i-1].Registro.Chave)
		i--;
	inser(Reg, Ap->p[i], grow, RegRetorno, ApRetorno);

	if(!*grow)
		return;

	if(Ap->n < MM){

		insert_into_page(Ap, *RegRetorno, *ApRetorno);
		*grow = false;
		return;
	}

	ApTemp = (TipoApontador)malloc(sizeof(TipoPagina));
	ApTemp->n = 0;
	ApTemp->p[0] = NULL;

	if(i < M+1){

		insert_into_page(ApTemp, Ap->r[MM-1], Ap->p[MM]);
		Ap->n--;
		insert_into_page(Ap, *RegRetorno, *ApRetorno);
	}else
		insert_into_page(ApTemp,*RegRetorno, *ApRetorno);

	for(j = M+2; j <= MM ;j++){
		insert_into_page(ApTemp, Ap->r[j-1], Ap->p[j]);
	}

	Ap->n =M;
	ApTemp->p[0] = Ap->p[M+1];
	*RegRetorno = Ap->r[M];
	*ApRetorno = ApTemp;


}

void push(TipoRegistro Reg, TipoApontador *Ap){ // INSERÇÃO 
	short grow;
	TipoRegistro RegRetorno;
	TipoPagina *ApRetorno, *ApTemp;

	inser(Reg, *Ap, &grow, &RegRetorno, &ApRetorno);

	if(grow){

		ApTemp = (TipoPagina*)malloc(sizeof(TipoPagina));
		ApTemp->n =1;
		ApTemp->r[0] = RegRetorno;
		ApTemp->p[1] = ApRetorno;
		ApTemp->p[0] = *Ap;
		*Ap = ApTemp;
	}
}


void bTreeSearch(TipoRegistro *Reg, TipoApontador Tree, Complexity *T){ // BUSCA NA ARVORE B
 
	long i=1;
	if(Tree==NULL){
		Reg->Registro.data1 = -1;
		return;
	}

	while(i < Tree->n && Reg->Registro.Chave > Tree->r[i-1].Registro.Chave){
		i++;
		T->comparation++;
	}
	if( Reg->Registro.Chave == Tree->r[i-1].Registro.Chave){
		*Reg = Tree->r[i-1];
		T->comparation++;
		return ;
	}

	T->comparation++;
	if(Reg->Registro.Chave < Tree->r[i-1].Registro.Chave)
		bTreeSearch(Reg, Tree->p[i-1], T);
	else
		bTreeSearch(Reg, Tree->p[i], T);
}