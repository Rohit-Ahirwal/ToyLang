#include "symbol.h"
#include <stdexcept>

void SymbolTable::enterScope() {
    scopes.push({});
}
void SymbolTable::exitScope() {
    if (scopes.empty()) {
        throw runtime_error("No scope to exit");
    }
    scopes.pop();
}

void SymbolTable::setVariable(const string& name, const Symbol& symbol) {
    if (scopes.empty()) {
        throw runtime_error("No active scope");
    }
    scopes.top()[name] = symbol;
}

Symbol SymbolTable::getVariable(const string& name) {
    stack<unordered_map<string, Symbol>> temp = scopes;

    while (!temp.empty()) {
        auto& currentScope = temp.top();
        if (currentScope.find(name) != currentScope.end()) {
            return currentScope[name];
        }
        temp.pop();
    }

    throw runtime_error("Variable is undefined: " + name);
}
