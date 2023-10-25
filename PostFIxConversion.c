#include <stdlib.h>
#include <stdio.h>
#include "PostFix.h"

//Operação de exemplo: a+b*c-d/e;

int main(void){
    setbuf(stdin, NULL);

    int i = 0;
    char operacaoChar[20];
    FILA operacao;
    PILHA operador;
    ITEM item;
    ITEM aux;
    criarFila(&operacao);
    criarPilha(&operador);

    menu();

    printf("\nDigite a operação em notação infixa: \n");
    scanf("%s", operacaoChar);

    while(operacaoChar[i] != '\0'){
        item.posicao = i;

        if(isOperand(operacaoChar[i])){
            item.caracter = operacaoChar[i];
            enfileirar(&operacao, item);
        }else{
            lookPilha(&operador, &item);
            aux = item;

            if(!isOperand(item.caracter) && (pre(item.caracter)>pre(operacaoChar[i]))){
                while(!pilhaVazia(operador)){
                    desempilhar(&operador, &item);
                    aux = item;
                    enfileirar(&operacao, aux);
                }
            }
            item.caracter = operacaoChar[i];
            empilhar(&operador, item);
        }
        i++;
    }

    while(!pilhaVazia(operador)){
        desempilhar(&operador, &item);
        aux = item;
        enfileirar(&operacao, aux);
    }

    imprimeFila(operacao);
    
    return 0;
}

void menu(){
    char arte[] =
            "██████╗  ██████╗ ███████╗███████╗██╗██╗ \n"
                "██╔══██╗██╔═══██╗██╔════╝██╔════╝██║╚██╗██╔╝ \n"                                 
            "██████╔╝██║   ██║███████╗█████╗  ██║ ╚███╔╝ \n"
            "██╔═══╝ ██║   ██║╚════██║██╔══╝  ██║ ██╔██╗ \n"                                  
            "██║     ╚██████╔╝███████║██║     ██║██╔╝ ██╗ \n"
            "╚═╝      ╚═════╝ ╚══════╝╚═╝     ╚═╝╚═╝  ╚═╝ \n"                                    
                                                                                        
            "  ██████╗ ██████╗ ███╗   ██╗██╗   ██╗███████╗██████╗ ███████╗ ██████╗ ██████╗ \n"
            " ██╔════╝██╔═══██╗████╗  ██║██║   ██║██╔════╝██╔══██╗██╔════╝██╔═══██╗██╔══██╗ \n"
            " ██║     ██║   ██║██╔██╗ ██║██║   ██║█████╗  ██████╔╝███████╗██║   ██║██████╔╝ \n"
            " ██║     ██║   ██║██║╚██╗██║╚██╗ ██╔╝██╔══╝  ██╔══██╗╚════██║██║   ██║██╔══██╗ \n"
            " ╚██████╗╚██████╔╝██║ ╚████║ ╚████╔╝ ███████╗██║  ██║███████║╚██████╔╝██║  ██║ \n"
            "╚═════╝ ╚═════╝ ╚═╝  ╚═══╝  ╚═══╝  ╚══════╝╚═╝  ╚═╝╚══════╝ ╚═════╝ ╚═╝  ╚═╝"
        ;

    printf("\n%s\n", arte);
}

void criarPilha(PILHA *pilha){
    pilha->topo = (PONT)malloc(sizeof(CELULA));
    pilha->fundo = pilha->topo;
    pilha->topo->prox = NULL;
    pilha->tamanho = 0;
}

void criarFila(FILA *fila){
    fila->first = (PONT)malloc(sizeof(CELULA));
    fila->last = fila->first;
    fila->last->prox = NULL;
}

int empilhar(PILHA *pilha, ITEM item){
    PONT aux = (PONT)malloc(sizeof(CELULA));

    pilha->topo->item = item;
    aux->prox=pilha->topo;
    pilha->topo = aux;
    pilha->tamanho++;
    return 0;
}

int enfileirar(FILA *fila, ITEM item){
    fila->last->prox = (PONT)malloc(sizeof(CELULA));
    fila->last = fila->last->prox;
    fila->last->item = item;
    fila->last->prox = NULL;
    return 0;
}

int desempilhar(PILHA *pilha, ITEM *item){
    if(pilhaVazia(*pilha)){
        printf("A pilha esta vazia");
        return -1;
    }

    PONT q;
    q = pilha->topo;
    pilha->topo = q->prox;
    *item = q->prox->item;
    free(q);
    pilha->tamanho--;
    return 0;
}

int desenfileirar(FILA *fila, ITEM *item){
    if(filaVazia(*fila)){
        printf("A fila esta vazia");
        return -1;
    }

    PONT q = fila->first;
    fila->first = q->prox;
    *item = q->prox->item;
    free(q);
    return 0;
}

int pilhaVazia(PILHA pilha){
    return pilha.topo == pilha.fundo;
}

int filaVazia(FILA fila){
    return fila.first == fila.last;
}

void imprimeFila(FILA fila){
    if(filaVazia(fila)){
        printf("\nFila vazia.\n");
    }

    PONT aux = fila.first->prox;

    printf("\nNotação Pós-fixa: ");
    while(aux != NULL){
        printf("%c", aux->item.caracter);
        aux = aux->prox;
    }
    printf("\n");
}

void imprimePilha(PILHA pilha){
    if(pilhaVazia(pilha)){
        printf("\nPIlha vazia.\n");
    }

    PONT aux = pilha.topo->prox;

    printf("\nOperadores: ");
    while(aux != NULL){
        printf("%c", aux->item.caracter);
        aux = aux->prox;
    }
    printf("\n");
}

int lookFila(FILA *fila, ITEM *item){
	if(filaVazia(*fila)){
		return -1;
	}
	*item = fila->first->prox->item;
	return 0;
}

int lookPilha(PILHA *pilha, ITEM *item){
	if(pilhaVazia(*pilha)){
		return -1;
	}
	*item = pilha->topo->prox->item;
	return 0;
}

int isOperand(char c){
    if(c == '+' || c == '-' || c == '*' || c == '/'){
        return 0;
    }else{
        return 1;
    }
}

int pre(char c){
    if(c == '+' || c == '-'){
        return 1;
    }
    if(c == '*' || c == '/'){
        return 2;
    }
    return -1;
}
