#pragma once
#include "clsScreen.h"

class clsCurrenciesFindScreen : protected clsScreen
{
private:

	enum enFindCurrencyOptions {code = 1, country = 2};

	static void _PrintCurrencyCard(clsCurrency Currency)
	{
		cout << "\nCurrency Card :\n";
		cout << "_______________________________\n";
		cout << "Country           : " << Currency.Country() << endl;
		cout << "Code              : " << Currency.CurrencyCode() << endl;
		cout << "Name              : " << Currency.CurrencyName() << endl;
		cout << "Rate(1$)          : " << Currency.Rate() << endl;
		cout << "_______________________________\n";
	}

	static void _ShowCurrencyByCode()
	{
		string Code = "";
		cout << "\nPlease enter Currency Code : ";
		cin >> Code;

		clsCurrency Currency = clsCurrency::FindByCode(Code);

		if (!Currency.IsEmpty())
		{
			cout << "\nCurrency Found :-)\n";
			_PrintCurrencyCard(Currency);
		}
		else
			cout << "Currency code is not found \n";
	}
	
	static void _ShowCurrencyByCountry()
	{
		string Country = "";
		cout << "\nPlease enter Country Name : ";
		cin >> Country;

		clsCurrency Currency = clsCurrency::FindByCountry(Country);

		if (!Currency.IsEmpty())
		{
			cout << "\nCurrency Found :-)\n";
			_PrintCurrencyCard(Currency);
		}
		else
			cout << "country name is not found \n";
	}

	static void _PerformFindCurrencyOptions(enFindCurrencyOptions PerformOptions)
	{
		switch (PerformOptions)
		{
		case clsCurrenciesFindScreen::code:
			_ShowCurrencyByCode();
			break;
		case clsCurrenciesFindScreen::country:
			_ShowCurrencyByCountry();
			break;
		default:
			break;
		}
	}

public:

	static void ShowFindCurrencyScreen()
	{
		_DrawScreenHeader("\tFind Currency Screen");

		char SearchAgain = 'y';
		while (toupper(SearchAgain) == 'Y')
		{
			cout << "\nFind by :  [1] code or [2] country ? ";
			int Choose = clsInputValidate::ReadIntNumberBetween(1, 2, "Error number, try again");
			_PerformFindCurrencyOptions((enFindCurrencyOptions)Choose);
			cout << "\n\nDo you to search again ? Y/N ";
			cin >> SearchAgain;
		}

	}
};

