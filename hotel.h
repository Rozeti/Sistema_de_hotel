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
