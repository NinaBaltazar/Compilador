#include <stdio.h>
#include <stdlib.h>  // Inclua stdlib.h para a função exit
#include "tokens.h"
#include "parser.h"

// Variável global para armazenar o token atual
Token currentToken;

// Função auxiliar para pegar o próximo token
void nextTokenHelper(FILE *source) {
    currentToken = nextToken(source);
}

// Função para verificar o token atual e obter o próximo
void match(TokenType expected, FILE *source) {
    if (currentToken.type == expected) {
        nextTokenHelper(source);
    } else {
        printf("Erro sintático: esperado '%s', mas encontrado '%s'.\n",
               tokenTypeToString(expected), tokenTypeToString(currentToken.type));
        exit(1);  // Interrompe a execução no caso de erro
    }
}

// Função principal do analisador sintático
void parseProgram(FILE *source) {
    nextTokenHelper(source);  // Obtém o primeiro token
    while (currentToken.type != TOKEN_EOF) {
        parseStatement(source);  // Analisa uma sequência de comandos
    }
    printf("Análise sintática concluída com sucesso.\n");
}

// Função que analisa comandos (if, while, atribuição, etc.)
void parseStatement(FILE *source) {
    if (currentToken.type == TOKEN_IF) {
        match(TOKEN_IF, source);
        parseExpression(source);  // Condição do if
        match(TOKEN_THEN, source);
        parseStatement(source);  // Comando após o then
        if (currentToken.type == TOKEN_ELSE) {
            match(TOKEN_ELSE, source);
            parseStatement(source);  // Comando após o else
        }
    } else if (currentToken.type == TOKEN_WHILE) {
        match(TOKEN_WHILE, source);
        parseExpression(source);  // Condição do while
        parseStatement(source);  // Corpo do while
    } else if (currentToken.type == TOKEN_IDENTIFIER) {
        match(TOKEN_IDENTIFIER, source);  // Variável de atribuição
        match(TOKEN_ASSIGN, source);  // Sinal de atribuição '='
        parseExpression(source);  // Expressão do lado direito
        match(TOKEN_SEMICOLON, source);  // Ponto e vírgula
    } else {
        printf("Erro sintático: comando inesperado '%s'.\n", tokenTypeToString(currentToken.type));
        exit(1);
    }
}

// Função que analisa expressões (operações aritméticas e lógicas)
void parseExpression(FILE *source) {
    parseTerm(source);  // Começa analisando um termo
    while (currentToken.type == TOKEN_PLUS || currentToken.type == TOKEN_MINUS) {
        nextTokenHelper(source);  // Consome o operador '+' ou '-'
        parseTerm(source);  // Analisa o próximo termo
    }
}

// Função que analisa termos (operações de multiplicação e divisão)
void parseTerm(FILE *source) {
    parseFactor(source);  // Começa analisando um fator
    while (currentToken.type == TOKEN_MULTIPLY || currentToken.type == TOKEN_DIVIDE) {
        nextTokenHelper(source);  // Consome o operador '*' ou '/'
        parseFactor(source);  // Analisa o próximo fator
    }
}

// Função que analisa fatores (números, identificadores ou expressões entre parênteses)
void parseFactor(FILE *source) {
    if (currentToken.type == TOKEN_LPAREN) {
        match(TOKEN_LPAREN, source);
        parseExpression(source);  // Expressão entre parênteses
        match(TOKEN_RPAREN, source);
    } else if (currentToken.type == TOKEN_NUMBER_INT || currentToken.type == TOKEN_NUMBER_REAL) {
        nextTokenHelper(source);  // Consome o número
    } else if (currentToken.type == TOKEN_IDENTIFIER) {
        nextTokenHelper(source);  // Consome o identificador
    } else {
        printf("Erro sintático: fator inesperado '%s'.\n", tokenTypeToString(currentToken.type));
        exit(1);
    }
}
