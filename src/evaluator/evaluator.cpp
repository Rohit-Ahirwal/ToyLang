#include "evaluator.h"
#include <cctype>
#include <stdexcept>
#include <iostream>

SymbolTable symbolTable;

template <typename T>
string getTypeName(const T& value) {
    return typeid(value).name();
}

void evaluate(const vector<ASTNode*>& nodes) {
    symbolTable.enterScope();
    for (ASTNode* node : nodes) {
        switch (node->type) {
            case TokenType::LOG:
                evaluateLog(node);
                break;
            case TokenType::ASSIGNMENT:
                evaluateAssignment(node);
                break;
            case TokenType::IF:
                evaluateCondition(node);
                break;
            default:
                throw runtime_error("Invalid syntax found");
        }
    }
    symbolTable.exitScope();
}

void evaluateLog(const ASTNode* node) {
    ASTNode* expr = node->right;
    ValueType logValue = evaluateExpression(expr);
    if (holds_alternative<int>(logValue)) cout << get<int>(logValue) << endl;
    if (holds_alternative<float>(logValue)) cout << get<float>(logValue) << endl;
    if (holds_alternative<string>(logValue)) cout << get<string>(logValue) << endl;
    if (holds_alternative<bool>(logValue)) cout << get<bool>(logValue) << endl;
}

void evaluateAssignment(const ASTNode* node) {
    string varName = node->left->value;
    ValueType varValue = evaluateExpression(node->right);

    symbolTable.setVariable(varName, {varValue, TokenType::NUMBER});
}

void evaluateCondition(const ASTNode* node) {
    bool conditionResult = get<bool>(evaluateExpression(node->condition));

    if (conditionResult) {
        evaluate(node->body);
    } else if (!conditionResult && !node->elifBlocks.empty()) {
        for (auto elif: node->elifBlocks) {
            evaluateCondition(elif);
        }
    }
    
    if (!conditionResult && node->elseBlock != nullptr) {
        evaluate(node->elseBlock->body);
    }
}

ValueType evaluateExpression(const ASTNode* node) {
    ValueType leftValue, rightValue;
    switch (node->type) {
        case TokenType::NUMBER:
            return stoi(node->value);
            break;
        case TokenType::FLOAT:
            return stof(node->value);
            break;
        case TokenType::STRING:
            return node->value;
            break;
        case TokenType::BOOL:
            if (node->value == "true") {
                return true;
            } else {
                return false;
            }
            break;
        case TokenType::ADD:
            leftValue = evaluateExpression(node->left);
            rightValue = evaluateExpression(node->right);

            if (holds_alternative<int>(leftValue) && holds_alternative<int>(rightValue)) {
                return get<int>(leftValue) + get<int>(rightValue);
            } else if (holds_alternative<float>(leftValue) && holds_alternative<float>(rightValue)) {
                return get<float>(leftValue) + get<float>(rightValue);
            } else if (holds_alternative<string>(leftValue) && holds_alternative<string>(rightValue)) {
                return get<string>(leftValue) + get<string>(rightValue);
            } else if (holds_alternative<int>(leftValue) && holds_alternative<float>(rightValue)) {
                return get<int>(leftValue) + get<float>(rightValue);
            } else if (holds_alternative<float>(leftValue) && holds_alternative<int>(rightValue)) {
                return get<float>(leftValue) + get<int>(rightValue);
            } else {
                throw runtime_error("Addition operation is not allowed between " + getTypeName(leftValue) + " and " + getTypeName(rightValue));
            }
            break;
        case TokenType::MINUS:
            leftValue = evaluateExpression(node->left);
            rightValue = evaluateExpression(node->right);

            if (holds_alternative<int>(leftValue) && holds_alternative<int>(rightValue)) {
                return get<int>(leftValue) - get<int>(rightValue);
            } else if (holds_alternative<float>(leftValue) && holds_alternative<float>(rightValue)) {
                return get<float>(leftValue) - get<float>(rightValue);
            } else if (holds_alternative<int>(leftValue) && holds_alternative<float>(rightValue)) {
                return get<int>(leftValue) - get<float>(rightValue);
            } else if (holds_alternative<float>(leftValue) && holds_alternative<int>(rightValue)) {
                return get<float>(leftValue) - get<int>(rightValue);
            } else {
                throw runtime_error("Subtraction operation is not allowed between " + getTypeName(leftValue) + " and " + getTypeName(rightValue));
            }
            break;
        case TokenType::STAR:
            leftValue = evaluateExpression(node->left);
            rightValue = evaluateExpression(node->right);

            if (holds_alternative<int>(leftValue) && holds_alternative<int>(rightValue)) {
                return get<int>(leftValue) * get<int>(rightValue);
            } else if (holds_alternative<float>(leftValue) && holds_alternative<float>(rightValue)) {
                return get<float>(leftValue) * get<float>(rightValue);
            } else if (holds_alternative<int>(leftValue) && holds_alternative<float>(rightValue)) {
                return get<int>(leftValue) * get<float>(rightValue);
            } else if (holds_alternative<float>(leftValue) && holds_alternative<int>(rightValue)) {
                return get<float>(leftValue) * get<int>(rightValue);
            } else {
                throw runtime_error("Multiplication operation is not allowed between " + getTypeName(leftValue) + " and " + getTypeName(rightValue));
            }
            break;
        case TokenType::SLASH:
            leftValue = evaluateExpression(node->left);
            rightValue = evaluateExpression(node->right);

            if (holds_alternative<int>(leftValue) && holds_alternative<int>(rightValue)) {
                if (get<int>(rightValue) == 0) {
                    throw runtime_error("Division by zero");
                }
                return get<int>(leftValue) / get<int>(rightValue);
            } else if (holds_alternative<float>(leftValue) && holds_alternative<float>(rightValue)) {
                if (get<float>(rightValue) == 0.0f) {
                    throw runtime_error("Division by zero");
                }
                return get<float>(leftValue) / get<float>(rightValue);
            } else if (holds_alternative<int>(leftValue) && holds_alternative<float>(rightValue)) {
                if (get<float>(rightValue) == 0.0f) {
                    throw runtime_error("Division by zero");
                }
                return get<int>(leftValue) / get<float>(rightValue);
            } else if (holds_alternative<float>(leftValue) && holds_alternative<int>(rightValue)) {
                if (get<int>(rightValue) == 0) {
                    throw runtime_error("Division by zero");
                }
                return get<float>(leftValue) / get<int>(rightValue);
            } else {
                throw runtime_error("Division operation is not allowed between " + getTypeName(leftValue) + " and " + getTypeName(rightValue));
            }
            break;
        case TokenType::EQUAL:
            leftValue = evaluateExpression(node->left);
            rightValue = evaluateExpression(node->right);

            return leftValue == rightValue;
            break;
        case TokenType::GTHAN:
            leftValue = evaluateExpression(node->left);
            rightValue = evaluateExpression(node->right);

            return leftValue > rightValue;
            break;
        case TokenType::LTHAN:
            leftValue = evaluateExpression(node->left);
            rightValue = evaluateExpression(node->right);

            return leftValue < rightValue;
            break;
        case TokenType::LTHAN_EQUAL:
            leftValue = evaluateExpression(node->left);
            rightValue = evaluateExpression(node->right);

            return leftValue <= rightValue;
            break;
        case TokenType::GTHAN_EQUAL:
            leftValue = evaluateExpression(node->left);
            rightValue = evaluateExpression(node->right);

            return leftValue >= rightValue;
            break;
        case TokenType::IDENTIFIER:
            return symbolTable.getVariable(node->value).value;
            break;
        default:
            throw runtime_error("Invalid syntax error");
            break;
    }
}