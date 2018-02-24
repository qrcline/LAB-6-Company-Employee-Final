#include "company.h"
#include "employee.h"
//Constructor for Company. Sets the _employeeCount to zero.
Company::Company()
{
	_employeeCount = 0; 
	for (int i = 0; i < MAX_EMPLOYEES; i++)
	{
		_employees[i] = NULL; 
	}
}

//Adds an employee to the list. The parameters specify the information about the employee.
//If the employee fits in the array (!IsFull()) then it creates a new Employee with the given data and places it in the next available position.
//Returns true if it was able to add it, false otherwise.
bool Company::AddEmployee(unsigned int id, const string& name , double salary, unsigned int managerId)
{
	if (!IsFull())
	{
		Employee *pemployee;
		pemployee = new Employee(id, name, salary, managerId); 
		_employees[_employeeCount] = pemployee;

		return true;


	}
	else return false;
}

//Adds the specified employee to the list. If the employee fits in the array (!isFull()) then it creates a new Employee using the copy constructor
//and places it in the next available position. Returns true if it was able to add it, false otherwise.
bool Company::AddEmployee(const Employee& employee)
{
	if (!IsFull())
	{
		Employee *pemployee; // making a pointer and allocating memory for an employee
		pemployee = new Employee(employee); // 
		_employees[_employeeCount] = pemployee;

		Employee::Employee(employee);
		return true;

	}
	else return false;
}

//Uses binary search to find an employee using the ID given in the parameter. Returns -1 if the employee is not found. If it is found returns the position of that employee.
int Company::FindById(unsigned int id)
{
	int flag;
	flag = BinarySearch(id);
	return flag; 
	


	return 0;
}

//Uses linear search starting from the position specified by the second parameter to find the first occurrence of the given name in the Array. 
//Returns -1 if the employee is not found. If it is found returns the position of that employee.

int Company::FindByName(const string& name, unsigned int position)
{	
	//int record = 0;

	for (int i = position; i < (int) _employeeCount; i++)
	{
		if (_employees[i]->GetName() == name)
			return i;
	}
	return -1;
}

//Reads an istream and extracts all the employees’ data from there, and adds the employees to exsiting list of employees (up to the size of the array i.e. MAX_EMPLOYEES).
//Sorts the array. Returns the number of employees read.

int Company::Read(istream& input)
{
	
	
	
	while (!input.eof() && _employeeCount != MAX_EMPLOYEES )
	{
		Employee* pemployee;
		pemployee = new Employee (0, "", 0.0, 0);
		if (pemployee->Read(input) == true)
		{
			AddEmployee(*pemployee);
			//_employeeCount++;  //This is getting incriminted somewhere else 
			_employeeCount++;
		}

		
		
	}
	Sort();
	return _employeeCount; 


}

//Writes all the available employees to the ostream. Returns the number of employees written.
int Company::Write(ostream& output)
{
	int count = 0;
	for (int i = 0; i < (int) _employeeCount -1; i++)
	{	
		Get(i)->Write(output);
		count++;
	}
	return count+1;
}

//Returns true if the array of employees is full, false otherwise.

bool Company::IsFull()
{
	if (_employeeCount < 10) 
	{
		return false;
	}
	else return true; 
	
}

//Returns a pointer to the Employee at the position specified by the parameter. If the position is invalid, it returns NULL. 
//The referenced object belongs to the object and should not be “deleted” by the client.

Employee* Company::Get(unsigned int position)
{
	if (position <= MAX_EMPLOYEES && _employees[position] != NULL)
	{
		return _employees[position]; 
	}
	else
	 return NULL;
	
}

//Returns the number of employees in the Company (_employeeCount)
unsigned int Company::GetEmployeeCount()
{
	return _employeeCount; 
}

//Frees the memory by releasing all the dynamically created employees in the array.DO NOT try to delete the actual array since it was not dynamically created.
Company::~Company()
{
	for (unsigned int i = 0; i < _employeeCount; i++) 
	{
	delete _employees[i];
	}
	
	//delete[] _employees; 
	
}



//Executes a binary search in the array. The parameter indicates the key that is being searched. Returns position found or -1 if not found.

int Company::BinarySearch(unsigned int input)
{
	Sort();
	int first = 0;
	int last = _employeeCount-1 ;
	while (first <= last)
	{
		int mid = (first + last) / 2;

		if (input < (unsigned int) _employees[mid]->GetId())
		{
			last = mid - 1;
		}
			

		else if (input > (unsigned int) _employees[mid]->GetId())
		{
			first = mid + 1;
		}
			
		else 
			return mid;

	}

	return -1;
}

//Sorts the array of employees by ID. You may use any sorting algorithm (Bubble, Insertion, Selection).
void Company::Sort()
{
	bool exchangeMade = true; 
	Employee* tmp;

	for (int pass = 1; pass < (int) _employeeCount && exchangeMade; pass++)
	{
		exchangeMade = false;

		//On each pass the range of elements decreases by 1
		for (int index = 0; index <(int) _employeeCount - pass; index++)
		{
			//If adjacent pari out of order, swap them
			if (_employees[index]->GetId() > _employees[index + 1]->GetId())
			{
				
				tmp = _employees[index];

				_employees[index] = _employees[index + 1];
				_employees[index + 1] = tmp;
				exchangeMade = true; 
				
			}
		}
	}
}
