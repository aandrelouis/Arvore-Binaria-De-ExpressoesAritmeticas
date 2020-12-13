#ifndef ARVORE
#define ARVORE

typedef struct arv Arv;

//função não recebe argumentos
//Ira retornar um NULL 
Arv* CriaVazia();


//Função recebe um ponteiro Arv, um ponteiro char e um ponteiro int;
//Essa função ira retornar um ponteiro arv que ira ser o inicio da arvore
//A sua função é construir a arvore apartir do texto , usando a recursão 
//usando o ponteiro int pos para pecorrer a string  dentro do char texto
Arv* Parsing(Arv* arv, char* texto,int* pos);


//Função recebe um ponteiro Arv 
//Essa função ira retornar um float que corresponde a todas operações realizadas dentro da arvore
//A sua função é calcular o valor da expressão da string e retornar o float resultado, usando a recursão 
//fazendo as verificações de validade do ponteiro, e simbolo do operador
float CalculaArvore(Arv* arv);


//Essa função não recebe argumentos
//Essa função ira retonar o ponteiro arv alocado , e suas variaveis inicializadas
//sua função é inicializar um ponteiro arv
Arv* CriaARvore();


//Função recebe um ponteiro Arv 
//Essa funçõa não retorna nada
//ira usar a recursão para imprimir toda a arvore
void ImprimeArvore(Arv* arv);

//Função recebe um ponteiro Arv 
//Essa funçõa retorna NULL
//ira pecorrer toda a arvore liberado os ponteiros
Arv* LiberaArvore(Arv* arv);

#endif