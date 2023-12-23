#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include <ctime> // get it form C library
#include <iomanip>
using namespace std;
class clsDate
{
private:
	struct stDate
	{
		short Day;
		short Month;
		short Year;
	};
	stDate _Data;
protected:
	static void PrintMonthTittle(short Month)
	{
		string Months[13] = { "","January", "February" ,"March" ,"April" ,"May" ,"June" ,"July", "August" ,"September" ,"October","November", "December" };
		cout << "__________________________" << Months[Month] << "__________________________" << endl;
		cout << "\n";
		cout << setw(3) << "Sun" << " " << setw(3) << "Mon" << " " << setw(3) << "Tue" << " "
			<< setw(3) << "Wed" << " " << setw(3) << "Thu" << " " << setw(3) << "Fri" << " "
			<< setw(3) << "Sat" << " ";
		cout << "\n";
	}

	static string Space(short num)
	{
		string TotalSpace = "";
		for (short i = 0; i < num; i++)
		{
			TotalSpace = "    " + TotalSpace;
		}
		return TotalSpace;
	}
public:
	clsDate()
	{
		time_t t = time(0); // get time now
		tm* now = localtime(&t);
		_Data.Day = now->tm_mday;
		_Data.Month = now->tm_mon + 1;
		_Data.Year = now->tm_year + 1900;
	}

	clsDate(string DateFromUser)
	{
		vector <string> vDateString = SplitString(DateFromUser, GetDelim(DateFromUser));
		_Data.Day = stoi(vDateString[0]);
		_Data.Month = stoi(vDateString[1]);
		_Data.Year = stoi(vDateString[2]);
	}

	clsDate(short Day, short Month, short Year)
	{
		_Data.Day = Day;
		_Data.Month = Month;
		_Data.Year = Year;
	}

	// set and get property
	void SetDay(short Day)
	{
		_Data.Day = Day;
	}
	short GetDay()
	{
		return _Data.Day;
	}
	void SetMonth(short Month)
	{
		_Data.Month = Month;
	}
	short GetMonth()
	{
		return _Data.Month;
	}
	void SetYear(short Year)
	{
		_Data.Year = Year;
	}
	short GetYear()
	{
		return _Data.Year;
	}
	__declspec(property(put = SetDay, get = GetDay)) short Day;
	__declspec(property(put = SetMonth, get = GetMonth)) short Month;
	__declspec(property(put = SetYear, get = GetYear)) short Year;

	clsDate(int Days, int Year)
	{
		_Data = ConvertTotalDaysFromTheBeginningOfYearToData(Year, Days);
	}

	void PrintDate()
	{
		cout << _Data.Day << "/" << _Data.Month << "/" << _Data.Year << endl;
	}

	string GetDelim(string Date)
	{
		for (char& d : Date)
		{
			if (d == '/' || d == '-')
			{
				string s(1, d);
				return s;
			}
		}
	};

	vector <string> SplitString(string S1, string delim)
	{
		vector <string> vTokens;
		short pos = 0;
		string sWord; // define a string variable
		// use find() function to get the position of the delimiters
		while ((pos = S1.find(delim)) != std::string::npos)
		{
			sWord = S1.substr(0, pos);
			if (sWord != "")
			{
				vTokens.push_back(sWord);
			}
			S1.erase(0, pos + delim.length());
		}
		if (S1 != "")
		{
			vTokens.push_back(S1);

		}
		return vTokens;
	}

	static bool CheckLeapYear(int Number)
	{
		return ((Number % 4 == 0 && Number % 100 != 0) || (Number % 400 == 0));
	}

	bool CheckLeapYear()
	{
		return CheckLeapYear(_Data.Year);
	}

	static int NumberOfDaysInCertainMonth(int Month)
	{
		int arr[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		return arr[Month];
	}

	int NumberOfDaysInCertainMonth()
	{
		return NumberOfDaysInCertainMonth(_Data.Month);
	}

	static int CountDaysInMonth(int Year, int Month)
	{
		return (Month == 2) ? (CheckLeapYear(Year) ? 29 : NumberOfDaysInCertainMonth(Month))
			: NumberOfDaysInCertainMonth(Month);
	}

	int CountDaysInMonth()
	{
		return CountDaysInMonth(_Data.Year, _Data.Month);
	}

	static stDate ConvertTotalDaysFromTheBeginningOfYearToData(int Year, int NumberOfDays)
	{
		short CountDays = 0;
		stDate FullDate;
		for (short i = 1; i < 13; i++)
		{
			CountDays += CountDaysInMonth(Year, i);
			if (CountDays >= NumberOfDays)
			{
				FullDate.Day = CountDaysInMonth(Year, i) - (CountDays - NumberOfDays);
				FullDate.Month = i;
				FullDate.Year = Year;
				return FullDate;
			}
		}
	}

	stDate ConvertTotalDaysFromTheBeginningOfYearToData(int Number)
	{
		return ConvertTotalDaysFromTheBeginningOfYearToData(_Data.Year, Number);
	}

	static short DayOrder(short Year, short Month, short Day)
	{
		short a, y, m, d;
		a = (14 - Month) / 12;
		y = Year - a;
		m = Month + (12 * a) - 2;
		// use gregorian calender 
		d = (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
		return d;
	}

	short DayOrder()
	{
		return DayOrder(_Data.Year, _Data.Month, _Data.Day);
	}

	static void PrintDayName(short Year, short Month, short Day)
	{
		string DaysOfWeeks[7] = { "Sunday", "Monday", "Tuesday", "Wednesday" ,"Thursday", "Friday", "Saturday" };
		cout << "Data          : " << Day << "/" << Month << "/" << Year << endl;
		cout << "Day Order     : " << DayOrder(Year, Month, Day) << endl;
		cout << "Day Name      : " << DaysOfWeeks[DayOrder(Year, Month, Day)];
	}

	void PrintDayName()
	{
		PrintDayName(_Data.Year, _Data.Month, _Data.Day);
	}

	static void PrintCalendar(short Year, short Month)
	{
		PrintMonthTittle(Month);
		int Days = CountDaysInMonth(Year, Month);
		short FirstDayInMonth = DayOrder(Year, Month, 1);
		short Separator = FirstDayInMonth;

		cout << Space(FirstDayInMonth);
		for (short i = 1; i <= Days; i++)
		{
			Separator++;
			cout << setw(3) << i << " ";
			if (Separator == 7)
			{
				cout << "\n";
				Separator = 0;
			}
		}
		cout << "\n_________________________________________________________" << endl;
	}

	void PrintCalendar()
	{
		PrintCalendar(_Data.Year, _Data.Month);
	}

	static void PrintYearCalendar(int Year)
	{
		cout << "\n_________________________________________________________" << endl;
		cout << "\n" << setw(30) << "Calendar " << Year;
		cout << "\n_________________________________________________________" << endl;
		for (short i = 1; i < 13; i++)
		{
			PrintCalendar(Year, i);
		}
	}

	void PrintYearCalendar()
	{
		PrintYearCalendar(_Data.Year);
	}

	static short TotalDaysFromTheBeginningOfYear(int Year, int Month, int Days)
	{
		short CountDays = 0;
		for (short i = 1; i < 13; i++)
		{
			if (i == Month)
				return CountDays + Days;
			CountDays += CountDaysInMonth(Year, i);
		}
	}

	short TotalDaysFromTheBeginningOfYear()
	{
		return TotalDaysFromTheBeginningOfYear(_Data.Year, _Data.Month, _Data.Day);
	}

	static stDate CountDataAfterAddedDays(stDate Date, short AddedDays)
	{
		short RemainingDays = AddedDays + TotalDaysFromTheBeginningOfYear(Date.Year, Date.Month, Date.Day);
		short MonthDays = 0;
		Date.Month = 1;
		while (true)
		{
			MonthDays = CountDaysInMonth(Date.Year, Date.Month);
			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date.Month++;
				if (Date.Month > 12)
				{
					Date.Month = 1;
					Date.Year++;
				}
			}
			else
			{
				Date.Day = RemainingDays;
				break;
			}
		}
		return Date;
	}

	void CountDataAfterAddedDays(int AddedDays)
	{
		_Data = CountDataAfterAddedDays(_Data, AddedDays);
	}

	static bool IsDate1LessThanDate2(clsDate Date1, clsDate Date2)
	{
		if (Date2.Year > Date1.Year)
			return true;
		else
		{
			if (Date2.Year == Date1.Year)
			{
				if (Date2.Month > Date1.Month)
				{
					return true;
				}
				else
				{
					if (Date2.Month == Date1.Month)
					{
						if (Date2.Day > Date1.Day)
							return true;
						else
							return false;
					}
					else
					{
						return false;
					}
				}
			}
			else
			{
				return false;
			}
		}
	}

	bool IsDate1LessThanDate2(clsDate Date2)
	{
		return IsDate1LessThanDate2(*this, Date2);
	}

	static bool IsDate1EqualsDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1.Year == Date2.Year) ? ((Date1.Month == Date2.Month) ? ((Date1.Day == Date2.Day) ? true : false) : false) : false;
	}
	bool IsDate1EqualsDate2(clsDate Date2)
	{
		return IsDate1EqualsDate2(*this, Date2);
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return (IsDate1LessThanDate2(Date1, Date2) || IsDate1EqualsDate2(Date1, Date2)) ? false : true;
	}

	bool IsDate1AfterDate2(clsDate Date2)
	{
		return IsDate1AfterDate2(*this, Date2);
	}

	static short CompareDateFunction(clsDate Date1, clsDate Date2)
	{
		return IsDate1EqualsDate2(Date1, Date2) ? 0 : ((IsDate1AfterDate2(Date1, Date2) ? 1 : -1));
	}

	short CompareDateFunction(clsDate Date2)
	{
		return  CompareDateFunction(*this, Date2);
	}

	static bool CheckLastDay(short Year, short Month, short Day)
	{
		return(Day == CountDaysInMonth(Year, Month)) ? true : false;
	}

	bool CheckLastDay()
	{
		return  CheckLastDay(Year, Month, Day);
	}

	static bool CheckLastMonth(short Month)
	{
		return(Month == 12) ? true : false;
	}

	bool CheckLastMonth()
	{
		return CheckLastMonth(Month);
	}

	static clsDate IncreaseDateByOneDay(clsDate Date)
	{
		short LastDayInMonth = CountDaysInMonth(Date.Year, Date.Month);
		if (Date.Day == LastDayInMonth)
		{
			if (Date.Month == 12)
			{
				Date.Month = 1;
				Date.Day = 1;
				Date.Year++;
			}
			else
			{
				Date.Month++;
				Date.Day = 1;
			}
		}
		else
			Date.Day++;

		return Date;
	}

	void IncreaseDateByOneDay()
	{
		*this = IncreaseDateByOneDay(*this);
	}

	static int DifferenceInDays(clsDate Date1, clsDate Date2)
	{
		int Days = 0;
		while (IsDate1LessThanDate2(Date1, Date2))
		{
			Days++;
			Date1 = IncreaseDateByOneDay(Date1);
		}
		return Days;
	}

	int DifferenceInDays(clsDate Date2)
	{
		return DifferenceInDays(*this, Date2);
	}
	
	static stDate ReadDateNow()
	{
		time_t t = time(0); // get time now
		tm* now = localtime(&t);
		stDate Date;
		Date.Year = now->tm_year + 1900;
		Date.Month = now->tm_mon + 1;
		Date.Day = now->tm_mday;
		return Date;
	}

	static int CalculateAgeInDays(clsDate Date1)
	{
		int TotalDays = 0;
		stDate DateNow = ReadDateNow();
		//Calculate the remainder of the person's year of birth.
		TotalDays = (CheckLeapYear(Date1.Year)) ? 366 - TotalDaysFromTheBeginningOfYear(Date1.Year,Date1.Month,Date1.Day) : 365 - TotalDaysFromTheBeginningOfYear(Date1.Year, Date1.Month, Date1.Day);
		//Calculating the days of years between the date of birth and the current year
		for (short i = Date1.Year + 1; i < DateNow.Year; i++)
		{
			CheckLeapYear(i) ? TotalDays += 366 : TotalDays += 365;
		}
		// Calculating the days that passed in the current year
		TotalDays = TotalDays + TotalDaysFromTheBeginningOfYear(DateNow.Year, DateNow.Month, DateNow.Day);
		return TotalDays;
	}
	
	int CalculateAgeInDays()
	{
		return CalculateAgeInDays(*this);
	}

	static int NegativeDifferenceInDays(clsDate Date1, clsDate Date2, bool PositiveDate = true)
	{
		int Days = 0;
		if (PositiveDate)
		{
			while (IsDate1LessThanDate2(Date1, Date2))
			{
				Days++;
				Date1 = IncreaseDateByOneDay(Date1);
			}
			return Days;
		}
		else
		{
			while (IsDate1LessThanDate2(Date2, Date1))
			{
				Days--;
				Date2 = IncreaseDateByOneDay(Date2);
			}
			return Days;
		}

	}

	int NegativeDifferenceInDays(clsDate Date2, bool PositiveDate = true)
	{
		return NegativeDifferenceInDays(*this, Date2, PositiveDate);
	}

	static clsDate IncreaseDateByXDay(clsDate Date, int XDays)
	{
		for (short i = 0; i < XDays; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}
		return Date;
	}

	void IncreaseDateByXDay(int XDays)
	{
		*this =  IncreaseDateByXDay(*this, XDays);
	}
	static clsDate IncreaseDateByOneWeek(clsDate Date)
	{
		return Date = IncreaseDateByXDay(Date, 7);
	}

	void IncreaseDateByOneWeek()
	{
		*this = IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreaseDateByXWeek(clsDate Date, int XWeek)
	{
		for (short i = 0; i < XWeek; i++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}
		return Date;
	}

	void IncreaseDateByXWeek(int XWeek)
	{
		*this = IncreaseDateByXWeek(*this, XWeek);
	}

	static clsDate IncreaseDateByOneMonth(clsDate Date)
	{

		(Date.Month == 12) ? (Date.Month = 1, Date.Year++) : Date.Month++;
		int TotalDaysInCertianMonth = CountDaysInMonth(Date.Year, Date.Month);
		while (Date.Day > TotalDaysInCertianMonth)
		{
			Date.Day--;
		}
		return Date;
	}

	void IncreaseDateByOneMonth()
	{
		*this = IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByXMonth(clsDate Date, int XMonth)
	{
		for (short i = 0; i < XMonth; i++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}
		return Date;
	}

	void IncreaseDateByXMonth(int XMonth)
	{
		*this = IncreaseDateByXMonth(*this, XMonth);
	}

	static clsDate IncreaseDateXYearFaster(clsDate Date, int XYear)
	{
		Date.Year = Date.Year + XYear;
		return Date;
	}

	void IncreaseDateXYearFaster(int XYear)
	{
		*this = IncreaseDateXYearFaster(*this, XYear);
	}

	static clsDate DecreaseDateByOneDay(clsDate Date)
	{
		if (Date.Day == 1 && Date.Month == 1)
		{
			Date.Day = 31;
			Date.Month = 12;
			Date.Year--;
		}
		else if (Date.Day == 1)
		{
			Date.Month--;
			Date.Day = CountDaysInMonth(Date.Year, Date.Month);
		}
		else
			Date.Day--;

		return Date;
	}

	void DecreaseDateByOneDay()
	{
		*this = DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByXDay(clsDate Date, int XDays)
	{
		for (short i = 0; i < XDays; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}

	void DecreaseDateByXDay(int XDays)
	{
		*this = DecreaseDateByXDay(*this, XDays);
	}

	static clsDate DecreaseDateByOneWeek(clsDate Date)
	{
		return Date = DecreaseDateByXDay(Date, 7);
	}

	void DecreaseDateByOneWeek()
	{
		*this = DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeek(clsDate Date, int XWeek)
	{
		for (short i = 0; i < XWeek; i++)
		{
			Date = DecreaseDateByOneWeek(Date);
		}
		return Date;
	}

	void DecreaseDateByXWeek(int XWeek)
	{
		*this = DecreaseDateByXWeek(*this, XWeek);
	}

	static clsDate DecreaseDateByOneMonth(clsDate Date)
	{

		(Date.Month == 1) ? (Date.Month = 12, Date.Year--) : Date.Month--;
		int TotalDaysInCertianMonth = CountDaysInMonth(Date.Year, Date.Month);
		while (Date.Day > TotalDaysInCertianMonth)
		{
			Date.Day--;
		}
		return Date;
	}

	void DecreaseDateByOneMonth()
	{
		*this = DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXMonth(clsDate Date, int XMonth)
	{
		for (short i = 0; i < XMonth; i++)
		{
			Date = DecreaseDateByOneMonth(Date);
		}
		return Date;
	}

	void DecreaseDateByXMonth(int XWeek)
	{
		*this = DecreaseDateByXMonth(*this, XWeek);
	}

	static clsDate DecreaseDateByOneYear(clsDate Date)
	{
		Date.Year--;
		return Date;
	}

	void DecreaseDateByOneYear()
	{
		*this = DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateXYear(clsDate Date, int XYear)
	{
		for (short i = 0; i < XYear; i++)
		{
			Date = DecreaseDateByOneYear(Date);
		}
		return Date;
	}

	void DecreaseDateXYear(int XYear)
	{
		*this = DecreaseDateByXMonth(*this, XYear);
	}

	static clsDate DecreaseDateXYearFaster(clsDate Date, int XYear)
	{
		Date.Year = Date.Year - XYear;
		return Date;
	}

	void DecreaseDateXYearFaster(int XYear)
	{
		*this = DecreaseDateXYearFaster(*this, XYear);
	}

	static bool ValidateDate(clsDate Date)
	{
		if (Date.Month < 1 || Date.Month > 12)
			return false;

		short TotalDaysInCurrentMonth = CountDaysInMonth(Date.Year, Date.Month);
		return (Date.Day == 0 || Date.Day > TotalDaysInCurrentMonth) ? false : true;
	}

	bool ValidateDate()
	{
		return ValidateDate(*this);
	}
};


