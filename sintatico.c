// #include <stdio.h>
// #include <string.h>
// #include "lexico.c"
// #include "sintatico.h"
#include <stdio.h>
#include "lexico.h"
#include "sintatico.h"

extern Token tokens[100]; // Utilizamos o array de tokens gerado pelo analisador léxico
extern int tokenCount;
int currentIndex = 0;

Token proximoToken() {
    if (currentIndex < tokenCount) {
        return tokens[currentIndex++];
    }
    return (Token){FIM, ""}; // Retorna um token de fim se não houver mais
}

void parse(char *code) {
    Token token = proximoToken(code); // Correto, passa o 'code' como argumento
    while (token.tipo != FIM) {
        // Imprimir cada token para verificar a análise léxica
        printf("Token: Tipo=%d, Valor=%s\n", token.tipo, token.valor);
        token = proximoToken(code); // Continuar analisando o código
    }

    printf("Análise sintática concluída!\n");
}


// // Prototipos de funções
// void analisarDeclaracaoVariaveis();
// void analisarComandos();
// void analisarCondicional();
// void analisarMostrar();
// void analisarLer();
// void analisarEnquanto();
// void analisarRepitaAte();

// void parse(char *code) {
//     // Inicializar o índice para garantir que a análise começará do início
//     currentIndex = 0;

//     // Chamar a função para iniciar a análise sintática
//     analisarCodigo(code);
// }

// void analisarCodigo(char *code) {
//     printf("Iniciando análise sintática do código:\n");

//     // Primeiro analisamos as declarações de variáveis
//     analisarDeclaracaoVariaveis(code);

//     // Depois o corpo do programa (comandos)
//     analisarComandos(code);
// }

// void analisarComandos(char *code) {
//     Token token = proximoToken(code);

//     while (token.tipo != FIM) {
//         if (token.tipo == SE) {
//             analisarCondicional(code);
//         } else if (token.tipo == MOSTRAR) {
//             analisarMostrar(code);
//         } else if (token.tipo == LER) {
//             analisarLer(code);
//         } else if (token.tipo == ENQUANTO) {
//             analisarEnquanto(code);
//         } else if (token.tipo == REPITA) {
//             analisarRepitaAte(code);
//         } else {
//             // Token inesperado, pode ser um erro de sintaxe
//             printf("Erro: Comando desconhecido ou malformado: %s\n", token.valor);
//         }
//         token = proximoToken(code);
//     }
// }

// // Função para analisar o comando de mostrar
// void analisarMostrar(char *code) {
//     Token token = proximoToken(code);
//     printf("- Comando de saída correto: mostrar ");

//     // Verifica se é seguido por '('
//     if (token.tipo == DELIMITADOR && strcmp(token.valor, "(") == 0) {
//         printf("(");
//         token = proximoToken(code);

//         // Deve ser um identificador ou número
//         if (token.tipo == IDENTIFICADOR || token.tipo == NUMERO_INTEIRO || token.tipo == NUMERO_REAL) {
//             printf("%s", token.valor);
//             token = proximoToken(code);

//             // Verifica se fecha com ')'
//             if (token.tipo == DELIMITADOR && strcmp(token.valor, ")") == 0) {
//                 printf(")\n");

//                 // Verifica se finaliza com ';'
//                 token = proximoToken(code);
//                 if (token.tipo == DELIMITADOR && strcmp(token.valor, ";") == 0) {
//                     printf(";\n");
//                 } else {
//                     printf("Erro: Esperado ';' após mostrar.\n");
//                 }
//             } else {
//                 printf("Erro: Esperado ')' após o identificador.\n");
//             }
//         } else {
//             printf("Erro: Esperado identificador ou número dentro de 'mostrar'.\n");
//         }
//     } else {
//         printf("Erro: Esperado '(' após 'mostrar'.\n");
//     }
// }

// // Função para analisar o comando de ler
// void analisarLer(char *code) {
//     Token token = proximoToken(code);
//     printf("- Comando de entrada correto: ler ");

//     // Verifica se é seguido por '('
//     if (token.tipo == DELIMITADOR && strcmp(token.valor, "(") == 0) {
//         printf("(");
//         token = proximoToken(code);

//         // Deve ser um ou mais identificadores, separados por vírgula
//         while (token.tipo == IDENTIFICADOR) {
//             printf("%s", token.valor);
//             token = proximoToken(code);

//             if (token.tipo == DELIMITADOR && strcmp(token.valor, ",") == 0) {
//                 printf(", ");
//                 token = proximoToken(code);
//             } else {
//                 break;
//             }
//         }

//         // Verifica se fecha com ')'
//         if (token.tipo == DELIMITADOR && strcmp(token.valor, ")") == 0) {
//             printf(")\n");

//             // Verifica se finaliza com ';'
//             token = proximoToken(code);
//             if (token.tipo == DELIMITADOR && strcmp(token.valor, ";") == 0) {
//                 printf(";\n");
//             } else {
//                 printf("Erro: Esperado ';' após 'ler'.\n");
//             }
//         } else {
//             printf("Erro: Esperado ')' após o(s) identificador(es).\n");
//         }
//     } else {
//         printf("Erro: Esperado '(' após 'ler'.\n");
//     }
// }

// // Função para analisar o comando de repetição 'enquanto'
// void analisarEnquanto(char *code) {
//     Token token = proximoToken(code);
//     printf("- Estrutura de repetição 'enquanto' correta: enquanto ");

//     // Verifica se é seguido por '('
//     if (token.tipo == DELIMITADOR && strcmp(token.valor, "(") == 0) {
//         printf("(");
//         token = proximoToken(code);

//         // Verifica a condição (espera-se um identificador ou número)
//         if (token.tipo == IDENTIFICADOR || token.tipo == NUMERO_INTEIRO || token.tipo == NUMERO_REAL) {
//             printf("%s", token.valor);
//             token = proximoToken(code);

//             // Verifica se há um operador
//             if (token.tipo == OPERADOR) {
//                 printf(" %s ", token.valor);
//                 token = proximoToken(code);

//                 // Verifica o segundo operando (identificador ou número)
//                 if (token.tipo == IDENTIFICADOR || token.tipo == NUMERO_INTEIRO || token.tipo == NUMERO_REAL) {
//                     printf("%s", token.valor);
//                     token = proximoToken(code);

//                     // Fecha parênteses
//                     if (token.tipo == DELIMITADOR && strcmp(token.valor, ")") == 0) {
//                         printf(")\n");

//                         // Abre bloco '{'
//                         token = proximoToken(code);
//                         if (token.tipo == DELIMITADOR && strcmp(token.valor, "{") == 0) {
//                             printf("{\n");

//                             // Processa comandos dentro do bloco
//                             token = proximoToken(code);
//                             while (token.tipo != DELIMITADOR || strcmp(token.valor, "}") != 0) {
//                                 printf("Comando dentro do bloco: %s\n", token.valor);
//                                 token = proximoToken(code);
//                             }

//                             printf("}\n");
//                         } else {
//                             printf("Erro: Esperado '{' após a condição.\n");
//                         }
//                     } else {
//                         printf("Erro: Esperado ')' no final da condição.\n");
//                     }
//                 }
//             }
//         }
//     }
// }

// // Função para analisar o comando 'repita até'
// void analisarRepitaAte(char *code) {
//     Token token = proximoToken(code);
//     printf("- Estrutura de repetição 'repita-ate' correta: repita {\n");

//     // Espera-se uma sequência de comandos dentro do bloco
//     token = proximoToken(code);
//     while (token.tipo != ATE) {
//         printf("Comando dentro do bloco: %s\n", token.valor);
//         token = proximoToken(code);
//     }

//     // Verifica a condição após 'ate'
//     printf("} ate ");

//     token = proximoToken(code);
//     if (token.tipo == DELIMITADOR && strcmp(token.valor, "(") == 0) {
//         printf("(");
//         token = proximoToken(code);

//         // Verifica condição (identificador ou número)
//         if (token.tipo == IDENTIFICADOR || token.tipo == NUMERO_INTEIRO || token.tipo == NUMERO_REAL) {
//             printf("%s", token.valor);
//             token = proximoToken(code);

//             // Verifica operador
//             if (token.tipo == OPERADOR) {
//                 printf(" %s ", token.valor);
//                 token = proximoToken(code);

//                 // Verifica segundo operando
//                 if (token.tipo == IDENTIFICADOR || token.tipo == NUMERO_INTEIRO || token.tipo == NUMERO_REAL) {
//                     printf("%s", token.valor);
//                     token = proximoToken(code);

//                     // Fecha parênteses
//                     if (token.tipo == DELIMITADOR && strcmp(token.valor, ")") == 0) {
//                         printf(")\n");
//                     } else {
//                         printf("Erro: Esperado ')' no final da condição 'ate'.\n");
//                     }
//                 }
//             }
//         }
//     }
// }
