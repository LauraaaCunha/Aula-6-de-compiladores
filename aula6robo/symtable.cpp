#include "symtable.h"
#include <iostream>
#include <iomanip>

using namespace std;

bool SymTable::Insert(string nome, Symbol simbolo) {
    auto resultado = tabela.insert({nome, simbolo});
    return resultado.second; 

}

Symbol* SymTable::Find(string nome) {
    auto encontrado = tabela.find(nome);
    if (encontrado == tabela.end()) {
        return nullptr;
    }
    return &(encontrado->second);
}

void SymTable::Show() {
    cout << endl;
    cout << "Tabela de Simbolos" << endl;

    cout << left 
    << setw(15) << "Nome"
    << setw(15) << "Tipo"
    << setw(15) << "Valor" 
    << endl;

    for (auto item: tabela) {
        cout << left 
        << setw(15) << item.second.nome
        << setw(15) << item.second.tipo
        << setw(15) << item.second.valor 
        << endl;
    }
}