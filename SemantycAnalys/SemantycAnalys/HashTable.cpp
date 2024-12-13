#include "HashTable.h"

HashTable::HashTable() {
	d = new Token[1000000];
}

long long HashTable::get_key(const std::string& str) const
{
	long long last = 0;
	for (int i = 0; i < str.size(); ++i)
	{
		long long key = (last * 32 + str[i]) % N;
		last = key;
	}
	return last;
}

bool HashTable::isRepeat(long long key, std::string str) const
{
	if (key >= N)
		throw 1;
	if (str == d[key].value)
		return true;
	return false;
}

bool HashTable::changeType(Token& tk, std::string new_type)
{
	long long key = get_key(tk.value);
	if (d[key].OpType == "") {
		d[key].OpType = new_type;
		return true;
	}
	else {
		return false;
	}
}

std::string HashTable::getType(long long key) const
{
	return d[key].getOpType();
}

void HashTable::add(const Token& tk)
{
	long long key = get_key(tk.value);
	int i = 1;
	bool flag = true;
	while (flag) {
		if (!isRepeat(key, tk.value))
		{
			if (d[key].value == "") {
				d[key] = tk;
				flag = true;
			}
			else {
				key = (key + i) % N;
				flag = false;
			}
		}
		else
			return;

	}
}

long long HashTable::find(Token& tk) const
{
	long long key = get_key(tk.value);
	if (d[key].value == "")
		return -1;
	else {
		for (long long i = key; i != key; i = (i + 1) % N)
			if (d[i].value == tk.value)
				return i;
	}
}

long long HashTable::find(std::string str) const
{
	long long key = get_key(str);
	if (d[key].value == "")
		return -1;
	else {
		if (d[key].value == str)
			return key;
		else
			for (long long i = key + 1; i != key; i = (i + 1) % N)
				if (d[i].value == str)
					return i;
	}
}

void HashTable::print() const
{
	setlocale(LC_ALL, "rus");
	std::ofstream out("output.txt");

	int idx = 0;
	out << "Интекс | Тип | Значение" << std::endl;
	for (int i = 0; i < N; ++i) {
		if (d[i].type != LeksemType::NON && d[i].type != LeksemType::Nope)
			out << idx++ << "  " << d[i] << std::endl;
	}
	out << std::endl << "Плохая лексема" << std::endl;
	for (int i = 0; i < N; ++i) {
		if (d[i].type == LeksemType::Nope)
			out << d[i] << std::endl;
	}
}

void HashTable::del(Token& tk)
{
	long long key = find(tk);
	if (key != -1)
		d[key] = Token();
}