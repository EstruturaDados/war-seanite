#include <stdio.h>
#include <string.h>

#define MAX_TERRITORIOS 5
#define MAX_NOME 50
#define MAX_COR 20

typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

int main() {
    Territorio mapa[MAX_TERRITORIOS];

    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: ");
        fgets(mapa[i].nome, MAX_NOME, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0'; // remove \n

        printf("Cor do Exército: ");
        fgets(mapa[i].cor, MAX_COR, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Número de Tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // limpa o buffer
    }

    printf("\n🌍 Estado Atual do Mapa:\n");
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("Território %d - %s | Exército: %s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }

    return 0;
}