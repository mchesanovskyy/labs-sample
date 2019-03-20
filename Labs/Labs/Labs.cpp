#include <iostream>
#include <iomanip>
#include <locale>;
#include "windows.h";
#include "Labs\LabFactory.h"

using namespace std;

// Виводить список доступних ЛР
// Використано бібліотеку iomanip (left, right, setw) для форматування
// https://cpppatterns.com/patterns/write-data-in-columns.html
void help() {
	auto labs = LabFactory::GetInstance().GetLabs();
	string nameLabel = "Lab Name";
	string descLabel = "Description";
	int maxAllowedLength = 60;
	int maxNameLen = nameLabel.length();
	int maxDescLen = descLabel.length();
	for (size_t i = 0; i < labs.size(); i++)
	{
		int nameLen = labs[i]->GetName().length();
		if (maxNameLen < nameLen && nameLen < maxAllowedLength) {
			maxNameLen = nameLen;
		}

		int descLen = labs[i]->GetDescription().length();
		if (maxDescLen < descLen && descLen < maxAllowedLength) {
			maxDescLen = descLen;
		}
	}

	cout << right << setw(maxNameLen) << nameLabel << "\t" << left << setw(maxDescLen) << descLabel << endl;
	for (size_t i = 0; i < labs.size(); i++)
	{
		cout << right << setw(maxNameLen) << labs[i]->GetName() << "\t" << left << setw(maxDescLen) << labs[i]->GetDescription() << endl;
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "Enter 'help' to see a list of available labs" << endl;
	while (true)
	{
		cout << "=> Please enter LR name: ";
		string command;

		// Далі використовується метод getline замість звичного 'cin >>'
		// оскільки останній запис буде читати з консолі до першого пробілу,
		// засіть того, щоб читати весь рядок.
		// Детальніше: http://www.cplusplus.com/forum/beginner/213159/
		getline(std::cin, command);
		
		if (IsEqualsIgnoreCase(command, "help")) {
			help();
			continue;
		}

		Lab* selectedLab = LabFactory::GetInstance().GetLabByName(command); // знаходимо ЛР
		
		// перевіряємо чи знайдено ЛР
		if (selectedLab == nullptr) {
			cout << "LR not found!" << endl;
		}
		else {
			// Якщо знайдено - даємо на виконання
			selectedLab->Execute(); 
		}
	}
}