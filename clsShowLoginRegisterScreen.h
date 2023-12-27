#pragma once
class clsShowLoginRegisterScreen : protected clsScreen
{
private:

	static vector <string> _LoadLoginRegisterFromFile()
	{
		fstream MyFile;
		MyFile.open("LogFile.txt", ios::in);
		string Line;
		vector <string> Registers;
		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				Registers.push_back(Line);
			}
		}
		MyFile.close();
		return Registers;
	}

	static void _PrintRegisterScreenHeader()
	{
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "______________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(30) << "Date/Time";
		cout << "| " << left << setw(25) << "User Name";
		cout << "| " << left << setw(25) << "Password";
		cout << "| " << left << setw(25) << "Permissions";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "______________________________________________\n" << endl;
	}

	static void _PrintRegisterRecordLine(vector <string>& Register)
	{

		cout << setw(8) << left << "" << "| " << setw(30) << left << Register[0];
		cout << "| " << setw(25) << left << Register[1];
		cout << "| " << setw(25) << left << Register[2];
		cout << "| " << setw(25) << left << Register[3];
		cout << endl;
	}

	static void _PrintRegisterScreenBody(vector <string>& Registers)
	{
		if (Registers.size() == 0)
			cout << "\t\t\t\tNo Log in Register Available In the System!";
		else
		{
			for (string Register : Registers)
			{
				vector <string> OneLine = clsString::SplitString(Register, "#//#");
				_PrintRegisterRecordLine(OneLine);
			}
		}
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "______________________________________________\n" << endl;
	}

public:

	static void ShowLoginRegisterScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pShowLogRegister))
		{
			return;// this will exit the function and it will not continue
		}

		vector <string> Registers = _LoadLoginRegisterFromFile();

		string Title = "\tLogin Register List Screen";
		string SubTitle = "\t    (" + to_string(Registers.size()) + ") User(s).";

		_DrawScreenHeader(Title, SubTitle);

		_PrintRegisterScreenHeader();

		_PrintRegisterScreenBody(Registers);
	}
};

