#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <vector>
#include <string>
#include <typeinfo>
#include "../symbol/symbol.h"
#include "../parser/parser.h"

template <typename T>
string getTypeName(const T& value);

void evaluate(const vector<ASTNode*>& nodes);

void evaluateBody(const vector<ASTNode*>& nodes);

void evaluateLog(const ASTNode* node);

void evaluateAssignment(const ASTNode* node);

void evaluateCondition(const ASTNode* node);

void evaluateWhileLoop(const ASTNode* node);

void evaluateForLoop(const ASTNode* node);

void evaluateAdjustment(const ASTNode* node);

template <typename T>
void evaluateNumericAdjustment(const string& varName, T currentValue, bool isIncrement, bool isDecrement);

ValueType evaluateExpression(const ASTNode* node);

#endif