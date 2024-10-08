#include <stdio.h>
#include <locale.h>  // Inclua para setlocale
#include "tokens.h"
#include "parser.h"  // Inclua o parser

// Função para escanear o arquivo e imprimir os tokens em um arquivo
void scanFile(FILE *source, FILE *output) {
    Token token;
    do {
        token = nextToken(source);
        // Imprime no arquivo em vez de imprimir no console
        fprintf(output, "Token: %d, Lexema: %s, Descrição: %s\n",
               token.type, token.lexeme, tokenTypeToString(token.type));
    } while (token.type != TOKEN_EOF);
}

int main() {
    // Configura a localização para português
    setlocale(LC_ALL, "pt_BR.UTF-8");

    // Abre o arquivo de entrada
    FILE *source = fopen("input.p-", "r");
    if (source == NULL) {
        printf("Erro ao abrir o arquivo de origem.\n");
        return 1; // Retorna 1 para indicar erro
    }

    // Abre o arquivo de saída para gravar os tokens (opcional)
    FILE *output = fopen("output.txt", "w");
    if (output == NULL) {
        printf("Erro ao abrir o arquivo de saída.\n");
        fclose(source); // Fecha o arquivo de entrada antes de sair
        return 1; // Retorna 1 para indicar erro
    }

    // Chama a função para escanear e imprimir os tokens no arquivo de saída (opcional)
    scanFile(source, output);

    // Chama o parser para realizar a análise sintática
    rewind(source); // Volta o ponteiro do arquivo para o início
    parseProgram(source);  // Função que inicia a análise sintática

    // Fecha os arquivos após a leitura
    fclose(source);
    fclose(output);

    return 0; // Retorna 0 para indicar sucesso
}
