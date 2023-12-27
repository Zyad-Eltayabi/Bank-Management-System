#pragma once
class clsCurrencyCalculator : protected clsScreen
{
private:

	static string _ReadCurrency()
	{
		string Currency;
		cout << "\nPlease Enter Currency From Code : ";
		Currency = clsInputValidate::ReadString();
		while (!clsCurrency::IsCurrencyExist(Currency))
		{
			cout << "\nThere is no currency with this code\n";
			cout << "\nPlease Enter Currency From Code : ";
			Currency = clsInputValidate::ReadString();
		}
		return Currency;
	}

	static void _PrintCurrencyCard(clsCurrency Currency)
	{
		cout << "_______________________________\n";
		cout << "Country           : " << Currency.Country() << endl;
		cout << "Code              : " << Currency.CurrencyCode() << endl;
		cout << "Name              : " << Currency.CurrencyName() << endl;
		cout << "Rate(1$)          : " << Currency.Rate() << endl;
		cout << "_______________________________\n";
	}

	static float _ConvertToUSDCurrency(clsCurrency Currency, float Amount)
	{
		return Amount / Currency.Rate();
	}

	static float _ConvertFromUSDCurrency(clsCurrency Currency, float Amount)
	{
		return Amount * Currency.Rate();
	}

public:
	static void ShowCurrencyCalculatorScreen()
	{
		char Reapet = 'y';
		while (toupper(Reapet) == 'Y')
		{
			system("cls");
			_DrawScreenHeader("Currency Calculator Screen");

			string Currency1 = _ReadCurrency();
			clsCurrency CurrencyFrom = clsCurrency::FindByCode(Currency1);

			string Currency2 = _ReadCurrency();
			clsCurrency CurrencyTo = clsCurrency::FindByCode(Currency2);

			cout << "\nEnter amount to Exchange : ";
			float Amount = clsInputValidate::ReadFloatNumber("Error number, enter number again");

			float ConvertFirstCurrencyToUSD = _ConvertToUSDCurrency(CurrencyFrom, Amount);

			cout << "\nConvert From : \n";
			_PrintCurrencyCard(CurrencyFrom);
			cout << Amount << " " << CurrencyFrom.CurrencyCode() << " = " << ConvertFirstCurrencyToUSD << " USD " << endl;

			if ( CurrencyTo.CurrencyCode() != "USD")
			{
				cout << "\nConvertint From USD to : \n";
				cout << "\nTo :\n";
				_PrintCurrencyCard(CurrencyTo);
				cout << Amount << " " << CurrencyFrom.CurrencyCode() << " = " <<
					_ConvertFromUSDCurrency(CurrencyTo, ConvertFirstCurrencyToUSD) << " " << CurrencyTo.CurrencyCode();
			}

			cout << "\n\nDo you want to perform another calculation  Y/N ? ";
			cin >> Reapet;
		}
	}
};

