#ifndef EMPLOYEEHASHRECORDSMENU_H
#define EMPLOYEEHASHRECORDSMENU_H
#include "HashNode.h"

class HashNode; //HashNode exists without defining it

class EmployeeHashRecordsMenu
{
	private:
		HashNode **HashTable; //Variable for HashNode class
		double TotalAnnualSalary; //Variable for Total Annual Salary
		int TotalRecords; //Variable for Total Record Count
		int CollisionFlag[17]; //Detect Collisions
		bool Deleted[17]; //Flag to detect if slot is empty b/c of deletion
		int Size; //Determine if Hash Table is empty
	public:
	        //Construct a New Hash Table
		EmployeeHashRecordsMenu();
		//Read Records from a File
		void CreateHashTable(); 
		//Generate Location for Account Number to Be Stored In
		int HashFunction(int key); 
		//Insert Records into Table
		void Insert(char last_name2[15], char first_name2[15], int account_num2, int month2, int day2,
		            int year2, double annual_salary2, char dept_code2, char phone_number2[12]); 
		//Function to convert the Month number into its abbreviation
		string Date(int month3);
		//Get Today's Date
		void GetDate(int &Month4, int &Day4, int &Year4);
		//Get Age of Employee
		int GetAge(int &Month5, int &Day5, int &Year5);
		//Print Subtitles
		void PrintSubtitles(ostream& OutF);
		//Print Total Records
		void PrintTotalRecords(ostream& OutF);
		//Print Total Annual Salary
		void PrintTotalAnnualSalary(ostream& OutF);
		//Print HashRecords Table
		void Print();
		//Print Data Depending on Collisions
		void Print_Data_Collisions(int, ostream& OutF);
		//Print the Data in the First Slot
		void Print_Non_Collision_Data(int, ostream& OutF);
		//Pause the System
		void Pause();
		//Set Boolean Deleted
		void setDeleted(int);
		//Return boolean value of Deleted
		bool isDeleted(int);
		//Add Data to Hash Table
		void AddData();
		//Press Any Key To Continue
		void PressAnyKey();
		//Function to Dump Records back into to "data_MST"
		void DumpRecords();
		//Search for Record in Hash Table (Checking for Duplicates)
		int SearchHashTable(int);
		//Delete a record 
		void DeleteRecord();
		//Prompt for & Validate Account Number
		void GetAccountNumber(int &);
		//Determine if Hash Table is Empty
		bool isEmpty();
		//Determine if Hash Table is Full
		bool isFull();
		//Prompt for & Validate Month
		void GetMonth(int &);
		//Prompt for & Validate Day
		void GetDay(int &);
		//Prompt for & Validate Year
		void GetYear (int &);
		//Prompt for & Validate First Name & Last Name
		void GetName(char (&)[15], char (&)[15]);
		//Check Dates For Being Out Of Bounds
		bool CheckDate(int Month, int Day, int Year);
		//Validate Date Using CheckDate()
		void ValidateDate(int &, int &, int &);
		//Prompt for & Validate Annual Salary
		void GetAnnualSalary(double&);
		//Prompt for & Validate Department Code 
		void GetDepartmentCode(char&);
		//Prompt for Phone Number 
	        void GetPhoneNumber(char (&)[12]);
		//Validate Phone Number
		void ValidatePhoneNumber(char (&)[12]);
		//Determines if year is Leap Year
		bool isLeap (int year);
		//Validates given year
		bool isValidDate(int, int, int);
		//Modify Record
		void Modify();
		//Assign Hash_Key to Modified Data
		void ModifyData(int Hash_Key, char phone_number2[12]);
		//Validate Numbers
		void Validate_Numbers(int&, string);	
	        //Delete Memory for ALL Internal Components
		~EmployeeHashRecordsMenu();
};//EmployeeHashRecordsMenu
#endif
