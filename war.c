#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NOME 30
#define MAX_COR 10

typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

// Funções
Territorio* alocarTerritorios(int quantidade);
void cadastrarTerritorios(Territorio* mapa, int quantidade);
void exibirMapa(Territorio* mapa, int quantidade);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);
void limparBufferEntrada();

int main() {
    srand(time(NULL));

    int quantidade;
    printf("Informe o número de territórios (ex: 5): ");
    scanf("%d", &quantidade);
    limparBufferEntrada();

    Territorio* mapa = alocarTerritorios(quantidade);
    if (!mapa) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, quantidade);

    int opcao;
    do {
        exibirMapa(mapa, quantidade);

        printf("\nEscolha uma ação:\n");
        printf("1 - Atacar\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        if (opcao == 1) {
            int i, j;
            printf("Escolha o território atacante (0 a %d): ", quantidade - 1);
            scanf("%d", &i);
            printf("Escolha o território defensor (0 a %d): ", quantidade - 1);
            scanf("%d", &j);
            limparBufferEntrada();

            if (i == j || i < 0 || j < 0 || i >= quantidade || j >= quantidade) {
                printf("⚠️ Escolha inválida.\n");
            } else if (strcmp(mapa[i].cor, mapa[j].cor) == 0) {
                printf("⚠️ Não é possível atacar um território da mesma cor.\n");
            } else {
                atacar(&mapa[i], &mapa[j]);
            }
        }

    } while (opcao != 0);

    liberarMemoria(mapa);
    return 0;
}

// Aloca memória para os territórios
Territorio* alocarTerritorios(int quantidade) {
    return (Territorio*)calloc(quantidade, sizeof(Territorio));
}

// Cadastra os dados dos territórios
void cadastrarTerritorios(Territorio* mapa, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("\nTerritório %d:\n", i);
        printf("Nome: ");
        fgets(mapa[i].nome, MAX_NOME, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets(mapa[i].cor, MAX_COR, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBufferEntrada();
    }
}

// Exibe o estado atual do mapa
void exibirMapa(Territorio* mapa, int quantidade) {
    printf("\n🌍 Mapa Atual:\n");
    for (int i = 0; i < quantidade; i++) {
        printf("%d - %s | Exército: %s | Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Simula um ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("🎲 Dado do atacante: %d\n", dadoAtacante);
    printf("🎲 Dado do defensor: %d\n", dadoDefensor);

    if (dadoAtacante >= dadoDefensor) {
        printf("✅ Ataque bem-sucedido!\n");
        defensor->tropas--;
        if (defensor->tropas <= 0) {
            printf("🏳️ Território conquistado!\n");
            strncpy(defensor->cor, atacante->cor, MAX_COR);
            defensor->tropas = 1;
            atacante->tropas--;
        }
    } else {
        printf("❌ Defesa bem-sucedida! O atacante perde 1 tropa.\n");
        atacante->tropas--;
        if (atacante->tropas < 0) atacante->tropas = 0;
    }
}

// Libera a memória alocada
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

// Limpa o buffer de entrada
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}