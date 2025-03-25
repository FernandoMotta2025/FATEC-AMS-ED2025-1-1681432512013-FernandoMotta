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
    int opcao, numero, quantidade;
    char cliente[50], descricao[100], status[20];
    
    do {
        printf("\n1. Adicionar Pedido\n");
        printf("2. Consultar Pedido\n");
        printf("3. Atualizar Status\n");
        printf("4. Deletar Pedido\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();
        
        switch (opcao) {
            case 1:
                printf("Numero do pedido: ");
                scanf("%d", &numero);
                getchar(); 
                printf("Nome do cliente: ");
                fgets(cliente, 50, stdin);
                cliente[strcspn(cliente, "\n")] = 0; 
                printf("Descricao do pedido: ");
                fgets(descricao, 100, stdin);
                descricao[strcspn(descricao, "\n")] = 0;
                printf("Quantidade: ");
                scanf("%d", &quantidade);
                getchar();
                printf("Status do pedido (Pendente, Em preparo, Pronto, Entregue): ");
                fgets(status, 20, stdin);
                status[strcspn(status, "\n")] = 0;
                
                lista = inserirPedido(lista, numero, cliente, descricao, quantidade, status);
                printf("Pedido adicionado!\n");
                break;
            
            case 2:
                printf("Numero do pedido para consulta: ");
                scanf("%d", &numero);
                obterPedido(lista, numero);
                break;
                
            case 3:
                printf("Numero do pedido para atualizar o status: ");
                scanf("%d", &numero);
                getchar();
                printf("Novo status do pedido: ");
                fgets(status, 20, stdin);
                status[strcspn(status, "\n")] = 0;
                atualizarStatus(lista, numero, status);
                break;
                
            case 4:
                printf("Numero do pedido a deletar: ");
                scanf("%d", &numero);
                lista = deletarPedido(lista, numero);
                break;
                
            case 5:
                liberarLista(lista);
                printf("Saindo...\n");
                break;
                
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 5);
    
    return 0;
}
