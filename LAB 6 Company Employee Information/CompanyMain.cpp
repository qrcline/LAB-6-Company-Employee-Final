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
void SearchByName(string, Company&);

//main function
int main()
{
	// Initilization of classes
	Company company;
	int input = 0;
	string stringInput;

	
	while (input != 9)
	{
		cout << "1. Load a Company File\n2.Save Company Data to File \n3. List all Employees\n4.Search by Name \n5. Search by ID\n6. Find Employee Boss Infromation\n7. Add a New Employee\n8.Check if the Database is Full\n9. Exit" << endl; 
		cin >> input; 
		

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
			SearchByName(stringInput, company);
			break;

		case 5:
			cout << "5";
			break;

		case 6:
			cout << "5";
			break;

		case 7:
			cout << "6";
			break;

		case 8:
			cout << "7";
			break;

		case 9:
			cout << "8";
			break;

		default:
			cout << "Invalid input, please try again";


		}
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
		}*/exit;
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

void SearchByName(string name, Company& company)
{

	company.FindByName(name, );

}