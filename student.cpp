// Provided by:  Patrick Vanegas
// Email Address: vanegas.patrick@yahoo.com
// Project 3 - Cafeteria Simulation
//
//	FILE: student.cpp
//	PROVIDES: implementations for the genPrice function and the overloaded << operator, all other functions were implemented inline
#include <string>
#include "student.h"
#include <iostream>
#include <iomanip> //provides setprecision
using namespace std;

namespace csc212_kl_f2012_a4template
{
	//precondition: the function is called inside the Student constructor as a helper function
	//postcondition: the Price is updated to the correct value depending on the choice of the student's meals
	void Student::genPrice()
	{	//price is ouncesofsalad*priceofounce + entreecost + desert
		if (entreeName == "lasagna")
			price += LASAGNAPRICE;
		if (entreeName == "chicken")
			price += CHICKENPRICE;
		if (entreeName == "fishsticks")
			price += FISHPRICE;
		if (dessertName == "cheesecake")
			price += CHEESECAKEPRICE;
		if (dessertName == "pudding")
			price += PUDDINGPRICE;
		price += ouncesSalad*SALADOUNCEPRICE;

	}

	std::ostream& operator<<(std::ostream& os, const Student& s)
	{
		os << s.name << ": $" << fixed << std::setprecision(2) << s.price << endl;  //two decimal places is always displayed in the price
		return os;
	}
}

