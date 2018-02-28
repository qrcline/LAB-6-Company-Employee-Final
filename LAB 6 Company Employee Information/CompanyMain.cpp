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

// included for error output time delay
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;

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
	string menue = "1. Load a Company File\n2.Save Company Data to File \n3. List all Employees\n4.Search by Name \n5. Search by ID\n6. Find Employee Boss Infromation\n7. Add a New Employee\n8.Check if the Database is Full\n9. Exit\n";
	int input = 0;
	int flag=0;
	string stringInput;

	
	while (input != 9)
	{
		flag = false; 
		cout << menue;
		cin >> input;
		
		/*flag = InputCheckInt(input);
		while (!flag)
		{	cin.clear();
			cin.ignore(255,'\n');
			cout << menue; 
			cin >> input; 
			
		}*/
	
		
		

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
		/*cin.clear();
		cin.ignore();*/
	}

}

void load(string filename, Company& company)
{
	////get file name input from user
	//cout << "File Name:";
	//getline(cin, filename);

	//opens file from specified directory
	ifstream  log(filename);

	//Checks if file opens, if fails displays message
	if (log.fail())
	{
		cout << "Can not open " << filename << endl;
		/*sleep_for(1s);
		cout << "Closing in 5 seconds";
		for (int i = 0; i < 5; i++)
		{
			cerr << ".";
			sleep_for(1s);
		}*/
		
	}	
	else
	{
		int employeesRead;
		employeesRead= company.Read(log);
		cout << "File loaded, " << employeesRead << " records read" << endl; 
		// Adds employees from file
		

	}
}

void WriteToFile(string fileName, Company& company)
{
	ofstream outputFile(fileName);
	company.Write(outputFile);
}

int SearchByName( Company& company)
{
	int flag;
	string name;

	while (name == "")
	{
		cout << "Employee Name: ";
		cin >> name;
	}
	 int position = 0;
	for (unsigned int i = position; i < company.GetEmployeeCount(); i++)
	{
		
		
		if (position != -1)
		{
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
		else
		{
			cout << "No Employee Found" << endl; 
			flag = 0;
			break; 
		}
		
	}
	return flag; 

}

bool InputCheckInt(int input)
{
	if (input >= 1 && input <= 9)
	{
		return true;
	}
	else
		return false; 


}



bool InputCheckIntId(int input)
{
	if (cin.fail() == true)
	{
		return false;
		
	}
	else 
		return true;


	/*if (input >= 1 && input <= MAX_EMPLOYEES)
	{
		return true;
	}
	else
		return false;*/


}


void SearchById(Company & company)
{
	int iD;
	bool loopFlag = true;
	cout << "Employee ID: ";
	cin >> iD;

	while (loopFlag == true)
	{
		if (InputCheckIntId(iD) == false)
		{
			cin.clear();
			cin.ignore(255, '\n');
			cout << "Employee ID: ";
			cin >> iD;

		}

		else
		{
			loopFlag = false;
			int position;
			position = company.FindById(iD);
			if (position == -1)
			{
				cout << "No Employee Found" << endl << endl; 
			}
			else
			{
				Employee* employee;
				employee = company.Get(position);
				cout << employee->ToString() << endl;

				cout << "would you like to give " << employee->GetName() << " a raise? (Y/N): ";
				string input;
				cin >> input;
				bool raiseFlag=true; 
				while (raiseFlag == true)
				{
					if (input == "y" || input == "Y")
					{
						cout << "What is the raise: ";
						double raise;
						cin.clear();
						cin.ignore(255, '\n');
						cin >> raise;

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
							employee->Raise(raise);
							raiseFlag = false;
						}
					}
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
	

void FindEmployeBoss(Company& company)
{
	int iD;
	cout << "Employee ID: ";
	cin >> iD;
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
			Employee* employee;
			employee = company.Get(position);
			cout << employee->ToString() << endl;
			cout << "Manager:" << endl;
			Employee* manager;
			int managerPosition = employee->GetManagerId();
			manager = company.Get(company.FindById(employee->GetManagerId()));
			cout << manager->ToString() << endl;

			
		}


	}
}

void AddNewEmployee(Company& company)
{
	unsigned int iD;
	string name;
	double salary;
	unsigned int managerID;
	

	if (company.GetEmployeeCount() == (unsigned int)10)
	{
		cout << "Cannot add new records, database is full" << endl;
	}
	
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


		//Checks if id alrady exists
		bool idCheckFlag = false;
		
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
		


		cout << "Name: ";
		cin >> name;
		cout << "Salary: ";
		cin >> salary;
		/*while (cin.fail())
		{
			cout << "Invalid input, please try again";
			cin.clear();
			cin.ignore(255, '\n');
			cin >> salary; 
		}*/
		cout << "Boss ID (0 for none): ";
		cin >> managerID;
		bool flag;
		flag = company.AddEmployee(iD, name, salary, managerID);

		if (flag == true)
		{
			cout << endl <<name<< " added successfully" << endl;
		}

	}
	


}
	

