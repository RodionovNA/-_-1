/*
Лексический анализ.
Требования:
0) Все классы в отдельных файлах
1) Текс кода должен быть во входном файле(не вводим в консоль), результат-в выходном файле
2) Текс считывается не более одного раза
3) Реализация КА
4) Реализация хеш-таблицы(отдельный класс)
токен типа pair не делать
5) Обязательно метод разрешения коллизий(метод цепочек или открытая адресация)
6) Если метод цепочек, то реализуем список
7) В выходном файле печатаем хеш-таблицу
формат: Индекс|Тип|Лексема
8) Если плохая лексема(ошибка), ее не сохраняем в хеш-таблицу
9) Плохая лексема|Нераспознаная
печатать после таблицы
10) Проект нужно загрузить в репозиторий

Синтаксический алализ.
Требования:
1) Синтаксический анализоатор должен быть реализован в виде отдельного классса.
2) Повторное считывание исходного текста не допускается.
3) Программа должна выдавать сообщения о встретившихся синтаксических ошибках. Сообщения должны казывать на
место во входном файле, где эта ошибка была обнаружена. Сообщения должны  быть максимально информативными.
4) Программа должна явно генерировать дерево разбора и выводить его в выходной файл.
5) Если использумый алгоритм синтаксического анализа требует преобразования грамматики, необходимо проделать это преобразование.
6) Придерживается строго той грамматики, которая дана в вашем варианте. Никаких лишних констукций не выдумываем.

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
Id -> id_name слово состоящее из заглаыных и строчных букв латинского алфавита
Const -> int_num слово, представляющее собой целое число

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
		cout << "Успешный синтаксический анализ." << endl;
		ofstream out("output_syn.txt");
		if (out.is_open())
			syn->print(out);
		if (!syn->programNode->setType(go.table))
			cout << "Ошибка ! - неверно указан тип PROGRAM" << endl;
		else {
			try {
				ofstream out("output_semant.txt");
				out << syn->programNode->setTr(go.table);
				out.close();
				cout << "Успешный семантический анализ." << endl;
			}
			catch (...) {
				cout << "Ошибка ! Использована неинициализированная переменная ";
			}
		}
		out.close();
		
	}
}