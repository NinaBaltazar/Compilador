#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "tokens.h"

// Função para ignorar espaços em branco e comentários
void skipWhitespaceAndComments(FILE *source) {
    char c = fgetc(source);

    while (c != EOF) {
        // Ignorar espaços em branco
        if (c == ' ' || c == '\t' || c == '\n') {
            c = fgetc(source);
            continue;
        }

        // Ignorar comentários /*...*/
        if (c == '/') {
            char next = fgetc(source);
            if (next == '*') {
                while (1) {
                    c = fgetc(source);
                    if (c == EOF) return;
                    if (c == '*' && (next = fgetc(source)) == '/') break;
                }
                c = fgetc(source);
                continue;
            } else {
                ungetc(next, source);
            }
        }
        break;
    }

    if (c != EOF) {
        ungetc(c, source);
    }
}

// Função que retorna o próximo token
Token nextToken(FILE *source) {
    char c;
    Token token;

    skipWhitespaceAndComments(source);
    c = fgetc(source);

    if (c == EOF) {
        token.type = TOKEN_EOF;
        strcpy(token.lexeme, "EOF");
        return token;
    }

    if (isalpha(c)) {
        char buffer[100];
        int i = 0;
        do {
            buffer[i++] = c;
            c = fgetc(source);
        } while (isalnum(c) || c == '_');
        buffer[i] = '\0';
        ungetc(c, source);

        if (strcmp(buffer, "inteiro") == 0) token.type = TOKEN_INT;
        else if (strcmp(buffer, "real") == 0) token.type = TOKEN_REAL;
        else if (strcmp(buffer, "se") == 0) token.type = TOKEN_IF;
        else if (strcmp(buffer, "entao") == 0) token.type = TOKEN_THEN;
        else if (strcmp(buffer, "senao") == 0) token.type = TOKEN_ELSE;
        else if (strcmp(buffer, "enquanto") == 0) token.type = TOKEN_WHILE;
        else if (strcmp(buffer, "repita") == 0) token.type = TOKEN_REPEAT;
        else if (strcmp(buffer, "ate") == 0) token.type = TOKEN_UNTIL;
        else if (strcmp(buffer, "ler") == 0) token.type = TOKEN_READ;
        else if (strcmp(buffer, "mostrar") == 0) token.type = TOKEN_WRITE;
        else token.type = TOKEN_IDENTIFIER;

        strcpy(token.lexeme, buffer);
    } else if (isdigit(c)) {
        char buffer[100];
        int i = 0;
        int isReal = 0;

        do {
            buffer[i++] = c;
            c = fgetc(source);
            if (c == '.') {
                isReal = 1;
                buffer[i++] = c;
                c = fgetc(source);
            }
        } while (isdigit(c));
        buffer[i] = '\0';
        ungetc(c, source);

        token.type = isReal ? TOKEN_NUMBER_REAL : TOKEN_NUMBER_INT;
        strcpy(token.lexeme, buffer);
    } else if (c == '+') {
        token.type = TOKEN_PLUS;
        strcpy(token.lexeme, "+");
    } else if (c == '-') {
        token.type = TOKEN_MINUS;
        strcpy(token.lexeme, "-");
    } else if (c == '*') {
        token.type = TOKEN_MULTIPLY;
        strcpy(token.lexeme, "*");
    } else if (c == '/') {
        token.type = TOKEN_DIVIDE;
        strcpy(token.lexeme, "/");
    } else if (c == '=') {
        char next = fgetc(source);
        if (next == '=') {
            token.type = TOKEN_EQ;
            strcpy(token.lexeme, "==");
        } else {
            ungetc(next, source);
            token.type = TOKEN_ASSIGN;
            strcpy(token.lexeme, "=");
        }
    } else if (c == '<') {
        char next = fgetc(source);
        if (next == '=') {
            token.type = TOKEN_LTE;
            strcpy(token.lexeme, "<=");
        } else {
            ungetc(next, source);
            token.type = TOKEN_LT;
            strcpy(token.lexeme, "<");
        }
    } else if (c == '>') {
        char next = fgetc(source);
        if (next == '=') {
            token.type = TOKEN_GTE;
            strcpy(token.lexeme, ">=");
        } else {
            ungetc(next, source);
            token.type = TOKEN_GT;
            strcpy(token.lexeme, ">");
        }
    } else if (c == '&') {
        char next = fgetc(source);
        if (next == '&') {
            token.type = TOKEN_AND;
            strcpy(token.lexeme, "&&");
        } else {
            printf("Erro léxico: caractere inesperado '&'.\n");
            exit(1);
        }
    } else if (c == '|') {
        char next = fgetc(source);
        if (next == '|') {
            token.type = TOKEN_OR;
            strcpy(token.lexeme, "||");
        } else {
            printf("Erro léxico: caractere inesperado '|'.\n");
            exit(1);
        }
    } else if (c == ';') {
        token.type = TOKEN_SEMICOLON;
        strcpy(token.lexeme, ";");
    } else if (c == ',') {
        token.type = TOKEN_COMMA;
        strcpy(token.lexeme, ",");
    } else if (c == '(') {
        token.type = TOKEN_LPAREN;
        strcpy(token.lexeme, "(");
    } else if (c == ')') {
        token.type = TOKEN_RPAREN;
        strcpy(token.lexeme, ")");
    } else {
        printf("Erro léxico: caractere inesperado '%c'.\n", c);
        exit(1);
    }

    return token;
}

// Função para converter o tipo de token em string
const char* tokenTypeToString(TokenType type) {
    switch (type) {
        case TOKEN_INT: return "inteiro";
        case TOKEN_REAL: return "real";
        case TOKEN_IF: return "se";
        case TOKEN_THEN: return "então";
        case TOKEN_ELSE: return "senão";
        case TOKEN_WHILE: return "enquanto";
        case TOKEN_REPEAT: return "repita";
        case TOKEN_UNTIL: return "até";
        case TOKEN_READ: return "ler";
        case TOKEN_WRITE: return "mostrar";
        case TOKEN_PLUS: return "+";
        case TOKEN_MINUS: return "-";
        case TOKEN_MULTIPLY: return "*";
        case TOKEN_DIVIDE: return "/";
        case TOKEN_AND: return "&&";
        case TOKEN_OR: return "||";
        case TOKEN_LT: return "<";
        case TOKEN_LTE: return "<=";
        case TOKEN_GT: return ">";
        case TOKEN_GTE: return ">=";
        case TOKEN_EQ: return "==";
        case TOKEN_NEQ: return "!=";
        case TOKEN_ASSIGN: return "=";
        case TOKEN_SEMICOLON: return ";";
        case TOKEN_COMMA: return ",";
        case TOKEN_LPAREN: return "(";
        case TOKEN_RPAREN: return ")";
        case TOKEN_LBRACE: return "{";
        case TOKEN_RBRACE: return "}";
        case TOKEN_IDENTIFIER: return "identificador";
        case TOKEN_NUMBER_INT: return "número inteiro";
        case TOKEN_NUMBER_REAL: return "número real";
        case TOKEN_EOF: return "EOF";
        default: return "token desconhecido";
    }
}
