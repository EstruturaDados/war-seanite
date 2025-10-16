#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERRITORIOS 5
#define MAX_NOME 50
#define MAX_COR 20

typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
    int conquistado;
} Territorio;

typedef struct {
    int tipo; // 1 = destruir exército verde, 2 = conquistar 3 territórios
    int concluida;
} Missao;

void inicializarTerritorios(Territorio *mapa) {
    const char *nomes[] = {"Alfa", "Bravo", "Charlie", "Delta", "Echo"};
    const char *cores[] = {"Verde", "Azul", "Vermelho", "Amarelo", "Preto"};
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        strcpy(mapa[i].nome, nomes[i]);
        strcpy(mapa[i].cor, cores[i]);
        mapa[i].tropas = rand() % 10 + 1;
        mapa[i].conquistado = 0;
    }
}

void exibirMapa(Territorio *mapa) {
    printf("\nEstado Atual do Mapa:\n");
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("Território %d: %s | Cor: %s | Tropas: %d | %s\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas,
               mapa[i].conquistado ? "Conquistado" : "Original");
    }
}

void simularBatalha(Territorio *mapa, int atacante, int defensor) {
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\nBatalha entre %s (A) e %s (D)\n", mapa[atacante].nome, mapa[defensor].nome);
    printf("Dado Atacante: %d | Dado Defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante >= dadoDefensor) {
        mapa[defensor].tropas--;
        printf("Atacante venceu! Tropas do defensor agora: %d\n", mapa[defensor].tropas);
        if (mapa[defensor].tropas <= 0) {
            mapa[defensor].conquistado = 1;
            strcpy(mapa[defensor].cor, mapa[atacante].cor);
            mapa[defensor].tropas = 1;
            printf("Território %s foi conquistado!\n", mapa[defensor].nome);
        }
    } else {
        printf("Defensor resistiu ao ataque.\n");
    }
}

void verificarMissao(Territorio *mapa, Missao *missao) {
    if (missao->tipo == 1) {
        int verdeRestante = 0;
        for (int i = 0; i < MAX_TERRITORIOS; i++) {
            if (strcmp(mapa[i].cor, "Verde") == 0 && mapa[i].tropas > 0) {
                verdeRestante++;
            }
        }
        missao->concluida = (verdeRestante == 0);
    } else if (missao->tipo == 2) {
        int conquistados = 0;
        for (int i = 0; i < MAX_TERRITORIOS; i++) {
            if (mapa[i].conquistado) {
                conquistados++;
            }
        }
        missao->concluida = (conquistados >= 3);
    }

    if (missao->concluida) {
        printf("\n🎉 Missão Concluída!\n");
    } else {
        printf("\n🚧 Missão ainda não concluída.\n");
    }
}

void mostrarMissao(Missao *missao) {
    printf("\nMissão Atual:\n");
    if (missao->tipo == 1) {
        printf("Destruir o exército Verde.\n");
    } else {
        printf("Conquistar 3 territórios.\n");
    }
}

int main() {
    srand(time(NULL));
    Territorio *mapa = calloc(MAX_TERRITORIOS, sizeof(Territorio));
    Missao missao = { .tipo = rand() % 2 + 1, .concluida = 0 };

    inicializarTerritorios(mapa);

    int opcao;
    do {
        printf("\nMenu Principal:\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missão\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                int a, d;
                exibirMapa(mapa);
                printf("Escolha território atacante (1-5): ");
                scanf("%d", &a);
                printf("Escolha território defensor (1-5): ");
                scanf("%d", &d);
                if (a >= 1 && a <= 5 && d >= 1 && d <= 5 && a != d) {
                    simularBatalha(mapa, a - 1, d - 1);
                } else {
                    printf("Escolhas inválidas.\n");
                }
                break;
            }
            case 2:
                mostrarMissao(&missao);
                verificarMissao(mapa, &missao);
                break;
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0 && !missao.concluida);

    free(mapa);
    return 0;
}