#include "Header.h"
#include <conio.h>
#include <iostream>
#include <string>

using namespace Program;
using namespace std;

int		main(void)
{
	char	usAnswer;
	Person	manTmp,*manPointer, *dopPointer;
	Using	helpTmp, *pointerTmp;

	manPointer = &manTmp;
	pointerTmp = &helpTmp;
	while (true)
	{
		cout << "Choose the action " << endl
			<< "1 > Hire employee" << endl
			<< "2 > Fire employee" << endl
			<< "3 > See all employees" << endl
			<< "0 > Exit " << endl;
		usAnswer = _getch();
		if (usAnswer == '1')
		{
			manPointer = pointerTmp->hire_person(manPointer);
			system("cls");
			cout << "Done!" << endl;

			continue;
		}
		else if (usAnswer == '2')
		{
			manPointer = pointerTmp->fire_person(manPointer);
			continue;
		}
		else if (usAnswer == '3')
		{
			int		i = -1;

			dopPointer = manPointer;
			if (perNumber <= 0)
				cout << "There is no employees yet!" << endl;
			else
				while (++i < perNumber)
				{
					cout << "Emloyee #" << i + 1 << ":" << endl
						<< "Name: " << dopPointer->getName() << endl
						<< "Position: " << dopPointer->getPosition() << endl
						<< "Salary: " << dopPointer->getSalary() << endl
						<< "Premium: " << dopPointer->getPremium() << endl
						<< "Wages rate: " << dopPointer->getWages() << endl
						<< "______________________________________" << endl;
					dopPointer++;
				}
		}
		else if (usAnswer == '0')
			break ;
		else
			cout << "Incorrect input!Try again." << endl;
	}
	if (delFlag)
		pointerTmp->mem_del(manPointer);
	return (0);
}