#pragma once

class clsDepositScreen : protected clsScreen
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
	static void AddDeposit()
	{
		_DrawScreenHeader("\tDeposit Screen");

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

		cout << "\nPlease enter deposite amount ? ";
		float DepositAmount = clsInputValidate::ReadFloatNumber("Error number, enter again ");

		char Perform = 'y';
		cout << "\nAre you sure you want to perform this transaction ?";
		cin >> Perform;

		if (toupper(Perform) == 'Y')
		{
			Client1.Deposit(DepositAmount);
			cout << "Account deposit successfully.\n";
			cout << "New Balance is : " << Client1.AccountBalance;
		}
		else
			cout << "\nOperation was cancelled.";
	}
};

