#pragma once

#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

//Employee Class declaration

class Employee
{
	/*friend class company;*/

public:

	Employee(
		unsigned int,
		const string&,
		double,
		unsigned int = 0);

	//Copy constructor for Employee
	Employee(const Employee&);

	//Acessors
	//returns ID
	unsigned int GetId() const;
	//returns the name
	string GetName() const;
	//returns the salary
	double GetSalary() const;
	//returns the boss ID
	unsigned int GetManagerId()const;
	//Returns a string representation of the Employee.
	string ToString();

	//Gives a raise to the employee, adding the specified amount to his or her current salary.
	void Raise(double);
	//Returns true if the employee specified by the parameter has same ID as current object.
	bool Equals(const Employee&);
	//Reads an employee from the istream returning true/false depending on whether read was successful.
	bool Read(istream&);
	//Writes the information about an employee, separated by spaces, to the ostream. A final end of line is written.
	void Write(ostream&);

	//Destructor
	~Employee();

private:

	//Private variables
	unsigned int _id;
	string _name;
	double _salary;
	unsigned int _managerId; 
};