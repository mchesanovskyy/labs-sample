#pragma once
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// Цей мотод використовується для порівняння на рівність 
// двох полів типу string ігноруючи регістр
inline bool IsEqualsIgnoreCase(const string& a, const string& b)
{
	return equal(a.begin(), a.end(), b.begin(), b.end(), [](char a, char b) { return tolower(a) == tolower(b); });
}

inline vector<string> Split(string strToSplit, char delimeter)
{
	stringstream ss(strToSplit);
	string item;
	vector<string> splittedStrings;
	while (getline(ss, item, delimeter))
	{
		splittedStrings.push_back(item);
	}
	return splittedStrings;
}

inline bool contains(char& source, char values[]) {
	for (int i = 0; i < (sizeof(values) / sizeof(*values)); i++)
	{
		if (values[i] == source) {
			return true;
		}
	}
	return false;
}