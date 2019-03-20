#pragma once
#include <vector>
#include "Abstracts\Lab.h"
#include "Implementations\Lab1.h"
#include "Implementations\Lab2.h"

using namespace std;

// Даний клас є реалізацією шаблону проектування Одинак(Singleton)
// Детальніше про даний шаблон: "https://uk.wikipedia.org/wiki/Одинак_(шаблон_проектування)"
// Реалізацію методів дивіться в LabFactory.cpp файлі
class LabFactory
{
private:
	static LabFactory _instance;

	LabFactory() // конструктор
	{
		// Цей метод виконається тільки один раз, при першому 
		// виклику зверненні до статичного методу GetInstance() і проведе ініціалізацію лабораторних робіт.
		InitLabs();
	}

	~LabFactory() // деструктор
	{
		ClearLabs();
	}

	// Всі лaбораторні роботи зберігаються в статичному векторі _labs, ініціалізація
	// якого відбувається в приватному статичному методі InitLabs.
	vector<Lab*> _labs;

	// Цей метод виконуватиметься в конструкторі при ініціалізації класу
	void InitLabs();
	// Цей метод виконуватиметься в деструкторі для вивільнення всіх ЛР.
	void ClearLabs();

public:
	static LabFactory& GetInstance();

	// Цей публічний статичний метод, який повертає одну з 
	// реалізацій(нащадків) класу Lab по назві лабораторної роботи.
	// Більше про статичні методи читайте тут:
	//https://www.learncpp.com/cpp-tutorial/812-static-member-functions/
	Lab* GetLabByName(string labName);

	// Повертає копію масиву з лабораторними роботами.
	vector<Lab*> GetLabs();
};
