
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B1-4                                 */
/*             Objetivo: <<   programação da calculadora HP12c    >>                */
/*                                                                                  */
/*                                            Autor: Fernando Motta Fernandes       */
/*                                                                   Data:02/04/2025*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM_MAX 100

typedef struct Pilha{
    double X, Y, Z, T;
} Pilha;

Pilha *criar_pilha(){
    Pilha *p = (Pilha *)malloc(sizeof(Pilha));  
    if (p == NULL) {
        printf("Erro: Falha ao alocar memória\n");
        exit(EXIT_FAILURE);
    }
    p->T = 0;
    p->Z = 0;
    p->Y = 0;
    p->X = 0;
    return p;
}

double top(Pilha *p){
    return p->X;
}

int cheia(Pilha *p){
    return (p->X != 0 && p->Y != 0 && p->Z != 0 && p->T != 0);
}

int vazia(Pilha *p){
    return (p->X == 0 && p->Y == 0 && p->Z == 0 && p->T == 0);
}

void push(Pilha *p, double dado){ 
    p->T = p->Z;
    p->Z = p->Y;
    p->Y = p->X;
    p->X = dado;
}

double pop(Pilha *p){ 
    double operador = p->X;
    p->X = p->Y;
    p->Y = p->Z;
    p->Z = p->T;
    p->T = 0;
    return operador; 
}

void calcularRPN(char *formula){
    Pilha *p = criar_pilha();
    char *token = strtok(formula, " ");
    char temp[50];

    char pilha_conv[TAM_MAX][TAM_MAX];                
    int top_conv = -1;                               

    while(token){ 
        if(isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))){
            if(!cheia(p)){
                double num = atof(token);                
                push(p, num);                             
                sprintf(temp, "%.2f ", num);             
                strcpy(pilha_conv[++top_conv], temp);           
            }
            else{
                printf("Erro: Memoria excedida\n");
                free(p);
                return;
            }
        }
        else{
            if(top_conv < 1){
                printf("Erro: Formatacao incorreta\n");
                free(p);
                return;
            }
            double b = pop(p);
            double a = pop(p);
            double result;

            switch(token[0]){
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/':
                    if(b == 0){
                        printf("Erro: Nao e possivel dividir por zero\n");
                        free(p);
                        return;
                    }
                    result = a / b; 
                    break;
                default:
                    printf("Erro: Operador incorreto\n");
                    free(p);
                    return;
            }
            push(p, result);
            sprintf(temp, "(%s %c %s) ", pilha_conv[top_conv - 1], token[0], pilha_conv[top_conv]);
            strcpy(pilha_conv[--top_conv], temp);
        }
        token = strtok(NULL, " ");
    }
    printf("-----\nResultado: %.2f \n", pop(p));
    printf("Expressao algebrica: %s\n", pilha_conv[0]);

    free(p);
}

int main(){
    char formula[TAM_MAX];

    printf("Insira a formula(formato RPN): ");
    fgets(formula, TAM_MAX, stdin);
    formula[strcspn(formula, "\n")] = 0;

    calcularRPN(formula);  
    return 0;
}
