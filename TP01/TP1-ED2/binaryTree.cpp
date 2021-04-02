#include "lib.h"

void insereChaveArquivoBinario(FILE* arq, FILE* newarq, long* cont){
  BinaryTree node_aux;
  BinaryTree newnode;
  TipoRegistro node;
  arq = fopen("binary_datas.bin", "rb");
  newarq = fopen("new_binary_datas.bin", "w+b");
  fclose(newarq);
  
  while(fread(&node, sizeof(TipoRegistro), 1, arq) == 1){
    
    newnode.Registro = node;
    newnode.chaveDi = -1;
    newnode.chaveEs = -1;

    newarq = fopen("new_binary_datas.bin", "ab");
    fwrite(&newnode, sizeof(BinaryTree), 1, newarq);
    fclose(newarq);



    newarq = fopen("new_binary_datas.bin", "rb");
    fread(&node_aux, sizeof(BinaryTree), 1, newarq);
    fclose(newarq);

    atualizaFilhoArquivoBinario(newarq, node, node_aux, cont);
    
    
  }

  newarq = fopen("new_binary_datas.bin", "rb");

  while(fread(&newnode, sizeof(BinaryTree), 1, newarq) == 1){
    cout << newnode.chaveEs << " " << newnode.Registro.Registro.Chave
         << " " << newnode.chaveDi << endl;
  }

fclose(newarq);
  fclose(arq);
}

void atualizaFilhoArquivoBinario(FILE* newarq, TipoRegistro node, BinaryTree node_aux, long* cont){
  if(node.Registro.Chave > node_aux.Registro.Registro.Chave){
    if(node_aux.chaveDi == -1){
      node_aux.chaveDi = *cont;
      *cont = *cont + 1;
      //achando o valor de quantos bytes teremos que pular para atualizar o elemento certo
      int valor = 0;
      newarq = fopen("new_binary_datas.bin", "rb");
      BinaryTree auxiliar;
      while(fread(&auxiliar, sizeof(BinaryTree), 1, newarq) == 1){
        if(auxiliar.Registro.Registro.Chave == node_aux.Registro.Registro.Chave){
          break;
        }else{
          valor++;
          
        }
      }
      fclose(newarq);
      //atualiza dentro do newarq
      newarq = fopen("new_binary_datas.bin", "r+b");
      fseek (newarq, valor * sizeof (BinaryTree), SEEK_SET);
      fwrite(&node_aux, sizeof(BinaryTree), 1, newarq);
      fclose(newarq);
      return;
    }else{
      newarq = fopen("new_binary_datas.bin", "rb");
      fseek (newarq, node_aux.chaveDi * sizeof (BinaryTree), SEEK_SET);
      fread(&node_aux, sizeof(BinaryTree), 1, newarq);
      rewind(newarq);
      fclose(newarq);
      atualizaFilhoArquivoBinario(newarq, node, node_aux, cont);
    }
  }
  if(node.Registro.Chave < node_aux.Registro.Registro.Chave){
    if(node_aux.chaveEs == -1){
      node_aux.chaveEs = *cont;
      *cont = *cont + 1;
      //achando o valor de quantos bytes teremos que pular para atualizar o elemento certo
      int valor = 0;
      newarq = fopen("new_binary_datas.bin", "rb");
      BinaryTree auxiliar;
      while(fread(&auxiliar, sizeof(BinaryTree), 1, newarq) == 1){
        if(auxiliar.Registro.Registro.Chave == node_aux.Registro.Registro.Chave){
          break;
        }else{
          valor++;
        }
      }
      fclose(newarq);
      //atualiza dentro do newarq
      newarq = fopen("new_binary_datas.bin", "r+b");
      fseek (newarq, valor * sizeof (BinaryTree), SEEK_SET);
      fwrite(&node_aux, sizeof(BinaryTree), 1, newarq);
      fclose(newarq);
      return;
    }else{
      newarq = fopen("new_binary_datas.bin", "rb");
      fseek (newarq, node_aux.chaveEs * sizeof (BinaryTree), SEEK_SET);
      fread(&node_aux, sizeof(BinaryTree), 1, newarq);
      rewind(newarq);
      fclose(newarq);
      atualizaFilhoArquivoBinario(newarq, node, node_aux, cont);
    }
  }
}

void pesquisaArvoreBinaria(FILE* newarq, TipoRegistro Reg, BinaryTree auxiliar){
  if(Reg.Registro.Chave == auxiliar.Registro.Registro.Chave){
    cout << "Chave: " << auxiliar.Registro.Registro.Chave << endl;
    cout << "Dado 1: " << auxiliar.Registro.Registro.data1 << endl;
    cout << "Dado 2: " << auxiliar.Registro.Registro.data2 << endl;
    return;
  }else if(Reg.Registro.Chave > auxiliar.Registro.Registro.Chave){
    //newarq = fopen("new_binary_datas.bin", "rb");
    rewind(newarq);
    fseek (newarq, auxiliar.chaveDi * sizeof (BinaryTree), SEEK_SET);
    fread(&auxiliar, sizeof(BinaryTree), 1, newarq);
    //fclose(newarq);
    pesquisaArvoreBinaria(newarq, Reg, auxiliar);
  }else if(Reg.Registro.Chave < auxiliar.Registro.Registro.Chave){
    //newarq = fopen("new_binary_datas.bin", "rb");
    rewind(newarq);
    fseek (newarq, auxiliar.chaveEs * sizeof (BinaryTree), SEEK_SET);
    fread(&auxiliar, sizeof(BinaryTree), 1, newarq);
    //fclose(newarq);
    pesquisaArvoreBinaria(newarq, Reg, auxiliar);
  } else{
    cout << "Nao existe na memoria" << endl;
  }
}