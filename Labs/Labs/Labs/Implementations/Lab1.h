#pragma once
#include <iostream>
#include "../Abstracts/Lab.h"
#include "../Helpers/helpers.h"

using namespace std;

class Lab1 : public Lab
{
public:
	// вказуємо назву для ЛР1
	virtual string GetName() {
		return "lab 1";
	}

	// вказуємо опис для ЛР1
	virtual string GetDescription() {
		return "Check whether a phrase is palindrome or not";
	}

	// Задаємо реалізацію для ЛР1
	virtual void Execute() {
		char extraSymbols[] = { ' ', ',', '!', '.', '?' };

		cout << "Please enter any phase: ";
		string value;
		getline(cin, value);

		string formattedValue = remove(value, extraSymbols);
		string reversed = reverse(formattedValue);

		cout << "Entered phase:  " << value << endl;
		cout << "Formatted phase:" << formattedValue << endl;
		cout << "Reversed phase: " << reversed << endl;
		cout << "Is Palindrome:  " << std::boolalpha << IsEqualsIgnoreCase(formattedValue, reversed) << endl;
	}

	string remove(string& str, char charsToRemove[])
	{
		string newStr = "";
		for (int i = 0; i < str.length(); i++)
		{
			if (!contains(str[i], charsToRemove)) {
				newStr += str[i];
			}
		}
		return newStr;
	}

	string reverse(string& str)
	{
		string reversedStr = "";
		for (int i = str.length() - 1; i >= 0; i--)
			reversedStr += str[i];

		return reversedStr;
	}
};