#include "lib.h"

bool ascendente(const TipoRegistro& a, const TipoRegistro& b){ // ORDENANDO ASCENDENTEMENTE

	if(a.Registro.Chave < b.Registro.Chave)
		return true;
	else
		return false;
}

bool descendente(const TipoRegistro& a, const TipoRegistro& b){// ORDENANDO DESCENDENTENTE

	if(a.Registro.Chave > b.Registro.Chave)
		return true;
	else
		return false;
}


void datasGenerator(long long int dataQnt, int order, char* fileName){

	string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char word[501]; 

	TipoRegistro aux;
	vector<TipoRegistro> vetor;
	FILE* file, *arq;

	if((file = fopen(fileName, "wb"))==NULL){

		cout<<"Problemas em Abrir ficheiro\n";
		exit(1);
	}


	if((arq = fopen("binary_datas.txt", "w"))==NULL){

		cout<<"Problemas em Abrir ficheiro\n";
		exit(1);
	}


	srand(time(NULL));

	int size = alphabet.length()-1;
	for(long long int i=0; i<dataQnt; i++){

		for(int j=0; j < 500; j++){

			word[j] = alphabet[rand()%size];
		}
		// long chave = ((int)word[0]-48) * ((	int)word[1]-48) *((int)word[2]-48) *((int)word[3]-48) *((int)word[4]-48) *((int)word[5]-48) *((int)word[6]-48) *((int)word[7]-48) *((int)word[8]-48)%100000000;
		// aux.Registro.Chave = 10*i + rand()%10;
		aux.Registro.Chave =  rand()%20000000;
		aux.Registro.data1 = rand() % 5000000;
		strcpy(aux.Registro.data2, word);

		if(order  == 3){
			fprintf(arq, "%li %lli %s\n", aux.Registro.Chave, aux.Registro.data1, aux.Registro.data2);
			fwrite(&aux, sizeof(TipoRegistro), 1, file);
		}else
			vetor.push_back(aux);
	}


	if(order ==1){
		sort(vetor.begin(), vetor.end(), ascendente);

	}
	if(order == 2){

		sort(vetor.begin(), vetor.end(), descendente);
	}

	if(order != 3){
		for(auto it = vetor.begin(); it != vetor.end(); ++it){
			
			TipoRegistro temp;
			temp = *it;
			// cout<<"Dado: "<<temp.Registro.data2<<"\n";
			fwrite(&temp, sizeof(TipoRegistro), 1, file);
			fprintf(arq, "%li %lli %s\n", temp.Registro.Chave, temp.Registro.data1, temp.Registro.data2);
		}
	}
	fclose(file);
}


void dataLoader(TipoApontador *Tree, char* fileName){

	FILE* file;

	if((file = fopen(fileName, "rb"))==NULL){

		cout<<"Problemas em Ler ficheiro\n";
		exit(1);
	}

	TipoRegistro temp;
	while(fread(&temp, sizeof(TipoRegistro), 1, file) == 1){
		push(temp, Tree);
	}
}

