#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

#include <vector>

#include "symtable.h"

using namespace std;




class Parser
{
private:


    vector<Token> tokens;


    int posicao;

    SymTable tabela;
  
    bool consumir(TipoToken esperado);
    bool declaracao();
    bool atribuicao();




    bool comando();

    bool direcao();


public:

  
    Parser(vector<Token> listaTokens);
    bool programa();
    void mostrarTabela();


};


#endif
