#pragma once
#include <iostream>
#include <string> 

using namespace std;
typedef unsigned int  ui;

namespace Program
{
	static ui it = 1;
	class Carriage
	{
	private:
		string	type;
		ui		serial_nunber;
	public:
		Carriage() {}
		Carriage(string str)
		{
			type = str;
			serial_nunber = it++;
		}
		string	getType()
		{
			return (type);
		}
		ui		getSN()
		{
			return (serial_nunber);
		}
		~Carriage() {};
	};

	class Stack
	{
	private:
		Carriage	obj;
		Stack*		p = NULL;
	public:
		Stack() {}
		Stack(Stack *stack, Carriage pz)
		{
			p = stack;
			obj = pz;
		}
		void		Push(Carriage a)
		{
			Stack *stack = new Stack(p, a);
			p = stack;
		}
		Carriage	Pop()
		{
			Stack *stack = p;
			Carriage temp = (*stack).obj;
			p = p->p;
			delete stack;
			return temp;
		}
		Stack		*Peek()
		{
			return p;
		}
		Carriage	Get_obj()
		{
			return obj;
		}
		int			Amount()
		{
			Stack *stack = p;
			int num = 0;
			while (stack != NULL)
			{
				stack = (*stack).p;
				num++;
			}
			return num;
		}
		~Stack() {}
	};
}
