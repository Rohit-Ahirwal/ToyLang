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
    size_t lineNumber = 1;
    vector<ASTNode*> astNodes;

    while (idx < tokens.size()) {
        switch (tokens[idx].type) {
            case TokenType::LOG:
                astNodes.push_back(parseLog(tokens, idx, lineNumber));
                break;
            case TokenType::IDENTIFIER:
                astNodes.push_back(parseAssignment(tokens, idx, lineNumber));
                break;
            case TokenType::NUMBER:
                astNodes.push_back(parseExpression(tokens, idx, lineNumber));
                break;
            case TokenType::FLOAT:
                astNodes.push_back(parseExpression(tokens, idx, lineNumber));
                break;
            case TokenType::STRING:
                astNodes.push_back(parseExpression(tokens, idx, lineNumber));
                break;
            case TokenType::BOOL:
                astNodes.push_back(parseExpression(tokens, idx, lineNumber));
                break;
            case TokenType::IF:
                astNodes.push_back(parseCondition(tokens, idx, lineNumber));
                break;
            default:
                throw runtime_error("Invalid syntax: '" + tokens[idx].value + "' at line " + to_string(lineNumber));
                break;
        }
    }

    return astNodes;
}

ASTNode* parseExpression(const vector<Token>& tokens, size_t& idx, size_t& lineNumber) {
    if (tokens[idx].type == TokenType::NUMBER || tokens[idx].type == TokenType::FLOAT || tokens[idx].type == TokenType::IDENTIFIER || tokens[idx].type == TokenType::STRING || tokens[idx].type == TokenType::BOOL) {
        size_t tempIdx = idx;
        ASTNode* node = nullptr;

        if (tokens[idx+1].type == TokenType::ADD || tokens[idx+1].type == TokenType::MINUS || tokens[idx+1].type == TokenType::STAR || tokens[idx+1].type == TokenType::SLASH) { // Arithmetc operation check
            idx++;
            node = createNode(tokens[idx].type, tokens[idx].value);
            node->left = createNode(tokens[tempIdx].type, tokens[tempIdx].value);
            idx++;
            node->right = parseExpression(tokens, idx, lineNumber);
        } else if (tokens[idx+1].type == TokenType::GTHAN || tokens[idx+1].type == TokenType::LTHAN || tokens[idx+1].type == TokenType::EQUAL || tokens[idx+1].type == TokenType::LTHAN_EQUAL || tokens[idx+1].type == TokenType::GTHAN_EQUAL) {
            idx++;
            node = createNode(tokens[idx].type, tokens[idx].value);
            node->left = createNode(tokens[tempIdx].type, tokens[tempIdx].value);
            idx++;
            node->right = parseExpression(tokens, idx, lineNumber);
        } else {
            node = createNode(tokens[idx].type, tokens[idx].value);
        }
        return node;

    } else {
        throw runtime_error("Syntax Error: Unexpected token in expression. found '" + tokens[idx].value + "' at line number " + to_string(lineNumber));
    }
}

ASTNode* parseStatements(const vector<Token>& tokens, size_t& idx, size_t& lineNumber) {
    ASTNode* statementNode = nullptr;

    switch (tokens[idx].type) {
        case TokenType::LOG:
            statementNode = parseLog(tokens, idx, lineNumber);
            break;
        case TokenType::IDENTIFIER:
            statementNode = parseAssignment(tokens, idx, lineNumber);
            break;
        case TokenType::NUMBER:
            statementNode = parseExpression(tokens, idx, lineNumber);
            break;
        case TokenType::FLOAT:
            statementNode = parseExpression(tokens, idx, lineNumber);
            break;
        case TokenType::IF:
            statementNode = parseCondition(tokens, idx, lineNumber);
            break;
        default:
            throw runtime_error("Invalid syntax: '" + tokens[idx].value + "' at line " + to_string(lineNumber));
            break;
    }
}

ASTNode* parseLog(const vector<Token>& tokens, size_t& idx, size_t& lineNumber) {
    idx++; // Skip log keyword
    expect(tokens, idx, TokenType::LPARAN, "(", lineNumber);

    ASTNode* logNode = new ASTNode(TokenType::LOG, "");
    logNode->right = parseExpression(tokens, idx, lineNumber);
    idx++;

    expect(tokens, idx, TokenType::RPARAN, ")", lineNumber);

    expect(tokens, idx, TokenType::NEWLINE, "Semicolon", lineNumber);
    lineNumber++;

    return logNode;
}

ASTNode* parseAssignment(const vector<Token>& tokens, size_t& idx, size_t& lineNumber) {
    if (tokens[idx+1].type == TokenType::ASSIGNMENT) {
        ASTNode* varNode = createNode(tokens[idx].type, tokens[idx].value);
        idx++;

        ASTNode* assignNode = createNode(tokens[idx].type, tokens[idx].value);
        idx++;
        assignNode->left = varNode;
        assignNode->right = parseExpression(tokens, idx, lineNumber);
        idx++;

        expect(tokens, idx, TokenType::NEWLINE, "Semicolon", lineNumber);
        lineNumber++;

        return assignNode;
    }    
}

ASTNode* parseCondition(const vector<Token>& tokens, size_t& idx, size_t& lineNumber) {
    // Create Node of If block
    ASTNode* conditionNode = createNode(tokens[idx].type, tokens[idx].value);
    idx++;

    expect(tokens, idx, TokenType::LPARAN, "(", lineNumber);
    conditionNode->condition = parseExpression(tokens, idx, lineNumber); // Parse condition of block
    idx++;

    expect(tokens, idx, TokenType::RPARAN, ")", lineNumber);
    expect(tokens, idx, TokenType::LBRACE, "{", lineNumber);

    // Parse body of the block
    while (idx < tokens.size() && tokens[idx].type != TokenType::RBRACE) {
        conditionNode->body.push_back(parseStatements(tokens, idx, lineNumber));
    }

    expect(tokens, idx, TokenType::RBRACE, "}", lineNumber);

    while (idx < tokens.size() && tokens[idx].type == TokenType::ELIF) {
        // Create Node of Elif block
        ASTNode* elifNode = createNode(tokens[idx].type, tokens[idx].value);
        idx++;

        expect(tokens, idx, TokenType::LPARAN, "(", lineNumber);
        elifNode->condition = parseExpression(tokens, idx, lineNumber); // Parse condition of block
        idx++;

        expect(tokens, idx, TokenType::RPARAN, ")", lineNumber);
        expect(tokens, idx, TokenType::LBRACE, "{", lineNumber);

        // Parse body of the block
        while (idx < tokens.size() && tokens[idx].type != TokenType::RBRACE) {
            elifNode->body.push_back(parseStatements(tokens, idx, lineNumber));
        }

        expect(tokens, idx, TokenType::RBRACE, "}", lineNumber);

        conditionNode->elifBlocks.push_back(elifNode);
    }

    if (tokens[idx].type == TokenType::ELSE) {
        // Create Node of Elif block
        ASTNode* elseBlock = createNode(tokens[idx].type, tokens[idx].value);
        idx++;

        expect(tokens, idx, TokenType::LBRACE, "{", lineNumber);

        // Parse body of the block
        while (idx < tokens.size() && tokens[idx].type != TokenType::RBRACE) {
            elseBlock->body.push_back(parseStatements(tokens, idx, lineNumber));
        }

        expect(tokens, idx, TokenType::RBRACE, "}", lineNumber);
        conditionNode->elseBlock = elseBlock;
    } else {
        conditionNode->elseBlock = nullptr;
    }

    return conditionNode;
}

void expect(const vector<Token>& tokens, size_t& idx, TokenType expectedType, string TypeInString, size_t& lineNumber) {
    if (tokens[idx].type == expectedType) {
        idx++;
    } else {
        throw runtime_error("Syntax error on line " + to_string(lineNumber) + ": Expected token of type '" + TypeInString + "', but got '" + tokens[idx].value + "'.");
    }
}