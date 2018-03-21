#include <iostream>
using namespace std;
#include <fstream>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <string>
#include <ctime>
#include <unistd.h>
#include <cmath>
#include <limits>
#include <sstream>
#include "EmployeeHashRecordsMenu.h"
#include <stdlib.h>

//Max size of Hash Table
const int TableSize = 17;

//-|----------------------------------
//-| 1. Construct a New Hash Table
//-|----------------------------------
EmployeeHashRecordsMenu :: EmployeeHashRecordsMenu()
{
	//Initialize TotalAnnualSalary & TotalRecords to 0
	TotalAnnualSalary = 0.00;
    TotalRecords = 0;

	//Create a New Hash Table with 17 elements
	HashTable = new HashNode*[TableSize];

	//Assign all 17 records to NULL & CollisionCount[] to 0, & Deleted[] to false
	for(int i = 0; i < TableSize; i++)
	{
		HashTable[i] = NULL;
		CollisionFlag[i] = 0;
		Deleted[i] = false;
	}//for
}//HashRecords() 


//-|--------------------------------
//-| 2. Read Records from a File
//-|--------------------------------
void EmployeeHashRecordsMenu :: CreateHashTable()
{
	//Declare variables
	ifstream inF; //Variable for Input File                 
	char last_name6[15]; //Variable for Last Name
	char first_name6[15]; //Variable for First Name
	int account_num6; //Variable for Account Number
	int month6; //Variable for Month
	int day6; //Variable for Day
	int year6; //Variable for Year
	double annual_salary6; //Variable for Annual Salary
	char dept_code6; //Variable for Department Code
	char phone_number6[12];//Variable for Phone Number

	//Open File
	inF.open("data_MST");
	
	//Test File For Error
	if(inF.fail())
	{
		   cout << endl << "FATAL ERROR: UNABLE TO OPEN FILE \"data_MST\". TERMINATING..."
                << endl << endl;
           exit (1);
	}//if
	
	//Else, Read in the Data
	else
	{
		//Read in data
		while(inF >> last_name6 >> first_name6 >> account_num6 >> month6 >> day6 >> year6 >> annual_salary6 >> dept_code6 >> phone_number6)
		{
			//Check for if HashTable is full
			if(isFull())
			{
				//Print statement to screen
				cout << endl << "Hash Table is FULL... [NO MORE RECORDS] can be added" << endl;
			
				//PRESS ANY KEY TO CONTINUE
				PressAnyKey();
				
				//Break out of loop
				break;
			}//if
			
			//Validate That Annual Salary is Greater than 0
			if(annual_salary6 < 0.0)
				continue;
			
			//Capitalize dept_code3
			dept_code6 = toupper(dept_code6);
			
			//Add One TotalRecords
		    TotalRecords++;
			
			//Add annual_salary6 to TotalAnnualSalary
			TotalAnnualSalary += annual_salary6;

			//Send Data to Insert() Function
			Insert(last_name6, first_name6, account_num6, month6, day6, year6, annual_salary6, dept_code6, phone_number6);
			
			//Increment Size by 1
			Size++;
		}//while
	}//else	  
	//Ignore Until End 
	inF.ignore(numeric_limits<streamsize>::max(),'\n');

	//Close File
	inF.close();
	
	//COULD DELETE [BE AWARE] - Print Out Statement that Hash Table is Created
	cout << endl << "Hash Table is CREATED" << endl;
			
	//PRESS ANY KEY TO CONTINUE
	PressAnyKey();
}//CreateHashTable

//-|-----------------------------------------------------------
//-| 3. Generate Location for Account Number to Be Stored In
//-|-----------------------------------------------------------
int EmployeeHashRecordsMenu :: HashFunction(int key)
{
	  //Compute & Return Index to Insert Function
	  return key % TableSize;
}//HashFunction
			  
//-|---------------------------------
//-| 4. Insert Records into Table
//-|---------------------------------
void EmployeeHashRecordsMenu :: Insert(char last_name2[15],char first_name2[15], int account_num2, int month2, int day2,
									   int year2, double annual_salary2, char dept_code2, char phone_number2[12])
{
	//Declare Variables
	int sub_script; //Variable to store probing location
	int Count = 0; //Variable to detect if Hash Table is full
	bool OpenSlotFound = false; //Variable to find open slot
	
	//Create Hash Key
	int Hash_Key = HashFunction(account_num2);
	
	//Check for Unused Slot, IF NULL, Insert Data into Slot
	if(HashTable[Hash_Key] == NULL || isDeleted(Hash_Key))
	{
		//Insert Data Into Slot
		HashTable[Hash_Key] = new HashNode(last_name2, first_name2, account_num2, month2, day2,
		                                   year2, annual_salary2, dept_code2, phone_number2);
	}//if
	
	//Else, Probe through the list for a open slot, (loop back to zero if needed)
	else
	{
		//Initialize sub_script to 0
		sub_script = 0;

		//Probe through list for open slot
		while(sub_script < TableSize)
		{
			//Check for if HashTable[sub_script] != NULL, then add 1 to count
			if(HashTable[sub_script] != NULL)
				Count++;
			//Iterate sub_script by 1
			sub_script++;
		}//while
		
		//Check for if HashTable is full
		if(isFull())
		{
			cout << endl << "Hash Table is FULL " << account_num2 << " cannot be added" << endl;
			
			//PRESS ANY KEY TO CONTINUE
			PressAnyKey();
		}//if
		
		else
		{
			//Move linear down the table & search for open slot
			for(sub_script = Hash_Key + 1; sub_script < TableSize; sub_script++)
			{
				//Search for open location
				if(HashTable[sub_script] == NULL || isDeleted(sub_script))
				{
					//Add data into open slot
					HashTable[sub_script] = new HashNode(last_name2, first_name2, account_num2, month2, day2,
													     year2, annual_salary2, dept_code2, phone_number2);
					//Assign CollisionFlag[] to 1
					CollisionFlag[sub_script] = 1;
					
					//Assign OpenSlotFound Flag to true
					OpenSlotFound = true;
					
					//break out of loop
					break;
				}//if
			}//for
		
			//If OpenSlotFound is false, check the upper part of the array for a empty slot
			if(OpenSlotFound == false)
			{
				for(sub_script = 0; sub_script < Hash_Key && CollisionFlag[sub_script] == 0; sub_script++)
				{
					//Search for open location
					if(HashTable[sub_script] == NULL || isDeleted(sub_script))
					{
						//Add data into open slot
						HashTable[sub_script] = new HashNode(last_name2, first_name2, account_num2, month2, day2,
															 year2, annual_salary2, dept_code2, phone_number2);
						//Assign CollisionFlag[] to 1
						CollisionFlag[sub_script] = 1;
						
						//Assign OpenSlotFound Flag to true
						OpenSlotFound = true;
						
						//break out of loop
						break;
					}//if
				}//for
			}//if
		}//inner-else
	}//outer-else
}//Insert

//-|----------------------------------------------------------------
//-| 5. Function to convert the Month number into its abbreviation
//-|----------------------------------------------------------------
string EmployeeHashRecordsMenu :: Date(int month3)
{
   //Declare Array To Hold Month Abbreviation
   const string DateAbbr[12] = {"Jan. ", "Feb. ", "Mar. ", "Apr. ", 
		                        "May ", "Jun. ", "Jul. ", "Aug. ", 
						        "Sep. ", "Oct. ", "Nov. ", "Dec. "};
	
   //Convert Month into Abbreviation
   switch(month3)
   {
	   case 1:  return DateAbbr[0];
		        break;
	   case 2:  return DateAbbr[1];
		        break;
	   case 3:  return DateAbbr[2];
		        break;
	   case 4:  return DateAbbr[3];
			    break;
	   case 5:  return DateAbbr[4];
		        break;
	   case 6:  return DateAbbr[5];
			    break;
	   case 7:  return DateAbbr[6];
			    break;
	   case 8:  return DateAbbr[7];
			    break;
	   case 9:  return DateAbbr[8];
		        break;
	   case 10: return DateAbbr[9];
			    break;
	   case 11: return DateAbbr[10];
				break;
	   case 12: return DateAbbr[11];
				break;
	   default: return ("Wrong Month Inserted....");
		        break;
   }//Switch
}//Date
			  
//-|-------------------------
//-| 6. Get Today's Date
//-|-------------------------
void EmployeeHashRecordsMenu :: GetDate(int &Month4, int &Day4, int &Year4)
{
	//Get Today's Date
	time_t t = time(0);
	tm* ltm = localtime(&t);
	
	//Assign Today's Month, Day, & Year
	Month4 = (ltm->tm_mon + 1);
	Day4 = ltm->tm_mday;
	Year4 = (ltm->tm_year + 1900);
}//GetDate

//-|----------------------------
//-| 7. Get Age of Employee
//-|----------------------------
int EmployeeHashRecordsMenu :: GetAge(int &Month5, int &Day5, int &Year5)
{
	//Declare Variables
	int Month2, Day2, Year2;
	
	//Call GetDate()
	GetDate(Month2, Day2, Year2);
	
	//Declare Array to Hold Employee's Birthday
	int Date1[] = {Month5, Day5, Year5};
	
	//Declare Array to Hold Today's Date
	int Date2[] = {Month2, Day2, Year2};

	//Subtract Date From Given Date
    tm a = {0,0,0,Day5,Month5,Year5};
	tm b = {0,0,0,Day2,Month2,Year2};
	time_t x = mktime(&a);
	time_t y = mktime(&b);
	
	//Get Employee's Birthday
	if(x != (time_t)(-1) && y != (time_t)(-1))
	{
		    //Declare Variables to Convert Employee's Birthday into Their Age
            double difference = difftime(y,x)/(60*60*24);
		    int rounding = (int)round(difference);
			int year = rounding/365;
			int days = rounding%365;
			int months = days/30;
		
			//-|-------------------------------------
			//-| 7[extra]. Convert The Date into Age
			//-|-------------------------------------
			
			//If year is >= 1 & months >= 6 & day >= 183 then, add 1 to the year
			if(year >= 1 && months >= 6 && days >= 183)
				return (year+1);
			//If year is >= 1 & months <= 5 & days <= 182 then, return the year as is
		    else if(year >= 1 & months <= 5 && days <= 182)
				return (year);
			//Else, return the 0
		    else
				return 0;
	}//if
}//GetAge()
			  
//-|----------------------			 
//-| 8. Print Subtitles
//-|----------------------
void EmployeeHashRecordsMenu :: PrintSubtitles(ostream& OutF)
{ 
	//Print Title & Subtitles to Screen
	cout << endl << endl << setw(66) << "Employee Report" << endl;
	cout << setw(66) << "***************" << endl << endl;
	cout << left << "Last Name" << right << setw(16) << "Acct. Number" 
		 << right << setw(24) << "Date of Birth" << right << setw(24) << "Annual Salary"
		 << right << setw(31) << "Department Code" << right << setw(18) << "Age" << endl; 
	
	//Print Title & Subtitles to File
	OutF << endl << endl << setw(66) << "Employee Report" << endl;
	OutF << setw(66) << "***************" << endl << endl;
	OutF << left << "Last Name" << right << setw(16) << "Acct. Number" 
		 << right << setw(23) << "Date of Birth" << right << setw(24) << "Annual Salary"
		 << right << setw(23) << "Department Code" << right << setw(13) << "Age" << endl; 
}//PrintSubtitles
			  
//-|-------------------------
//-| 9. Print Total Records
//-|-------------------------
void EmployeeHashRecordsMenu :: PrintTotalRecords(ostream& OutF)
{
	//Print the Total Records to Screen
	cout << endl << endl << left << "Total Record Count: " << TotalRecords << endl;
	
	//Print the Total Records to File
	OutF << endl << endl << left << "Total Record Count: " << TotalRecords << endl;
}//PrintTotalRecords
			  
//-|-------------------------------			  
//-| 10. Print Total Annual Salary
//-|-------------------------------
void EmployeeHashRecordsMenu :: PrintTotalAnnualSalary(ostream& OutF)
{
	//Print the Annual Salary to Screen
	cout << endl << endl << left << "Total Annual Salary: " << TotalAnnualSalary;
	
	//Print the Annual Salary to File
	OutF << endl << endl << left << "Total Annual Salary: " << TotalAnnualSalary;
}//PrintTotalAnnualSalary
			    
//-|-----------------------------
//-| 11. Print HashRecords Table
//-|-----------------------------
void EmployeeHashRecordsMenu :: Print()
{
	//Decalre Variables
	ofstream OutF; //ofstream variable
	
	//Open Outfile
	OutF.open("Printed_Data.txt");
	
	//Call PrintSubtitle() Function
	PrintSubtitles(OutF);
	
	//Print out Contents of Hash Table
	for(int i = 0; i < TableSize; i++)
	{
		//Assign CollisionSize to CollisionFlag[i]
		int CollisionSize = CollisionFlag[i];
		
		//Check for if CollisionSize > 0
		if(CollisionSize == 0)
		{
			//Call Print_Non_Collision_Data
			Print_Non_Collision_Data(i, OutF);
		}//if
		
		//Else, Print the Non Collision Data
		else
		{
			//Call Print_Data_Collisions
			Print_Data_Collisions(i, OutF);	
		}//else
	}//for
	
	//Call PrintTotalAnnualSalary() Function
	PrintTotalAnnualSalary(OutF);
	            
	//Print TotalRecords() Function
	PrintTotalRecords(OutF);
	
	//Close Outfile
	OutF.close();
	
	//Call PressAnyKey()
	PressAnyKey();
}//Print
			 
//-|-------------------------------------------------
//-| 12. Delete Memory for ALL Internal Components
//-|-------------------------------------------------
EmployeeHashRecordsMenu :: ~EmployeeHashRecordsMenu()
{
	//Traverse through Hash Table
	for(int i = 0; i < TableSize; i++)
    {
		if (HashTable[i] != NULL)
			delete HashTable[i];
    }//for
	
	//Delete the HashTable
    delete[] HashTable;
}//EmployeeHashRecordsMenu Destructor

//-|------------------------------------------
//-| 13. PrintData Depending on Collisions
//-|------------------------------------------
void EmployeeHashRecordsMenu :: Print_Data_Collisions(int sub_script, ostream& OutF)
{		
	//Check for if HashTable[i] is not NULL or != -1, if so, print out the data to Screen
	if(HashTable[sub_script] != NULL)
	{
		cout << left << HashTable[sub_script]->last_name << "\t\t"; 
		cout << setfill('0') << right << setw(4) << HashTable[sub_script]->account_num << '*';
	    cout << setfill(' ') << right << setw(20) << Date(HashTable[sub_script]->month);
		cout << setfill('0') << setw(2) << HashTable[sub_script]->day << ", " << HashTable[sub_script]->year;
		cout << setfill(' ') << right << setw(21) << fixed << setprecision(2) << HashTable[sub_script]->annual_salary;
		cout << right << setw(19) << "\t" << HashTable[sub_script]->dept_code;
		cout << right << setw(19) << "\t" << GetAge(HashTable[sub_script]->month, HashTable[sub_script]->day, HashTable[sub_script]->year) << endl;
	}//if		
	
	//Check for if HashTable[i] is not NULL or != -1, if so, print out the data to File
	if(HashTable[sub_script] != NULL)
	{
		OutF << left << HashTable[sub_script]->last_name << "\t\t"; 
		OutF << setfill('0') << right << setw(4) << HashTable[sub_script]->account_num << '*';
	    OutF << setfill(' ') << right << setw(20) << Date(HashTable[sub_script]->month);
		OutF << setfill('0') << setw(2) << HashTable[sub_script]->day << ", " << HashTable[sub_script]->year;
		OutF << setfill(' ') << right << setw(21) << fixed << setprecision(2) << HashTable[sub_script]->annual_salary;
		OutF << right << setw(19) << "\t" << HashTable[sub_script]->dept_code;
		OutF << right << setw(19) << "\t" << GetAge(HashTable[sub_script]->month, HashTable[sub_script]->day, HashTable[sub_script]->year) << endl;
	}//if		
}//PrintDataCollisions

//-|----------------------------------------
//-| 14. Print the Data in the First Slot
//-|----------------------------------------
void EmployeeHashRecordsMenu :: Print_Non_Collision_Data(int sub_script, ostream& OutF)
{
	//Check for if HashTable[i] is not NULL or != -1, if so, print out the data to Screen
	if(HashTable[sub_script] != NULL)
	{
		cout << left << HashTable[sub_script]->last_name << "\t\t"; 
		cout << setfill('0') << right << setw(4) << HashTable[sub_script]->account_num << " ";
	    cout << setfill(' ') << right << setw(20) << Date(HashTable[sub_script]->month);
		cout << setfill('0') << setw(2) << HashTable[sub_script]->day << ", " << HashTable[sub_script]->year;
		cout << setfill(' ') << right << setw(21) << fixed << setprecision(2) << HashTable[sub_script]->annual_salary;
		cout << right << setw(19) << "\t" << HashTable[sub_script]->dept_code;
		cout << right << setw(19) << "\t" << GetAge(HashTable[sub_script]->month, HashTable[sub_script]->day, HashTable[sub_script]->year) << endl;
	}//if		
	
	//Check for if HashTable[i] is not NULL or != -1, if so, print out the data to File
	if(HashTable[sub_script] != NULL)
	{
		OutF << left << HashTable[sub_script]->last_name << "\t\t"; 
		OutF << setfill('0') << right << setw(4) << HashTable[sub_script]->account_num << " ";
	    OutF << setfill(' ') << right << setw(20) << Date(HashTable[sub_script]->month);
		OutF << setfill('0') << setw(2) << HashTable[sub_script]->day << ", " << HashTable[sub_script]->year;
		OutF << setfill(' ') << right << setw(21) << fixed << setprecision(2) << HashTable[sub_script]->annual_salary;
		OutF << right << setw(19) << "\t" << HashTable[sub_script]->dept_code;
		OutF << right << setw(19) << "\t" << GetAge(HashTable[sub_script]->month, HashTable[sub_script]->day, HashTable[sub_script]->year) << endl;
	}//if		
}//PrintFirstData()

//-|---------------------------
//-| 15. Pause the System
//-|---------------------------
void EmployeeHashRecordsMenu :: Pause()
{
	//Pause The System for 2 Seconds
	sleep(2);
}//Pause

//-|-------------------------
//-| 16. Set Boolean Deleted
//-|-------------------------
void EmployeeHashRecordsMenu :: setDeleted(int sub_script)
{
	//Assign Deleted[] to true
	Deleted[sub_script] = true;
}//setDeleted

//-|---------------------------------------
//-| 17. Return boolean value of Deleted
//-|---------------------------------------
bool EmployeeHashRecordsMenu :: isDeleted(int sub_script)
{
	//return Deleted[]
	return Deleted[sub_script];
}//isDeleted

//-|-----------------------------
//-| 18. Add Data to Hash Table
//-|-----------------------------
void EmployeeHashRecordsMenu :: AddData()
{
	//Declare Variables
	char last_name2[15]; //Variable for Last Name
	char first_name2[15]; //Variable for First Name
	int account_num2; //Variable for Account Number
	int month2; //Variable for Month
	int day2; //Variable for Day
	int year2; //Variable for Year
	double annual_salary2; //Variable for Annual Salary
	char dept_code2; //Variable for Department Code
	char phone_number2[12]; //Variable for Phone Number
	
	//Check for if Hash Table is Full
	if(isFull())
	{
		//Print out Statement to screen
		cout << endl << endl << "Hash Table is FULL, [NO] Account Number can be ADDED!" << endl;
				
		//Call PressAnyKey()
		PressAnyKey();
	}//if
	
	//Else, proceed to possibly deleting the AccountNumber
	else
	{
		//Call GetAccountNumber() to Prompt & Validate Account Number
		GetAccountNumber(account_num2);
	
	    //-|--------------------------------------------------------------
		//-| 18[extra]. Search Hash Table for a Duplicate Account Number
		//-|--------------------------------------------------------------
		
		//Assign Hash_Index to SearchHashTable(AccountNumber) [Call SearchHashTable()]
		int Hash_Index = SearchHashTable(account_num2);
	
		//Determine if AccountNumber was found in Hash Table
		if(Hash_Index != -1)
		{
			//Print out Statement to Screen
			cout << endl << "DUPLICATES ARE NOT ALLOWED" << endl;
				
			//Call PressAnyKey()
			PressAnyKey();
		}//if
		
		//Else, Proceed to Add Data
		else
		{
			//Call GetName() to Prompt for Last Name, Middle Initial, & First Name
			GetName(last_name2, first_name2);
			
			//Call GetMonth() to Prompt for Month & Validate Month
			GetMonth(month2);
			
			//Call GetDay() to Prompt for Day & Validate Day
			GetDay(day2);
			
			//Call GetYear() to Prompt for Year & Validate Year 
			GetYear(year2);
				
			//Validate the User Input Date as One
			ValidateDate(month2, day2, year2);
				
			//Call GetAnnualSalary() to Prompt for Annual Salary & Validate Annual Salary
			GetAnnualSalary(annual_salary2);
			
			//Call GetDepartmentCode() to Prompt for Department Code & Validate Department Code
			GetDepartmentCode(dept_code2);
			
			//Call GetPhoneNumber() to Prompt for Phone Number & Validate Phone Number
			GetPhoneNumber(phone_number2);
			
			//Once Data Passes each test, Send Data to Insert() Funtion
			Insert(last_name2, first_name2, account_num2, month2, day2, year2, annual_salary2, dept_code2, phone_number2);
			
			//Count the Total Records Inputted into the Hash Table
			TotalRecords++;
	
			//Add annual_salary2 to TotalAnnualSalary
			TotalAnnualSalary += annual_salary2;
			
			//Increment the Size by 1
			Size++;
			
			//Display Statement
			cout << endl << endl << "RECORD " << account_num2 << " ADDED" << endl;
		}//else
	}//else
}//AddData

//-|---------------------------------
//-| 19. Press Any Key To Continue
//-|---------------------------------
void EmployeeHashRecordsMenu :: PressAnyKey()
{
	//Wait Until Any Key is Pressed BEFORE returning to Main Menu
	cout << endl;
	cout << endl << "Press ANY KEY to return to MAIN MENU: ";
	cin.ignore();
	cin.get();
	cout << endl << endl;
}//PressAnyKey

//-|-------------------------------------------------------
//-| 20. Function to Dump Records back into to "data_MST"
//-|-------------------------------------------------------
void EmployeeHashRecordsMenu :: DumpRecords()
{
	//Declare & Open outfile
	ofstream OutF;
	OutF.open("data_MST");
	
	//Print Out Contents of Hash Table
	for(int sub_script = 0; sub_script < TableSize; sub_script++)
	{
		if(HashTable[sub_script] != NULL)
		{
			OutF << HashTable[sub_script]->first_name << " " << HashTable[sub_script]->last_name << " " << HashTable[sub_script]->account_num
				 << " " << HashTable[sub_script]->month << " " << HashTable[sub_script]->day << " " << HashTable[sub_script]->year
				 << " " << HashTable[sub_script]->annual_salary << " " << HashTable[sub_script]->dept_code << " " << HashTable[sub_script]->phone_number
				 << endl;
		}//if	
	}//for
	
	//Display Save Statement
	cout << endl << endl << "CHANGES SAVED " << TotalRecords << " records written to data_MST FILE" << endl << endl;
	
	//Clear the File (COULD HURT YOUR PROGRAM ---- PLEASE DELETE THIS MESSAGE!!!!)
	OutF.clear();
	
	//Flush the File
	OutF.flush();
	
	//Close Out File
	OutF.close();
}//DumpRecords

//-|----------------------------------------------------------------
//-| 21. Search for Record in HashTable (Checking for Duplicates)
//-|----------------------------------------------------------------
int EmployeeHashRecordsMenu :: SearchHashTable(int account_num5)
{
	//Get Hash Code
	int Hash_Key = HashFunction(account_num5);
	
	//Search for Record in HashTable until Empty is encountered
	while(HashTable[Hash_Key] != NULL)
	{
		//If the HashTable[Hash_Key] Account Number equals account_num5, then return the Hash_Key
		if(HashTable[Hash_Key]->account_num == account_num5)
		{
			//Return the sub_script
			return Hash_Key;
			//Break out of loop
			break;
		}//if	
		
		//Go to next cell
		Hash_Key++;
		
		//Wrap Around the Table
		Hash_Key %= TableSize;
	}//while

	//Otherwise, the account_num was not found
	return -1;
}//SearchHashTable

//-|------------------------
//-| 22. Delete a record 
//-|------------------------
void EmployeeHashRecordsMenu :: DeleteRecord()
{
	//Declare Variables
	int AccountNumber; //Variable for AccountNumber
	int Hash_Index = 0; //Variable to hold Hash Index
	
	//Check for if Hash Table is empty
	if(isEmpty())
	{
		//Print out Statement to Screen
		cout << endl << endl << "Hash Table is EMPTY, [NO] Account Number can be DELETED!" << endl;
				
		//Call PressAnyKey()
		PressAnyKey();
	}//if
	
	//Else, proceed to possibly deleting the AccountNumber
	else
	{
		//Call GetAccountNumber() to Prompt & Validate Account Number
		GetAccountNumber(AccountNumber);
	
		//-|--------------------------------------------------------------
		//-| 22[extra]. Search Hash Table for a Duplicate Account Number
		//-|--------------------------------------------------------------
		
		//Assign Hash_Index to SearchHashTable(AccountNumber) [Call SearchHashTable()]
		Hash_Index = SearchHashTable(AccountNumber);
	
		//Determine if AccountNumber was found in Hash Table
		if(Hash_Index == -1)
		{
			//Print out Statement to Screen
			cout << endl << endl << "ACCOUNT NUMBER " << AccountNumber << " NOT FOUND!" << endl;
					
			//Call PressAnyKey()
			PressAnyKey();
		}//if
		
		//Else, Proceed to Delete AccountNumber
		else
		{
			//Declare Variables
			HashNode *temp = HashTable[Hash_Index]; //Assign temp node to HashTable[Hash_Index]
			
			//Assign NULL to HashTable[Hash_Index] for further use
			HashTable[Hash_Index] = NULL;
			
			//Call setDeleted() to set HashTable[Hash_Index] to true
			setDeleted(Hash_Index);
			
			//Display Statement
			cout << endl << endl << "RECORD " << AccountNumber << " DELETED" << endl;
			
			//Decrement Size by 1
			Size--;
			
			//Decrement TotalRecords by 1
			TotalRecords--;
			
			//Call PressAnyKey() Funtion to Continue
			PressAnyKey();
		}//else
	}//else
}//DeleteRecord

//-|--------------------------------------------
//-| 23. Prompt for & Validate Account Number
//-|--------------------------------------------
void EmployeeHashRecordsMenu :: GetAccountNumber(int & AccountNumber)
{
	//Declare Prompt for Account Number
	string Prompt = "Enter Account Number: ";
	
	//Call Validate_Numbers() to Prompt for Account Number & Validate Number
	Validate_Numbers(AccountNumber, Prompt);
}//GetAccountNumber

//-|---------------------------------------
//-| 24. Determine if Hash Table is Empty
//-|---------------------------------------
bool EmployeeHashRecordsMenu :: isEmpty()
{
	//Return Size == 0, if (Size == 0) then the Hash Table is empty
	return (Size == 0);
}//isEmpty

//-|---------------------------------------
//-| 25. Determine if Hash Table is Full
//-|---------------------------------------
bool EmployeeHashRecordsMenu :: isFull()
{
	//Return Size == TableSize, if (Size == TableSize) then the Hash Table is full
	return (Size == TableSize);
}//isFull
		

//-|----------------------------------
//-| 26. Prompt for & Validate Month
//-|----------------------------------
void EmployeeHashRecordsMenu :: GetMonth(int &Month)
{
	//Declare Prompt for Month ----> 02
	string Prompt = "Enter Month (EX: 02 OR 2): ";
	
	//Call Validate_Numbers() to Prompt & Validate Month
	Validate_Numbers(Month, Prompt);
		
	//Validate Month
	while (Month < 1 || Month > 12)
	{
		//Call Validate_Numbers() to Prompt & Validate Month
		Validate_Numbers(Month, Prompt);
	}//while
}//GetMonth52

//-|----------------------------------
//-| 27. Prompt for & Validate Day
//-|----------------------------------
void EmployeeHashRecordsMenu :: GetDay(int &Day)
{
	//Declare Prompt for Day ----> 03
	string Prompt = "Enter Day (EX: 03 OR 3): ";
	
	//Call Validate_Numbers() to Prompt & Validate Day
	Validate_Numbers(Day, Prompt);
		
	//Validate Day
	while(Day < 1 || Day > 31)
	{
		//Call Validate_Numbers() to Prompt & Validate Day
		Validate_Numbers(Day, Prompt);
	}//while
}//GetDay

//-|----------------------------------
//-| 28. Prompt for & Validate Year
//-|----------------------------------
void EmployeeHashRecordsMenu :: GetYear(int &Year)
{
	//Declare Prompt for Year ----> 2018
	string Prompt = "Enter Year (EX: 2018): ";
	
	//Call Validate_Numbers() to Prompt & Validate Year
	Validate_Numbers(Year, Prompt);
	
	//Validate Year
	while(Year <= 0)
	{
		//Call Validate_Numbers() to Prompt & Validate Year
		Validate_Numbers(Year, Prompt);
	}//while
}//GetYear

//-|-----------------------------
//-| 29. Prompt for & [Validate]
//-|-----------------------------
void EmployeeHashRecordsMenu :: GetName(char (&LastName)[15], char (&FirstName)[15])
{
	    //Prompt for Last Name
		cout << "Enter Last Name: ";
		cin >> LastName;
			
		//Prompt for First Name
		cout << "Enter First Name: ";
		cin >> FirstName;
}//GetName

//-|---------------------------------------
//-| 30. Determines if year is Leap Year
//-|---------------------------------------
bool EmployeeHashRecordsMenu :: isLeap (int year)
{
	//Return true if the year is a multiple of 4 and not a multiple of 100.
	return(((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}//isLeap

//-|-----------------------------
//-| 31. Validate given year
//-|-----------------------------
bool EmployeeHashRecordsMenu :: isValidDate(int month2, int day2, int year2)
{
	//Declare Max & Min Valid Years
	const int MAX_YEAR = 9999;
	const int MIN_YEAR = 1800;
	
	 // If year, month and day are not in given range, return false
    if(year2 > MAX_YEAR || year2 < MIN_YEAR)
      return false;
 
    //Handle February month with leap year
    if(month2 == 2)
    {
        if (isLeap(year2))
           return (day2 <= 29);
        else
           return (day2 <= 28);
    }//if
 
    //Handle the months of April, June, Sept and Nov.
    if(month2 == 4 || month2 == 6 || month2 == 9 || month2 == 11)
		return (day2 <= 30);
 
	//Return true, if date is valid
    return true;
}//isValidDate

//-|------------------------------------------
//-| 32. Check Dates For Being Out Of Bounds
//-|------------------------------------------
bool EmployeeHashRecordsMenu :: CheckDate(int Month, int Day, int Year)
{
	//Get Today's Date
	time_t t = time(0);
	tm* ltm = localtime(&t);
	
	//Return False If Today's Year Is Less Than or Equal To File's Year
	if((ltm->tm_year + 1900) < Year)
		return false;
	
	//Return False If Today's Month Is Less Than or Equal To User's Input Month, Today's Day Is Less Than User's Input, 
	//and Today's Year Is Less Than or Equal To User's Input 
	//(e.g - Today: 2/19/2018 ----> User's Input Date: 2/20/2018)
	else if((ltm->tm_mon + 1) <= Month && (ltm->tm_mday) < Day && (ltm->tm_year + 1900) <= Year)
		return false;
	
	//Return False If Today's Month Is Less Than User's Input Month, Today's Day Is Less Than User's Input Day, 
	//and Today's Year Is Less Than or Equal To User's Input Year 
	//(e.g - Today: 2/21/2018 ----> User's Input Date: 2/27/2018)
	else if((ltm->tm_mon + 1) < Month && (ltm->tm_mday) < Day && (ltm->tm_year + 1900) <= Year)
		return false;
	
	//Return False If Today's Month Is Less Than User's Input Month, Today's Day Is Less Than or Equal To User's Input Day, 
	//and Today's Year Is Less Than or Equal To User's Input Year 
	//(e.g - Today: 2/19/2018 ----> User's Input Date: 3/19/2018)
	else if((ltm->tm_mon + 1) < Month && (ltm->tm_mday) <= Day && (ltm->tm_year + 1900) <= Year)
		return false;
	
	//Return True if User's Input Date Doesn't FAIL Test
	else 
		return true;
}//CheckDate
		
//-|------------------------------------
//-| 33. Validate Date Using CheckDate()
//-|------------------------------------
void EmployeeHashRecordsMenu :: ValidateDate(int &Month2, int &Day2, int &Year2)
{
	//Validate Date as One (Make Sure Date is not out of Boundaries)
	while(CheckDate(Month2, Day2, Year2) == false || isValidDate(Month2, Day2, Year2) == false)
	{
		//Prompt for Correct Date
		cout << endl << "Invalid Date: " << endl << endl;
		
		//Call Pause() Funtion
		Pause();
		
		//Call GetMonth()
		GetMonth(Month2);
		
		//Call GetDay()
		GetDay(Day2);
		
		//Call GetYear()
		GetYear(Year2);
	}//while
}//ValidateDate

//-|-----------------------------------------
//-| 34. Prompt for & Validate Annual Salary
//-|-----------------------------------------
void EmployeeHashRecordsMenu :: GetAnnualSalary(double &AnnualSalary)
{
	//Prompt for Annual Salary
	cout << "Enter Annual Salary: ";
	cin >> AnnualSalary;
	
	//Validate Annual Salary
	while(AnnualSalary < 0.00)
	{
		//Re-Prompt for Annual Salary
		cout << "Enter Annual Salary: ";
		cin >> AnnualSalary;
	}//while
}//GetAnnualSalary

//-|---------------------------------------------
//-| 35. Prompt for & Validate Department Code 
//-|---------------------------------------------
void EmployeeHashRecordsMenu :: GetDepartmentCode(char& DepartmentCode)
{
	//Prompt for Department Code
	cout << "Enter Department Code: ";
	cin >> DepartmentCode;
	
	//Validate Department Code
	while(!isalpha(DepartmentCode))
	{
		//Re-Prompt for Annual Salary
		cout << "Enter Department Code: ";
		cin >> DepartmentCode;
	}//while
	
	//Make DepartmentCode Uppercase To Lessen Readability
	DepartmentCode = toupper(DepartmentCode);
}//GetDepartmentCode

//-|----------------------------------------
//-| 36. Prompt for Phone Number
//-|----------------------------------------
void EmployeeHashRecordsMenu :: GetPhoneNumber(char (&PhoneNumber)[12])
{
	//Prompt for Phone Number
	cout << "Enter Phone Number (EX: 813-555-7469): ";
	cin >> PhoneNumber;

	//Call ValidatePhoneNumber()
	ValidatePhoneNumber(PhoneNumber);
}//ValidatePhoneNumber

//-|------------------------------------------------------
//-| 37. Validate Phone Number
//-|------------------------------------------------------
void EmployeeHashRecordsMenu :: ValidatePhoneNumber(char (&char_PhoneNumber)[12])
{
	//Declare Variable
	bool isPhoneNumber = true; //Variable to confirm if Phone Number is valid
	int PhoneNumberCounter = 0; //Variable to count Phone Number values
	int DashesCounter = 0; //Variable to count Phone Number dashes
	const int PhoneNum_Value = 10; //Variable to determine if Phone Number has 10 values
	const int Dashes_Value = 2; //Variable to determine if Phone Number has 2 dashes
	int i = 0; //Loop Control Variable
	
		
	//-|-----------------------------
	//-| 37b. Validate Phone Number
	//-|-----------------------------
	
	//Check size of string
	while(strlen(char_PhoneNumber) == 0 || strlen(char_PhoneNumber) > 12)
	{
		//Output Statement
		cout << endl << endl << "Phone Number is out of BOUNDS [Phone Number == 0 OR Phone Number >12 (including dashes)]" << endl << endl << endl;
		
		//Re-Prompt for Phone Number
		GetPhoneNumber(char_PhoneNumber);
	}//1st while
		
	//Check for Phone Number containing ANYTHING ELSE other than #'s & dashes's
	while(isPhoneNumber == true && i < (strlen(char_PhoneNumber)))
	{	
		//Check for if Phone Number Contains Number's
		if(char_PhoneNumber[i] >='0' && char_PhoneNumber[i] <= '9')
		{
			//Count PhoneNumberCounter by 1
			PhoneNumberCounter++;
		}//if
		
		//Check for if Phone Number Contains Dashes
		else if(char_PhoneNumber[i] == '-')
			//Count DashesCounter by 1
			DashesCounter++;

		//Else, the User Input is not a Phone Number
		else
			isPhoneNumber = false;
					
		//Iterate i by 1
		i++;	
	}//while
	
	//If |isPhoneNumber == false| OR |PhoneNumberCounter > 10 OR < 10| OR |DashesCounter > 2 OR < 2|, 
	//Call ValidatePhoneNumber() to Re-Prompt for Phone Number
	if((isPhoneNumber == false) || (PhoneNumberCounter > PhoneNum_Value) || (PhoneNumberCounter < PhoneNum_Value)
	                             || (DashesCounter > Dashes_Value) || (DashesCounter < Dashes_Value))
	{	
		//Assign DashesCounter & PhoneNumberCounter to 0
		DashesCounter = PhoneNumberCounter = 0;
		
		//Re-Prompt for Phone Number
		GetPhoneNumber(char_PhoneNumber);
	}//if
}//GetPhoneNumber

//-|----------------------
//-| 38. Modify Record
//-|----------------------
void EmployeeHashRecordsMenu :: Modify()
{
	//Declare variables                 
	char last_name3[15]; //Variable for Last Name
	char first_name3[15]; //Variable for First Name
	int account_num3; //Variable for Account Number
	int month3; //Variable for Month
	int day3; //Variable for Day
	int year3; //Variable for Year
	double annual_salary3; //Variable for Annual Salary
	char dept_code3; //Variable for Department Code
	char phone_number3[12];//Variable for Phone Number
	int Hash_Index = 0; //Hash_Index Variable
	
	//Check for if Hash Table is empty
	if(isEmpty())
	{
		//Print out EMPTY Statement to screen
		cout << endl << endl << "Hash Table is EMPTY, [NO] Account Number can be MODIFIED!" << endl;
				
		//Call PressAnyKey()
		PressAnyKey();
	}//if
	
	//Else, proceed to possibly modifying the AccountNumber
	else
	{
		//Call GetAccountNumber() to Prompt & Validate Account Number
		GetAccountNumber(account_num3);
	
		//-|--------------------------------------------------------------
		//-| 38[extra]. Search Hash Table for a Duplicate Account Number
		//-|--------------------------------------------------------------
		
		//Assign Hash_Index to SearchHashTable(AccountNumber) [Call SearchHashTable()]
		Hash_Index = SearchHashTable(account_num3);
	
		//Determine if AccountNumber was found in Hash Table
		if(Hash_Index == -1)
		{
			//Print out Statement to Screen
			cout << endl << endl << "ACCOUNT NUMBER " << account_num3 << " NOT FOUND!" << endl;
					
			//Call PressAnyKey()
			PressAnyKey();
		}//if

		//Else, Proceed to Modify AccountNumber
		else
		{
			//Call GetPhoneNumber() to Prompt for Phone Number & Validate Phone Number
			GetPhoneNumber(phone_number3);
			
			//Once Data Passes each test, Send Data to Insert() Funtion to Modify
			ModifyData(Hash_Index, phone_number3);

			//Display Statement
			cout << endl << "ACCOUNT NUMBER " << account_num3 << " PHONE NUMBER MODIFIED" << endl << endl;
		
			//Call PressAnyKey() Funtion to Continue
			PressAnyKey();
		}//else
	}//else
}//Modify

//-|---------------------------
//-| 39. Validate Numbers
//-|---------------------------
void EmployeeHashRecordsMenu :: Validate_Numbers(int &Numberto_Convert, string Prompt)
{
	//Declare Variable
	string Convert_NUM;  //Variable to input Numberto_Convert into
	bool is_NUM = false;  //Flag to determine if string is a number
	int i = 0;  //Loop Contol Variable
	Numberto_Convert = 0; //Assign Numberto_Convert to Zero to place string Convert_NUM into Numberto_Convert

	//OutPut Prompt
	cout << Prompt;
	cin >> Convert_NUM;
	
    //Validate Number
    while(is_NUM == false && i < Convert_NUM.size())
    {
		//If any Convert_NUM characters do not contain a number, prompt user for a valid input
		if((Convert_NUM[i] >= '0' && Convert_NUM[i] <= '9') == false)
		{
			cin.clear(); // clears error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore until maxed/newline is reached
			
			//Assign 0 to i
			i = 0;
			
			//Re-Prompt
			cout << Prompt;
			cin >> Convert_NUM;
		}//if
		else
		{
			//If char is a number, increment i by one
			i++;
		}//else
    }//while

	//Create a object from the class stringstream to convert string into integer
    stringstream Convert(Convert_NUM);
 
    //Stream value into Numberto_Convert
    Convert >> Numberto_Convert;
}//Validate_Numbers

//-|---------------------------------------------------
//-| 40. Assign Hash_Key to Modified Phone Number Data
//-|---------------------------------------------------
void EmployeeHashRecordsMenu :: ModifyData(int Hash_Key, char phone_number2[12])
{
	//Create a new HashTable[Hash_Key] & assign new phone_number to Account
	strncpy(HashTable[Hash_Key]->phone_number, phone_number2, 12);
}//ModifyData