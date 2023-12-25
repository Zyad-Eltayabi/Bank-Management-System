#pragma once
class clsTransferScreen : protected clsScreen
{
private:

	static void _PrintClientCard(clsBankClient Client)
	{
		cout << "\nClient Card : \n";
		cout << "_________________________________\n";
		cout << "\nFull Name      : " << Client.FullName() << endl;
		cout << "Acc. Number    : " << Client.GetAccountNumber() << endl;
		cout << "Balance        : " << Client.AccountBalance << endl;
		cout << "_________________________________\n";
	}

	static string _ReadAccountNumber()
	{
		string AccountNumber = "";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		return AccountNumber;
	}
public:
	static void ShowTransferScreen()
	{
		_DrawScreenHeader("\tTransfer Screen");

		cout << "\nPlease Enter client Account Number to Transfer From: ";
		string AccountNumber = _ReadAccountNumber();
		clsBankClient ClientToTransferFrom = clsBankClient::Find(AccountNumber);
		_PrintClientCard(ClientToTransferFrom);

		cout << "\nPlease Enter client Account Number to Transfer to: ";
		AccountNumber = _ReadAccountNumber();
		clsBankClient ClientToTransferTo = clsBankClient::Find(AccountNumber);
		_PrintClientCard(ClientToTransferTo);

		cout << "\nPlease enter Transfer amount ? ";
		float  TransferAmount = clsInputValidate::ReadFloatNumber("Error number, enter again ");
		while (TransferAmount > ClientToTransferFrom.AccountBalance)
		{
			cout << "\nAmount Exceeds the available , please enter another Amount ? ";
			TransferAmount = clsInputValidate::ReadFloatNumber("Error number, enter again ");
		};


		char Perform = 'y';
		cout << "\nAre you sure you want to perform this transaction ?";
		cin >> Perform;

		if (toupper(Perform) == 'Y')
		{
			ClientToTransferFrom.Transfer(ClientToTransferTo, TransferAmount);
			cout << "\nTransfer done successfully.\n";
			_PrintClientCard(ClientToTransferFrom);
			_PrintClientCard(ClientToTransferTo);
		}
		else
			cout << "\nOperation was cancelled.";
	}
};

