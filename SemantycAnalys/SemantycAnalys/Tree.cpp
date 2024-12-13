#include "Tree.h"
#include <iostream>

using namespace std;

void Tree::space(ostream& os, int i)
{
    for (int d = 0; d < i; ++d)
        os << "\t\t\t";
}

void Tree::setAt()
{
    for (int i = 0; i < this->At.size(); ++i)
    {
        tr += At[i]->tr + " ";
    }
}

color Tree::getMark() const
{
    return mark;
}

ProgramNode::ProgramNode()
{
    At.push_back(begin_node);
    At.push_back(description_node);
    // ...
}

void ProgramNode::print(ostream& os, int depth)
{
    space(os, depth);
    os << "Program" << endl;

    if (begin_node != nullptr)
        begin_node->print(os, depth + 1);
    if (description_node != nullptr)
        description_node->print(os, depth + 1);
    if (operators_node != nullptr)
        operators_node->print(os, depth + 1);
    if (end_node != nullptr)
        end_node->print(os, depth + 1);
}

ProgramNode::~ProgramNode()
{
    delete begin_node;
    delete description_node;
    delete operators_node;
    delete end_node;
}

bool ProgramNode::setType(HashTable& table)
{
    begin_node->setType(table);
    end_node->setType(table);
    if (begin_node->type != end_node->type)
        return false;
    return description_node->setType(table);
}

string ProgramNode::setTr(HashTable& table)
{
    tr += begin_node->setTr(table) + " ";
    tr += description_node->setTr(table) + " ";
    tr += operators_node->setTr(table) + " ";
    tr += end_node->setTr(table) + " ";
    return tr;
}

void VarListNode::setVarListNode(VarListNode* buf)
{
    if (this->varlist_node != nullptr)
        this->varlist_node->setVarListNode(buf);
    else
        this->varlist_node = buf;
}

void VarListNode::print(ostream& os, int depth)
{
    space(os, depth);
    os << "VarList" << std::endl;
    if (id_node) id_node->print(os, depth + 1);
    if (terminal_node) terminal_node->print(os, depth + 1);
    if (varlist_node) varlist_node->print(os, depth + 1);
}

VarListNode::~VarListNode()
{
    delete id_node;
    delete terminal_node;
    delete varlist_node;
}

bool VarListNode::setType(HashTable& table, string& t)
{
    bool flag = false;
    type = t;
    if (id_node != nullptr)
        flag = id_node->setType(table, t);
    if (varlist_node != nullptr && flag)
        flag = varlist_node->setType(table, t);
    return flag;
}

string VarListNode::setTr(HashTable& table)
{
    tr = id_node->getType() + " ";
    if (varlist_node != nullptr) {
        tr += varlist_node->setTr(table);
        count += varlist_node->count;
    }
    return tr;
}

void ExprNode::print(ostream& os, int depth)
{
    space(os, depth);
    os << "Expr" << std::endl;
    if (simpleexpr_node) simpleexpr_node->print(os, depth + 1);
    if (terminal_node) terminal_node->print(os, depth + 1);
    if (expr_node) expr_node->print(os, depth + 1);
}

void ExprNode::setExprNode(ExprNode* buf)
{
    if (this->expr_node != nullptr)
        this->expr_node->setExprNode(buf);
    else
        this->expr_node = buf;
}

ExprNode::~ExprNode()
{
    delete simpleexpr_node;
    delete terminal_node;
    delete expr_node;
}

string ExprNode::setTr(HashTable& table)
{
    
    if (expr_node != nullptr) {
        tr = expr_node->setTr(table) + tr;
        tr = simpleexpr_node->setTr(table) + " " + tr;
        tr += terminal_node->getType() + " ";
    }
    else {
        tr += simpleexpr_node->setTr(table);
    }

    return tr;
}

void DescriptionNode::setDescriptionNode(DescriptionNode* buf)
{
    if (this->description_node != nullptr)
        this->description_node->setDescriptionNode(buf);
    else
        this->description_node = buf;
}

void DescriptionNode::print(ostream& os, int depth)
{
    space(os, depth);
    os << "Description" << endl;
    if (descr_node) descr_node->print(os, depth + 1);
    if (description_node) description_node->print(os, depth + 1);
}

DescriptionNode::~DescriptionNode()
{
    delete descr_node;
    delete description_node;
}

bool DescriptionNode::setType(HashTable& table)
{
    bool flag = false;
    if (descr_node != nullptr)
        flag = descr_node->setType(table);
    if (description_node != nullptr && flag)
        flag = description_node->setType(table);
    return flag;
}

string DescriptionNode::setTr(HashTable& table)
{
    tr += descr_node->setTr(table) + " ";
    if (description_node != nullptr)
        tr += description_node->setTr(table) + " ";
    return tr;
}

void OperatorsNode::setOperatorsNode(OperatorsNode* buf)
{
    if (this->operators_node != nullptr)
        this->operators_node->setOperatorsNode(buf);
    else
        this->operators_node = buf;
}

void OperatorsNode::setOpNode(OpNode* buf)
{
    if (this->Op_node != nullptr)
    {
        if (this->operators_node != nullptr)
            this->operators_node->setOpNode(buf);
        else
        {
            this->operators_node = new OperatorsNode();
            this->operators_node->setOpNode(buf);
        }
    }
    else
        this->Op_node = buf;
}

void OperatorsNode::print(ostream& os, int depth)
{
    space(os, depth);
    os << "Operators" << endl;
    if (this->Op_node != nullptr)
        Op_node->print(os, depth + 1);
    if (this->operators_node != nullptr)
        operators_node->print(os, depth + 1);
}

OperatorsNode::~OperatorsNode()
{
    delete Op_node;
    delete operators_node;
}

string OperatorsNode::setTr(HashTable& table)
{
    tr += Op_node->setTr(table) + " ";
    if (operators_node != nullptr)
        tr += operators_node->setTr(table);
    return tr;
}

BeginNode::BeginNode()
{
    At.push_back(terminal_node);
    At.push_back(id_node);
}

void BeginNode::print(ostream& os, int depth)
{
    space(os, depth);
    os << "Begin" << std::endl;
    if (terminal_node) terminal_node->print(os, depth + 1);
    if (id_node) id_node->print(os, depth + 1);
}

BeginNode::~BeginNode()
{
    delete terminal_node;
    delete id_node;
}

bool BeginNode::setType(HashTable& table)
{
    type = id_node->getType();
    return true;
}

string BeginNode::setTr(HashTable& table)
{
    tr += "PROGRAM ";
    tr += id_node->getType() + " ";
    return tr;
}



void EndNode::print(ostream& os, int depth)
{
    space(os, depth);
    os << "End" << endl;
    if (terminal_node) terminal_node->print(os, depth + 1);
    if (id_node) id_node->print(os, depth + 1);
}

EndNode::~EndNode()
{
    delete terminal_node;
    delete id_node;
}

string EndNode::setTr(HashTable& table)
{
    tr += terminal_node->getType() + " ";
    tr += id_node->getType() + " ";
    return tr;
}

bool EndNode::setType(HashTable& table)
{
    type = id_node->getType();
    return true;
}

void DescrNode::print(ostream& os, int depth)
{
    space(os, depth);
    os << "Descr" << endl;
    if (type_node) type_node->print(os, depth + 1);
    if (varlist_node) varlist_node->print(os, depth + 1);
}

DescrNode::~DescrNode()
{
    delete type_node;
    delete varlist_node;
}

bool DescrNode::setType(HashTable& table)
{
    type = type_node->type;
    return varlist_node->setType(table, type);
}

string DescrNode::setTr(HashTable& table)
{
    tr += type + " " + varlist_node->setTr(table) + " "; // T.type Id.tr VarList.tr VarList.count + 1 DECL
    tr += to_string(varlist_node->count + 1); 
    tr += " DECL";
    return tr;
}

TypeNode::TypeNode()
{
    At.push_back(terminal_node);
}

void TypeNode::print(ostream& os, int depth)
{
    space(os, depth);
    os << "Type" << endl;
    if (terminal_node) terminal_node->print(os, depth + 1);
}

TypeNode::~TypeNode()
{
    delete terminal_node;
}

void TypeNode::setAt()
{
    tr = "INTEGER";
}

void OpNode::print(ostream& os, int depth)
{
    space(os, depth);
    os << "Op" << std::endl;
    if (id_node) id_node->print(os, depth + 1);
    if (terminal_node_equal) terminal_node_equal->print(os, depth + 1);
    if (expr_node) expr_node->print(os, depth + 1);
    if (terminal_node_if) terminal_node_if->print(os, depth + 1);
    if (conditions_node) conditions_node->print(os, depth + 1);
    if (terminal_node_then) terminal_node_then->print(os, depth + 1);
    if (operators_node_then) operators_node_then->print(os, depth + 1);
    if (terminal_node_else) terminal_node_else->print(os, depth + 1);
    if (operators_node_else) operators_node_else->print(os, depth + 1);
}

OpNode::~OpNode()
{
    delete id_node;
    delete terminal_node_equal;
    delete expr_node;
    delete terminal_node_if;
    delete conditions_node;
    delete terminal_node_then;
    delete operators_node_then;
    delete terminal_node_else;
    delete operators_node_else;
}

string OpNode::setTr(HashTable& table)
{
    if (id_node != nullptr)
    {
        long long key = table.get_key(id_node->getType());
        if (table.getType(key) != "INTEGER")
            throw Err_info("Error! Initialize ID");

        tr += id_node->getType() + " ";
        tr += expr_node->setTr(table);
        tr += " = ";
    }

    else {
        if (terminal_node_else != nullptr) {
            tr += conditions_node->setTr(table) + " ";
            tr += "m1 BF ";
            tr += operators_node_then->setTr(table) + " ";
            tr += "m2 BRL ";
            tr += "m1 DEFL ";
            tr += operators_node_else->setTr(table) + " ";
            tr += "m2 DEFL ";
        }
        else {
            tr += conditions_node->setTr(table) + " ";
            tr += "m BF ";
            tr += operators_node_then->setTr(table) + " ";
            tr += "m DEFL ";  
        }
    }
    
    return tr;
}


void SimpleExprNode::print(ostream& os, int depth)
{
    space(os, depth);
    os << "SimpleExpr" << endl;
    if (id_node) id_node->print(os, depth + 1);
    if (const_node) const_node->print(os, depth + 1);
    if (terminal_node_open_bracket) terminal_node_open_bracket->print(os, depth + 1);
    if (expr_node) expr_node->print(os, depth + 1);
    if (terminal_node_close_bracket) terminal_node_close_bracket->print(os, depth + 1);
}

SimpleExprNode::~SimpleExprNode()
{
    delete id_node;
    delete const_node;
    delete terminal_node_open_bracket;
    delete terminal_node_close_bracket;
}

string SimpleExprNode::setTr(HashTable& table)
{
    if (id_node != nullptr)
    {
        long long key = table.get_key(id_node->getType());
        if (table.getType(key) != "INTEGER")
            throw Err_info("Error! Initialize ID");

        tr += id_node->getType() + " ";
    }
    if (const_node != nullptr)
        tr += const_node->setTr() + " ";

    if (expr_node != nullptr)
    {
        tr += expr_node->setTr(table) + " ";
    }
    return tr;
}

void ConditionsNode::print(ostream& os, int depth)
{
    space(os, depth);
    os << "Conditions" << endl;
    if (expr_node1) expr_node1->print(os, depth + 1);
    if (relationsoperators_node) relationsoperators_node->print(os, depth + 1);
    if (expr_node2) expr_node2->print(os, depth + 1);
}

ConditionsNode::~ConditionsNode()
{
    delete expr_node1;
    delete relationsoperators_node;
    delete expr_node2;
}

string ConditionsNode::setTr(HashTable& table)
{
    tr += expr_node1->setTr(table) + " ";
    tr += expr_node2->setTr(table) + " ";
    tr += relationsoperators_node->setTr(table) + " ";
    return tr;
}

void RelationsOperatorsNode::print(ostream& os, int depth)
{
    space(os, depth);
    os << "RelationsOperators" << endl;
    if (terminal_node) terminal_node->print(os, depth + 1);
}

RelationsOperatorsNode::~RelationsOperatorsNode()
{
    delete terminal_node;
}

string RelationsOperatorsNode::setTr(HashTable& table)
{
    tr += terminal_node->getType() + " ";
    return tr;
}

void IDNode::print(ostream& os, int depth)
{
    space(os, depth);
    os << "ID" << endl;
    if (terminal_node) terminal_node->print(os, depth + 1);
}

IDNode::IDNode()
{
    At.push_back(terminal_node);
}

bool IDNode::setType(HashTable& table, string& t)
{
    type = t;
    return table.changeType(terminal_node->token, t);

    //int idx = table.find(terminal_node->token);

}

string IDNode::getType()
{
    return terminal_node->getType();
}

IDNode::~IDNode()
{
    delete terminal_node;
}

void ConstNode::print(ostream& os, int depth)
{
    space(os, depth);
    os << "Const" << endl;
    if (terminal_node) terminal_node->print(os, depth + 1);
}

ConstNode::ConstNode()
{
    At.push_back(terminal_node);
}

ConstNode::~ConstNode()
{
    delete terminal_node;
}

string ConstNode::setTr()
{
    tr = terminal_node->getType();
    return tr;
}

void TerminalNode::setAt()
{
    tr = token.getValue();
}

void TerminalNode::print(ostream& os, int depth)
{
    space(os, depth);
    os << "Terminal: " << token << endl;
}

TerminalNode::TerminalNode(const Token& tk)
{
    tr = tk.getValue();
}

string TerminalNode::getType()
{
    return token.getValue();
}
