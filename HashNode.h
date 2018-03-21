#ifndef HASHNODE_H
#define HASHNODE_H
#include <cstring>

//HashNode Class Declaration - For Linear Probing
class HashNode
{
	public:
		char last_name[15]; //Variable for Last Name
		char first_name[15]; //Variable for First Name
		int account_num; //Variable for Account Number
		int month; //Variable for Month
		int day; //Variable for Day
		int year; //Variable for Year
		double annual_salary; //Variable for Annual Salary
		char dept_code; //Variable for Department Code
		char phone_number[12]; //Variable for Phone Number
		HashNode(); //1st Constructor HashNode
		HashNode(char last_name1[15], char first_name1[15], int account_num1, int month1, int day1,
		         int year1, double annual_salary1, char dept_code1, char phone_number1[12])
		{
		    //Initialize Variables to Inserted Variables
		    strncpy(last_name, last_name1, 15);
                    last_name[14] = '\0';
		    strncpy(first_name, first_name1, 15);
                    first_name[14] = '\0';
		    account_num = account_num1;
		    month = month1;
		    day = day1;
		    year = year1;
		    annual_salary = annual_salary1;
		    dept_code = dept_code1;
		    strncpy(phone_number, phone_number1, 12);
                    phone_number[11] = '\0';
		}//2nd Constructor HashNode
};//HashNode
#endif
