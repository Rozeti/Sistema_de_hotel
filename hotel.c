#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hotel.h"

void inicializarHotel(Hotel *hotel) {
    for (int i = 0; i < MAX_QUARTOS; i++) {
        hotel->quartos[i].inicio = NULL;
        hotel->quartos[i].ocupado = 0;
    }
}

void mostrarMenu() {
    printf("\n      =======> MENU <=======\n");
    printf("1. Inserir hospedes em um quarto\n");
    printf("2. Listar hospedes por ordem alfabetica\n");
    printf("3. Buscar hospede\n");
    printf("4. Editar hospede\n");
    printf("5. Liberar um quarto\n");
    printf("6. Mostrar os numeros dos quartos\n");
    printf("7. Salvar lista de hospedes com respectivos quartos em arquivo\n");
    printf("0. Sair\n");
    printf("--> Escolha uma opcao: ");
}

void inserirHospede(Hotel *hotel) {
    int quarto;
    char nome[MAX_NOME];
    int idade;
    char cpf[MAX_CPF];
    printf("\n1. Inserir hospede: ");
    printf("\n--> Digite o nome do hospede: ");
    scanf(" %[^\n]", nome);
    printf("--> Digite a idade do hospede: ");
    scanf("%d", &idade);
    printf("--> Digite o CPF do hospede (apenas numeros): ");
    scanf("%s", cpf);

    printf("\n-> Quartos disponiveis e ocupados:\n");
    for (int i = 0; i < MAX_QUARTOS; i++) {
        printf("Quarto %d: ", i + 1);
        if (hotel->quartos[i].ocupado) {
            printf("Ocupado\n");
        } else {
            printf("Vazio\n");
        }
    }

    printf("\n--> Em qual quarto deseja inserir o hospede: ");
    scanf("%d", &quarto);
    quarto--;

    if (quarto < 0 || quarto >= MAX_QUARTOS) {
        printf("# Quarto invalido. #\n");
        return;
    }

    Node *novo = (Node *)malloc(sizeof(Node));
    if (novo == NULL) {
        printf("\nErro ao alocar memoria.\n");
        return;
    }

    char nomeFormatado[MAX_NOME];
    strcpy(nomeFormatado, nome);
    nomeFormatado[0] = toupper(nomeFormatado[0]); 
    for (int j = 1; nomeFormatado[j] != '\0'; j++) {
        if (nomeFormatado[j - 1] == ' ') { 
            nomeFormatado[j] = toupper(nomeFormatado[j]); 
        }
    }

    strcpy(novo->nome, nomeFormatado);
    novo->idade = idade;
    strcpy(novo->cpf, cpf);

    Node *atual = hotel->quartos[quarto].inicio;
    Node *anterior = NULL;
    while (atual != NULL && strcmp(atual->nome, nomeFormatado) < 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (anterior == NULL) {
        novo->prox = hotel->quartos[quarto].inicio;
        hotel->quartos[quarto].inicio = novo;
    } else {
        anterior->prox = novo;
        novo->prox = atual;
    }

    hotel->quartos[quarto].ocupado = 1;
    printf("\n-> Hospede inserido com sucesso no quarto %d.\n\n", quarto + 1);
}

void listarHospedes(Hotel *hotel) {
    printf("\n2. Lista de hospedes:\n\n");
    int algumQuartoOcupado = 0; 

    for (int i = 0; i < MAX_QUARTOS; i++) {
        if (hotel->quartos[i].ocupado == 1) {
            algumQuartoOcupado = 1; 
            printf("-> Quarto %d:\n", i + 1);
            Node *atual = hotel->quartos[i].inicio;
            while (atual != NULL) {
                printf("- %s | Idade: %d | CPF: %s\n", atual->nome, atual->idade, atual->cpf);
                atual = atual->prox;
            }
        }
    }
    printf("\n");

    if (!algumQuartoOcupado) {
        printf("# Nenhum quarto foi ocupado ainda. #\n\n");
    }
}

void buscarHospede(Hotel *hotel) {
    char nome[MAX_NOME];
    printf("\n3. Busca por hospede: \n");
    printf("\n--> Digite o nome do hospede que deseja buscar: ");
    scanf(" %[^\n]", nome);

    int encontrado = 0;

    for (int i = 0; i < MAX_QUARTOS; i++) {
        Node *atual = hotel->quartos[i].inicio;
        while (atual != NULL) {
            char nomeSalvo[MAX_NOME];
            strcpy(nomeSalvo, atual->nome);
            for (int j = 0; nomeSalvo[j] != '\0'; j++) {
                nomeSalvo[j] = tolower(nomeSalvo[j]);
            }
            char nomeBuscado[MAX_NOME];
            strcpy(nomeBuscado, nome);
            for (int j = 0; nomeBuscado[j] != '\0'; j++) {
                nomeBuscado[j] = tolower(nomeBuscado[j]);
            }
            if (strstr(nomeSalvo, nomeBuscado) != NULL) {
                encontrado = 1;
                printf("\n-> Encontrado: \n");
                printf("- O hospede %s esta no quarto %d.\n", atual->nome, i + 1);
                printf("- Idade: %d\n", atual->idade);
                printf("- CPF: %s\n\n", atual->cpf);
            }
            atual = atual->prox;
        }
    }
    if (!encontrado) {
        printf("\n# Hospede nao encontrado. #\n\n");
    }
}

void editarHospede(Hotel *hotel) {
    char nome[MAX_NOME];
    printf("\n4. Editar hospede: \n");
    printf("\n--> Digite o nome do hospede que deseja editar: ");
    scanf(" %[^\n]", nome);

    int encontrado = 0; 

    for (int i = 0; i < MAX_QUARTOS; i++) {
        Node *atual = hotel->quartos[i].inicio;
        while (atual != NULL) {
            char nomeSalvo[MAX_NOME];
            strcpy(nomeSalvo, atual->nome);
            for (int j = 0; nomeSalvo[j] != '\0'; j++) {
                nomeSalvo[j] = tolower(nomeSalvo[j]);
            }

            char nomeBuscado[MAX_NOME];
            strcpy(nomeBuscado, nome);
            for (int j = 0; nomeBuscado[j] != '\0'; j++) {
                nomeBuscado[j] = tolower(nomeBuscado[j]);
            }

            if (strstr(nomeSalvo, nomeBuscado) != NULL) {
                encontrado = 1; 

                Node *copia = (Node *)malloc(sizeof(Node)); 
                if (copia == NULL) {
                    printf("Erro ao alocar memoria.\n");
                    return;
                }
                strcpy(copia->nome, atual->nome);
                copia->idade = atual->idade;
                strcpy(copia->cpf, atual->cpf);
                copia->prox = NULL;

                int opcao;
                do {
                    printf("\n-> Encontrado: \n");
                    printf("\n===> Menu de Edicao <===\n");
                    printf("1. Editar nome\n");
                    printf("2. Editar idade\n");
                    printf("3. Editar CPF\n");
                    printf("0. Salvar e voltar ao menu principal\n");
                    printf("--> Escolha uma opcao: ");
                    scanf("%d", &opcao);

                    switch (opcao) {
                        case 1:
                            printf("\n1. Editar nome: ");
                            printf("\n\n--> Digite o novo nome do hospede: ");
                            scanf(" %[^\n]", copia->nome);

                            char novoNomeFormatado[MAX_NOME];
                            strcpy(novoNomeFormatado, copia->nome);
                            novoNomeFormatado[0] = toupper(novoNomeFormatado[0]); 
                            for (int j = 1; novoNomeFormatado[j] != '\0'; j++) {
                                if (novoNomeFormatado[j - 1] == ' ') {
                                    novoNomeFormatado[j] = toupper(novoNomeFormatado[j]); 
                                }
                            }
                            strcpy(atual->nome, novoNomeFormatado);
                            break;
                        case 2:
                            printf("\n2. Editar idade: ");
                            printf("\n--> Digite a nova idade do hospede: ");
                            scanf("%d", &copia->idade);
                            atual->idade = copia->idade;
                            break;
                        case 3:
                            printf("\n3. Editar CPF: ");
                            printf("\n--> Digite o novo CPF do hospede (apenas numeros): ");
                            scanf("%s", copia->cpf);
                            strcpy(atual->cpf, copia->cpf);
                            break;
                        case 0:
                            printf("\nAlteracoes salvas.\n\n");
                            break;
                        default:
                            printf("\n# Opcao invalida. Tente novamente. #\n");
                    }
                } while (opcao != 0);

                free(copia); 
            }
            atual = atual->prox;
        }
        if (encontrado) {
            break;
        }
    }
    if (!encontrado) {
        printf("\n# Hospede nao encontrado. #\n");
    }
    salvarLista(hotel);
}
