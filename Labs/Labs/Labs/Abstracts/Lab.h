#pragma once
#include <string>
using namespace std;

// Клас Lab є абстрактним, оскільки він має абстрактні методи 
// (тобто, ті, що не мають реалізації; на це вказує virtual ... () = 0;)
// Більше про абстрактний клас можете прочитати тут: 
// https://en.wikibooks.org/wiki/C%2B%2B_Programming/Classes/Abstract_Classes
// http://www.cplusplus.com/doc/tutorial/polymorphism/
class Lab
{
public:
	virtual string GetName() = 0;
	virtual string GetDescription() = 0;
	virtual void Execute() = 0;
};