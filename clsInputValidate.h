#pragma once
#include <iostream>
#include "clsDate.h"

using namespace std;

class clsInputValidate
{
public:

	static void  Srand()
	{
		//Seeds the random number generator in C++, called only once
		srand((unsigned)time(NULL));
	}

	static  int RandomNumber(int From, int To)
	{
		//Function to generate a random number
		int randNum = rand() % (To - From + 1) + From;
		return randNum;
	}

	static bool IsNumberBetween(int Number, int From, int To)
	{
		return (Number >= From && Number <= To);
	}

	static bool IsNumberBetween(double Number, double From, double To)
	{
		return (Number >= From && Number <= To);
	}

	static bool IsDateBetween(clsDate DateCheck, clsDate Date1, clsDate Date2)
	{
		if (
			(clsDate::IsDate1EqualsDate2(DateCheck, Date1) || clsDate::IsDate1AfterDate2(DateCheck, Date1))
			&&
			(clsDate::IsDate1EqualsDate2(DateCheck, Date2) || clsDate::IsDate1LessThanDate2(DateCheck, Date2))
			)
			return true;
		if (
			(clsDate::IsDate1EqualsDate2(DateCheck, Date1) || clsDate::IsDate1LessThanDate2(DateCheck, Date1))
			&&
			(clsDate::IsDate1EqualsDate2(DateCheck, Date2) || clsDate::IsDate1AfterDate2(DateCheck, Date2))
			)
			return true;
	}

	static int ReadIntNumber(string ErrorMessage)
	{
		int Number = 0;
		cin >> Number;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ErrorMessage << endl;
			cin >> Number;
		}
		return Number;
	}
	
	static double ReadDoubleNumber(string ErrorMessage)
	{
		double Number = 0;
		cin >> Number;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ErrorMessage << endl;
			cin >> Number;
		}
		return Number;
	}

	static float ReadFloatNumber(string ErrorMessage)
	{
		float Number = 0;
		cin >> Number;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ErrorMessage << endl;
			cin >> Number;
		}
		return Number;
	}

	static int ReadIntNumberBetween(int From, int To, string ErrorMessage)
	{
		int Number = ReadIntNumber("Error number, try again");
		while (! IsNumberBetween(Number,From,To))
		{
			cout << ErrorMessage << endl;
			Number = ReadIntNumber("Error number, try again");
		}
		return Number;
	}

	static double ReadDoubleNumberBetween(double From, double To, string ErrorMessage)
	{
		double Number = ReadDoubleNumber("Error number, try again");
		while (! IsNumberBetween(Number,From,To))
		{
			cout << ErrorMessage << endl;
			Number = ReadDoubleNumber("Error number, try again");
		}
		return Number;
	}

	static string ReadString()
	{
		string s;
		getline(cin >> ws, s);
		return s;
	}

};

