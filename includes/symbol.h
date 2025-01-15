#ifndef SYMBOL_H
#define SYMBOL_H

#include <unordered_map>
#include <variant>
#include <stack>
#include "../lexer/lexer.h"

using ValueType = variant<int, double, string, bool>;

struct Symbol {
    ValueType value;
    TokenType type;
};

class SymbolTable {
private:
    stack<unordered_map<string, Symbol>> scopes;

public:
    void enterScope();
    void exitScope();
    void setVariable(const string& name, const Symbol& symbol);
    Symbol getVariable(const string& name);
};

#endif // SYMBOL_H
