#pragma once
#include "Tree.h"
#include <stack>
#include <queue>

using namespace std;

enum N {
	Program, Begin, Description, Operators, End,
	ID, Descr, Op, Type, VarList, Expr, Conditions,
	SimpleExpr, RelationsOperators, Const,
	TERMINAL_Id, TERMINAL_Const, TERMINAL
};

enum flags {
	afterTHEN,
	afterELSE,
	NON
};

enum whereErr {
	Begin_err,
	Description_err,
	Operators_err,
	End_err,
};

enum status {
	del_simbol,
	err,
	all_read,
};

class Syntax_analys
{
public:
	Syntax_analys() = default;
	status fun(stack<N> NT, queue<Token>& line, stack<string> T);
	void SetNullptrNodes();
	void print(ostream& os);
	void setFalseDeleted_simbol();
public:
	bool is_deleted_simbol = false;
	whereErr checkErr = Begin_err;
	bool ExprInSimpleExpr = false;
	flags whereOperators = NON;

	ExprNode* ExprInBrackets = nullptr;
	ProgramNode* programNode = nullptr;
	BeginNode* beginNode = nullptr;
	EndNode* endNode = nullptr;
	DescriptionNode* descriptionNode = nullptr;
	OperatorsNode* operatorsNode = nullptr;
	DescrNode* descrNode = nullptr;
	TypeNode* typeNode = nullptr;
	VarListNode* varlistNode = nullptr;
	OpNode* opNode = nullptr;
	SimpleExprNode* simpleexprNode = nullptr;
	ExprNode* exprNode = nullptr;
	ConditionsNode* conditionsNode = nullptr;
	RelationsOperatorsNode* relationsoperatorsNode = nullptr;
	IDNode* idNode = nullptr;
	ConstNode* constNode = nullptr;
	TerminalNode* terminalNode = nullptr;

	Tree* BufNode = nullptr;
	DescriptionNode* BufDescriptionNode = nullptr;
	VarListNode* BufVarListNode = nullptr;
	ExprNode* BufExprNode = nullptr;
	ProgramNode* BufProgramNode = nullptr;
	OpNode* BufOpNode = nullptr;
	OperatorsNode* BufOperatorsNode = nullptr;
	OperatorsNode* IFOperatorsNode = nullptr;
	SimpleExprNode* BufSimpleExprNode = nullptr;
};