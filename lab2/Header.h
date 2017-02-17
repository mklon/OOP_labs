#pragma once
#include <string>
#include <iostream>
#include <conio.h>

using namespace std;

namespace Program
{
	const int	averageSalary = 6000;
	static int	perNumber = 0;
	static bool	delFlag = 0;

	class Person
	{
	private:
		string	name;
		string	position;
		float	salary;
		float	premium;
		float	wages_rate;
	public:
		Person() {};
		Person(string perName, string perPos)
		{
			name = perName;
			position = perPos;
			setWage(position);
			setPremiun();
			setSalery();
		}	
		void	setWage(string perPos)
		{
			if (position == "Specialist")
				wages_rate = 3000;
			else if (position == "Specialist Category 1")
				wages_rate = 3500;
			else if (position == "Specialist Category 2")
				wages_rate = 5000;
			else if (position == "Specialist of the highest category")
				wages_rate = 6500;
			else if (position == "Head of Department")
				wages_rate = 8000;
			else if (perPos == "Director")
				wages_rate = 10000;
			else
				wages_rate = 0;
		}
		void	setPremiun(void)
		{
			if (wages_rate < averageSalary)
				premium = wages_rate / 2;
			else
				premium = wages_rate / 10 * 3;
		}
		void	setSalery(void)
		{
			salary = premium + wages_rate;
		}
		string	getName(void)
		{
			return (name);
		}
		string	getPosition(void)
		{
			return (position);
		}
		float	getSalary(void)
		{
			return (salary);
		}
		float	getPremium(void)
		{
			return (premium);
		}
		float	getWages(void)
		{
			return (wages_rate);
		}
		~Person() {};
	};

	class Using
	{
	public:
		Using() {}
		Person	*hire_person(Person *manPointer)
		{
			int		i;
			char	choosePos;
			string	manPos;
			string	manName;

			i = -1;
			cout << "Enter the name of person > " << endl;
			getline(cin, manName);
			while (true)
			{
				cout << "Choose the position of person > " << endl
					<< "1 > Specialist" << endl
					<< "2 > Specialist Category 1" << endl
					<< "3 > Specialist Category 2" << endl
					<< "4 > Specialist of the highest category" << endl
					<< "5 > Head of Department" << endl
					<< "6 > Director" << endl;
				choosePos = _getch();
				if (choosePos > '0' && choosePos < '7')
				{
					if (choosePos == '1')
						manPos = "Specialist";
					else if (choosePos == '2')
						manPos = "Specialist Category 1";
					else if (choosePos == '3')
						manPos = "Specialist Category 2";
					else if (choosePos == '4')
						manPos = "Specialist of the highest category";
					else if (choosePos == '5')
						manPos = "Head of Department";
					else if (choosePos == '6')
						manPos = "Director";
				}
				else
				{
					cout << "Incorrect input!Try again." << endl;
					continue ;
				}	
				break ;			
			}
			perNumber++;	
			Person *mass = new Person[perNumber];
			while (++i < (perNumber - 1))
				mass[i] = manPointer[i];
			mass[perNumber - 1] = Person(manName, manPos);
			if (delFlag)
				mem_del(manPointer);
			delFlag = 1;
			return (mass);
		}

		Person	*fire_person(Person *manPointer)
		{
			int		i = -1;
			bool	flag = false;
			string	manName;
			Person	*dopPointer;

			dopPointer = manPointer;
			cout << "Enter the name of person > " << endl;

			getline(cin, manName);
			while (++i < perNumber)
				if (!((&((dopPointer++)->getName()))->compare(manName)))
				{
					cout << "sf";
					flag = !flag;
					break;
				}
			system("cls");
			if (!flag)
			{	
				cout << "No such person!" << endl;
				return (manPointer);
			}
			i = -1;
			perNumber--;
			dopPointer = manPointer;
			Person *mass = new Person[perNumber];
			if (flag)
				while (++i < perNumber)
				{
					if (!((&(dopPointer->getName()))->compare(manName)))
						dopPointer++;
					mass[i] = *dopPointer;
					dopPointer++;
				}
			if (delFlag)
				mem_del(manPointer);
			delFlag = 1;
			cout << "Done!" << endl;
			return (mass);
		}
		void	mem_del(Person *masPointer)
		{
			delete [] masPointer;
		}
		~Using() {}
	};
}
