#include "lib.h"


void displayOptions(string option, double numOption, bool should){

	if(numOption != -1){
		tab;
		cout<<option<<" ";
		int size = 50 - option.length();
		for(int i=0; i<size;i++){
			cout<<"-";
		}

		if(should){
			printf(" %lf", numOption);
		}else
		cout<<" "<<fixed<<setprecision(0)<<numOption;br2;
	}else{
		tab;
		cout<<option;br2;
	}
}



void menuPrincipal(int metodo,int quantidade, int situacao){

	//int typeSearchOption, sortType;
	long  key;
	Complexity T;

	T.comparation=0;
	T.numOfTrans=0;

	char fileName[20] = "binary_datas.bin";


	//cls;
	//br1;

	//displayOptions("Busca Sequencial Indexada", 1);
	//displayOptions("Arvore Binaria de Pesquisa", 2);
	//displayOptions("Arvore B", 3);
	//displayOptions("Arvore B*", 4);

	//br1;
	//tab;
	//cout<<":_";
	//cin >> typeSearchOption;


	//cls;
	//br1;	
	//displayOptions("Quantidade de Dados");

	//br1;
	//tab;
	//cout<<":_";
	//cin >> quantity;

	//cls;
	//br1;	
	//displayOptions("Ordenado Ascendentemente", 1);
	//displayOptions("Ordenado Descendentemente", 2);
	//displayOptions("Aleatorio", 3);

	//br1;
	//tab;
	//cout<<":_";
	//cin >> sortType;

	datasGenerator(quantidade, situacao, fileName);
	cls;
	tab;
	displayOptions("A chave");
	br1;
	tab;
	cout<<":_";
	cin >> key;


	
	TipoRegistro Reg;
	Reg.Registro.Chave = key;

	switch(metodo){

		case 1:{
			long indexSize = (quantidade/100)+1;
			TypeIndex Index[indexSize];
			T.start = clock();
			if(situacao==2){
				index_builder(fileName, Index, &T);
				sequentalIndexedSearch(&Reg, indexSize, Index, fileName,&T, false);
			}else if(situacao == 3)
				randomSeqSearch(&Reg, fileName, &T);
			else{
				index_builder(fileName, Index, &T);
				sequentalIndexedSearch(&Reg, indexSize, Index, fileName,&T, true);
			}
			break;
		}

		case 2:{
			FILE* arq;
			FILE* newarq; 
			long *cont;
			*cont = 1;
			BinaryTree auxiliar;
			//T.start = clock();
			insereChaveArquivoBinario(arq, newarq, cont);
			
			newarq = fopen("new_binary_datas.bin", "rb");
			//fread(&auxiliar, sizeof(BinaryTree), 1, newarq);
			while(fread(&auxiliar, sizeof(BinaryTree), 1, newarq) == 1){
				if(auxiliar.Registro.Registro.Chave == Reg.Registro.Chave){
					cout << "Chave: " << auxiliar.Registro.Registro.Chave << endl;
    				cout << "Dado 1: " << auxiliar.Registro.Registro.data1 << endl;
    				cout << "Dado 2: " << auxiliar.Registro.Registro.data2 << endl;
				}
			}
			//pesquisaArvoreBinaria(newarq, Reg, auxiliar);
			fclose(newarq);
			break;
		}

		case 3:{
			TipoApontador Tree = (TipoApontador)malloc(sizeof(TipoPagina));
			tree_starter(&Tree);
			T.start = clock();
			dataLoader(&Tree, fileName);
			bTreeSearch(&Reg, Tree, &T);
			break;
		}

		case 4:{
			displayOptions("Em construcao ainda!");
			break;
		}

		default:{

			displayOptions("Opcao Errada!");
			break;
		}
	}

	//T.end = clock();
	//T.time = ((double)T.end - T.start) / double(CLOCKS_PER_SEC);
	//complexityDiscription(&T, Reg);
}


void complexityDiscription(Complexity *T, TipoRegistro Reg){

	cls;
	br1;
	displayOptions("O tempo da busca: ", T->time, true);
	displayOptions("O Numero de comparaçoes: ", (double)T->comparation);
	if(T->numOfTrans != 0)
		displayOptions("O Numero de trasferencias: ", (double)T->numOfTrans);

	if(Reg.Registro.Chave != -1){

		br1;		
		displayOptions("A chave: ", (double)Reg.Registro.Chave);
		displayOptions("O Dado1: ", (double)Reg.Registro.data1);
		displayOptions("O Dado2: ");
		tab;
		cout<<Reg.Registro.data2;
	}else{
		tab;cout<<"Ops nao achado ";
	}
}