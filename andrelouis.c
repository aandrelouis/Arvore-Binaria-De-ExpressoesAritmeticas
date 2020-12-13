#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arv.h"



int main(){
    Arv* arv=NULL;
    FILE *config;FILE *saida;
    char texto[250]="";

    config=fopen("entrada.txt","r");                         //abertura do pconfig modo leitura
    saida=fopen("saida.txt","w");   

    if(!config){
        printf("O diretório de arquivos de configuração não foi informado");
        exit(1);
    } 
        //loop até chegar ao final do arquivo
    while (fscanf(config, "%s", texto) != EOF){
        int pos=0;   
    
        //criando uma nova arvore para cada linha do arquivo
        arv=CriaARvore();
        arv = Parsing(arv,texto,&pos);//função de construir a arvore
        ImprimeArvore(arv);
        printf("\n");

        //calculando o valor da expressão da arvore
        float valor=0;
        valor = CalculaArvore(arv);

        //salvando o valor da expressão no arquivo saida
        fprintf(saida,"%.2f\n",valor);

        //liberando a arvore utilizada para essa linha
        LiberaArvore(arv);
    }

   
    fclose(saida);
    fclose(config);
    return 0; 
}