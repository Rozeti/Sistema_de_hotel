#ifndef HOTEL_H
#define HOTEL_H

#define MAX_QUARTOS 15
#define MAX_NOME 50
#define MAX_CPF 15

typedef struct Node {
    char nome[MAX_NOME];
    int idade;
    char cpf[MAX_CPF];
    struct Node *prox;
} Node;

typedef struct {
    Node *inicio;
    int ocupado;
} Quarto;

typedef struct {
    Quarto quartos[MAX_QUARTOS];
} Hotel;

void inicializarHotel(Hotel *hotel);
void inserirHospede(Hotel *hotel);
void listarHospedes(Hotel *hotel);
void buscarHospede(Hotel *hotel);
void editarHospede(Hotel *hotel);
void liberarQuarto(Hotel *hotel);
void mostrarQuartos(Hotel *hotel);
void salvarLista(Hotel *hotel);
void carregarLista(Hotel *hotel);
void liberarLista(Node *inicio);

#endif 
