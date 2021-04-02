#include "lib.h"

void index_builder(char* fileName,TypeIndex* Index, Complexity* T){

	FILE* file;

	if((file = fopen(fileName, "rb"))== NULL){

		cout<<"Houve Problemas na Leitura\n";
		exit(1);
	}

	TipoRegistro aux;
	int cont = 0;

	while(fread(&aux, sizeof(TipoRegistro), 1, file) == 1){

		T->numOfTrans++;
		Index[cont].Chave = aux.Registro.Chave;
		Index[cont].position = cont;
		fseek(file, 99*sizeof(TipoRegistro), SEEK_CUR);

		cont++;
		// cout<<cont<<"\n";
		// cout<<aux.Registro.Chave<<" "<<aux.Registro.data2<<"\n";
	}

	fclose(file);
}



void sequentalIndexedSearch(TipoRegistro *Reg, long indexSize, TypeIndex *Index, char* fileName, Complexity* T, bool ascendingOrder){

	FILE* file;
	if((file = fopen(fileName, "rb"))==NULL){

		cout<<"Problemas em Ler ficheiro\n";
		exit(1);
	}


	TipoRegistro onePage[sizePage], resul;
	resul.Registro.Chave = -1;
	long i, qtd;
	long int desc;

	i=0;

	if (ascendingOrder){
		while(i < indexSize && Index[i].Chave <= Reg->Registro.Chave){ // PROCURADO A PAGINA ONDE O DADO PROVAVELMENTE PODE ESTAR
			i++;
			T->comparation++;
		}
	}else{

		while(i < indexSize && Index[i].Chave >= Reg->Registro.Chave){ // PROCURADO A PAGINA ONDE O DADO PROVAVELMENTE PODE ESTAR
			i++;
			T->comparation++;
		}
	}

	if(i==0){
		
		Reg->Registro.Chave = -1;
		return ;
	}
	
	else{

		if(i < indexSize){ // PROCURANDO SABER SE A PAGINA QUE SERA LIDA ESTÁ OU NAO IMCOMPLETA 
			qtd = sizePage;
		}else{ // CASO FOR IMCOMPLETA, SABER NUMERO EXATO DE DADOS 

			fseek(file, 0, SEEK_END);
			qtd = ((ftell(file)/sizeof(TipoRegistro)))%sizePage;
		}
	}

	desc = (Index[i-1].position) * sizeof(TipoRegistro)*sizePage; // PEGANDO QUANTIDADE DE BITS QUERÁ PULADO PARA A PAGINA DESEJADA
	
	fseek(file, desc, SEEK_SET); // PULAR PARA A PAGINA DESEJADA

	if(qtd == 0){
		qtd = 8;
	}

	fread(&onePage, sizeof(TipoRegistro), qtd, file); // LER A PAGINA
	T->numOfTrans++;
	int aux = seqSearch(onePage, qtd, Reg->Registro.Chave, T); // BUSCA SEQUENCIAL NA PAGINA TRANSFERIDA DE MEMORIA EXTERNA PARA INTERNA

	if(aux != -1){

		*Reg = onePage[aux];
		return ;
	}else{

		Reg->Registro.Chave = -1;
	}
}	

void randomSeqSearch(TipoRegistro *Reg, char* fileName, Complexity *T) {// QUANDO OS REGISTROS NAO ESTAO ORDENADOS

	FILE* file;


	if((file = fopen(fileName, "rb"))==NULL){

		cout<<"Problemas em Ler ficheiro\n";
		exit(1);
	}

	TipoRegistro temp;

	while(fread(&temp, sizeof(TipoRegistro), 1, file)==1){
		T->comparation++;
		T->numOfTrans++;
		if(temp.Registro.Chave == Reg->Registro.Chave){

			*Reg = temp;
			return;
		}
	}

	Reg->Registro.Chave = -1;
}


int seqSearch(TipoRegistro* onePage, long size, long key, Complexity* T){

	for(int i=0; i<size; i++){
		if(onePage[i].Registro.Chave == key){
			T->comparation++;
			return i;
		}
	}

	return -1;

}