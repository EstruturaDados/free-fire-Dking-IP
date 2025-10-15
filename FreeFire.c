#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Itens_Max_Mochila 10 //quantidade de itens maximo na mochila
#define Max_Str 20

// struct dos itens da mochila
typedef struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct mochila {
    Item itens[Itens_Max_Mochila];
    int total;
} mochila;


// WANTED: Manter todos os protótipos de funções juntos aqui.
void inicializarMochila(mochila *mochila);
void Inserir_Item(mochila *mochila, const char* nome, const char* tipo, int quantidade);
void Remover_Item(mochila *mochila, const char* nome);
void Buscar_Item(mochila *mochila, const char*nome);
void ImprimirItensCadastrados(const mochila *mochila);
void ImpressaoItensInicial(const mochila *mochila);
void Menu();
void LimparBuffer();
void LiberarMemoria();


int main(){
    mochila mochila;
    // mochila.total = 0; // Esta linha não é mais necessária, pois a função inicializarMochila já faz isso.
    int opcao;
    char nome[Max_Str], tipo[Max_Str];
    int quantidade;

    inicializarMochila(&mochila);

    do {
        printf("===========================");
        printf("\n MOCHILA DE SOBREVIVENCIA\n");
        printf("===========================\n\n");

        ImpressaoItensInicial(&mochila);
        ImprimirItensCadastrados(&mochila);
        Menu();
        printf("Escolha uma opcao: "); // Pequena melhoria na mensagem
        scanf("%d", &opcao);
        LimparBuffer();

        switch (opcao) {
            case 1:
                printf("\n----- Adicionar item -----\n");
                printf("Nome do item: \n");
                fgets(nome, Max_Str, stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Tipo do item (arma, municao, cura, etc): \n");
                fgets(tipo, Max_Str, stdin);
                tipo[strcspn(tipo, "\n")] = '\0';

                printf("Quantidade do item: \n");
                scanf("%d", &quantidade);
                LimparBuffer();

                Inserir_Item(&mochila, nome, tipo, quantidade);
                // WANTED: Removida a chamada ImprimirItensCadastrados daqui para evitar duplicidade.
                break;

            case 2:
                printf("\n----- Remover item -----\n");
                printf("Digite o nome do item que voce deseja remover: \n");
                fgets(nome, Max_Str, stdin);
                nome[strcspn(nome, "\n")] = '\0';

                Remover_Item(&mochila, nome);
                // WANTED: Removida a chamada ImprimirItensCadastrados para evitar duplicidade
                break;

            case 3:
                printf("\n----- Buscar item -----\n");
                printf("Digite o nome do item que deseja buscar: \n");
                fgets(nome, Max_Str, stdin);
                nome[strcspn(nome, "\n")] = '\0';

                Buscar_Item(&mochila, nome);
                break;

            case 0:
                printf("Saindo da mochila...\n");
                break;

            default:
                printf("Opcao invalida.\n");
                break;
        }

    } while (opcao != 0);
    
    return 0;
}


// --- Definição das Funções ---

void inicializarMochila(mochila *mochila){
    mochila->total = 0;
}

void Menu(){
    printf("\n1. Adicionar item \n");
    printf("2. Remover item \n");
    // WANTED: O texto foi corrigido.
    printf("3. Buscar item na mochila \n");
    printf("0. Sair da mochila \n\n");
}

void ImpressaoItensInicial(const mochila *mochila){
    if (mochila->total == 0) {
        printf("Itens na mochila %d / %d.\n\n", mochila->total, Itens_Max_Mochila);
    } else {
        printf("\nItens na mochila (%d/%d):\n\n", mochila->total, Itens_Max_Mochila);
    }
}

void Inserir_Item(mochila *mochila, const char* nome, const char* tipo, int quantidade){
    if (mochila->total == Itens_Max_Mochila){
        printf("Mochila cheia. Nao foi possivel adicionar o item.\n");
        return;
    }

    strcpy(mochila->itens[mochila->total].nome, nome);
    strcpy(mochila->itens[mochila->total].tipo, tipo);
    mochila->itens[mochila->total].quantidade = quantidade;
    mochila->total++;

    printf("\nItem '%s' adicionado com sucesso na mochila!\n", nome);
}

void Remover_Item(mochila *mochila, const char* nome){
    int i, pos = -1;

    for (i = 0; i < mochila->total; i++){
        if (strcmp(mochila->itens[i].nome, nome) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Erro, item '%s' nao encontrado na mochila.\n", nome);
        return;
    }

    for (i = pos; i < mochila->total - 1; i++) {
        mochila->itens[i] = mochila->itens[i + 1];
    }
    mochila->total--;
    printf("Item '%s' removido da mochila.\n", nome);
}

void Buscar_Item(mochila *mochila, const char* nome){
    for (int i = 0; i < mochila->total; i++){
        if (strcmp(mochila->itens[i].nome, nome) == 0){
            printf("\n--- Item Encontrado ---\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\n", mochila->itens[i].nome, mochila->itens[i].tipo, mochila->itens[i].quantidade);
            return;
        }
    }
    printf("Item '%s' nao encontrado na mochila.\n", nome);
}

void ImprimirItensCadastrados(const mochila *mochila){
    if (mochila->total == 0){
        return;
    }
    
    for (int i = 0; i < mochila->total; i++) {
        printf("-> Nome: %-15s | Tipo: %-15s | Qtd: %d\n", 
               mochila->itens[i].nome, 
               mochila->itens[i].tipo,
               mochila->itens[i].quantidade);
    }
    printf("\n");
}

void LimparBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Esta função não é necessária pois não há alocação dinâmica de memória (malloc).
void LiberarMemoria(){

}