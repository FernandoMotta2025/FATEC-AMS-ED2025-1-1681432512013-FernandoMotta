/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B2-2                                 */
/*             Objetivo: <<   utilização do Bubblesort    >>                        */
/*                                                                                  */
/*                                            Autor: Fernando Motta Fernandes       */
/*                                                                   Data:06/05/2025*/

#include <stdio.h>

int main() {
    int quant, i, j, temp;

    // Pede a quantidade de elementos
    printf("Digite a quantidade de elementos: ");
    scanf("%d", &quant);

    int arr[quant];

    // Lê os elementos
    for(i = 0; i < quant; i++) {
        printf("Digite o elemento %d: ", i + 1);
        scanf("%d", &arr[i]);
    }

    
    for(i = 0; i < quant - 1; i++) {
        for(j = 0; j < quant - i - 1; j++) {
            
            if(arr[j] > arr[j + 1]) {
                // Troca os elementos
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // Exibe o array em ordem crescente
    printf("Array : ");
    for(i = 0; i < quant; i++) {
        printf("%d  ", arr[i]);
    }
    return 0;
}
