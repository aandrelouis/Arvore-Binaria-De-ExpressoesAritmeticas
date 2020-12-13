#include "arv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct arv{
    char letra;         //char letra para guardar o operador
    float numero;       //float para guardar os numeros
    Arv*  direita;      //arvore direita
    Arv*  esquerda;     //arvore esquerda
};


Arv* CriaVazia(){
    return NULL;
}


void ImprimeArvore(Arv* arv){
    if(arv != NULL){
        printf("(");
        ImprimeArvore(arv->esquerda);
        
        if(arv->letra != 'X')
        printf("%c",arv->letra);
        
        if(arv->numero != 0)
        printf("%.0f",arv->numero);
        
        ImprimeArvore(arv->direita);
        printf(")");
    }
}


Arv* CriaARvore(){
    Arv* arv =(Arv*)malloc(sizeof(Arv));
    arv->direita = NULL;
    arv->esquerda = NULL;
    arv->letra='X';     
    arv->numero=0;
    return arv;
}


Arv* AdicionaNaArvore(Arv* arv, char letra){
    if(arv->esquerda == NULL){
        arv->esquerda = CriaARvore();
        arv->esquerda->letra=letra;
    }
    else{
        arv->direita = CriaARvore();
        arv->direita->letra=letra;
    }
    return arv;
}



Arv* Parsing(Arv* arv, char* texto,int* pos){
        //Se o char for ( ele entra nessa função e verifica os casos que podem acontecer
        if(texto[*pos] == '(' ){
            
            //Se logo depois da '(' vier um numero, então é apenas um numero,a função deve apenas andar mais uma posição na string , e a função de tratar numeros ira resolver 
            if(texto[*pos + 1] >= '0' && texto[*pos + 1] <= '9'){
                *pos = *pos + 1;    //a função ira somente andar mais uma posição e ficar no inicio do numero que está dentro da chave
            }            
            
            //se não entrar no primeiro if(é apenas um numero), quer dizer que devemos criar um novo nó para a esquerda 
            else if(texto[*pos] == '(' ){
                *pos = *pos + 1;    //andamos uma posição na string
                    if(arv->esquerda== NULL){
                        arv->esquerda = CriaARvore();  //criamos o ponteiro arvore alocado
                    }
                    arv->esquerda = Parsing(arv->esquerda,texto,pos);   //chamamos a função recursivamente para criar a arvore para aquele nó
            }
        }
       
        if(texto[*pos] >= '0' && texto[*pos] <= '9'){            
                char* valor = NULL;
            
                //essa função ira copiar a string até o valor sinalizado ')' ,e guardar o pedaço copiado na variavel valor
                valor = strtok(texto+(*pos),")");
                
                //a função atof ira converter o conteudo em string para float e atribuir a numero 
                arv->numero= atof(valor);            

                //contando qual é o tamanho do numero(string salva em valor)
                int numero = 0;
                numero = strlen(valor);
                numero++;

                //avançando de acordo com o tamanho do numero
                *pos = *pos + numero;
            
            return arv;
        }
  
        //se for um operador ira entrar nessa condição e logo depois ira chamar a função de criar para a direita
        if((texto[*pos] == '+' ) || (texto[*pos] == '-') || (texto[*pos] == '/') || (texto[*pos] == '*') ){
            //já guarda  o sinal do operador na letra
            arv->letra = texto[*pos];   
            *pos = *pos + 1;  //anda uma posição na string
        
            //cria um arv para a direita e aloca                 
            if(arv->direita == NULL){
                arv->direita = CriaARvore();
            }

            //chamamos a função recursivamente para criar a arvore para aquele nó 
            arv->direita = Parsing(arv->direita,texto,pos);
        }
        
        //se for um ) , ira andar mais uma posição e depois retornar 
        if(texto[*pos] == ')' ){
            *pos = *pos + 1;
            return arv;
        }
        
    return arv;
}




float CalculaArvore(Arv* arv){
    //se o arv for null retorna zero
    if(arv == NULL){
        return 0;
    }

    //se a direita e a esquerda forem NULL será uma folha , então retorna o numero
    if(arv->direita==NULL && arv->esquerda == NULL){
        return arv->numero;
    }

    //Chama a função recursivamente para calcular para direita e para a esquerda e receber os valores
    float direita = CalculaArvore(arv->direita);
    float esquerda = CalculaArvore(arv->esquerda); 


    //verifica qual sera a operação
    //quando a letra for +
    if(arv->letra == '+'){
        return (esquerda + direita);
    }

    //quando a letra for -
    if(arv->letra == '-'){
        return (esquerda - direita);
    }

    //quando a letra for /
    if(arv->letra == '/'){
        return (esquerda / direita);
    }

    //quando a letra for *
    if(arv->letra == '*'){
        return (esquerda * direita);
    }
}


Arv* LiberaArvore(Arv* arv){
    if( arv != NULL){   //se o ponteiro for diferente de NULL
       LiberaArvore(arv->esquerda); //libera o nó para esquerda 
       LiberaArvore(arv->direita);  //libera o nó para direita
       free(arv);       //libera o ponteiro 
    }
    return NULL;
}