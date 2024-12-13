#pragma once
#include "Token.h"
#include "HashTable.h"
#include <vector>

using namespace std;

enum color {
	white,
	black
};

class Tree
{
public:
	void space(ostream& os, int i);
	virtual void print(ostream& os, int depth) = 0;
	virtual ~Tree() = default;
	virtual void setAt();
	color getMark() const;
	vector<Tree*> At;
	color mark = white;
	//virtual string setTr() = 0;
	pair<bool, string> err_flag = {true, ""};
private:
	string tr;
};

class ProgramNode;
class BeginNode;
class EndNode;
class DescriptionNode;
class OperatorsNode;
class DescrNode;
class TypeNode;
class VarListNode;
class OpNode;
class SimpleExprNode;
class ExprNode;
class ConditionsNode;
class RelationsOperatorsNode;
class IDNode;
class ConstNode;
class TerminalNode;

struct Err_info {
	Err_info(string bag_name) {
		info_err = bag_name;
	}
	string info_err;
};

class ProgramNode : public Tree
{
public:
	ProgramNode();
	void print(ostream& os, int depth = 0) override;

	BeginNode* begin_node = nullptr;
	DescriptionNode* description_node = nullptr;
	OperatorsNode* operators_node = nullptr;
	EndNode* end_node = nullptr;
	~ProgramNode();

	bool setType(HashTable& table);
	string setTr(HashTable& table);

	string tr;
};

class BeginNode : public Tree
{
public:
	BeginNode();
	TerminalNode* terminal_node = nullptr;
	IDNode* id_node = nullptr;

	void print(ostream& os, int depth = 0) override;
	~BeginNode();
	bool setType(HashTable& table);
	string setTr(HashTable& table);
	string type;

	string tr;
};

class EndNode : public Tree
{
public:
	EndNode() = default;
	TerminalNode* terminal_node = nullptr;
	IDNode* id_node = nullptr;

	void print(ostream& os, int depth = 0) override;
	~EndNode();

	string type;
	string tr;
	string setTr(HashTable& table);
	bool setType(HashTable& table);
};

class DescriptionNode : public Tree
{
public:
	void setDescriptionNode(DescriptionNode* buf);
	DescriptionNode() = default;
	DescrNode* descr_node = nullptr;
	DescriptionNode* description_node = nullptr;

	void print(ostream& os, int depth = 0) override;
	~DescriptionNode();

	bool setType(HashTable& table);
	string setTr(HashTable& table);
	string tr;

};

class OperatorsNode : public Tree
{
public:
	void setOperatorsNode(OperatorsNode* buf);
	void setOpNode(OpNode* buf);
	OperatorsNode() = default;
	OpNode* Op_node = nullptr;
	OperatorsNode* operators_node = nullptr;

	void print(ostream& os, int depth = 0) override;
	~OperatorsNode();

	string setTr(HashTable& table);
	string tr;
};

class DescrNode : public Tree
{
public:
	DescrNode() = default;
	TypeNode* type_node = nullptr;
	VarListNode* varlist_node = nullptr;

	void print(ostream& os, int depth = 0) override;
	~DescrNode();

	bool setType(HashTable& table);
	string setTr(HashTable& table);
	string type;
	string tr;

};

class TypeNode : public Tree
{
public:
	TypeNode();
	TerminalNode* terminal_node = nullptr;

	void print(ostream& os, int depth = 0) override;
	~TypeNode();

	void setAt() override;
	string type = "INTEGER";
	string tr;

};

class VarListNode : public Tree
{
public:
	void setVarListNode(VarListNode* buf);
	VarListNode() = default;
	IDNode* id_node = nullptr;
	TerminalNode* terminal_node = nullptr;
	VarListNode* varlist_node = nullptr;

	void print(ostream& os, int depth = 0) override;
	~VarListNode();

	bool setType(HashTable& table, string& t);
	string setTr(HashTable& table);
	string type;
	string tr;
	int count = 1;
};

class OpNode :public Tree
{
public:
	OpNode() = default;

	void print(ostream& os, int depth = 0) override;

	IDNode* id_node = nullptr;
	TerminalNode* terminal_node_equal = nullptr;
	ExprNode* expr_node = nullptr;

	TerminalNode* terminal_node_if = nullptr;
	ConditionsNode* conditions_node = nullptr;
	TerminalNode* terminal_node_then = nullptr;
	OperatorsNode* operators_node_then = nullptr;
	TerminalNode* terminal_node_else = nullptr;
	OperatorsNode* operators_node_else = nullptr;

	~OpNode();
	string setTr(HashTable& table);
	string tr;
};

class SimpleExprNode : public Tree
{
public:
	void print(ostream& os, int depth = 0) override;
	SimpleExprNode() = default;
	IDNode* id_node = nullptr;
	ConstNode* const_node = nullptr;
	TerminalNode* terminal_node_open_bracket = nullptr;
	ExprNode* expr_node = nullptr;
	TerminalNode* terminal_node_close_bracket = nullptr;

	~SimpleExprNode();
	string setTr(HashTable& table);
	string tr;

};

class ExprNode : public Tree
{
public:

	void print(ostream& os, int depth = 0) override;

	ExprNode() = default;
	void setExprNode(ExprNode* buf);
	SimpleExprNode* simpleexpr_node = nullptr;
	TerminalNode* terminal_node = nullptr;
	ExprNode* expr_node = nullptr;

	~ExprNode();
	string setTr(HashTable& table);
	string type;
	string tr;

};

class ConditionsNode : public Tree
{
public:

	void print(ostream& os, int depth = 0) override;

	ConditionsNode() = default;
	ExprNode* expr_node1 = nullptr;
	RelationsOperatorsNode* relationsoperators_node = nullptr;
	ExprNode* expr_node2 = nullptr;

	~ConditionsNode();
	string tr;
	string setTr(HashTable& table);
};

class RelationsOperatorsNode : public Tree
{
public:

	void print(ostream& os, int depth = 0) override;

	RelationsOperatorsNode() = default;
	TerminalNode* terminal_node = nullptr;
	~RelationsOperatorsNode();

	string setTr(HashTable& table);
	string tr;

};

class IDNode : public Tree
{
public:
	void print(ostream& os, int depth = 0) override;

	IDNode();
	TerminalNode* terminal_node = nullptr;

	bool setType(HashTable& table, string& t);
	string getType(); // для PROGRAM и END
	string type;
	~IDNode();

	string tr;
};

class ConstNode : public Tree
{
public:
	void print(ostream& os, int depth = 0) override;

	ConstNode();
	TerminalNode* terminal_node = nullptr;
	~ConstNode();
	string setTr();
	string tr;
};

class TerminalNode : public Tree
{
public:
	void print(ostream& os, int depth = 0) override;
	TerminalNode() = default;
	TerminalNode(const Token& tk);

	string getType(); // сама переменная и есть тип
	Token token;

	void setAt() override;
	string tr;
};