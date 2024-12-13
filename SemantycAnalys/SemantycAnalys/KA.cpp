#include "KA.h"

void KA::create_table(Syntax_analys*& syn)
{
    setlocale(LC_ALL, "Russian");
    std::ifstream in("input.txt");
    if (!in.is_open()) {
        throw std::runtime_error("Error. File not found!");
    }

    char ch;
    std::string trash;
    std::string cash;
    bool write_num = false;
    bool write_name = false;
    bool is_trash = false;
    int q = 0;
    Token tk;
    stack<N> stN;
    stN.push(Program);
    stack<string> T;
    queue<Token> line;
    while (in.get(ch) && !isError) {

        cash += ch;
        switch (q)
        {
        case -1:
            default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
            break;
        case 0:
            switch (ch)
            {
            case ' ':
                cash = "";
                break;
            case '\n':
                cnt_line++;
                if (syn->fun(stN, line, T) == err)
                {
                    if (line.empty())
                        cout << "Ошибка в строке номер  " << cnt_line << "  ! Добавьте недостающие символы" << endl;
                    else {
                        cout << "Ошибка в строке номер " << cnt_line << "  ! Удалите лишние символы ";
                    }
                    isError = true;
                }
                syn->setFalseDeleted_simbol();
                clearQ(line);
                syn->SetNullptrNodes();
                cash = "";
                break;

            case 'P': // -> PROGRAM
                q = 1;
                break;
            case '(': // -> (
                tk = Token(LeksemType::Brackets, "(");
                table.add(tk);
                line.push(tk);
                cash = "";
                q = 0;
                break;
            case ',':
                tk = Token(LeksemType::Operator, ",");
                table.add(tk);
                line.push(tk);
                cash = "";
                q = 0;
                break;
            case ')':
                tk = Token(LeksemType::Brackets, ")");
                table.add(tk);
                line.push(tk);
                q = 0;
                cash = "";
                break;
            case 'I': // -> IF.eps.
                q = 18;
                break;
            case 'T': // -> THEN.eps.
                q = 14;
                break;
            case '+': // -> +
                q = 0;
                tk = Token(LeksemType::Operator, "+");
                table.add(tk);
                line.push(tk);
                cash = "";
                break;
            case '-': // -> -
                q = 0;
                tk = Token(LeksemType::Operator, "-");
                table.add(tk);
                line.push(tk);
                cash = "";
                break;
            case 'E': // -> E - > ELSE.eps. | END.eps.
                q = 8;
                break;
            case '=':
                q = 0;
                tk = Token(LeksemType::Equal, "=");
                table.add(tk);
                line.push(tk);
                cash = "";
                break;
            case '.':
                q = 20; // . -> .EQ. | .NE. | .GT. | .L -> .LE. | .LT.
                break;

            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 1:
            switch (ch)
            {
            case 'R':
                q = 2;
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 2:
            switch (ch)
            {
            case 'O':
                q = 3;
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 3:
            switch (ch)
            {
            case 'G':
                q = 4;
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 4:
            switch (ch)
            {
            case 'R':
                q = 5;
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 5:
            switch (ch)
            {
            case 'A':
                q = 6;
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 6:
            switch (ch)
            {
            case 'M':
                q = 7;
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 7:
            switch (ch)
            {
            case ' ': // -> PROGRAM
            case '\n':

                tk = Token(LeksemType::KeyWord, "PROGRAM");
                line.push(tk);
                table.add(tk);
                if (ch == '\n')
                {
                    cnt_line++;
                    if (syn->fun(stN, line, T) == err)
                    {
                        if (line.empty())
                            cout << "Ошибка в строке номер  " << cnt_line << "  ! Добавьте недостающие символы" << endl;
                        else {
                            cout << "Ошибка в строке номер " << cnt_line << "  ! Удалите лишние символы ";
                        }
                        isError = true;
                    }
                    syn->setFalseDeleted_simbol();
                    clearQ(line);
                    syn->SetNullptrNodes();
                }
                q = 0;
                cash = "";
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 8:
            switch (ch)
            {
            case 'N':
                q = 9;
                break;
            case 'L':
                q = 11;
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 9:
            switch (ch)
            {
            case 'D':
                q = 10;
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 10: // -> END
            switch (ch)
            {
            case ' ':
            case '\n':
                tk = Token(LeksemType::KeyWord, "END");
                table.add(tk);
                line.push(tk);
                if (ch == '\n')
                {
                    cnt_line++;
                    if (syn->fun(stN, line, T) == err)
                    {
                        if (line.empty())
                            cout << "Ошибка в строке номер  " << cnt_line << "  ! Добавьте недостающие символы" << endl;
                        else {
                            cout << "Ошибка в строке номер " << cnt_line << "  ! Удалите лишние символы ";
                        }
                        isError = true;
                    }
                    syn->setFalseDeleted_simbol();
                    clearQ(line);
                    syn->SetNullptrNodes();
                }
                cash = "";
                q = 0;
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 11:
            switch (ch)
            {
            case 'S':
                q = 12;
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 12:
            switch (ch)
            {
            case 'E':
                q = 13;
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 13: // -> ELSE
            switch (ch)
            {
            case ' ':
            case '\n':
                q = 3;
                tk = Token(LeksemType::KeyWord, "ELSE");
                table.add(tk);
                line.push(tk);
                if (ch == '\n')
                {
                    cnt_line++;
                    if (syn->fun(stN, line, T) == err)
                    {
                        if (line.empty())
                            cout << "Ошибка в строке номер  " << cnt_line << "  ! Добавьте недостающие символы" << endl;
                        else {
                            cout << "Ошибка в строке номер " << cnt_line << "  ! Удалите лишние символы ";
                        }
                        isError = true;
                    }
                    syn->setFalseDeleted_simbol();
                    clearQ(line);
                    syn->SetNullptrNodes();
                }
                cash = "";
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 14:
            switch (ch)
            {
            case 'H':
                q = 15;
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 15:
            switch (ch)
            {
            case 'E':
                q = 16;
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 16:
            switch (ch)
            {
            case 'N':
                q = 17;
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 17: // -> THEN
            switch (ch)
            {
            case ' ':
            case '\n':
                tk = Token(LeksemType::KeyWord, "THEN");
                table.add(tk);
                line.push(tk);
                if (ch == '\n')
                {
                    cnt_line++;
                    if (syn->fun(stN, line, T) == err)
                    {
                        if (line.empty())
                            cout << "Ошибка в строке номер  " << cnt_line << "  ! Добавьте недостающие символы" << endl;
                        else {
                            cout << "Ошибка в строке номер " << cnt_line << "  ! Удалите лишние символы ";
                        }
                        isError = true;
                    }
                    syn->setFalseDeleted_simbol();
                    clearQ(line);
                    syn->SetNullptrNodes();
                }
                cash = "";
                q = 0;
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 18:
            switch (ch)
            {
            case 'N':
                q = 30;
                break;
            case 'F':
                q = 19;
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 19: // -> IF
            switch (ch)
            {
            case ' ':
            case '\n':
                tk = Token(LeksemType::KeyWord, "IF");
                table.add(tk);
                line.push(tk);
                if (ch == '\n')
                {
                    cnt_line++;
                    if (syn->fun(stN, line, T) == err)
                    {
                        if (line.empty())
                            cout << "Ошибка в строке номер  " << cnt_line << "  ! Добавьте недостающие символы" << endl;
                        else {
                            cout << "Ошибка в строке номер " << cnt_line << "  ! Удалите лишние символы ";
                        }
                        isError = true;
                    }
                    syn->setFalseDeleted_simbol();
                    clearQ(line);
                    syn->SetNullptrNodes();
                }
                cash = "";
                q = 0;
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 20:
            switch (ch)
            {
            case 'E':
                q = 21;
                break;
            case 'N':
                q = 23;
                break;
            case 'G':
                q = 25;
                break;
            case 'L':
                q = 27;
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 21:
            switch (ch)
            {
            case 'Q':
                q = 22;
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 22: // -> .EQ.
            switch (ch)
            {
            case '.':
            case '\n':
                q = 0;
                tk = Token(LeksemType::Comparator, ".EQ.");
                table.add(tk);
                line.push(tk);
                if (ch == '\n')
                {
                    cnt_line++;
                    if (syn->fun(stN, line, T) == err)
                    {
                        if (line.empty())
                            cout << "Ошибка в строке номер  " << cnt_line << "  ! Добавьте недостающие символы" << endl;
                        else {
                            cout << "Ошибка в строке номер " << cnt_line << "  ! Удалите лишние символы ";
                        }
                        isError = true;
                    }
                    syn->setFalseDeleted_simbol();
                    clearQ(line);
                    syn->SetNullptrNodes();
                }
                cash = "";
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 23:
            switch (ch)
            {
            case 'E':
                q = 24;
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 24: // -> .NE.
            switch (ch)
            {
            case '.':
            case '\n':
                q = 0;
                tk = Token(LeksemType::Comparator, ".NE.");
                table.add(tk);
                line.push(tk);
                if (ch == '\n')
                {
                    cnt_line++;
                    if (syn->fun(stN, line, T) == err)
                    {
                        if (line.empty())
                            cout << "Ошибка в строке номер  " << cnt_line << "  ! Добавьте недостающие символы" << endl;
                        else {
                            cout << "Ошибка в строке номер " << cnt_line << "  ! Удалите лишние символы ";
                        }
                        isError = true;
                    }
                    syn->setFalseDeleted_simbol();
                    clearQ(line);
                    syn->SetNullptrNodes();
                }
                cash = "";
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 25:
            switch (ch)
            {
            case 'T':
                q = 26;
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 26: // -> .GT.
            switch (ch)
            {
            case '.':
            case '\n':
                q = 0;
                tk = Token(LeksemType::Comparator, ".GT.");
                table.add(tk);
                line.push(tk);
                if (ch == '\n')
                {
                    cnt_line++;
                    if (syn->fun(stN, line, T) == err)
                    {
                        if (line.empty())
                            cout << "Ошибка в строке номер  " << cnt_line << "  ! Добавьте недостающие символы" << endl;
                        else {
                            cout << "Ошибка в строке номер " << cnt_line << "  ! Удалите лишние символы ";
                        }
                        isError = true;
                    }
                    syn->setFalseDeleted_simbol();
                    clearQ(line);
                    syn->SetNullptrNodes();
                }
                cash = "";
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 27:
            switch (ch)
            {
            case 'E':
                q = 28;
                break;
            case 'T':
                q = 29;
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 28: // -> .LE.
            switch (ch)
            {
            case '.':
            case '\n':
                tk = Token(LeksemType::Comparator, ".LE.");
                table.add(tk);
                line.push(tk);
                if (ch == '\n')
                {
                    cnt_line++;
                    if (syn->fun(stN, line, T) == err)
                    {
                        if (line.empty())
                            cout << "Ошибка в строке номер  " << cnt_line << "  ! Добавьте недостающие символы" << endl;
                        else {
                            cout << "Ошибка в строке номер " << cnt_line << "  ! Удалите лишние символы ";
                        }
                        isError = true;
                    }
                    syn->setFalseDeleted_simbol();
                    clearQ(line);
                    syn->SetNullptrNodes();
                }
                cash = "";
                q = 0;
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 29: // -> .LT.
            switch (ch)
            {
            case '.':
            case '\n':
                tk = Token(LeksemType::Comparator, ".LT.");
                table.add(tk);
                line.push(tk);
                if (ch == '\n')
                {
                    cnt_line++;
                    if (syn->fun(stN, line, T) == err)
                    {
                        if (line.empty())
                            cout << "Ошибка в строке номер  " << cnt_line << "  ! Добавьте недостающие символы" << endl;
                        else {
                            cout << "Ошибка в строке номер " << cnt_line << "  ! Удалите лишние символы ";
                        }
                        isError = true;
                    }
                    syn->setFalseDeleted_simbol();
                    clearQ(line);
                    syn->SetNullptrNodes();
                }
                cash = "";
                q = 0;
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 30:
            switch (ch)
            {
            case 'T':
                q = 31;
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 31:
            switch (ch)
            {
            case 'E':
                q = 32;
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 32:
            switch (ch)
            {
            case 'G':
                q = 33;
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 33:
            switch (ch)
            {
            case 'E':
                q = 34;
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 34:
            switch (ch)
            {
            case 'R':
                q = 35;
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        case 35:
            switch (ch)
            {
            case ' ':
            case '\n':
                tk = Token(LeksemType::KeyWord, "INTEGER");
                table.add(tk);
                line.push(tk);
                if (ch == '\n')
                {
                    stN.push(Program);
                    cnt_line++;
                    if (syn->fun(stN, line, T) == err)
                    {
                        if (line.empty())
                            cout << "Ошибка в строке номер  " << cnt_line << "  ! Добавьте недостающие символы" << endl;
                        else {
                            cout << "Ошибка в строке номер " << cnt_line << "  ! Удалите лишние символы ";
                        }
                        isError = true;
                    }
                    syn->setFalseDeleted_simbol();
                    clearQ(line);
                    syn->SetNullptrNodes();
                }
                cash = "";
                q = 0;
                break;
            default:
                default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
                break;
            }
            break;
        default:
            default_check(line, ch, is_trash, write_name, write_num, q, trash, cash, syn);
            break;
        }
    }

    if (cash == "ELSE" || cash == "IF" || cash == "THEN" || cash == "END" || cash == "INTEGER")
    {
        tk = Token(LeksemType::KeyWord, cash);
        table.add(tk);
        line.push(tk);
        if (ch == '\n')
        {
            stN.push(Program);
            cnt_line++;
            if (syn->fun(stN, line, T) == err)
            {
                if (line.empty())
                    cout << "Ошибка в строке номер  " << cnt_line << "  ! Добавьте недостающие символы" << endl;
                else {
                    cout << "Ошибка в строке номер " << cnt_line << "  ! Удалите лишние символы ";
                }
                isError = true;
            }
            syn->setFalseDeleted_simbol();
            clearQ(line);
            syn->SetNullptrNodes();
        }
    }
    else if (cash == "(" || cash == ")")
    {
        tk = Token(LeksemType::Brackets, cash);
        table.add(tk);
        line.push(tk);
        cnt_line++;
        if (syn->fun(stN, line, T) == err)
        {
            if (line.empty())
                cout << "Ошибка в строке номер  " << cnt_line << "  ! Добавьте недостающие символы" << endl;
            else {
                cout << "Ошибка в строке номер " << cnt_line << "  ! Удалите лишние символы ";
            }
            isError = true;
        }
        syn->setFalseDeleted_simbol();
        clearQ(line);
        syn->SetNullptrNodes();
    }
    else if (cash == "+" || cash == "-")
    {
        tk = Token(LeksemType::Operator, cash);
        table.add(tk);
        line.push(tk);
        cnt_line++;
        if (syn->fun(stN, line, T) == err)
        {
            if (line.empty())
                cout << "Ошибка в строке номер  " << cnt_line << "  ! Добавьте недостающие символы" << endl;
            else {
                cout << "Ошибка в строке номер " << cnt_line << "  ! Удалите лишние символы ";
            }
            isError = true;
        }
        syn->setFalseDeleted_simbol();
        clearQ(line);
        syn->SetNullptrNodes();
    }
    else if (write_num)
    {
        tk = Token(LeksemType::Const, cash);
        table.add(tk);
        line.push(tk);
        cnt_line++;
        if (syn->fun(stN, line, T) == err)
        {
            if (line.empty())
                cout << "Ошибка в строке номер  " << cnt_line << "  ! Добавьте недостающие символы" << endl;
            else {
                cout << "Ошибка в строке номер " << cnt_line << "  ! Удалите лишние символы ";
            }
            isError = true;
        }
        syn->setFalseDeleted_simbol();
        clearQ(line);
        syn->SetNullptrNodes();
    }
    else if (write_name)
    {
        tk = Token(LeksemType::Id, cash);
        table.add(tk);
        line.push(tk);
        cnt_line++;
        if (syn->fun(stN, line, T) == err)
        {
            if (line.empty())
                cout << "Ошибка в строке номер  " << cnt_line << "  ! Добавьте недостающие символы" << endl;
            else {
                cout << "Ошибка в строке номер " << cnt_line << "  ! Удалите лишние символы ";
            }
            isError = true;
        }
        syn->setFalseDeleted_simbol();
        clearQ(line);
        syn->SetNullptrNodes();
    }
    else if (is_trash)
    {
        table.add(Token(LeksemType::Nope, cash));
    }
    else if (cash == ".EQ." || cash == ".NE." || cash == ".GT." || cash == ".LE." || cash == ".LT.")
    {
        tk = Token(LeksemType::Comparator, cash);
        table.add(tk);
        line.push(tk);
        cnt_line++;
        if (syn->fun(stN, line, T) == err)
        {
            if (line.empty())
                cout << "Ошибка в строке номер  " << cnt_line << "  ! Добавьте недостающие символы" << endl;
            else {
                cout << "Ошибка в строке номер " << cnt_line << "  ! Удалите лишние символы ";
            }
            isError = true;
        }
        syn->setFalseDeleted_simbol();
        clearQ(line);
        syn->SetNullptrNodes();
    }

    in.close();
}

void KA::print()
{
    table.print();
}

void KA::clearQ(queue<Token>& q)
{
    while (!q.empty()) {
        q.pop();
    }
}

bool KA::is_num(int val)
{
    for (int i = '0'; i <= '9'; ++i)
        if (val == i)
            return true;
    return false;
}

bool KA::is_alf(char ch)
{
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

void KA::default_check(queue<Token>& line, char ch, bool& is_trash, bool& write_name, bool& write_num, int& q, std::string& trash,
    std::string& cash, Syntax_analys*& syn)
{
    if (ch == ' ' || ch == '\n') {
        cash.pop_back();
        if (write_name) {
            Token tk(LeksemType::Id, cash);
            line.push(tk);

            if (ch == '\n')
            {
                stack<N> stN;
                stN.push(Program);
                stack<string> T;
                cnt_line++;
                if (syn->fun(stN, line, T) == err)
                {
                    if (line.empty())
                        cout << "Ошибка в строке номер  " << cnt_line << "  ! Добавьте недостающие символы" << endl;
                    else {
                        cout << "Ошибка в строке номер " << cnt_line << "  ! Удалите лишние символы ";
                    }
                    isError = true;
                }
                syn->setFalseDeleted_simbol();
                clearQ(line);
                syn->SetNullptrNodes();
            }
            table.add(tk);
        }
        if (write_num) {
            Token tk(LeksemType::Const, cash);
            line.push(tk);
            if (ch == '\n')
            {
                stack<N> stN;
                stN.push(Program);
                stack<string> T;
                this->cnt_line++;
                if (syn->fun(stN, line, T) == err)
                {
                    if (line.empty())
                        cout << "Ошибка в строке номер  " << cnt_line << "  ! Добавьте недостающие символы" << endl;
                    else {
                        cout << "Ошибка в строке номер " << cnt_line << "  ! Удалите лишние символы ";
                    }
                    isError = true;
                }
                syn->setFalseDeleted_simbol();
                clearQ(line);
                syn->SetNullptrNodes();
            }
        }
        if (is_trash) {
            table.add(Token(LeksemType::Nope, cash));
        }

        cash = "";
        write_name = false;
        write_num = false;
        is_trash = false;
        q = 0;
        return;
    }
    else if (!is_trash && is_num(ch) && !write_name) {
        write_num = true;
    }
    else if (!is_trash && is_alf(ch) && !write_num) {
        write_name = true;
    }

    /*else if (!is_trash && (write_name || write_num) && (ch == ')' || ch == '(')) {
        Token bracket(LeksemType::Brackets, cash.back());
        line.push();
        table.add(bracket);
        cash.pop_back();
        if (write_name)
            table.add(Token(LeksemType::Id, cash));
        else if (write_num)
           table.add(Token(LeksemType::Const, cash));

        cash = "";
        write_name = false;
        write_num = false;
        is_trash = false;
        q = 0;
        return;
    }*/
    else {
        is_trash = true;
        write_name = false;
        write_num = false;
    }

    q = -1;
}
