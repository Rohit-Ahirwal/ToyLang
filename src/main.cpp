#include <iostream>
#include <fstream>
#include <sstream>
#include "parser/parser.h"
#include "lexer/lexer.h"
#include "evaluator/evaluator.h"

using namespace std;

// Helper function to convert TokenType to a string (for printing)
string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::ADD: return "ADD";
        case TokenType::NUMBER: return "NUMBER";
        case TokenType::MINUS: return "MINUS";
        case TokenType::STAR: return "STAR";
        case TokenType::LOG: return "STAR";
        // Add other token types as needed
        default: return "UNKNOWN";
    }
}

void printAST(const ASTNode* node, int level = 0) {
    if (!node) return;  // Base case: null node

    // Indentation for better readability
    string indent(level * 4, ' ');

    // Print the current node's value and type
    cout << indent << "Node (" << tokenTypeToString(node->type) << "): " << node->value << endl;

    // Recursively print left and right children (if they exist)
    if (node->left) {
        cout << indent << "Left child: " << endl;
        printAST(node->left, level + 1);  // Increase indentation for child
    }
    if (node->right) {
        cout << indent << "Right child: " << endl;
        printAST(node->right, level + 1);  // Increase indentation for child
    }
}

void executeFile(const string& filename) {
    if (filename.substr(filename.find_last_of(".") + 1) != "toy") {
        throw runtime_error("Not a valid toy file " + filename);
    }

    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open the file " + filename);
        return;
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string text = buffer.str();

    try {
        vector<Token> tokens = tokenize(text);
        vector<ASTNode*> ast = parse(tokens);
        // for (auto node: ast) {
        //     printAST(node);
        // }
        evaluate(ast);

    } catch(const exception& e) {
        cerr << e.what() << '\n';
    }
    
    file.close();
}

int main(int argc, char* argv[]) {
    if (argc == 2) {
        string filename = argv[1];
        executeFile(filename);
    } else {
        cerr << "No toy file found" << endl;
    }

    return 0;
}