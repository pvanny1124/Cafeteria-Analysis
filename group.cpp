// Provided by:   Patrick Vanegas
// Email Address: vanegas.patrick@yahoo.com

// project3 - Cafeteria Simulation
//
//	FILE: group.cpp
//	PROVIDES: implementations for the overloaded << operator, all other functions were implemented inline

#include <string>
#include <queue>
#include <stack>
#include "student.h"
#include <iostream>
#include <iomanip> //provides setprecision
#include "group.h"
using namespace std;

namespace csc212_kl_f2012_a4template
{
	std::ostream& operator<<(std::ostream& os, Group& g)
	{
		/* YOUR CODE GOES HERE*/
		
		os << "Group " << g.color << "\n";
		stack<Student> temp;
		for (size_t i = 0; i < g.students.size(); i++)
		{
			os << g.students.front();
			temp.push(g.students.front());
			g.students.pop();
			g.students.push(temp.top());
		}
		os << "Total: " << g.price << endl; //group's total price 
		return os; 
	}
}