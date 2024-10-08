#include <stdio.h>
#include "lexico.h"
#include "sintatico.h"

int main() {
    char code[] = "mostrar(5 + 3); ler(a, b); enquanto(a < 10) { a = a + 1; }";
    
    printf("Iniciando Análise Léxica e Sintática:\n");
    parse(code);  // Corrigir a função chamada para 'parse'
    
    return 0;
}
