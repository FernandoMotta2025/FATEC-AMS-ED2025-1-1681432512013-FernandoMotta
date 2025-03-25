#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pedido {
    int numero;
    char cliente[50];
    char descricao[100];
    int quantidade;
    char status[20];
    struct Pedido *proximo;
} Pedido;

Pedido* criarLista() {
    return NULL;
}

Pedido* inserirPedido(Pedido *lista, int numero, char cliente[], char descricao[], int quantidade, char status[]) {
    Pedido *novo = (Pedido*) malloc(sizeof(Pedido));
    if (!novo) {
        printf("Erro na alocacao de memoria!\n");
        return lista;
    }
    novo->numero = numero;
    strcpy(novo->cliente, cliente);
    strcpy(novo->descricao, descricao);
    novo->quantidade = quantidade;
    strcpy(novo->status, status);
    novo->proximo = lista;
    return novo;
}

void obterPedido(Pedido *lista, int numero) {
    Pedido *atual = lista;
    while (atual) {
        if (atual->numero == numero) {
            printf("Pedido #%d\nCliente: %s\nDescricao: %s\nQuantidade: %d\nStatus: %s\n", 
                   atual->numero, atual->cliente, atual->descricao, atual->quantidade, atual->status);
            return;
        }
        atual = atual->proximo;
    }
    printf("Pedido nao encontrado!\n");
}

void atualizarStatus(Pedido *lista, int numero, char novoStatus[]) {
    Pedido *atual = lista;
    while (atual) {
        if (atual->numero == numero) {
            strcpy(atual->status, novoStatus);
            printf("Status atualizado com sucesso!\n");
            return;
        }
        atual = atual->proximo;
    }
    printf("Pedido nao encontrado!\n");
}

Pedido* deletarPedido(Pedido *lista, int numero) {
    Pedido *atual = lista, *anterior = NULL;
    while (atual && atual->numero != numero) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (!atual) {
        printf("Pedido nao encontrado!\n");
        return lista;
    }
    if (!anterior)
        lista = atual->proximo;
    else
        anterior->proximo = atual->proximo;
    free(atual);
    printf("Pedido removido com sucesso!\n");
    return lista;
}

void liberarLista(Pedido *lista) {
    Pedido *atual;
    while (lista) {
        atual = lista;
        lista = lista->proximo;
        free(atual);
    }
}

int main() {
    Pedido *lista = criarLista();

    lista = inserirPedido(lista, 1, "Motta", "Macarrao", 2, "Pendente");
    lista = inserirPedido(lista, 2, "Fernando", "Sanduiche", 3, "Pronto");
    
    obterPedido(lista, 1);
    obterPedido(lista, 2);
    
    atualizarStatus(lista, 1, "Pronto");
    
    obterPedido(lista, 1);
    
    lista = deletarPedido(lista, 1);
    
    obterPedido(lista, 1);
    obterPedido(lista, 2);
    liberarLista(lista);
    return 0;
}
