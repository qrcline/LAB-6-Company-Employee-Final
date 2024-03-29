// Title: Lab 6 Company Employee Database Unit Test - Lab6UnitTest.cpp
//
// Purpose: Runs validation tests on the Company's Database classes for Lab 6
//
// Class: CSC 2430 Winter 2018
//
// Author: Carlos Arias

#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>

using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::string;
using std::stringstream;
using std::istream;
using std::ostream;

#include "employee.h"
#include "company.h"


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);

	stringstream inbuffer0, inbuffer1, inbuffer2, outbuffer;
	
	Company* company;
	Employee employee(0, "", 0);
	// Check Employee initial state
	assert(employee.GetId() == 0);
	assert(employee.GetName() == "***");
	assert(employee.GetManagerId() == 0);
	assert(employee.GetSalary() == 0.0);
	cerr << "Employee Tests Passed Successfully" << endl;

	// Check Company initial state
	company = new Company();
	assert(!company->IsFull());
	assert(company->GetEmployeeCount() == 0);
	assert(company->Get(0) == NULL);
	assert(company->FindById(1) == -1);
	assert(company->FindByName("Name") == -1);
	cerr << "Initial Company Tests Passed Successfully" << endl;


	// Empty file
	inbuffer0.str("");
	assert(company->Read(inbuffer0) == 0);
	assert(!company->IsFull());
	assert(company->GetEmployeeCount() == 0);
	assert(company->Get(0) == NULL);
	assert(company->FindById(1) == -1);
	assert(company->FindByName("Name") == -1);
	cerr << "Company Test with Empty File Passed Successfully" << endl;


	// Load Employees
	inbuffer1.str(
		"10 Anna 2250 2\n"
		"1 Peter 250 0\n"
		"11 Melissa 1450 1\n"
		"4 Leonel 1801 0\n"
		"3 Silvia 150 1\n"
		"16 Nicole 50 0\n"
		"5 Jon 3500 1\n"
		"2 Dio 100 0\n"
		"9 Jon 4100 2\n"
	);
	Employee* ptrEmployee;
	
	int employeeIndex;
	assert(company->Read(inbuffer1) == 9);
	assert(!company->IsFull());
	assert(company->Get(0)->Equals(Employee(1, "Peter", 250))); // Testing sort
	assert((employeeIndex = company->FindById(1)) != -1);
	assert((ptrEmployee = company->Get(employeeIndex)) != NULL);
	assert(ptrEmployee->GetId() == 1);
	assert(ptrEmployee->GetName() == "Peter");
	assert(ptrEmployee->GetSalary() == 250);
	assert(ptrEmployee->GetManagerId() == 0);
	assert((employeeIndex = company->FindByName("Jon")) != -1);
	assert((ptrEmployee = company->Get(employeeIndex)) != NULL);
	assert(ptrEmployee->GetId() == 5);
	assert(ptrEmployee->GetName() == "Jon");
	assert(ptrEmployee->GetSalary() == 3500);
	assert(ptrEmployee->GetManagerId() == 1);
	assert((employeeIndex = company->FindByName("Jon", employeeIndex + 1)) != -1);
	assert((ptrEmployee = company->Get(employeeIndex)) != NULL);
	assert(ptrEmployee->GetId() == 9);
	assert(ptrEmployee->GetName() == "Jon");
	assert(ptrEmployee->GetSalary() == 4100);
	assert(ptrEmployee->GetManagerId() == 2);
	assert(company->GetEmployeeCount() == 9);
	assert(company->Write(outbuffer) == 9);
	cerr << "Company Test with Data File (1) Passed Successfully" << endl;

	delete company;
	company = new Company();
	inbuffer2.str(
		"10 Anna 2250 2\n"
		"1 Peter 250 0\n"
		"11 Melissa 1450 1\n"
		"4 Leonel 1801 0\n"
		"3 Silvia 150 1\n"
		"16 Nicole 50 0\n"
		"5 Jon 3500 1\n"
		"2 Dio 100 0\n"
		"9 Jon 4100 2\n"
		"8 Chris 800 0\n"
		"100 Kat 4875 2\n"
	);
	assert(company->Read(inbuffer2) == MAX_EMPLOYEES);
	assert(company->IsFull());
	assert(company->Get(0)->Equals(Employee(1, "Peter", 250))); // Testing sort
	assert((employeeIndex = company->FindById(8)) != -1);
	assert((ptrEmployee = company->Get(employeeIndex)) != NULL);
	assert(ptrEmployee->GetId() == 8);
	assert(ptrEmployee->GetName() == "Chris");
	assert(ptrEmployee->GetSalary() == 800);
	assert(ptrEmployee->GetManagerId() == 0);
	assert((employeeIndex = company->FindByName("Jon")) != -1);
	assert((ptrEmployee = company->Get(employeeIndex)) != NULL);
	assert(ptrEmployee->GetId() == 5);
	assert(ptrEmployee->GetName() == "Jon");
	assert(ptrEmployee->GetSalary() == 3500);
	assert(ptrEmployee->GetManagerId() == 1);
	assert((employeeIndex = company->FindByName("Jon", employeeIndex + 1)) != -1);
	assert((ptrEmployee = company->Get(employeeIndex)) != NULL);
	assert(ptrEmployee->GetId() == 9);
	assert(ptrEmployee->GetName() == "Jon");
	assert(ptrEmployee->GetSalary() == 4100);
	assert(ptrEmployee->GetManagerId() == 2);
	ptrEmployee->Raise(1000);
	assert(ptrEmployee->GetSalary() == 5100);
	assert(company->GetEmployeeCount() == 10);
	assert(company->Write(outbuffer) == 10);
	cerr << "Company Test with Data File (2) Passed Successfully" << endl;

	delete company;

	cerr << "Congratulations you passed all the tests!" << endl;

    return 0;
}

