#ifndef PARSER_H
#define PARSER_H

#include "../lexer/lexer.h"
#include <vector>
#include <string>

using namespace std;

struct ASTNode {
    TokenType type;
    string value;
    ASTNode* left;
    ASTNode* right;
    ASTNode* condition;
    vector<ASTNode*> body;
    vector<ASTNode*> elifBlocks;
    ASTNode* elseBlock;

    ASTNode(TokenType t, string v) : type(t), value(v), left(nullptr), right(nullptr) {}
};

ASTNode* createNode(TokenType type, const string& value);

vector<ASTNode*> parse(const vector<Token>& tokens);

ASTNode* parseExpression(const vector<Token>& tokens, size_t& idx, size_t& lineNumber);

ASTNode* parseStatements(const vector<Token>& tokens, size_t& idx, size_t& lineNumber);

ASTNode* parseLog(const vector<Token>& tokens, size_t& idx, size_t& lineNumber);

ASTNode* parseAssignment(const vector<Token>& tokens, size_t& idx, size_t& lineNumber);

ASTNode* parseCondition(const vector<Token>& tokens, size_t& idx, size_t& lineNumber);

void expect(const vector<Token>& tokens, size_t& idx, TokenType expectedType, string TypeInString, size_t& lineNumber);

#endif