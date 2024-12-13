#include "Token.h"

bool Token::operator==(LeksemType& op) const
{
    if (this->type == type && value == value)
        return true;
    return false;
}

bool Token::operator==(std::string str) const
{
    if (value == str)
        return true;
    return false;
}

std::string Token::getOpType() const
{
    return OpType;
}

LeksemType Token::getType() const
{
    return type;
}

std::string Token::getValue() const
{
    return value;
}
