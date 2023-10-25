typedef struct CELULA_TAG *PONT;

typedef struct {
    int posicao;
    char caracter;
}ITEM;

typedef struct CELULA_TAG{
    ITEM item;
    PONT prox;
}CELULA;

typedef struct{
    PONT topo, fundo;
    int tamanho;
}PILHA;

typedef struct{
    PONT first, last;
}FILA;

void menu();
void criarPilha(PILHA *pilha);
void criarFila(FILA *fila);
int empilhar(PILHA *pilha, ITEM item);
int enfileirar(FILA *fila, ITEM item);
int desempilhar(PILHA *pilha, ITEM *item);
int desenfileirar(FILA *fila, ITEM *item);
int filaVazia(FILA fila);
int pilhaVazia(PILHA pilha);
void imprimePilha(PILHA pilha);
void imprimeFila(FILA fila);
int lookPilha(PILHA *pilha, ITEM *item);
int lookFila(FILA *fila, ITEM *item);
int isOperand(char c);
int pre(char c);
