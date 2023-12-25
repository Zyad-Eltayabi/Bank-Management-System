#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <ctime> // get it form C library
#include "Global.h"

using namespace std;

class clsAddDate
{
private:

public:

	static string LoggedCurrentUser()
	{
		return CurrentUser.UserName;
	}

	static string GetDate()
	{
		time_t t = time(0); // get time now
		tm* now = localtime(&t);
		return to_string(now->tm_mday) + "/" + to_string(now->tm_mon + 1) + "/" + to_string(now->tm_year + 1900);
	}
};

