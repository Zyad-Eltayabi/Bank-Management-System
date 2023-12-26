#pragma once
class clsTransferLogScreen : protected clsScreen
{
private:

	static vector <string> _LoadTransferLogFromFile()
	{
		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::in);
		string Line;
		vector <string> Transfer;
		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				Transfer.push_back(Line);
			}
		}
		MyFile.close();
		return Transfer;
	}

	static void _PrintTransfersScreenHeader()
	{
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "______________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(25) << "Date/Time";
		cout << "| " << left << setw(10) << "s.Acct";
		cout << "| " << left << setw(10) << "d.Acct";
		cout << "| " << left << setw(10) << "Amount";
		cout << "| " << left << setw(10) << "s.Balance";
		cout << "| " << left << setw(10) << "d.Balance";
		cout << "| " << left << setw(15) << "User";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "______________________________________________\n" << endl;
	}

	static void _PrintTransferRecordLine(vector <string>& Transfers)
	{

		cout << setw(8) << left << "" << "| " << setw(25) << left << Transfers[0];
		cout << "| " << setw(10) << left << Transfers[1];
		cout << "| " << setw(10) << left << Transfers[2];
		cout << "| " << setw(10) << left << Transfers[3];
		cout << "| " << setw(10) << left << Transfers[4];
		cout << "| " << setw(10) << left << Transfers[5];
		cout << "| " << setw(15) << left << Transfers[6] << endl;
	}

	static void _PrintTransferScreenBody(vector <string>& Transfers)
	{
		if (Transfers.size() == 0)
			cout << "\t\t\t\tNo Log in Transfer Available In the System!";
		else
		{
			for (string Transfer : Transfers)
			{
				vector <string> OneLine = clsString::SplitString(Transfer, "#//#");
				_PrintTransferRecordLine(OneLine);
			}
		}
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "______________________________________________\n" << endl;
	}

public:
	static void ShowTransferLogScreen()
	{
		vector <string> Transfers = _LoadTransferLogFromFile();

		string Title = "\Transfer Log List Screen";
		string SubTitle = "\t    (" + to_string(Transfers.size()) + ") Record(s).";

		_DrawScreenHeader(Title, SubTitle);
		_PrintTransfersScreenHeader();
		_PrintTransferScreenBody(Transfers);

	}
};

