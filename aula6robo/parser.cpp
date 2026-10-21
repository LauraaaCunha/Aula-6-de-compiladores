#include "parser.h"
#include <iostream>
using namespace std;


Parser::Parser(vector<Token> listaTokens)
{
    tokens = listaTokens;

    posicao = 0;
}

bool Parser::consumir(TipoToken esperado)
{
    if (posicao < tokens.size())
    {
        if (tokens[posicao].tipo == esperado)
        {
            posicao++;

            return true;
        }


        cout << endl;

        cout << "ERRO SINTATICO!" << endl;

        cout << "Esperado: "
             << nomeToken(esperado)
             << endl;

        cout << "Encontrado: "
             << tokens[posicao].valor
             << endl;

        return false;
    }


    cout << endl;

    cout << "ERRO SINTATICO!" << endl;

    cout << "Esperado: "
         << nomeToken(esperado)
         << endl;

    cout << "Encontrado: FIM DA ENTRADA"
         << endl;


    return false;
}

bool Parser::direcao()
{
    if (posicao >= tokens.size())
    {
        cout << "ERRO SINTATICO!" << endl;

        cout << "Esperado: DIREITA ou ESQUERDA"
             << endl;

        return false;
    }


    if (tokens[posicao].tipo == DIREITA)
    {
        posicao++;

        return true;
    }


    if (tokens[posicao].tipo == ESQUERDA)
    {
        posicao++;

        return true;
    }


    cout << endl;

    cout << "ERRO SINTATICO!" << endl;

    cout << "Esperado: DIREITA ou ESQUERDA"
         << endl;

    cout << "Encontrado: "
         << tokens[posicao].valor
         << endl;


    return false;
}
      
bool Parser::declaracao()
{
    string tipo;



    if (tokens[posicao].tipo == TIPO_NUMERO)
    {
        tipo = "numero";

        consumir(TIPO_NUMERO);
    }

    else if (tokens[posicao].tipo == TIPO_DIRECAO)
    {
        tipo = "direcao";

        consumir(TIPO_DIRECAO);
    }

    else
    {
        return false;
    }


    if (posicao >= tokens.size() || tokens[posicao].tipo != IDENTIFICADOR)
    {
        cout << endl;

        cout << "ERRO SINTATICO!" << endl;

        cout << "Esperado: IDENTIFICADOR"
             << endl;

        return false;
    }

    string nome = tokens[posicao].valor;


    consumir(IDENTIFICADOR);


    Symbol simbolo;

    simbolo.nome = nome;

    simbolo.tipo = tipo;

    simbolo.valor = "-";


    if (!tabela.Insert(nome, simbolo))
    {
        cout << endl;

        cout << "ERRO SEMANTICO!" << endl;

        cout << "Identificador '"
             << nome
             << "' ja declarado."
             << endl;

        return false;
    }


    if (!consumir(PONTO_VIRGULA))
        return false;


    return true;
}


bool Parser::atribuicao()
{
    string nome = tokens[posicao].valor;


    Symbol* simbolo =
        tabela.Find(nome);


    if (simbolo == nullptr)
    {
        cout << endl;

        cout << "ERRO SEMANTICO!" << endl;

        cout << "Identificador '"
             << nome
             << "' nao declarado."
             << endl;

        return false;
    }


    consumir(IDENTIFICADOR);


    if (!consumir(IGUAL))
        return false;

    if (simbolo->tipo == "numero")
    {

        if (posicao >= tokens.size() ||
            tokens[posicao].tipo != NUMERO)
        {
            cout << endl;

            cout << "ERRO SEMANTICO!" << endl;

            cout << "A variavel '"
                 << nome
                 << "' espera um valor numerico."
                 << endl;

            return false;
        }

        simbolo->valor =
            tokens[posicao].valor;


        consumir(NUMERO);
    }


    else if (simbolo->tipo == "direcao")
    {

        if (posicao >= tokens.size() ||
           (tokens[posicao].tipo != DIREITA &&
            tokens[posicao].tipo != ESQUERDA))
        {
            cout << endl;

            cout << "ERRO SEMANTICO!" << endl;

            cout << "A variavel '"
                 << nome
                 << "' espera uma direcao."
                 << endl;

            return false;
        }

        simbolo->valor =
            tokens[posicao].valor;


        posicao++;
    }


    if (!consumir(PONTO_VIRGULA))
        return false;


    return true;
}


bool Parser::comando()
{
        if (posicao < tokens.size() &&
        tokens[posicao].tipo == IDENTIFICADOR)
    {
        return atribuicao();
    }


    if (posicao < tokens.size() &&
        (tokens[posicao].tipo == ANDAR ||
         tokens[posicao].tipo == ESPERAR ||
         tokens[posicao].tipo == DESVIAR))
    {
        string nomeComando = tokens[posicao].valor;

        posicao++;


        if (posicao < tokens.size() &&
            tokens[posicao].tipo == NUMERO)
        {
            consumir(NUMERO);
        }


        else if (posicao < tokens.size() &&
                 tokens[posicao].tipo ==
                 IDENTIFICADOR)
        {
            string nome =
                tokens[posicao].valor;

            Symbol* simbolo =
                tabela.Find(nome);


            if (simbolo == nullptr)
            {
                cout << endl;

                cout << "ERRO SEMANTICO!"
                     << endl;

                cout << "Identificador '"
                     << nome
                     << "' nao declarado."
                     << endl;

                return false;
            }


            if (simbolo->tipo != "numero")
            {
                cout << endl;

                cout << "ERRO SEMANTICO!"
                     << endl;

                cout << "'" << nomeComando << "' espera uma "
                     << "variavel do tipo numero."
                     << endl;

                return false;
            }


            consumir(IDENTIFICADOR);
        }


        else
        {
            cout << endl;

            cout << "ERRO SINTATICO!"
                 << endl;

            cout << "Esperado: NUMERO "
                 << "ou IDENTIFICADOR"
                 << endl;

            return false;
        }


        if (!consumir(PONTO_VIRGULA))
            return false;


        return true;
    }


    if (posicao < tokens.size() &&
        tokens[posicao].tipo == PARAR)
    {
        consumir(PARAR);

        if (!consumir(PONTO_VIRGULA))
            return false;

        return true;
    }


    if (posicao < tokens.size() &&
        tokens[posicao].tipo == VIRAR)
    {
        consumir(VIRAR);


        if (posicao < tokens.size() &&
           (tokens[posicao].tipo == DIREITA ||
            tokens[posicao].tipo == ESQUERDA))
        {
            posicao++;
        }


        else if (posicao < tokens.size() &&
                 tokens[posicao].tipo ==
                 IDENTIFICADOR)
        {
            string nome =
                tokens[posicao].valor;


            Symbol* simbolo =
                tabela.Find(nome);

            if (simbolo == nullptr)
            {
                cout << endl;

                cout << "ERRO SEMANTICO!"
                     << endl;

                cout << "Identificador '"
                     << nome
                     << "' nao declarado."
                     << endl;

                return false;
            }


            if (simbolo->tipo != "direcao")
            {
                cout << endl;

                cout << "ERRO SEMANTICO!"
                     << endl;

                cout << "'virar' espera uma "
                     << "variavel do tipo direcao."
                     << endl;

                return false;
            }


            consumir(IDENTIFICADOR);
        }


        else
        {
            cout << endl;

            cout << "ERRO SINTATICO!"
                 << endl;

            cout << "Esperado: DIREITA, "
                 << "ESQUERDA ou IDENTIFICADOR"
                 << endl;

            return false;
        }


        if (!consumir(PONTO_VIRGULA))
            return false;


        return true;
    }


    return false;
}


bool Parser::programa()
{
    if (!consumir(INICIO))
        return false;


    while (posicao < tokens.size() &&
          (tokens[posicao].tipo == TIPO_NUMERO ||
           tokens[posicao].tipo == TIPO_DIRECAO))
    {
        if (!declaracao())
            return false;
    }


    while (posicao < tokens.size() &&
          (tokens[posicao].tipo == ANDAR ||
           tokens[posicao].tipo == VIRAR ||
           tokens[posicao].tipo == ESPERAR ||
           tokens[posicao].tipo == PARAR ||
           tokens[posicao].tipo == DESVIAR ||
           tokens[posicao].tipo == IDENTIFICADOR))
    {
        if (!comando())
            return false;
    }


    if (!consumir(FIM))
        return false;


    if (posicao != tokens.size())
    {
        cout << endl;

        cout << "ERRO SINTATICO!" << endl;

        cout << "Existem tokens depois de 'fim'."
             << endl;

        return false;
    }


    return true;
}


void Parser::mostrarTabela()
{
    tabela.Show();
}