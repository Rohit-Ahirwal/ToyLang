#include "lexer.h"
#include <cctype>
#include <stdexcept>
#include <iostream>

vector<Token> tokenize(const string& text) {
    vector<Token> tokens;
    size_t idx = 0;
    size_t lineNumber = 1;

    while (idx < text.length()) {
        char current_char = text[idx];

        if (isspace(current_char)) {
            idx++;
        } else if (isdigit(current_char)) {
            string num;
            bool hasDecimal = false;

            while (idx < text.length() && (isdigit(text[idx]) || (!hasDecimal && text[idx] == '.'))) {
                if (text[idx] == '.') {
                    if (hasDecimal) throw runtime_error("Invalid number format: Multiple decimal points detected.");
                    hasDecimal = true;
                }

                num += text[idx++];
            }
            if (hasDecimal) {
                tokens.push_back({TokenType::FLOAT, num});
            } else {
                tokens.push_back({TokenType::NUMBER, num});
            }
        } else if (isalpha(current_char)) {
            string current_word;
            while (idx < text.length() && (isalnum(text[idx]) || text[idx] == '_')) {
                current_word += text[idx++];
            }
            if (current_word == "log") {
                tokens.push_back({TokenType::LOG, current_word});
            } else if (current_word == "while") {
                tokens.push_back({TokenType::WHILE, current_word});
            } else if (current_word == "for") {
                tokens.push_back({TokenType::FOR, current_word});
            } else if (current_word == "if") {
                tokens.push_back({TokenType::IF, current_word});
            } else if (current_word == "else") {
                tokens.push_back({TokenType::ELSE, current_word});
            } else if (current_word == "elif") {
                tokens.push_back({TokenType::ELIF, current_word});
            } else if (current_word == "true") {
                tokens.push_back({TokenType::BOOL, current_word});
            } else if (current_word == "false") {
                tokens.push_back({TokenType::BOOL, current_word});
            } else {
                tokens.push_back({TokenType::IDENTIFIER, current_word});
            }
        } else if (current_char == '"') {
            string str;
            idx++;

            while (idx < text.length() && text[idx] != '"') {
                if (text[idx] == '\\') {
                    ++idx;
                    if (idx < text.length()) {
                        if (text[idx] == '\"' || text[idx] == '\\') {
                            str += text[idx];
                        } else {
                            throw runtime_error("Invalid escape sequence.");
                        }
                    }
                } else {
                    str += text[idx];
                }
                ++idx;
            }

            if (idx < text.length() && text[idx] == '"') {
                // Closing quote
                ++idx;
                tokens.push_back({TokenType::STRING, str});
            } else {
                throw runtime_error("Unterminated string literal at line " + to_string(lineNumber));
            }
        } else {
            switch (current_char) {
                case '+':
                    if (text[idx+1] == '+') {
                        tokens.push_back({TokenType::INCREMENT, "++"});
                        idx += 2;
                    } else {
                        tokens.push_back({TokenType::ADD, string(1, current_char)});
                        idx++;
                    }
                    break;
                case '-':
                    if (text[idx+1] == '-') {
                        tokens.push_back({TokenType::DECREMENT, "--"});
                        idx += 2;
                    } else {
                        tokens.push_back({TokenType::MINUS, string(1, current_char)});
                        idx++;
                    }
                    break;
                case '*':
                    tokens.push_back({TokenType::STAR, string(1, current_char)});
                    idx++;
                    break;
                case '/':
                    tokens.push_back({TokenType::SLASH, string(1, current_char)});
                    idx++;
                    break;
                case '(':
                    tokens.push_back({TokenType::LPARAN, string(1, current_char)});
                    idx++;
                    break;
                case ')':
                    tokens.push_back({TokenType::RPARAN, string(1, current_char)});
                    idx++;
                    break;
                case '{':
                    tokens.push_back({TokenType::LBRACE, string(1, current_char)});
                    idx++;
                    break;
                case '}':
                    tokens.push_back({TokenType::RBRACE, string(1, current_char)});
                    idx++;
                    break;
                case '=':
                    if (text[idx+1] == '=') {
                        tokens.push_back({TokenType::EQUAL, "=="});
                        idx += 2;
                    } else {
                        tokens.push_back({TokenType::ASSIGNMENT, string(1, current_char)});
                        idx++;
                    }
                    break;
                case '<':
                    if (text[idx+1] == '=') {
                        tokens.push_back({TokenType::LTHAN_EQUAL, "<="});
                        idx += 2;
                    } else {
                        tokens.push_back({TokenType::LTHAN, string(1, current_char)});
                        idx++;
                    }
                    break;
                case '>':
                    if (text[idx+1] == '=') {
                        tokens.push_back({TokenType::GTHAN_EQUAL, ">="});
                        idx += 2;
                    } else {
                        tokens.push_back({TokenType::GTHAN, string(1, current_char)});
                        idx++;
                    }
                    break;
                case ';':
                    tokens.push_back({TokenType::NEWLINE, string(1, current_char)});
                    lineNumber++;
                    idx++;
                    break;
                default:
                    throw runtime_error("Unexpected character: '" + string(1, current_char) + "' at line no. " + to_string(lineNumber));
                    break;
            }
        }
    }

    return tokens;
}