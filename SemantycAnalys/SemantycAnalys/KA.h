#pragma once
#include "HashTable.h"
#include "Syntax_analys.h"
#include <iostream>

class KA {

public:
    HashTable table;
    char ch = ' ';
    int q = 0;
    int cnt_line = 0;

public:


    bool isError = false;

    KA() = default;

    bool is_num(int val);

    bool is_alf(char ch);

    void default_check(std::queue<Token>& line, char ch, bool& is_trash, bool& write_name, bool& write_num, int& q, std::string& trash,
        std::string& cash, Syntax_analys*& syn);

    void create_table(Syntax_analys*& syn);

    void print();

    void clearQ(std::queue<Token>& q);

};