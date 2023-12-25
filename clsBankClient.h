#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsInputValidate.h"
#include "clsUtility.h"

using namespace std;


class clsBankClient : public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2, DeleteMode = 3 };
	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	// Data file
	static string _Separator()
	{
		return "#//#";
	}

	static string _ClinetsFileName()
	{
		return "Clients.txt";
	}

	static clsBankClient _ConvertLineToClientObject(string Line)
	{
		vector <string> Clinet;
		Clinet = clsString::SplitString(Line, _Separator());
		return clsBankClient(enMode::UpdateMode, Clinet[0], Clinet[1], Clinet[2],
			Clinet[3], Clinet[4], Clinet[5], stod(Clinet[6]));
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return  clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector <clsBankClient> _LoadClientsDataFromFile()
	{
		vector <clsBankClient> vClients;
		fstream MyFile;
		MyFile.open(_ClinetsFileName(), ios::in);
		if (MyFile.is_open())
		{
			string Line = "";
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				vClients.push_back(Client);
			}
		}
		MyFile.close();
		return vClients;
	}

	static string _ConvertClientObjectToLine(clsBankClient vClients)
	{
		string stClientRecord = "";
		stClientRecord += vClients.FirstName + _Separator();
		stClientRecord += vClients.LastName + _Separator();
		stClientRecord += vClients.Email + _Separator();
		stClientRecord += vClients.Phone + _Separator();
		stClientRecord += vClients.GetAccountNumber() + _Separator();
		stClientRecord += vClients.PinCode + _Separator();
		stClientRecord += to_string(vClients.AccountBalance);

		return stClientRecord;
	}

	static void _SavaClientsDataToFile(vector <clsBankClient> vClients)
	{
		fstream MyFile;
		MyFile.open(_ClinetsFileName(), ios::out);
		string ClientLine = "";
		if (MyFile.is_open())
		{
			for (clsBankClient& Client : vClients)
			{
				ClientLine = _ConvertClientObjectToLine(Client);
				MyFile << ClientLine << endl;
			}
		}
		MyFile.close();
	}

	void _Update()
	{
		vector <clsBankClient> _vClients = _LoadClientsDataFromFile();
		for (clsBankClient& C : _vClients)
		{
			if (C.GetAccountNumber() == GetAccountNumber())
			{
				C = *this;
				break;
			}
		}
		_SavaClientsDataToFile(_vClients);
	}

	void _AddDataLineToFile(string DataLine)
	{
		fstream MyFile;
		MyFile.open(_ClinetsFileName(), ios::out | ios::app);
		if (MyFile.is_open())
		{
			MyFile << DataLine << endl;
		}
		MyFile.close();
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	void _SaveClientsDataAfterDeleting(vector <string> vClientsDateLine)
	{
		fstream MyFile;
		MyFile.open(_ClinetsFileName(), ios::out);
		if (MyFile.is_open())
		{
			for (string& ClientLine : vClientsDateLine)
			{
				MyFile << ClientLine << endl;
			}
		}
		MyFile.close();
	}

	void _Delete()
	{
		vector <clsBankClient> _vClientsDate = _LoadClientsDataFromFile();
		vector <string> vClientsDateLine;
		string ClientLine;
		for (clsBankClient Client : _vClientsDate)
		{
			ClientLine = _ConvertClientObjectToLine(Client);
			if (Client.GetAccountNumber() != GetAccountNumber())
				vClientsDateLine.push_back(ClientLine);
		}
		_SaveClientsDataAfterDeleting(vClientsDateLine);
	}

public:
	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone,
		string AccountNumber, string PinCode, float AccountBalance)
		:
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_AccountBalance = AccountBalance;
		_PinCode = PinCode;
	}

	string GetAccountNumber()
	{
		return _AccountNumber;
	}

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	string GetPinCode()
	{
		return _PinCode;
	}

	__declspec(property(put = SetPinCode, get = GetPinCode)) string PinCode;

	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	float GetAccountBalance()
	{
		return _AccountBalance;
	}

	__declspec(property(put = SetAccountBalance, get = GetAccountBalance)) float AccountBalance;

	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	//void Print()
	//{
	//	cout << "\nClinet Card :";
	//	cout << "\n___________________";
	//	cout << "\nFirstName    : " << FirstName;
	//	cout << "\nLastName     : " << LastName;
	//	cout << "\nFull Name    : " << FullName();
	//	cout << "\nEmail        : " << Email;
	//	cout << "\nAcc Number    : " << _AccountNumber;
	//	cout << "\nPassword      : " << _PinCode;
	//	cout << "\nBalance       : " << _AccountBalance;
	//	cout << "\n___________________\n";
	//}

	static clsBankClient Find(string AccountNumber)
	{
		vector <clsBankClient> Clinets;
		fstream MyFile;
		MyFile.open(_ClinetsFileName(), ios::in);
		if (MyFile.is_open())
		{
			string ClientDate;
			while (getline(MyFile, ClientDate))
			{
				clsBankClient Client = _ConvertLineToClientObject(ClientDate);
				if (Client.GetAccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}
			}
		}
		MyFile.close();
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		vector <clsBankClient> Clinets;
		fstream MyFile;
		MyFile.open(_ClinetsFileName(), ios::in);
		if (MyFile.is_open())
		{
			string ClientDate;
			while (getline(MyFile, ClientDate))
			{
				clsBankClient Client = _ConvertLineToClientObject(ClientDate);
				if (Client.GetAccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}
			}
		}
		MyFile.close();
		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		return (!Client.IsEmpty());
	}

	/*=================== Update Clients ==========================*/
	enum enSaveResults
	{
		svFaildEmptyObject = 0,
		svSucceeded = 1,
		svFaildAccountNumberExists = 2
	};

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case clsBankClient::enMode::EmptyMode:
			return enSaveResults::svFaildEmptyObject;

		case clsBankClient::enMode::UpdateMode:
			_Update();
			return enSaveResults::svSucceeded;

		case clsBankClient::enMode::AddNewMode:
			if (clsBankClient::IsClientExist(_AccountNumber))
				return enSaveResults::svFaildAccountNumberExists;
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
		case clsBankClient::enMode::DeleteMode:
			_Delete();
			_Mode = enMode::DeleteMode;
			return enSaveResults::svSucceeded;
		default:
			break;
		}
	}

	void ReadClientInfo(clsBankClient& Client1)
	{
		cout << "\nEnter First Name : ";
		Client1.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter Last Name : ";
		Client1.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email : ";
		Client1.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone : ";
		Client1.Phone = clsInputValidate::ReadString();

		cout << "\nEnter PinCode : ";
		Client1.PinCode = clsInputValidate::ReadString();

		cout << "\nEnter Account Balance : ";
		Client1.AccountBalance = clsInputValidate::ReadFloatNumber("Invalid number, enter number again");
	}

	void UpdateClient()
	{
		string AccountNumber = "";
		cout << "\nPlease Enter your Account Number : ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number is not found , choose another one : ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		Client1.Print();

		cout << "\n\nUpdate Client Info : ";
		cout << "\n______________________\n";

		ReadClientInfo(Client1);

		clsBankClient::enSaveResults SaveResult;
		SaveResult = Client1.Save();
		switch (SaveResult)
		{
		case clsBankClient::enSaveResults::svSucceeded:
			cout << "\nAccount Updated Successfully . \n";
			Client1.Print();
			break;
		case  clsBankClient::enSaveResults::svFaildEmptyObject:
			cout << "\nError account was not  saved because it's empty";
			break;
		default:
			break;
		}
	}

	/*===================  Add New Client ==========================*/
	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	/*===================  Delete Client ==========================*/

	static clsBankClient DeleteClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::DeleteMode, "", "", "", "", AccountNumber, "", 0);
	}

	/*=================== Total Balances ==========================*/
	static vector <clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	static float GetTotalBalances()
	{
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();
		double TotalBalances = 0;
		for (clsBankClient Client : vClients)
		{

			TotalBalances += Client.AccountBalance;
		}
		return TotalBalances;
	}

	void PrintClientRecordBalanceLine(clsBankClient Client)
	{

		cout << "| " << setw(15) << left << Client.GetAccountNumber();
		cout << "| " << setw(40) << left << Client.FullName();
		cout << "| " << setw(12) << left << Client.AccountBalance;

	}

	void ShowTotalBalances()
	{

		vector <clsBankClient> vClients = clsBankClient::GetClientsList();

		cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << "| " << left << setw(15) << "Accout Number";
		cout << "| " << left << setw(40) << "Client Name";
		cout << "| " << left << setw(12) << "Balance";
		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		double TotalBalances = clsBankClient::GetTotalBalances();

		if (vClients.size() == 0)
			cout << "\t\t\t\tNo Clients Available In the System!";
		else

			for (clsBankClient Client : vClients)
			{
				PrintClientRecordBalanceLine(Client);
				cout << endl;
			}

		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		cout << "\t\t\t\t\t   Total Balances = " << TotalBalances << endl;
		cout << "\t\t\t\t\t   ( " << clsUtil::NumberToText(TotalBalances) << ")";
	}

	/*=================== Deposite and Withdraw ==========================*/
	void Deposit(float Amount)
	{
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(float Amount)
	{
		if (Amount > _AccountBalance)
			return false;
		else
		{
			_AccountBalance -= Amount;
			Save();
		}
	}

	void Transfer(clsBankClient& ClientToTransferTo, float TransferAmount)
	{
		cout << Withdraw(TransferAmount);
		ClientToTransferTo.Deposit(TransferAmount);
	}
};