void Desconto(float *val, float desc) {
    *val -= (*val * (desc / 100));
}

int main() {
    float val, desc;

    printf("Digite o preco do produto: ");
    scanf("%f", &val);//entrada do valor


    printf("Digite o percentual de desconto: ");
    scanf("%f", &desc);//entrada da porcentagem a ser descontada 

    printf("Preco original: R$ %.2f\n", val);//saída do valor original


    Desconto(&val, desc);
    printf("Desconto aplicado: %.2f\n", desc);//saída da porcentagem a ser descontada
    printf("Preco final apos o desconto: R$ %.2f\n", val);//preco depois do ajuste(com uso do ponteiro)

    return 0;
}
