//Title: Lab 6 - CompanyMain.cpp

//Purpose: reads company database, query, and add employee, run operations on employees
// Class: CSC 2430 Winter 2018
// Author : Quinton Cline


#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <assert.h>
#include "employee.h"
#include "company.h"
using namespace std;


//functions
void load(string, Company&);
void WriteToFile(string, Company&);
int SearchByName( Company&);
bool InputCheckInt(int);
void SearchById(Company&);
bool InputCheckIntId(int);
void FindEmployeBoss(Company&);
void AddNewEmployee(Company&);

//main function
int main()
{
	// Initilization of classes
	Company company;
	//variables
	string menue = "1. Load a Company File\n2. Save Company Data to File \n3. List all Employees\n4. Search by Name \n5. Search by ID\n6. Find Employee Boss Infromation\n7. Add a New Employee\n8. Check if the Database is Full\n9. Exit\n";
	int input = 0;
	int flag=0;
	string stringInput;

	
	while (input != 9)
	{
		flag = false; 
		cout << menue;
		cin >> input;
		
		//Menue swithc statment
		switch(input)
		{
		case 1:
			cout << "Filename: ";
			cin >> stringInput;
			load(stringInput, company);
			break;

		case 2:
			cout << "Filename: ";
			cin >> stringInput; 
			WriteToFile(stringInput, company);
			break;

		case 3:
			company.Write(cout);
			cout << endl; 
			break;

		case 4:
			SearchByName( company);
			break;

		case 5:
			SearchById(company);
			break;

		case 6:
			FindEmployeBoss(company);
			break;

		case 7:
			AddNewEmployee(company);
			break;

		case 8:
			if (company.GetEmployeeCount() == (unsigned int)10)
			{
				cout << "The database is full " << endl; 
			}
			else
			{
				cout << "Database not full, it has " << company.GetEmployeeCount() << " records" << endl; 
			}
			break;

		case 9:
			
			break;

		default:
			cout << "Invalid input, please try again"<<endl;
			cin.clear();
			cin.ignore(255, '\n');

		}
	}

}

//Loads employees from file
void load(string filename, Company& company)
{
	//opens file from specified directory
	ifstream  log(filename);

	//Checks if file opens, if fails displays message
	if (log.fail())
	{
		cout << "Can not open " << filename << endl;
	}	
	else
	{
		int employeesRead;
		employeesRead= company.Read(log);
		cout << "File loaded, " << employeesRead << " records read" << endl; 
		// Adds employees from file
	}
}

//Writes whats currently in the database to file
void WriteToFile(string fileName, Company& company)
{
	ofstream outputFile(fileName);
	company.Write(outputFile);
}

// Searches the database for a name (Case sensitive)
int SearchByName( Company& company)
{
	int flag;
	string name;

	//If input is blank repromt
	while (name == "")
	{
		cout << "Employee Name: ";
		cin >> name;
	}

	//Steps through the array of employees checking for the name
	//Outputs data for names matching the query
	int position = 0;
	for (unsigned int i = position; i < company.GetEmployeeCount(); i++)
	{
		if (position != -1)
		{
			//Uses FindByName() to get the positon of employee with matching name
			position= company.FindByName(name,position);
			if (position == -1)
			{
				break; 
			}
			Employee* employee;
			employee = company.Get(position);
			cout << employee->ToString() << endl;
			flag = 1;
			position++;
		}
		//Outputs no employee found 
		else
		{
			cout << "No Employee Found" << endl; 
			flag = 0;
			break; 
		}
		
	}
	return flag; 

}

//check case statment input
bool InputCheckInt(int input)
{
	if (input >= 1 && input <= 9)
	{
		return true;
	}
	else
		return false; 


}


//checks integer input
bool InputCheckIntId(int input)
{
	if (cin.fail() == true)
	{
		return false;
		
	}
	else 
		return true;

}

//Search By ID function
void SearchById(Company & company)
{
	int iD;
	bool loopFlag = true;
	cout << "Employee ID: ";
	cin >> iD;

	//Loops tell flag is false
	while (loopFlag == true)
	{
		//checks if initial input is an number
		//Repromts if false
		if (InputCheckIntId(iD) == false)
		{
			cin.clear();
			cin.ignore(255, '\n');
			cout << "Employee ID: ";
			cin >> iD;

		}

		else
		{
			//Vars
			loopFlag = false;
			int position;

			//Finds postion of employee with ID using FindById()
			position = company.FindById(iD);

			//No employee found with that ID
			if (position == -1)
			{
				cout << "No Employee Found" << endl << endl; 
			}
			else
			{
				//If and employee with that ID found
				Employee* employee;
				employee = company.Get(position);
				//prints out employee information
				cout << employee->ToString() << endl;

				//Prompts the user if they want to give the current employee raise.
				cout << "would you like to give " << employee->GetName() << " a raise? (Y/N): ";
				string input;
				cin >> input;
				bool raiseFlag=true; 
				//Loops tell flag is false
				while (raiseFlag == true)
				{
					//Y input
					if (input == "y" || input == "Y")
					{
						cout << "What is the raise: ";
						double raise;
						cin.clear();
						cin.ignore(255, '\n');
						cin >> raise;
						
						//If input is invalid
						if (cin.fail() == true)
						{
							cin.clear();
							cin.ignore(255, '\n');
							cout << "Invalid input, please try again" << endl;
							cout << "What is the raise: ";
							double raise;
							cin >> raise;
						}
						
						else
						{
							//If imput valid initiates raise
							employee->Raise(raise);
							raiseFlag = false;
						}
					}
					//N input
					else if (input == "N" || input == "n")
					{
						raiseFlag = false;
						break;
					}
					else
					{
						cout << "Invalid input, please try again" << endl;
						cin >> input;
					}
				}

			}
		}
	}
}
	
//Finds the Manager/Boss of the employee
void FindEmployeBoss(Company& company)
{
	int iD;
	cout << "Employee ID: ";
	cin >> iD;
	//Checks input
	if (InputCheckIntId(iD) == false)
	{
		cout << "No Employee Found" << endl;

	}

	else
	{
		int position;
		position = company.FindById(iD);
		if (position == -1)
		{
			cout << "No Employee Found" << endl;

		}
		else
		{
			//Gets and displays information of employee
			Employee* employee;
			employee = company.Get(position);
			cout << employee->ToString() << endl;

			//Gets and displays information of Manager
			cout << "Manager:" << endl;
			Employee* manager;
			int managerPosition = employee->GetManagerId();
			manager = company.Get(company.FindById(employee->GetManagerId()));
			cout << manager->ToString() << endl;
		}
	}
}

//Adds a new employee specified by user
void AddNewEmployee(Company& company)
{
	unsigned int iD;
	string name;
	double salary;
	unsigned int managerID;
	
	//Checks if array is full
	if (company.GetEmployeeCount() == (unsigned int) MAX_EMPLOYEES )
	{
		cout << "Cannot add new records, database is full" << endl;
	}
	
	//User prompted to enter employee infromation 
	else
	{
		cout << "Create new employee" << endl;
		cout << "ID: ";
		cin >> iD;

		while (InputCheckIntId(iD) == false)
		{
		
			cout << "Invalid input, please try again" << endl;
			cin.clear();
			cin.ignore(255, '\n');
			cin >> iD;

		}


		//Checks if id already exists
		bool idCheckFlag = false;
		//loops tell flag is true
		//flag set true when correct id is entered
		while (idCheckFlag == false )
		{	int idLoopCount = 0;
			for (unsigned int i = 0; i < (int)company.GetEmployeeCount(); i++)
			{
				if (iD != company.Get(i)->GetId())
				{
					idLoopCount++;
				}
			}
			if (idLoopCount == company.GetEmployeeCount())
			{
				idCheckFlag = true;
			}
			if (idCheckFlag == false)
			{
				cout << "ID alrady in file, chose a different ID: ";
				cin >> iD;
				while (InputCheckIntId(iD) == false)
				{

					cout << "Invalid input, please try again" << endl;
					cin.clear();
					cin.ignore(255, '\n');
					cin >> iD;

				}
			}
		}
		//Prompts user for name
		cout << "Name: ";
		cin >> name;
		//Prompts user for salary and validates
		cout << "Salary: ";
		cin >> salary;
		while (cin.fail())
		{
			cout << "Invalid input, please try again ";
			cin.clear();
			cin.ignore(255, '\n');
			cin >> salary; 
		}

		//Prompts user for boss ID and validates
		cout << "Boss ID (0 for none): ";
		cin >> managerID;
		while (cin.fail())
		{
			cout << "Invalid input, please try again ";
			cin.clear();
			cin.ignore(255, '\n');
			cin >> managerID;
		}
		bool flag;

		//Adds employee to array
		flag = company.AddEmployee(iD, name, salary, managerID);

		if (flag == true)
		{
			cout << endl <<name<< " added successfully" << endl;
		}

	}
	


}
	

