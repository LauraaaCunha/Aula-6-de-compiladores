#ifndef SYMTABLE_H
#define SYMTABLE_H

#include <string>
#include <unordered_map>

using namespace std;

struct Symbol {
    string nome;
    string tipo;
    string valor;

};

class SymTable {
    private:
        unordered_map<string, Symbol> tabela;


    public:
        bool Insert(string nome, Symbol simbolo);
        Symbol* Find(string nome);

    
    void Show();

};
#endif