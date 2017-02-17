#include "Stack.h"
#include <conio.h>
#include <iostream>
#include <string>
#include <ctime>

using namespace Program;
using namespace std;

void	output(int i, int j)
{
	if (i == 0)
		cout << "Invalid data! Please, try again" << endl;
	else if (i == 1)
	{
		system("cls");
		cout << "Done!" << endl;
	}
	else if (i == 2)
	{
		system("cls");
		cout << " 1 > Display a first-class carriages" << endl
			<< " 2 > Display a second-class carriages" << endl
			<< " 3 > Display the amount of first-class carriages" << endl
			<< " 4 > Display the amount of second-class carriages" << endl << endl
			<< " Press any key to come back..." << endl;
		_getch();
		system("cls");
	}
	else if (i == 3)
	{
		system("cls");
		cout << " 1 > Display the entire train." << endl
			<< " 2 > Display the amount of carriages in the train" << endl
			<< " 3 > Sort carriages by types" << endl << endl
			<< " Press any key to come back..." << endl;
		_getch();
		system("cls");
	}
	if (j == 1)
		cout << "Select the following action (i - watch info/ e - exit)" << endl;
}

void	display(Stack* pointer)
{
	int		i = 0;

	if (pointer == NULL)
	{
		cout << "Train is empty!" << endl;
		return;
	}
	while (pointer != NULL)
	{
		if (++i % 7 == 0)
			cout << endl;
		Carriage car = (*pointer).Get_obj();
		cout << car.getType() << "{" << car.getSN() << "}";
		pointer = (*pointer).Peek();
		if (pointer == NULL) {
			break;
		}
		cout << " - ";
	}
	cout << endl;
}

Stack	random_fill(Stack train)
{
	int		i = -1, size = 10 + rand() % 10, m;

	while (++i < size)
	{
		m = rand() % 1000;
		if (m % 2 == 0)
			train.Push(Carriage("1C"));
		else
			train.Push(Carriage("2C"));
	}
	return (train);
}

Stack	fill_by_hand(Stack train)
{
	int		i = -1;
	char	answer;

	cout << "Enter the class of carriage separate by enter (1 -first class/ 2 - second class/ e - exit)" << endl;
	while (1)
	{
		answer = _getch();
		cout << answer << endl;
		if (!(answer == '1' || answer == '2' || answer == 'e' || answer == 'E'))
		{
			output(0, 0);
			continue;
		}
		else if (answer == '1')
			train.Push(Carriage("1C"));
		else if (answer == '2')
			train.Push(Carriage("2C"));
		else if (answer == 'e' || answer == 'E')
			break;
	}
	return (train);
}

int		main(int argc, char** argv)
{
	char	answer;
	Stack	train, fs_class, sc_class;

	srand(time(NULL));
	cout << "Would you like to fill stack by yourself or automatically? (y/a)" << endl;
	while (1)
	{
		answer = _getch();
		cout << answer << endl;
		if (!(answer == 'a' || answer == 'A' || answer == 'y' || answer == 'Y'))
		{
			output(0, 0);
			continue;
		}
		break;
	}
	if (answer == 'a' || answer == 'A')
		train = random_fill(train);
	else
		train = fill_by_hand(train);
	output(1, 1);
	while (1)
	{
		answer = _getch();
		cout << answer << endl;
		if (answer == 'i' || answer == 'I')
			output(3, 1);
		else if (answer == '1')
			display(train.Peek());
		else if (answer == '2')
			cout << "Amount carriages in a train > " << train.Amount() << endl;
		else if (answer == '3')
		{
			while (train.Peek() != NULL)
			{
				Carriage car = train.Pop();
				if (car.getType() == "1C")
					fs_class.Push(car);
				else
					sc_class.Push(car);
			}
			output(1, 1);
			break ;
		}
		else if (answer == 'e' || answer == 'E')
			exit(1);
		else
			output(0, 0);
	}
	while (1)
	{
		answer = _getch();
		cout << answer << endl;
		if (answer == 'i' || answer == 'I')
			output(2, 1);
		else if (answer == '1')
			display(fs_class.Peek());
		else if (answer == '2')
			display(sc_class.Peek());
		else if (answer == '3')
			cout << "Amount carriages of first class in a train > " << fs_class.Amount() << endl;
		else if (answer == '4')
			cout << "Amount carriages of second class in a train > " << sc_class.Amount() << endl;
		else if (answer == 'e' || answer == 'E')
			exit(1);
		else
			output(0, 0);
	}
	return 0;
}
