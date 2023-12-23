#pragma once

class clsWithdrawScreen : protected clsScreen
{
private:

	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.GetAccountNumber();
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";

	}

public:
	static void Withdraw()
	{
		_DrawScreenHeader("\Withdraw Screen");

		string AccountNumber = "";
		cout << "\nPlease Enter client Account Number: ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		_PrintClient(Client1);

		cout << "\nPlease enter Withdraw amount ? ";
		float WithdrawAmount = clsInputValidate::ReadFloatNumber("Error number, enter again ");

		char Perform = 'y';
		cout << "\nAre you sure you want to perform this transaction ?";
		cin >> Perform;

		if (toupper(Perform) == 'Y')
		{
			if (!Client1.Withdraw(WithdrawAmount))
			{
				cout << "\nCannot withdraw, Insuffecient Balance !";
				cout << "\nAmount to withdraw : " << WithdrawAmount << endl;
				cout << "Your balance is " << Client1.GetAccountBalance();
			}
			else
			{
				cout << "Account withdraw successfully.\n";
				cout << "Your new balance is " << Client1.GetAccountBalance();
			}
		}
		else
			cout << "\nOperation was cancelled.";
	}
};


