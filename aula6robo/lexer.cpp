#include "lexer.h"

#include <iostream>
#include <cctype>

using namespace std;


vector<Token> analisarLexico(string codigo)
{
    vector<Token> tokens;

    int i = 0;

    while (i < codigo.size())
    {
     
        if (isspace(codigo[i]))
        {
            i++;
            continue;
        }


 
        if (isalpha(codigo[i]))
        {
            string palavra = "";

            while (i < codigo.size() &&
                   isalpha(codigo[i]))
            {
                palavra += codigo[i];
                i++;
            }



            if (palavra == "inicio")
                tokens.push_back({INICIO, palavra});

            else if (palavra == "fim")
                tokens.push_back({FIM, palavra});

            else if (palavra == "andar")
                tokens.push_back({ANDAR, palavra});

            else if (palavra == "virar")
                tokens.push_back({VIRAR, palavra});

            else if (palavra == "direita")
                tokens.push_back({DIREITA, palavra});

            else if (palavra == "esquerda")
                tokens.push_back({ESQUERDA, palavra});

            else if (palavra == "esperar")
                tokens.push_back({ESPERAR, palavra});

            else if (palavra == "parar")
                tokens.push_back({PARAR, palavra});

            else if (palavra == "desviar")
                tokens.push_back({DESVIAR, palavra});

            else if(palavra == "numero")
                tokens.push_back({TIPO_NUMERO, palavra});

            else if(palavra == "direcao")
                tokens.push_back({TIPO_DIRECAO, palavra});


            else
            {
                tokens.push_back({IDENTIFICADOR, palavra});
            }
        }


        else if (isdigit(codigo[i]))
        {
            string numero = "";

            while (i < codigo.size() &&
                   isdigit(codigo[i]))
            {
                numero += codigo[i];
                i++;
            }

            tokens.push_back({NUMERO, numero});
        }

        else if (codigo[i] == '=')
        {
            tokens.push_back(
                {IGUAL, "="}
            );

            i++;
        }



        else if (codigo[i] == ';')
        {
            tokens.push_back(
                {PONTO_VIRGULA, ";"}
            );

            i++;
        }


        else
        {
            cout << "ERRO LEXICO!" << endl;

            cout << "Simbolo nao reconhecido: "
                 << codigo[i]
                 << endl;

            return {};
        }
    }


    return tokens;
}



string nomeToken(TipoToken tipo)
{
    switch (tipo)
    {
        case INICIO:
            return "INICIO";

        case FIM:
            return "FIM";

        case ANDAR:
            return "ANDAR";

        case VIRAR:
            return "VIRAR";

        case DIREITA:
            return "DIREITA";

        case ESQUERDA:
            return "ESQUERDA";

        case NUMERO:
            return "NUMERO";

        case PONTO_VIRGULA:
            return "PONTO_VIRGULA";
        
        case ESPERAR:
            return "ESPERAR";

        case PARAR:
            return "PARAR";

        case DESVIAR:
            return "DESVIAR";

        case TIPO_NUMERO:
            return "TIPO_NUMERO";

        case TIPO_DIRECAO:
            return "TIPO_DIRECAO";

        case IDENTIFICADOR:
            return "IDENTIFICADOR";

        case IGUAL:
            return "IGUAL";

        default:
            return "INVALIDO";
    }
}
