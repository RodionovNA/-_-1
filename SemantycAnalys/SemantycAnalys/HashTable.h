#pragma once
#include "Token.h"

class HashTable
{
private:
	const int N = 10000;
	Token* d;
public:
	HashTable();

	long long get_key(const std::string& str) const;

	bool isRepeat(long long key, std::string str) const;

	bool changeType(Token& tk, std::string new_type);

	std::string getType(long long key) const;

	void add(const Token& tk);

	long long find(Token& tk) const;

	long long find(std::string str) const;

	void print() const;

	void del(Token& tk);
};