#pragma once
class clsUpdateCurrencyRate : protected clsScreen
{
private:

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

	static void _UpdateRate(clsCurrency Currency)
	{
		cout << "\nUpdate Currency Rate\n";
		cout << "________________________\n";
		
		cout << "\nEnter New Rate : ";
		float NewRate = clsInputValidate::ReadFloatNumber("Error, enter the number again");

		Currency.UpdateRate(NewRate);
		_PrintCurrencyCard(Currency);
	}

public:
	static void ShowUpdateCurrencyRateScreen()
	{
		_DrawScreenHeader("\tUpdate Currency Screen");

		string Code = "";
		cout << "\nPlease enter Currency Code : ";
		cin >> Code;

		clsCurrency Currency = clsCurrency::FindByCode(Code);

		if (!Currency.IsEmpty())
		{
			_PrintCurrencyCard(Currency);

			char Update = 'y';
			cout << "\nAre you sure to update the rate of this  currency Y/N ? ";
			cin >> Update;

			if (toupper(Update) == 'Y')
			{
				_UpdateRate(Currency);
			}
			else
				cout << "\nOperation Cancelled\n";
		}
		else
			cout << "Currency code is not found \n";

	}
};

