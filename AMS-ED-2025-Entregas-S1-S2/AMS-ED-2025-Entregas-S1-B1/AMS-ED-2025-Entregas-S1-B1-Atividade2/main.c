#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATOS 50

typedef struct {
    char *nome;
    float *PE;
    float *AC;  
    float *PP;  
    float *EB;  
    float nota_final;
} Candidato;

void ler_notas(float *notas, int quant) {
    for (int i = 0; i < quant; i++) {
        printf("Digite a nota %d: ", i + 1);
        scanf("%f", &notas[i]);
    }
}

float NotaFinal(float *notas, int quant) {
    float maior = notas[0], menor = notas[0], soma = 0;
    for (int i = 0; i < quant; i++) {
        if (notas[i] > maior) maior = notas[i];
        if (notas[i] < menor) menor = notas[i];
        soma += notas[i];
    }
    return (soma - maior - menor) / (quant - 2);
}

int compara(const void *a, const void *b) {
    Candidato *c1 = (Candidato *)a;
    Candidato *c2 = (Candidato *)b;
    return (c2->nota_final > c1->nota_final) - (c2->nota_final < c1->nota_final);
}

int main() {
    Candidato *candidatos = malloc(MAX_CANDIDATOS * sizeof(Candidato));
    int n_candidatos = 0;

    if (candidatos == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    printf("Quantos candidatos deseja inserir? (%d): ", MAX_CANDIDATOS);
    scanf("%d", &n_candidatos);
    getchar();

    for (int i = 0; i < n_candidatos; i++) {
        printf("\nCandidato %d:\n", i + 1);

        candidatos[i].nome = malloc(100 * sizeof(char));
        if (candidatos[i].nome == NULL) {
            printf("Erro ao alocar memória para o nome do candidato!\n");
            return 1;
        }

        do {
            printf("Nome do candidato: ");
            fgets(candidatos[i].nome, 100, stdin);
            candidatos[i].nome[strcspn(candidatos[i].nome, "\n")] = 0;

            if (strlen(candidatos[i].nome) == 0) {
                printf("O candidato precisa de um nome!\n");
            }
        } while (strlen(candidatos[i].nome) == 0);

        candidatos[i].PE = malloc(4 * sizeof(float));
        candidatos[i].AC = malloc(5 * sizeof(float));
        candidatos[i].PP = malloc(10 * sizeof(float));
        candidatos[i].EB = malloc(3 * sizeof(float));

        if (candidatos[i].PE == NULL || candidatos[i].AC == NULL || candidatos[i].PP == NULL || candidatos[i].EB == NULL) {
            printf("Erro!\n");
            return 1;
        }

        printf("Notas PE (4):\n");
        ler_notas(candidatos[i].PE, 4);
        printf("Notas AC (5):\n");
        ler_notas(candidatos[i].AC, 5);
        printf("Notas PP (10):\n");
        ler_notas(candidatos[i].PP, 10);
        printf("Notas EB (3):\n");
        ler_notas(candidatos[i].EB, 3);

        float NF = (NotaFinal(candidatos[i].PE, 4) * 0.3) +
                   (NotaFinal(candidatos[i].AC, 5) * 0.1) +
                   (NotaFinal(candidatos[i].PP, 10) * 0.4) +
                   (NotaFinal(candidatos[i].EB, 3) * 0.2);

        candidatos[i].nota_final = NF;
    }

    qsort(candidatos, n_candidatos, sizeof(Candidato), compara);

    printf("\nTop 5 candidatos:\n");
    for (int i = 0; i < (n_candidatos < 5 ? n_candidatos : 5); i++) {
        printf("%d. %s - Nota Final: %.2f\n", i + 1, candidatos[i].nome, candidatos[i].nota_final);
    }

    for (int i = 0; i < n_candidatos; i++) {
        free(candidatos[i].nome);
        free(candidatos[i].PE);
        free(candidatos[i].AC);
        free(candidatos[i].PP);
        free(candidatos[i].EB);
    }
    free(candidatos);

    return 0;
}
