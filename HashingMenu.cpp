//------------------------------------------------------------------
// File name:   HashingMenu.cpp
// Assign ID:   Project 4B
// Due Date:    3/22/18 at 12:30 pm
//
// Purpose:     Write a C++ program that inputs an unknown number of records from a 
//              sequential file. Write a C++ program to create a hash table (containing 17 slots to store records)
//              store the records using account_num as the key field. Use the method called linear probing to handle 
//              collisions.
//       
// Author:      Tishauna Wilson
//------------------------------------------------------------------
#include "EmployeeHashRecordsMenu.cpp"
#include <cctype>
using namespace std;

//-|----------------------------------------------------------------
//-|Display The Main Menu Commands
//-|----------------------------------------------------------------
void ShowCommands()
{
	//Show The Commands
	cout << endl << endl;
	cout << "HASH TABLE UPDATE SYSTEM" << endl << endl;
	cout << "1) Create Hash table and populate with data records from input file Named \"data_MST\"" << endl;
	cout << "2) Add a Record" << endl;
	cout << "3) Modify a record" << endl;
	cout << "4) Delete a record" << endl;
	cout << "5) Print report" << endl;
	cout << "6) Quit" << endl;
	cout << endl;
}//ShowCommands

//-|----------------------------------------------------------------
//-|Perform The User Commands To Manipulate The Program
//-|----------------------------------------------------------------
void PerformCommand(int Command)
{	
	//Object for EmployeeHashRecordsMenu
	static EmployeeHashRecordsMenu Data;
	
    //Switch to Perform the Desired Command
	switch(Command)
	{
		case 1: //Create Hash Table
			    Data.CreateHashTable();
			    break;
		case 2: //Add a Record
				//Call AddData() Function
				Data.AddData();
			    break;
		case 3: //Modify a Record
				Data.Modify();
			    break;
		case 4: //Delete
				//Call DeleteRecord() Function
			    Data.DeleteRecord();
			    break;
		case 5: //Print Report
	            //Call Print() Function
	            Data.Print();
			    break;
		case 6: //Quit the Program {Dump Records from Hash Table back into the file "data_MST}, then terminates the program
				//Call DumpRecords() Function
			    Data.DumpRecords();
			    cout << endl << "TERMINATING PROGRAM." << endl;
			    cout << "(c) 2018, Tishauna Wilson" << endl << endl;
			    Data.Pause();
				//Exit out of program
			    exit(1);
			    break;
		default:break;	
	}//switch
}//PerformCommand

int main()
{
   //-|------------------------------------------------------------------------
   //-| Declare Variables
   //-|------------------------------------------------------------------------
   int Command = 0; //Variable to hold Command
   bool isCommand = true; //Variable to allow do-while loop to continue looping
   EmployeeHashRecordsMenu Data; //Object for EmployeeHashRecordsMenu
   string Prompt = "Enter Option: "; //string for Prompt
   string Re_EnterPrompt = "Error <Re-Enter Valid Option>: "; //string for Re_EnterPrompt
	
   //-| ----------------------------------------------------------------------
   //-| Print the copyright notice declaring authorship.
   //-| ----------------------------------------------------------------------
   cout << endl << "(c) 2018, Tishauna Wilson" << endl << endl; 

   //-| ----------------------------------------------------------------------
   //-| 1. Show The Commands of the Menu and Choose Perform A Command
   //-| ----------------------------------------------------------------------
   ShowCommands();
	
   //Prompt & Validate Commands by using Validate_Numbers()
   Data.Validate_Numbers(Command, Prompt);

   //Loop through do-while loop until program terminates
   do
   {
	   //Check for Commands that are out of Boundaries
	   while((Command != 1) && (Command != 2) && (Command != 3) && (Command != 4) && (Command != 5) && (Command != 6))
	   {
			  //Re-Prompt & Validate Commands by using Validate_Numbers()
			  Data.Validate_Numbers(Command, Re_EnterPrompt);
	   }//while
	 
	   //Once a valid Command is entered, call the PerformCommand() function
	   PerformCommand(Command);
	   
	   //Show Commands Again
	   ShowCommands();
	   
	   //Prompt & Validate Commands by using Validate_Numbers()
	   Data.Validate_Numbers(Command, Prompt);
	   
   }while(isCommand == true);//do-while
	
   //-| ----------------------------------------------------------------------
   //-| Print the copyright notice declaring authorship again.
   //-| ----------------------------------------------------------------------
   cout << endl << "(c) 2018, Tishauna Wilson" << endl << endl; 
   return 0;
}//main