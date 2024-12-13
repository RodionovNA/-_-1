/*
����������� ������.
����������:
0) ��� ������ � ��������� ������
1) ���� ���� ������ ���� �� ������� �����(�� ������ � �������), ���������-� �������� �����
2) ���� ����������� �� ����� ������ ����
3) ���������� ��
4) ���������� ���-�������(��������� �����)
����� ���� pair �� ������
5) ����������� ����� ���������� ��������(����� ������� ��� �������� ���������)
6) ���� ����� �������, �� ��������� ������
7) � �������� ����� �������� ���-�������
������: ������|���|�������
8) ���� ������ �������(������), �� �� ��������� � ���-�������
9) ������ �������|�������������
�������� ����� �������
10) ������ ����� ��������� � �����������

�������������� ������.
����������:
1) �������������� ����������� ������ ���� ���������� � ���� ���������� �������.
2) ��������� ���������� ��������� ������ �� �����������.
3) ��������� ������ �������� ��������� � ������������� �������������� �������. ��������� ������ �������� ��
����� �� ������� �����, ��� ��� ������ ���� ����������. ��������� ������  ���� ����������� ��������������.
4) ��������� ������ ���� ������������ ������ ������� � �������� ��� � �������� ����.
5) ���� ����������� �������� ��������������� ������� ������� �������������� ����������, ���������� ��������� ��� ��������������.
6) �������������� ������ ��� ����������, ������� ���� � ����� ��������. ������� ������ ���������� �� ����������.

Program -> Begin Description Operators End
Begin -> PROGRAM ID
End -> END Id
Description -> Descr | Descr Description
Operators -> Op | Op Operators
Descr -> Type VarList
Type -> INTEGER
VarList -> Id | Id, VarList
Op -> Id = Expr | IF Conditions THEN Operators | IF Conditions THEN Operators ELSE Operators
SimpleExpr -> Id | Const | ( Expr )
Expr -> SimpleExpr | SimpleExpr + Expr | SimpleExpr - Expr
Conditions -> Expr RelationsOperators Expr
RelationsOperators -> .EQ. | .NE. | .GT. | .LE. | .LT.
Id -> id_name ����� ��������� �� ��������� � �������� ���� ���������� ��������
Const -> int_num �����, �������������� ����� ����� �����

*/

#include <iostream>
#include "KA.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	KA go;
	Syntax_analys* syn = new Syntax_analys();
	go.create_table(syn);
	go.print();
	if (go.isError == false)
	{
		cout << "�������� �������������� ������." << endl;
		ofstream out("output_syn.txt");
		if (out.is_open())
			syn->print(out);
		if (!syn->programNode->setType(go.table))
			cout << "������ ! - ������� ������ ��� PROGRAM" << endl;
		else {
			try {
				ofstream out("output_semant.txt");
				out << syn->programNode->setTr(go.table);
				out.close();
				cout << "�������� ������������� ������." << endl;
			}
			catch (...) {
				cout << "������ ! ������������ �������������������� ���������� ";
			}
		}
		out.close();
		
	}
}