#include "Syntax_analys.h"

status Syntax_analys::fun(stack<N> NT, queue<Token>& line, stack<string> T)
{
	status value;
	switch (NT.top())
	{
	case TERMINAL:
		NT.pop();
		if (line.empty())
			return err;
		else if (line.front() == T.top())
		{
			terminalNode = new TerminalNode();
			terminalNode->token = line.front();
			T.pop();
			line.pop();
			is_deleted_simbol = true;
			if (NT.empty() && line.empty())
				return all_read;
			return del_simbol;
		}
		else {
			return err;
		}
	case TERMINAL_Const:
		NT.pop();
		if (line.empty())
			return err;
		else if (line.front().getType() == LeksemType::Const)
		{
			is_deleted_simbol = true;
			terminalNode = new TerminalNode();
			terminalNode->token = line.front();
			line.pop();
			if (NT.empty() && line.empty())
				return all_read;
			return del_simbol;
		}
		else {
			return err;
		}
	case TERMINAL_Id:
		NT.pop();
		if (line.empty())
			return err;
		else if (line.front().getType() == LeksemType::Id)
		{
			is_deleted_simbol = true;
			terminalNode = new TerminalNode();
			terminalNode->token = line.front();
			line.pop();
			if (NT.empty() && line.empty())
				return all_read;
			return del_simbol;
		}
		else {
			return err;
		}
	case Program:
		NT.pop();
		NT.push(Begin);
		value = fun(NT, line, T);
		if (value == all_read) {
			if (programNode == nullptr) {
				programNode = new ProgramNode();
				programNode->begin_node = beginNode;
			}
			else {
				programNode->begin_node = beginNode;
			}
			return all_read;
		}
		else if (value == err && !is_deleted_simbol) {
			checkErr = Description_err;
			NT.pop();
			NT.push(Description);
			value = fun(NT, line, T);
			if (value == all_read) {
				if (programNode == nullptr) {
					programNode = new ProgramNode();
					programNode->description_node = descriptionNode;
				}
				else {
					if (programNode->description_node != nullptr)
						programNode->description_node->setDescriptionNode(descriptionNode);
					else
						programNode->description_node = descriptionNode;
				}
				return all_read;
			}
			else if (value == err && !is_deleted_simbol) {
				checkErr = Operators_err;
				NT.pop();
				NT.push(Operators);
				value = fun(NT, line, T);
				if (value == all_read)
				{
					if (programNode == nullptr) {
						programNode = new ProgramNode();
						programNode->operators_node = operatorsNode;
					}
					else {
						if (programNode->operators_node != nullptr)
							programNode->operators_node->setOperatorsNode(operatorsNode);
						else
							programNode->operators_node = operatorsNode;
					}
					return all_read;
				}
				else if (value == err && !is_deleted_simbol) {
					checkErr = End_err;
					NT.pop();
					NT.push(End);
					value = fun(NT, line, T);
					if (value == all_read)
					{
						if (programNode == nullptr) {
							programNode = new ProgramNode();
							programNode->end_node = endNode;
						}
						else {
							programNode->end_node = endNode;
						}
						return all_read;
					}
					else {
						return err;
					}
				}
			}
		}
		return err;
	case Begin:
		NT.pop();
		NT.push(ID);
		NT.push(TERMINAL);
		T.push("PROGRAM");
		value = fun(NT, line, T);
		if (value == del_simbol)
		{
			beginNode = new BeginNode();
			beginNode->terminal_node = terminalNode;
			T.pop();
			NT.pop();
			value = fun(NT, line, T);
			if (value == all_read) {
				beginNode->id_node = idNode;
				return all_read;
			}
			return del_simbol;
		}
		else {
			return err;
		}
	case ID:
		NT.pop();
		NT.push(TERMINAL_Id);
		value = fun(NT, line, T);
		if (value != err)
		{
			idNode = new IDNode();
			idNode->terminal_node = terminalNode;
		}
		return value;
	case Description:
		NT.pop();
		NT.push(Descr);
		value = fun(NT, line, T);
		if (value == all_read) {
			if (descriptionNode != nullptr)
			{
				BufDescriptionNode = new DescriptionNode();
				BufDescriptionNode->descr_node = descrNode;

				descriptionNode->setDescriptionNode(BufDescriptionNode);
			}
			else {
				descriptionNode = new DescriptionNode();
				descriptionNode->descr_node = descrNode;
			}
			return all_read;
		}
		else if (value == del_simbol)
		{
			if (descriptionNode != nullptr)
			{
				BufDescriptionNode = new DescriptionNode();
				BufDescriptionNode->descr_node = descrNode;
				descriptionNode->setDescriptionNode(BufDescriptionNode);
			}
			else {
				descriptionNode = new DescriptionNode();
				descriptionNode->descr_node = descrNode;
			}
			NT.pop();
			NT.push(Description);
			varlistNode = nullptr;
			value = fun(NT, line, T);
			if (value == all_read) {
				return all_read;
			}
		}
		return err;
	case Descr:
		NT.pop();
		NT.push(VarList);
		NT.push(Type);
		value = fun(NT, line, T);
		if (value == del_simbol)
		{
			descrNode = new DescrNode();
			descrNode->type_node = typeNode;
			NT.pop();
			value = fun(NT, line, T);
			if (value != err)
			{
				descrNode->varlist_node = varlistNode;
			}
			return value;
		}
		else if (value == err) {
			return err;
		}
		else {
			NT.pop();
		}
	case Type:
		NT.pop();
		NT.push(TERMINAL);
		T.push("INTEGER");
		value = fun(NT, line, T);
		if (value == del_simbol)
		{
			typeNode = new TypeNode();
			typeNode->terminal_node = terminalNode;
		}
		return value;
	case VarList:
		NT.pop();
		NT.push(ID);
		value = fun(NT, line, T);
		if (value == del_simbol) {
			if (varlistNode != nullptr)
			{
				BufVarListNode = new VarListNode();
				BufVarListNode->id_node = idNode;
				NT.pop();
				NT.push(VarList);
				NT.push(TERMINAL);
				T.push(",");
				value = fun(NT, line, T);
				if (value == del_simbol)
				{
					BufVarListNode->terminal_node = terminalNode;
					varlistNode->setVarListNode(BufVarListNode);
					NT.pop(); // delete ","
					T.pop();
					value = fun(NT, line, T);
					return value;
				}
				return del_simbol;
			}
			else {
				NT.pop();
				NT.push(VarList);
				NT.push(TERMINAL);
				T.push(",");
				varlistNode = new VarListNode();
				varlistNode->id_node = idNode;
				value = fun(NT, line, T);
				if (value == del_simbol)
				{
					varlistNode->terminal_node = terminalNode;
					NT.pop(); // delete ","
					T.pop();
					value = fun(NT, line, T);
					return value;
				}
				return del_simbol;
			}
		}
		else if (value == all_read)
		{
			if (varlistNode != nullptr)
			{
				BufVarListNode = new VarListNode();
				BufVarListNode->id_node = idNode;
				varlistNode->setVarListNode(BufVarListNode);
			}
			else {
				varlistNode = new VarListNode();
				varlistNode->id_node = idNode;
			}
		}
		return value;
	case Operators:
		NT.pop();
		NT.push(Op);
		value = fun(NT, line, T);
		if (value == all_read) {

			if (operatorsNode != nullptr)
			{
				BufOperatorsNode = new OperatorsNode();
				BufOperatorsNode->Op_node = opNode;
				opNode = nullptr;
				BufOperatorsNode->setOperatorsNode(BufOperatorsNode);
				BufOperatorsNode = nullptr;
			}
			else {
				if (whereOperators != NON) // чтобы при переходу в Op -> If... записывал в OpNode -> THEN | ELSE Operators -> OpNode 
				{
					IFOperatorsNode->setOpNode(BufOpNode);
					BufOpNode = nullptr;
				}
				else {
					operatorsNode = new OperatorsNode();
					operatorsNode->Op_node = opNode;
					opNode = nullptr;
				}
			}
			return all_read;
		}
		else if (value == del_simbol)
		{
			if (operatorsNode != nullptr)
			{
				BufOperatorsNode = new OperatorsNode();
				BufOperatorsNode->Op_node = opNode;
				opNode = nullptr; // чтобы не сбивалось в случает Operators -> Op (read) Operators -> Op (read) Op не рассматривался как != nullptr
				operatorsNode->setOperatorsNode(BufOperatorsNode);
			}
			else {
				if (whereOperators != NON)
				{
					IFOperatorsNode->setOpNode(BufOpNode);
				}
				else {
					operatorsNode = new OperatorsNode();
					operatorsNode->Op_node = opNode;
					opNode = nullptr;
					operatorsNode->setOperatorsNode(BufOperatorsNode);
				}
			}
			NT.pop();
			NT.push(Operators); // кладет Операторс и опять идет по Оп
			value = fun(NT, line, T); // рукурсивно вернутся в случаи выше
			if (value == all_read)
				return all_read;
			return del_simbol;
		}
		return err;
	case Op:
		NT.pop();
		NT.push(Expr);
		NT.push(TERMINAL);
		T.push("=");
		NT.push(ID);
		value = fun(NT, line, T);
		if (opNode == nullptr) {
			if (value == del_simbol)
			{
				opNode = new OpNode();
				opNode->id_node = idNode;
				NT.pop();
				value = fun(NT, line, T);
				if (value == del_simbol)
				{
					opNode->terminal_node_equal = terminalNode;
					NT.pop();
					value = fun(NT, line, T);
					if (value != err)
					{
						opNode->expr_node = exprNode;
						exprNode = nullptr;
					}
					return value;
				}
				else
					return err;
			}
			else {
				T.pop();
				NT.pop(), NT.pop(), NT.pop();
				NT.push(Operators);
				NT.push(TERMINAL);
				T.push("THEN");
				NT.push(Conditions);
				NT.push(TERMINAL);
				T.push("IF");
				value = fun(NT, line, T);
				if (value == del_simbol) {
					opNode = new OpNode();
					opNode->terminal_node_if = terminalNode;
					NT.pop();
					T.pop(); // delete IF
					value = fun(NT, line, T);
					if (value == del_simbol)
					{
						opNode->conditions_node = conditionsNode;
						NT.pop(); // delete Conditions
						value = fun(NT, line, T);
						if (value == del_simbol)
						{
							opNode->terminal_node_then = terminalNode;
							NT.pop();
							T.pop(); // delete THEN
							whereOperators = afterTHEN;
							IFOperatorsNode = new OperatorsNode();
							value = fun(NT, line, T);
							whereOperators = NON;
							if (value == all_read) // IF .. THEN ..
							{
								opNode->operators_node_then = IFOperatorsNode;
								IFOperatorsNode = nullptr;
								return all_read;
							}
							if (value == del_simbol)
							{
								opNode->operators_node_then = IFOperatorsNode;
								IFOperatorsNode = nullptr;
								NT.pop();
								NT.push(Operators);
								T.push("ELSE");
								NT.push(TERMINAL);
								value = fun(NT, line, T);
								if (value == del_simbol)
								{
									opNode->terminal_node_else = terminalNode;
									NT.pop();
									T.pop();
									IFOperatorsNode = new OperatorsNode();
									whereOperators = afterELSE;
									value = fun(NT, line, T);
									whereOperators = NON;
									if (value == all_read) // IF .. THEN .. ELSE ..
									{
										opNode->operators_node_else = IFOperatorsNode;
										return all_read;
									}
									else {
										delete IFOperatorsNode;
										return value;
									}
								}

							}
							else { // если нетерминал не прочитался
								delete IFOperatorsNode;
							}
						}
					}
				}
				return err;
			}
		}
		else { // если OpNode была ранее создана так как OpNode создается после прочтения терминала 'IF' или Operators -> Op Operators -> Op Op
			if (value == del_simbol)
			{
				BufOpNode = new OpNode();
				BufOpNode->id_node = idNode; // кладет прочитанный IDNode созданный после прочтения нетерминала ID
				NT.pop();
				value = fun(NT, line, T);  // пробует удалить следующий нетерминал  '='
				if (value == del_simbol)
				{
					BufOpNode->terminal_node_equal = terminalNode; // если получилось удалить то сохраняется адрес в ветке-указателе
					NT.pop();
					value = fun(NT, line, T); // пробует удалить нетерминал Expr 
					if (value != err)
					{
						BufOpNode->expr_node = exprNode; // сохраняет его в указатель
						exprNode = nullptr;
						//IFOperatorsNode->setOpNode(BufOpNode); // если он перейдет в Operators у которого есть Op то он рекурсивно вызовет эту функцию от ветки Operators и (создаст ее если ее нет)
					}
					return value;
				}
				else {
					delete BufOpNode;
					return err;
				}
			}
			else if (value == err) { // если нетерминал ID не получилось удалить то пробуем удалить 'IF'
				T.pop();
				NT.pop(), NT.pop(), NT.pop();
				NT.push(Operators);
				NT.push(TERMINAL);
				T.push("THEN");
				NT.push(Conditions);
				NT.push(TERMINAL);
				T.push("IF");
				value = fun(NT, line, T);
				if (value == del_simbol) {
					BufOpNode = new OpNode();
					BufOpNode->terminal_node_if = terminalNode;
					IFOperatorsNode->setOpNode(BufOpNode); // ?? если получилось удалить нетерминал то пусть сразу добавляет его в дерево чтобы если потом опять зайдет в Operators то не потерял тот уровень как он пришел сюда
					NT.pop();
					T.pop(); // delete IF
					value = fun(NT, line, T);
					if (value == del_simbol)
					{
						BufOpNode->conditions_node = conditionsNode;
						NT.pop(); // delete Conditions
						value = fun(NT, line, T);
						if (value == del_simbol)
						{
							BufOpNode->terminal_node_then = terminalNode;
							NT.pop();
							T.pop(); // delete THEN	

							/*
							создаем новый указатель из предположения что Operators из которого мы пришли в Op еще не создан
							или мы ранее создавали Operators после THEN и привязали его к OpNode ветке

							так же Operators может быть создан сверху по правилу Operators -> Op Operators после удаления Op
							по этому лучше Buf
							*/

							value = fun(NT, line, T); // пробуем Operators прочитать Operators -> Op и опять в ветку != nullptr
							if (value == all_read) // IF .. THEN .. 
							{
								BufOpNode->operators_node_then = operatorsNode;
								return all_read;
							}
							if (value == del_simbol)
							{
								opNode->operators_node_then = operatorsNode;
								NT.pop();
								NT.push(Operators);
								T.push("ELSE");
								NT.push(TERMINAL);
								value = fun(NT, line, T);
								if (value == del_simbol)
								{
									opNode->terminal_node_else = terminalNode;
									NT.pop();
									T.pop();
									value = fun(NT, line, T);
									if (value == all_read) // IF .. THEN .. ELSE ..
									{
										opNode->operators_node_else = operatorsNode;
										return all_read;
									}
								}
								return del_simbol; // Если IF a .EQ. b THEN IF a .EQ. c ...
							}
						}
					}
				}
				return err;
			}
			else {

			}
		}
	case Conditions:
		NT.pop();
		NT.push(Expr);
		NT.push(RelationsOperators);
		NT.push(Expr);
		value = fun(NT, line, T);
		if (value == del_simbol)
		{
			conditionsNode = new ConditionsNode();
			conditionsNode->expr_node1 = exprNode;
			exprNode = nullptr;
			NT.pop();
			value = fun(NT, line, T);
			if (value == del_simbol)
			{
				conditionsNode->relationsoperators_node = relationsoperatorsNode;
				NT.pop();
				value = fun(NT, line, T);
				if (value != err)
				{
					conditionsNode->expr_node2 = exprNode;
					exprNode = nullptr;
				}
				return value;
			}
		}
		return err;
	case RelationsOperators:
		NT.pop();
		NT.push(TERMINAL);
		T.push(".EQ.");
		value = fun(NT, line, T);

		if (value == err)
		{
			T.pop();
			T.push(".NE.");
			value = fun(NT, line, T);
			if (value == err)
			{
				T.pop();
				T.push(".GT.");
				value = fun(NT, line, T);
				if (value == err)
				{
					T.pop();
					T.push(".LE.");
					value = fun(NT, line, T);
					if (value == err)
					{
						T.pop();
						T.push(".LT.");
						value = fun(NT, line, T);
					}
				}
			}
		}

		if (value != err)
		{
			relationsoperatorsNode = new RelationsOperatorsNode();
			relationsoperatorsNode->terminal_node = terminalNode;
		}
		return value;
	case SimpleExpr:
		NT.pop();
		NT.push(ID);
		value = fun(NT, line, T);
		if (value != err) {
			simpleexprNode = new SimpleExprNode();
			simpleexprNode->id_node = idNode;
			return value;
		}
		else {
			NT.pop();
			NT.push(Const);
			value = fun(NT, line, T);
			if (value != err) {
				simpleexprNode = new SimpleExprNode();
				simpleexprNode->const_node = constNode;
				return value;
			}
			else {
				NT.pop();
				NT.push(TERMINAL);
				T.push(")");
				NT.push(Expr);
				NT.push(TERMINAL);
				T.push("(");
				value = fun(NT, line, T);
				if (value == del_simbol)
				{
					if (ExprInSimpleExpr == false)
					{
						BufSimpleExprNode = new SimpleExprNode();
						BufSimpleExprNode->terminal_node_open_bracket = terminalNode;
						NT.pop(), T.pop(); // delete '('
						ExprInSimpleExpr = true; // показывает что Expr записывается в скобках, надо записывать в ExprInBrackets
						//ExprInBrackets = new ExprNode();
						value = fun(NT, line, T);
						BufSimpleExprNode->expr_node = ExprInBrackets;  // чтобы так же как в Expr но не трогал ранее созданный Expr

						ExprInBrackets = nullptr;
						ExprInSimpleExpr = false;
						if (value == del_simbol)
						{
							NT.pop(); // delete Expr
							value = fun(NT, line, T);

							if (value != err)
							{
								BufSimpleExprNode->terminal_node_close_bracket = terminalNode;
								simpleexprNode = BufSimpleExprNode;
								BufSimpleExprNode = nullptr;
							}
							return value;
						}
						else
							return err;
					}
					else { // если уже создали буфер для скобок и встретились скобки внутри скобок то надо добавить внутрь созданного ExprInBrackets
						/*
						нужно засетить скобку в ExprInBrackets->SimpleExpr->terminal_open_brackets
						*/

						NT.pop(), T.pop(); // delete '('
						//ExprInBrackets = new ExprNode();
						value = fun(NT, line, T);


						if (value == del_simbol)
						{
							NT.pop(); // delete Expr
							value = fun(NT, line, T);


							return value;
						}
						else
							return err;

					}
				}
				else
					return err;
			}
		}
	case Expr:
		NT.pop();
		NT.push(SimpleExpr);
		value = fun(NT, line, T);
		if (value == del_simbol)
		{
			if (exprNode == nullptr && ExprInSimpleExpr == false)
			{
				exprNode = new ExprNode();
				exprNode->simpleexpr_node = simpleexprNode; // error nel'zya prisvaivat' ( 5 + a ... esli nachinaetsya so skobki
				simpleexprNode = nullptr;
				NT.pop();
				NT.push(Expr);
				NT.push(TERMINAL);
				T.push("-");
				value = fun(NT, line, T);
				if (value == del_simbol)
				{
					exprNode->terminal_node = terminalNode;
					terminalNode = nullptr;
					T.pop(), NT.pop(); // одно число не может стоять в скобках по этому Expr считает SimpleExpr и знак а после рекурсивно в Expr перейдет и создаст BufExpr
					value = fun(NT, line, T);
					return value;
				}
				else if (value == err)
				{
					T.pop(), T.push("+");
					value = fun(NT, line, T);
					if (value == del_simbol)
					{
						exprNode->terminal_node = terminalNode;
						terminalNode = nullptr;
						NT.pop(), T.pop();
						value = fun(NT, line, T);
						return value;
					}
					else
						return del_simbol; // если не получилось удалить + а simpleExpr получилось 
				}
				else {
					return err;
				}
			}
			else
			{
				BufExprNode = new ExprNode();
				BufExprNode->simpleexpr_node = simpleexprNode; // тут он должен прикрепить или просто число и знак как обычно или все выражение в скобках которое до этого считывалось
				simpleexprNode = nullptr;
				NT.pop();
				NT.push(Expr);
				NT.push(TERMINAL);
				T.push("-");
				value = fun(NT, line, T);
				if (value == del_simbol)
				{
					T.pop(), NT.pop();
					BufExprNode->terminal_node = terminalNode;
					terminalNode = nullptr;
					if (ExprInSimpleExpr == true) // чтобы при считывании выражения в скобках не портить то что было считано до него 4 + ( а + 6 )
					{
						if (ExprInBrackets == nullptr)
							ExprInBrackets = BufExprNode;
						else
							ExprInBrackets->setExprNode(BufExprNode);
					}
					else {
						exprNode->setExprNode(BufExprNode);
					}
					value = fun(NT, line, T);
					return value;
				}
				else if (value == err)
				{
					T.pop(), T.push("+");
					value = fun(NT, line, T);
					if (value == del_simbol)
					{
						T.pop(), NT.pop();
						BufExprNode->terminal_node = terminalNode;
						if (ExprInSimpleExpr == true) // чтобы при считывании выражения в скобках не портить то что было считано до него 4 + ( а + 6 )
						{
							if (ExprInBrackets == nullptr)
								ExprInBrackets = BufExprNode;
							else
								ExprInBrackets->setExprNode(BufExprNode);
						}
						else {
							exprNode->setExprNode(BufExprNode);
						}
						BufExprNode = nullptr;
						value = fun(NT, line, T);
						return value;
					}
					else {
						if (ExprInSimpleExpr == true) // чтобы при считывании выражения в скобках не портить то что было считано до него 4 + ( а + 6 )
						{
							if (ExprInBrackets == nullptr)
								ExprInBrackets = BufExprNode;
							else
								ExprInBrackets->setExprNode(BufExprNode);
						}
						else {
							exprNode->setExprNode(BufExprNode);
						}
						BufExprNode = nullptr;
						return del_simbol;
					}
				}
				else {
					if (exprNode != nullptr)
					{
						if (ExprInSimpleExpr == true) // чтобы при считывании выражения в скобках не портить то что было считано до него 4 + ( а + 6 )
						{
							if (ExprInBrackets == nullptr)
								ExprInBrackets = BufExprNode;
							else
								ExprInBrackets->setExprNode(BufExprNode);
						}
						else {
							exprNode->setExprNode(BufExprNode);
						}
					}
					else {
						exprNode = new ExprNode();
						exprNode->simpleexpr_node = simpleexprNode;
						simpleexprNode = nullptr;
					}
				}
			}
		}
		else if (value == all_read) {
			if (exprNode != nullptr)
			{
				BufExprNode = new ExprNode();
				BufExprNode->simpleexpr_node = simpleexprNode;

				exprNode->setExprNode(BufExprNode);
			}
			else {
				exprNode = new ExprNode();
				exprNode->simpleexpr_node = simpleexprNode;
			}
		}
		return value;

	case Const:
		NT.pop();
		NT.push(TERMINAL_Const);
		value = fun(NT, line, T);
		if (value != err)
		{
			constNode = new ConstNode();
			constNode->terminal_node = terminalNode;
		}
		return value;
	case End:
		NT.pop();
		NT.push(ID);
		NT.push(TERMINAL);
		T.push("END");
		value = fun(NT, line, T);
		if (value == del_simbol)
		{
			endNode = new EndNode();
			endNode->terminal_node = terminalNode;
			NT.pop();
			value = fun(NT, line, T);
			if (value == all_read)
			{
				endNode->id_node = idNode;
				return all_read;
			}
		}
		return err;
	default:
		break;
	}
}

void Syntax_analys::SetNullptrNodes()
{
	beginNode = nullptr;
	endNode = nullptr;
	descriptionNode = nullptr;
	operatorsNode = nullptr;
	descrNode = nullptr;
	typeNode = nullptr;
	varlistNode = nullptr;
	opNode = nullptr;
	simpleexprNode = nullptr;
	exprNode = nullptr;
	conditionsNode = nullptr;
	relationsoperatorsNode = nullptr;
	idNode = nullptr;
	constNode = nullptr;
	terminalNode = nullptr;

	BufNode = nullptr;
	BufDescriptionNode = nullptr;
	BufVarListNode = nullptr;
	BufExprNode = nullptr;
	BufProgramNode = nullptr;
	BufOpNode = nullptr;
	BufOperatorsNode = nullptr;
	IFOperatorsNode = nullptr;
}

void Syntax_analys::print(ostream& os)
{
	programNode->print(os);
}

void Syntax_analys::setFalseDeleted_simbol()
{
	is_deleted_simbol = false;
}
