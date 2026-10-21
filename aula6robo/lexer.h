#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

using namespace std;



enum TipoToken
{
    INICIO,
    FIM,
    ANDAR,
    VIRAR,
    DIREITA,
    ESQUERDA,
    NUMERO,
    TIPO_NUMERO,
    TIPO_DIRECAO,
    IDENTIFICADOR,
    IGUAL,
    PONTO_VIRGULA,
    ESPERAR,
    PARAR,
    DESVIAR,
    INVALIDO
};


struct Token
{
    TipoToken tipo;
    string valor;
};



vector<Token> analisarLexico(string codigo);



string nomeToken(TipoToken tipo);


#endif
