#include <iostream>
#include <string>
#include <vector>

#include "lexer.h"
#include "parser.h"

using namespace std;


int main()
{
    string codigo;


    cout << "==============================" << endl;
    cout << "      MINI COMPILADOR" << endl;
    cout << "==============================" << endl;

    cout << endl;

    cout << "Digite o programa:" << endl;

    cout << endl;


  
    getline(cin, codigo);




    vector<Token> tokens =
        analisarLexico(codigo);


  
    if (tokens.empty())
    {
        return 1;
    }


    cout << endl;

    cout << "ANALISE LEXICA: OK" << endl;



    cout << endl;

    cout << "TOKENS:" << endl;

    cout << "------------------------" << endl;


    for (Token token : tokens)
    {
        cout << nomeToken(token.tipo);

        cout << " -> ";

        cout << token.valor;

        cout << endl;
    }




    cout << endl;

    Parser parser(tokens);


    if (parser.programa())
    {
        cout << "ANALISE SINTATICA: OK"
             << endl;

        cout << "Analise Semantica: ok"
             << endl;

        parser.mostrarTabela();
        cout << endl;

        cout << "PROGRAMA ACEITO!"
             << endl;
    }


    return 0;
}
