// parser.h
#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>  // Inclua stdlib.h para a função exit
#include "tokens.h"

// Declaração das funções do parser
void parseProgram(FILE *source);
void parseStatement(FILE *source);
void parseExpression(FILE *source);
void parseTerm(FILE *source);
void parseFactor(FILE *source);

// Variável global para armazenar o token atual
Token currentToken;

// Função auxiliar para pegar o próximo token
void nextTokenHelper(FILE *source); // Mantenha a declaração
void match(TokenType expected, FILE *source); // Mantenha a declaração

#endif
