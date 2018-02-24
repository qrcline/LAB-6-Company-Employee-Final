#pragma once

#include <iostream>
#include <string>
#include <assert.h>
#include "employee.h"

using namespace std;

//Company class decleration
const int MAX_EMPLOYEES = 10;

class Company
{
public:
	//Constructor for Company. Sets the _employeeCount to zero.
	Company();

	//Adds an employee to the list. The parameters specify the information about the employee.
	//If the employee fits in the array (!IsFull()) then it creates a new Employee with the given data and places it in the next available position.
	//Returns true if it was able to add it, false otherwise.
	bool AddEmployee(
		unsigned int,
		const string&,
		double,
		unsigned int = 0);

	//Adds the specified employee to the list. If the employee fits in the array (!isFull()) then it creates a new Employee using the copy constructor
	//and places it in the next available position. Returns true if it was able to add it, false otherwise.
	bool AddEmployee(
		const Employee&);

	//Uses binary search to find an employee using the ID given in the parameter. Returns -1 if the employee is not found. If it is found returns the position of that employee.
	int FindById(unsigned int);

	//Uses linear search starting from the position specified by the second parameter to find the first occurrence of the given name in the Array. 
	//Returns -1 if the employee is not found. If it is found returns the position of that employee.
	int FindByName(
		const string&,
		unsigned int = 0);

	//Reads an istream and extracts all the employees’ data from there, and adds the employees to exsiting list of employees (up to the size of the array i.e. MAX_EMPLOYEES).
	//Sorts the array. Returns the number of employees read.
	int Read(istream&);

	//Writes all the available employees to the ostream. Returns the number of employees written.
	int Write(ostream&);

	//Returns true if the array of employees is full, false otherwise.
	bool IsFull();

	//Returns a pointer to the Employee at the position specified by the parameter. If the position is invalid, it returns NULL. 
	//The referenced object belongs to the object and should not be “deleted” by the client.
	Employee* Get(unsigned int);

	//Returns the number of employees in the Company (_employeeCount)
	unsigned int GetEmployeeCount();

	//Frees the memory by releasing all the dynamically created employees in the array.DO NOT try to delete the actual array since it was not dynamically created.
	~Company();


private:

	//Array of Employee* MAX_EMPLOYEES is 10
	Employee* _employees[MAX_EMPLOYEES];
	//The number of actual employees in the array. In the beginning, there are no employees.
	unsigned int _employeeCount;
	//Executes a binary search in the array. The parameter indicates the key that is being searched. Returns position found or -1 if not found.
	int BinarySearch(unsigned int);
	//Sorts the array of employees by ID. You may use any sorting algorithm (Bubble, Insertion, Selection).
	void Sort();
};
