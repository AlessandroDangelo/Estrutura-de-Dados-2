// DEFINIÇÕES DAS ESTRUTURAS
// typedef long TipoChave;

// typedef struct TipoRegistro{
// 	Tipo Chave;
// } TipoRegistro;

// typedef enum{Interna, Externa} TipoIntExt;

// typedef struct TipoPagina* TipoApontador;

// typedef struct TipoPagina {
// 	TipoIntExt Pt;
// 	union {
// 		struct {
// 			int ni;
// 			TipoChave ri[MM];
// 			TipoApontador pi[MM + 1];
// 		} U0;

// 		struct {
// 			int ne;
// 			TipoRegistro re[MM2];
// 		} U1;
// 	}UU;
// }TipoPagina;

//DEFINIÇÕES DAS FUNÇÕES

// void Pesquisa(TipoRegistro *x, TipoApontador *Ap){
//     int i;
//     TipoApontador Pag;
//     Pag = *Ap;
//     if ((*Ap)->Pt == Interna){
//         i = 1;
//         while (i < Pag->UU.U0.ni && x->Chave > Pag->UU.U0.ri [i - 1]){
//             i++;
//             if(x->Chave < Pag->UU.U0.ri[i - 1]){
//                 Pesquisa(x, &Pag->UU.U0.pi[i - 1]);
//             }else{
//                 Pesquisa(x, &Pag->UU.U0.pi[i]);
//             }
//             return;
//         }
//     }
//     i = 1;
//     while (i < Pag->UU.U1.ne && x->Chave > Pag->UU.U1.re[i - 1].Chave){
//         i++;
//         if(x->Chave == Pag->UU.U1.re[i - 1].Chave){
//             *x = Pag->UU.U1.re[i - 1];
//         }else{
//             cout << "TipoRegistro nao esta presente na arvore\n";
//         }
//     }
// }

//INSERÇÃO

// void insert_into_page(TipoApontador Ap, TipoRegistro Reg, TipoApontador ApDir){
    
//     TipoApontador Pag;
//     Pag = *Ap;
// 	short positon;
// 	int k;
// 	k =  Pag->UU.U1.ne;
// 	positon = (k>0);

// 	while(positon){

// 		if(Reg.Chave >= Pag->UU.U1.re[k-1].Chave){
// 			positon = false;
// 			break;
// 		}

// 		Pag->UU.U1.re[k] = Pag->UU.U1.re[k-1];
// 		Pag->UU.U0.pi[k+1] = Pag->UU.U0.pi[k];
// 		k--;

// 		if(k < 1)
// 			positon = false;
// 	}

// 	Pag->UU.U1.re[k] = Reg;
// 	Pag->UU.U0.pi[k+1] = ApDir;
// 	Pag->UU.U1.ne++;
// }
/*
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

		cout<<"Ja existe item com a mesma chave\n";
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

void push(TipoRegistro Reg, TipoApontador *Ap){
	// cout<<"Push";
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
}*/