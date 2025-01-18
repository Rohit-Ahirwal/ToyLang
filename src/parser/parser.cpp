#include "parser.h"
#include <cctype>
#include <stdexcept>
#include <iostream>

ASTNode* createNode(TokenType type, const string& value) {
    return new ASTNode(type, value);
}

vector<ASTNode*> parse(const vector<Token>& tokens) {
    if (tokens.empty()) throw runtime_error("Empty input");

    size_t idx = 0;
    vector<ASTNode*> astNodes;

    while (idx < tokens.size()) {
        switch (tokens[idx].type) {
            case TokenType::LOG:
                astNodes.push_back(parseLog(tokens, idx));
                break;
            case TokenType::IDENTIFIER:
                astNodes.push_back(parseAssignment(tokens, idx));
                break;
            case TokenType::NUMBER:
                astNodes.push_back(parseExpression(tokens, idx));
                break;
            case TokenType::FLOAT:
                astNodes.push_back(parseExpression(tokens, idx));
                break;
            case TokenType::STRING:
                astNodes.push_back(parseExpression(tokens, idx));
                break;
            case TokenType::BOOL:
                astNodes.push_back(parseExpression(tokens, idx));
                break;
            case TokenType::WHILE:
                astNodes.push_back(parseWhileLoop(tokens, idx));
                break;
            case TokenType::FOR:
                astNodes.push_back(parseForLoop(tokens, idx));
                break;
            case TokenType::IF:
                astNodes.push_back(parseCondition(tokens, idx));
                break;
            default:
                throw runtime_error("Invalid syntax: '" + tokens[idx].value + "'");
                break;
        }
    }

    return astNodes;
}

ASTNode* parseExpression(const vector<Token>& tokens, size_t& idx) {
    if (tokens[idx].type == TokenType::NUMBER || tokens[idx].type == TokenType::FLOAT || tokens[idx].type == TokenType::IDENTIFIER || tokens[idx].type == TokenType::STRING || tokens[idx].type == TokenType::BOOL) {
        size_t tempIdx = idx;
        ASTNode* node = nullptr;

        if (tokens[idx+1].type == TokenType::ADD || tokens[idx+1].type == TokenType::MINUS || tokens[idx+1].type == TokenType::STAR || tokens[idx+1].type == TokenType::SLASH) { // Arithmetc operation check
            idx++;
            node = createNode(tokens[idx].type, tokens[idx].value);
            node->left = createNode(tokens[tempIdx].type, tokens[tempIdx].value);
            idx++;
            node->right = parseExpression(tokens, idx);
        } else if (tokens[idx+1].type == TokenType::GTHAN || tokens[idx+1].type == TokenType::LTHAN || tokens[idx+1].type == TokenType::EQUAL || tokens[idx+1].type == TokenType::LTHAN_EQUAL || tokens[idx+1].type == TokenType::GTHAN_EQUAL) {
            idx++;
            node = createNode(tokens[idx].type, tokens[idx].value);
            node->left = createNode(tokens[tempIdx].type, tokens[tempIdx].value);
            idx++;
            node->right = parseExpression(tokens, idx);
        } else if (tokens[idx+1].type == TokenType::INCREMENT || tokens[idx+1].type == TokenType::DECREMENT) {
            idx++;
            node = createNode(tokens[idx].type, tokens[idx].value);
            node->left = createNode(tokens[tempIdx].type, tokens[tempIdx].value);
        } else {
            node = createNode(tokens[idx].type, tokens[idx].value);
        }
        return node;

    } else {
        throw runtime_error("Syntax Error: Unexpected token in expression. found '" + tokens[idx].value + "'");
    }
}

ASTNode* parseStatements(const vector<Token>& tokens, size_t& idx) {
    ASTNode* statementNode = nullptr;

    switch (tokens[idx].type) {
        case TokenType::LOG:
            statementNode = parseLog(tokens, idx);
            break;
        case TokenType::IDENTIFIER:
            statementNode = parseAssignment(tokens, idx);
            break;
        case TokenType::NUMBER:
            statementNode = parseExpression(tokens, idx);
            break;
        case TokenType::FLOAT:
            statementNode = parseExpression(tokens, idx);
            break;
        case TokenType::STRING:
            statementNode = parseExpression(tokens, idx);
            break;
        case TokenType::BOOL:
            statementNode = parseExpression(tokens, idx);
            break;
        case TokenType::WHILE:
            statementNode = parseWhileLoop(tokens, idx);
            break;
        case TokenType::FOR:
            statementNode = parseForLoop(tokens, idx);
            break;
        case TokenType::IF:
            statementNode = parseCondition(tokens, idx);
            break;
        default:
            throw runtime_error("Invalid syntax: '" + tokens[idx].value + "'");
            break;
    }

    return statementNode;
}

ASTNode* parseLog(const vector<Token>& tokens, size_t& idx) {
    idx++; // Skip log keyword
    expect(tokens, idx, TokenType::LPARAN, "(");

    ASTNode* logNode = new ASTNode(TokenType::LOG, "");
    logNode->right = parseExpression(tokens, idx);
    idx++;

    expect(tokens, idx, TokenType::RPARAN, ")");

    expect(tokens, idx, TokenType::NEWLINE, "Semicolon");
    

    return logNode;
}

ASTNode* parseAssignment(const vector<Token>& tokens, size_t& idx) {
    if (tokens[idx+1].type == TokenType::ASSIGNMENT) {
        ASTNode* varNode = createNode(tokens[idx].type, tokens[idx].value);
        idx++;

        ASTNode* assignNode = createNode(tokens[idx].type, tokens[idx].value);
        idx++;
        assignNode->left = varNode;
        assignNode->right = parseExpression(tokens, idx);
        idx++;

        expect(tokens, idx, TokenType::NEWLINE, "Semicolon");
        

        return assignNode;
    } else {
        ASTNode* varNode = createNode(tokens[idx].type, tokens[idx].value);
        idx++;

        expect(tokens, idx, TokenType::NEWLINE, "Semicolon");
        

        return varNode;
    }
    return nullptr; 
}

ASTNode* parseCondition(const vector<Token>& tokens, size_t& idx) {
    // Create Node of If block
    ASTNode* conditionNode = createNode(tokens[idx].type, tokens[idx].value);
    idx++;

    expect(tokens, idx, TokenType::LPARAN, "(");
    conditionNode->condition = parseExpression(tokens, idx); // Parse condition of block
    idx++;

    expect(tokens, idx, TokenType::RPARAN, ")");
    expect(tokens, idx, TokenType::LBRACE, "{");

    // Parse body of the block
    while (idx < tokens.size() && tokens[idx].type != TokenType::RBRACE) {
        conditionNode->body.push_back(parseStatements(tokens, idx));
    }

    expect(tokens, idx, TokenType::RBRACE, "}");

    while (idx < tokens.size() && tokens[idx].type == TokenType::ELIF) {
        // Create Node of Elif block
        ASTNode* elifNode = createNode(tokens[idx].type, tokens[idx].value);
        idx++;

        expect(tokens, idx, TokenType::LPARAN, "(");
        elifNode->condition = parseExpression(tokens, idx); // Parse condition of block
        idx++;

        expect(tokens, idx, TokenType::RPARAN, ")");
        expect(tokens, idx, TokenType::LBRACE, "{");

        // Parse body of the block
        while (idx < tokens.size() && tokens[idx].type != TokenType::RBRACE) {
            elifNode->body.push_back(parseStatements(tokens, idx));
        }

        expect(tokens, idx, TokenType::RBRACE, "}");

        conditionNode->elifBlocks.push_back(elifNode);
    }

    if (tokens[idx].type == TokenType::ELSE) {
        // Create Node of Elif block
        ASTNode* elseBlock = createNode(tokens[idx].type, tokens[idx].value);
        idx++;

        expect(tokens, idx, TokenType::LBRACE, "{");

        // Parse body of the block
        while (idx < tokens.size() && tokens[idx].type != TokenType::RBRACE) {
            elseBlock->body.push_back(parseStatements(tokens, idx));
        }

        expect(tokens, idx, TokenType::RBRACE, "}");
        conditionNode->elseBlock = elseBlock;
    } else {
        conditionNode->elseBlock = nullptr;
    }

    return conditionNode;
}

ASTNode* parseWhileLoop(const vector<Token>& tokens, size_t& idx) {
    // Create Node of While block
    ASTNode* loopNode = createNode(tokens[idx].type, tokens[idx].value);
    idx++;

    expect(tokens, idx, TokenType::LPARAN, "(");
    loopNode->condition = parseExpression(tokens, idx);
    idx++;

    expect(tokens, idx, TokenType::RPARAN, ")");
    expect(tokens, idx, TokenType::LBRACE, "{");

    // Parse body of the block
    while (idx < tokens.size() && tokens[idx].type != TokenType::RBRACE) {
        loopNode->body.push_back(parseStatements(tokens, idx));
    }

    expect(tokens, idx, TokenType::RBRACE, "}");

    return loopNode;
}

ASTNode* parseForLoop(const vector<Token>& tokens, size_t& idx) {
    // Create Node of For block
    ASTNode* loopNode = createNode(tokens[idx].type, tokens[idx].value);
    idx++;
    
    expect(tokens, idx, TokenType::LPARAN, "(");
    loopNode->left = parseAssignment(tokens, idx);
    loopNode->condition = parseExpression(tokens, idx);
    idx++;
    expect(tokens, idx, TokenType::NEWLINE, ";");

    loopNode->right = parseExpression(tokens, idx);
    idx++;
    
    expect(tokens, idx, TokenType::RPARAN, ")");
    expect(tokens, idx, TokenType::LBRACE, "{");

    while (idx < tokens.size() && tokens[idx].type != TokenType::RBRACE) {
        loopNode->body.push_back(parseStatements(tokens, idx));
    }

    expect(tokens, idx, TokenType::RBRACE, "}");

    return loopNode;
}

void expect(const vector<Token>& tokens, size_t& idx, TokenType expectedType, string TypeInString) {
    if (tokens[idx].type == expectedType) {
        idx++;
    } else {
        throw runtime_error("Syntax error: Expected token of type '" + TypeInString + "', but got '" + tokens[idx].value + "'.");
    }
}