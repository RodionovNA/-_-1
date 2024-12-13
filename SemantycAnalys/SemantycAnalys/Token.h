#pragma once
#include <string>
#include <fstream>
#include <queue>
#include <stack>


enum class LeksemType {
    NON, // по умполчанию
    Nope, // нераспознанная лексема
    KeyWord, // Program, Begin, INTEGER, ...
    Comparator, // > < == !=
    Brackets,
    Id, // name
    Const, // number
    Equal, // =
    Operator, // + - *
};

class Token {
    friend class HashTable;

public:
    Token() = default;
    Token(LeksemType type, std::string val) : type(type), value(val) {}
    Token(LeksemType type, char ch) : type(type), value(std::string(1, ch)) {}
    friend std::ostream& operator<<(std::ostream& os, const Token& tk) {
        switch (tk.type)
        {
        case LeksemType::Nope:
            os << tk.value;
            break;
        case LeksemType::KeyWord:
            os << "KeyWord" << " " << tk.value;
            break;
        case LeksemType::Comparator:
            os << "Comparator" << " " << tk.value;
            break;
        case LeksemType::Brackets:
            os << "Brackets" << " " << tk.value;
            break;
        case LeksemType::Id:
            os << "Id" << " " << tk.value;
            break;
        case LeksemType::Const:
            os << "Const" << " " << tk.value;
            break;
        case LeksemType::Equal:
            os << "Equal" << " " << tk.value;
            break;
        case LeksemType::Operator:
            os << "Operator" << " " << tk.value;
            break;
        default:
            break;
        }
        return os;
    }
    bool operator ==(LeksemType& op) const;
    bool operator ==(std::string str) const;
    std::string getOpType() const;
    LeksemType getType() const;
    std::string getValue() const;
private:
    LeksemType type = LeksemType::NON;
    std::string value = "";
    std::string OpType = "";
};