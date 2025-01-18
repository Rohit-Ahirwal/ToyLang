#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <string>

using namespace std;

enum class TokenType {
    NUMBER,
    FLOAT,
    BOOL,
    STRING,
    LPARAN,
    RPARAN,
    LBRACE,
    RBRACE,
    ADD,
    MINUS,
    STAR,
    SLASH,
    EQUAL,
    GTHAN,
    LTHAN,
    GTHAN_EQUAL,
    LTHAN_EQUAL,
    INCREMENT,
    DECREMENT,
    LOG,
    IDENTIFIER,
    ASSIGNMENT,
    NEWLINE,
    IF,
    ELSE,
    ELIF,
    WHILE,
    FOR
};

struct Token {
    TokenType type;
    string value;
};

vector<Token> tokenize(const string& text);

#endif