// // // lexico.c

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexico.h"

int currentIndex = 0; // Índice global para navegar pelo código

extern Token tokens[100];
extern int tokenCount;
extern int currentIndex;

// Função que verifica se um caractere é um delimitador
int isDelimiter(char ch) {
    char delimiters[] = "(),{};"; // Adicionamos a vírgula ',' como delimitador
    return strchr(delimiters, ch) != NULL;
}

// Função que verifica se uma string é um operador
int isOperator(char *str) {
    char *operators[] = {"+", "-", "*", "/", ">", "<", "==", "!=", ">=", "<="}; // Operadores
    for (int i = 0; i < 10; i++) {
        if (strcmp(str, operators[i]) == 0) return 1;
    }
    return 0;
}

// Função que verifica se uma string é um número
int isNumber(char *str) {
    int hasDecimal = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (isdigit(str[i])) continue;
        if (str[i] == '.' && !hasDecimal) {
            hasDecimal = 1;
        } else {
            return 0;
        }
    }
    return 1;
}

// Função para pular espaços em branco
void skipWhitespace(char *code, int *i) {
    while (isspace(code[*i])) (*i)++;
}

// Função para obter o próximo token do código
Token proximoToken(char *code) {
    Token token;
    token.valor[0] = '\0';
    skipWhitespace(code, &currentIndex);

    char currentChar = code[currentIndex];
    
    if (currentChar == '\0') {
        token.tipo = FIM;
        return token;
    }

    // Detectar delimitadores
    if (isDelimiter(currentChar)) {
        token.tipo = DELIMITADOR;
        token.valor[0] = currentChar;
        token.valor[1] = '\0';
        currentIndex++;
        return token;
    }

    // Detectar operadores
    char temp[3] = {code[currentIndex], code[currentIndex + 1], '\0'};
    if (isOperator(temp)) {
        token.tipo = OPERADOR;
        strcpy(token.valor, temp);
        currentIndex += 2;
        return token;
    } else if (isOperator(&code[currentIndex])) {
        token.tipo = OPERADOR;
        token.valor[0] = code[currentIndex];
        token.valor[1] = '\0';
        currentIndex++;
        return token;
    }

    // Detectar números
    int start = currentIndex;
    while (isdigit(code[currentIndex]) || code[currentIndex] == '.') {
        currentIndex++;
    }

    if (start != currentIndex) {
        strncpy(token.valor, code + start, currentIndex - start);
        token.valor[currentIndex - start] = '\0';
        token.tipo = strchr(token.valor, '.') ? NUMERO_REAL : NUMERO_INTEIRO;
        return token;
    }

    // Detectar identificadores e palavras-chave
    start = currentIndex;
    while (isalpha(code[currentIndex])) {
        currentIndex++;
    }
    
    if (start != currentIndex) {
        strncpy(token.valor, code + start, currentIndex - start);
        token.valor[currentIndex - start] = '\0';

        // Verificar se é palavra-chave
        if (isKeyword(token.valor)) {
            token.tipo = PALAVRA_CHAVE;
        } else {
            token.tipo = IDENTIFICADOR;
        }
        return token;
    }

    token.tipo = FIM;
    return token;
}

// Função para verificar se uma string é uma palavra-chave
int isKeyword(char *str) {
    char *keywords[] = {"inteiro", "real", "se", "enquanto", "repita", "ate", "mostrar", "ler"};
    for (int i = 0; i < 8; i++) {
        if (strcmp(str, keywords[i]) == 0) return 1;
    }
    return 0;
}


// #include "lexico.h"
// #include <stdio.h>
// #include <string.h>

// Token tokens[100]; // Array para armazenar os tokens
// int tokenCount = 0; // Contador de tokens

// // Simplesmente ignora espaços em branco
// void skipWhitespace(char *code, int *i) {
//     while (code[*i] == ' ' || code[*i] == '\n' || code[*i] == '\t') {
//         (*i)++;
//     }
// }

// // Função que realiza a tokenização do código
// void tokenize(char *code) {
//     int i = 0;
//     while (code[i] != '\0') {
//         skipWhitespace(code, &i);

//         // Exemplo de como identificar identificadores e palavras-chave
//         if (isalpha(code[i])) {
//             char buffer[100] = {0};
//             int j = 0;
//             while (isalpha(code[i])) {
//                 buffer[j++] = code[i++];
//             }

//             // Verifica se é palavra-chave
//             if (isKeyword(buffer)) {
//                 printf("Token: PALAVRA_CHAVE (%s)\n", buffer);
//                 tokens[tokenCount++] = (Token){PALAVRA_CHAVE, ""};
//                 strcpy(tokens[tokenCount - 1].valor, buffer);
//             } else {
//                 printf("Token: IDENTIFICADOR (%s)\n", buffer);
//                 tokens[tokenCount++] = (Token){IDENTIFICADOR, ""};
//                 strcpy(tokens[tokenCount - 1].valor, buffer);
//             }
//         }

//         // Outros tipos de tokens, como números, operadores, delimitadores, etc.
//         // Implementar detecção de números, operadores e delimitadores

//         i++;
//     }

//     tokens[tokenCount++] = (Token){FIM, ""}; // Token de fim de código
// }




// // #include <stdio.h>
// // #include <ctype.h>
// // #include <string.h>
// // #include "lexico.h"

// // #define MAX 100

// // int currentIndex = 0;

// // // Variável global para manter o índice do código
// // int currentIndex = 0;  // Indica a posição atual no código

// // Token proximoToken(char *code) {
// //     Token token;
// //     char buffer[MAX] = {0};
// //     int j = 0;

// //     if (code[currentIndex] == '\0') {
// //     token.tipo = FIM;
// //     strcpy(token.valor, "EOF");
// //     return token;
// // }

// //     // Ignorar espaços em branco
// //     skipWhitespace(code, &currentIndex);

// //     if (isalpha(code[currentIndex]) || code[currentIndex] == '_') {
// //         // Identificador ou palavra-chave
// //         while (isalnum(code[currentIndex]) || code[currentIndex] == '_') {
// //             buffer[j++] = code[currentIndex++];
// //         }
// //         buffer[j] = '\0';

// //         if (isKeyword(buffer)) {
// //             token.tipo = PALAVRA_CHAVE;
// //         } else {
// //             token.tipo = IDENTIFICADOR;
// //         }
// //         strcpy(token.valor, buffer);
// //     } else if (isdigit(code[currentIndex])) {
// //         // Número inteiro ou real
// //         while (isdigit(code[currentIndex])) {
// //             buffer[j++] = code[currentIndex++];
// //         }
// //         if (code[currentIndex] == '.') {
// //             buffer[j++] = code[currentIndex++];
// //             while (isdigit(code[currentIndex])) {
// //                 buffer[j++] = code[currentIndex++];
// //             }
// //             buffer[j] = '\0';
// //             token.tipo = NUMERO_REAL;
// //         } else {
// //             buffer[j] = '\0';
// //             token.tipo = NUMERO_INTEIRO;
// //         }
// //         strcpy(token.valor, buffer);
// //     } else if (isDelimiter(code[currentIndex])) {
// //         // Delimitador
// //         token.tipo = DELIMITADOR;
// //         token.valor[0] = code[currentIndex];
// //         token.valor[1] = '\0';
// //         currentIndex++;  // Avançar no código
// //     } else {
// //         // Operador ou desconhecido
// //         while (!isspace(code[currentIndex]) && !isalnum(code[currentIndex]) && !isDelimiter(code[currentIndex])) {
// //             buffer[j++] = code[currentIndex++];
// //         }
// //         buffer[j] = '\0';

// //         if (isOperator(buffer)) {
// //             token.tipo = OPERADOR;
// //         } else {
// //             token.tipo = FIM;  // Ou algum tipo para token desconhecido
// //         }
// //         strcpy(token.valor, buffer);
// //     }

// //     return token;
// // }

// // // typedef struct {
// // //     TipoToken tipo;
// // //     char valor[100];
// // // } Token;

// // // const char *keywords[] = {"inteiro", "real", "se", "entao", "senao", "enquanto", "repita", "ate", "ler", "mostrar"};
// // // const char *operators[] = {"+", "-", "*", "/", "=", "==", ">", "<", ">=", "<=", "&&", "||", "!="};
// // // const char delimiters[] = {';', ',', '(', ')', '{', '}'};

// // // // Função para verificar se uma string é uma palavra-chave
// // // int isKeyword(char *str) {
// // //     for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
// // //         if (strcmp(str, keywords[i]) == 0)
// // //             return 1;
// // //     }
// // //     return 0;
// // // }

// // // // Função para verificar se uma string é um operador
// // // int isOperator(char *str) {
// // //     for (int i = 0; i < sizeof(operators) / sizeof(operators[0]); i++) {
// // //         if (strcmp(str, operators[i]) == 0)
// // //             return 1;
// // //     }
// // //     return 0;
// // // }

// // // // Função para verificar se um caractere é um delimitador
// // // int isDelimiter(char ch) {
// // //     for (int i = 0; i < sizeof(delimiters); i++) {
// // //         if (ch == delimiters[i])
// // //             return 1;
// // //     }
// // //     return 0;
// // // }

// // // // Função para ignorar espaços em branco
// // // void skipWhitespace(char *code, int *i) {
// // //     while (isspace(code[*i])) {
// // //         (*i)++;
// // //     }
// // // }

// // // // Função para analisar e identificar os tokens
// // // void tokenize(char *code) {
// // //     int i = 0;
// // //     while (code[i] != '\0') {
// // //         skipWhitespace(code, &i);

// // //         char buffer[MAX] = {0};
// // //         int j = 0;

// // //         if (isalpha(code[i]) || code[i] == '_') {
// // //             while (isalnum(code[i]) || code[i] == '_') {
// // //                 buffer[j++] = code[i++];
// // //             }
// // //             buffer[j] = '\0';

// // //             if (isKeyword(buffer)) {
// // //                 printf("Token: PALAVRA-CHAVE, Valor: %s\n", buffer);
// // //             } else {
// // //                 printf("Token: IDENTIFICADOR, Valor: %s\n", buffer);
// // //             }
// // //         } else if (isdigit(code[i])) {
// // //             while (isdigit(code[i])) {
// // //                 buffer[j++] = code[i++];
// // //             }

// // //             if (code[i] == '.') {
// // //                 buffer[j++] = code[i++];
// // //                 while (isdigit(code[i])) {
// // //                     buffer[j++] = code[i++];
// // //                 }
// // //                 buffer[j] = '\0';
// // //                 printf("Token: NUMERO_REAL, Valor: %s\n", buffer);
// // //             } else {
// // //                 buffer[j] = '\0';
// // //                 printf("Token: NUMERO_INTEIRO, Valor: %s\n", buffer);
// // //             }
// // //         } else if (isDelimiter(code[i])) {
// // //             printf("Token: DELIMITADOR, Valor: %c\n", code[i]);
// // //             i++;
// // //         } else {
// // //             while (!isspace(code[i]) && !isalnum(code[i]) && !isDelimiter(code[i])) {
// // //                 buffer[j++] = code[i++];
// // //             }
// // //             buffer[j] = '\0';

// // //             if (isOperator(buffer)) {
// // //                 printf("Token: OPERADOR, Valor: %s\n", buffer);
// // //             } else {
// // //                 printf("Token: DESCONHECIDO, Valor: %s\n", buffer);
// // //             }
// // //         }
// // //     }
// // // }
