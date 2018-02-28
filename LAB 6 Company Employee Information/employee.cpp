#include <sstream>
#include <iostream>
#include <iomanip>
#include "employee.h"

//Creates an employee using the values given by the parameters. The last parameter represents the boss ID.
//If the name parameter is an empty string, the constructor should initialize the name to “***”
Employee::Employee(unsigned int id, const string & name, double salary, unsigned int managerId)
{
	_id = id;
	if (name == "")
	{
		_name = "***";
	}
	else 
	_name = name;
	_salary = salary;
	_managerId = managerId;
}

//Copy constructor for employee
Employee::Employee(const Employee & employee)
{
	_id = employee.GetId(); 
	_name = employee.GetName();
	_salary = employee.GetSalary();
	_managerId = employee.GetManagerId();

}

//Returns employee id
unsigned int Employee::GetId() const
{
	return _id;
}

//Returns employee name
string Employee::GetName() const
{
	return _name;
}

//Returns employee salary
double Employee::GetSalary() const
{
	return _salary;
}

// Returns employees manager number
unsigned int Employee::GetManagerId() const
{
	return _managerId;
}

//Returns a string representation of the Employee.
string Employee::ToString()
{
	stringstream s;
	s << "Name:" << setw(10) << left<< _name << right<< " ID:" << setw(5) << right<< _id << " Salary:" << setw(10) <<  showpoint<< _salary << " Manager ID:" << setw(5) << _managerId << left;
	return s.str();
}

//Gives a raise to the employee, adding the specified amount to his or her current salary.
void Employee::Raise(double raise)
{
	_salary += raise;
}

//Returns true if the employee specified by the parameter has same ID as current object.
bool Employee::Equals(const Employee & employee)
{
	if (employee.GetId() == _id)
	{
		return true;
	}
	else return false; 
}

//Reads an employee from the istream returning true/false depending on whether read was successful.
bool Employee::Read(istream & input)
{
	unsigned int id= INT_MAX;
	string name = "";
	double salary= INT_MAX;
	unsigned int managerId = INT_MAX;

	input >> id >> name >> salary >> managerId;
	if (input.fail())
	{
		return false;
	}
	else
	{
		_id = id;
		_name = name;
		_salary = salary;
		_managerId = managerId;
		return true;

	}
}

//Writes the information about an employee, separated by spaces, to the ostream. A final end of line is written.
void Employee::Write(ostream& output)
{
	output << _id << " " <<  _name << " " << _salary << " " << _managerId   << endl; 
}

//Destructor
Employee::~Employee()
{

}