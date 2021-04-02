#include "lib.h"
//#include <bits/stdc++.h>

int main(int argc, char const *argv[]){	

	int metodo, quantidade, situacao;
	metodo = atoi(argv[1]);
	quantidade = atoi(argv[2]);
	situacao = atoi(argv[3]);
	
	menuPrincipal(metodo, quantidade, situacao);
	
	return 0;
}