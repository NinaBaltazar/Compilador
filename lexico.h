
// lexico.h
#ifndef LEXICO_H
#define LEXICO_H

typedef struct {
    int tipo;
    char valor[100];
} Token;

enum TipoToken {
    IDENTIFICADOR,
    NUMERO,
    OPERADOR,
    DELIMITADOR,
    FIM
};

Token proximoToken(); // Remover o parâmetro 'char *code'

#endif

// typedef enum {
//     PALAVRA_CHAVE,   // Para "inteiro", "real", "se", "enquanto", "repita", "ate"
//     IDENTIFICADOR,
//     NUMERO_INTEIRO,
//     NUMERO_REAL,
//     SE,
//     OPERADOR,        // Para operadores como ">", "<", "==", etc.
//     DELIMITADOR,     // Para delimitadores como "(", ")", "{", "}", ";", ","
//     MOSTRAR,         // Token específico para o comando "mostrar"
//     LER,             // Token específico para o comando "ler"
//     ENQUANTO,        // Token específico para "enquanto"
//     REPITA,          // Token específico para "repita"
//     ATE,             // Token específico para "ate"
//     FIM,            // Para indicar o final do código
// } TipoToken;

// typedef struct {
//     TipoToken tipo;
//     char valor[100];
// } Token;

// // Funções do analisador léxico
// void tokenize(char *code);
// int isKeyword(char *str);
// int isOperator(char *str);
// int isDelimiter(char ch);
// void skipWhitespace(char *code, int *i);

// #endif
