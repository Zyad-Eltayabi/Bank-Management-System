#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsClientsListScreen.h"
#include "clsAddNewClientsScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLoginScreen.h"
#include "clsShowLoginRegisterScreen.h"
#include "clsShowCurrencyMainScreen.h"
#include "Global.h"

using namespace std;

class clsMainScreen : protected clsScreen
{
private:
	enum enMainMenueOptions
	{
		enShow = 1,
		enAdd = 2,
		enDelete = 3,
		enUpdate = 4,
		enFind = 5,
		enTransactions = 6,
		enManageUsers = 7,
		enLoginRegister = 8,
		enCurrencyExchange = 9,
		enLogout = 10
	};

	static int _ReadMainMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 10]? ";
		int Choice = clsInputValidate::ReadIntNumberBetween(1, 10, "Error input , Enter Number between 1 to 10 ? ");
		return Choice;
	}

	static void _GoBackToMainMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";
		system("pause>0");
		ShowMainMenue();
	}

	static void _ShowAllClientsScreen()
	{
		clsClientListScreen::ShowClientsList();
	}

	static void _ShowAddNewClientsScreen()
	{
		clsAddNewClientScreen::ShowAddNewClientScreen();

	}

	static void _ShowDeleteClientScreen()
	{
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}

	static void _ShowUpdateClientScreen()
	{
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}

	static void _ShowFindClientScreen()
	{
		clsFindClientScreen::ShowFindClientScreen();
	}

	static void _ShowTransactionsMenue()
	{
		clsTransactionsScreen::ShowTransactionsMenue();
	}

	static void _ShowManageUsersMenue()
	{
		clsManageUsersScreen::ShowManageUsersMenue();
	}

	static void _ShowLoginRegisterScreen()
	{
		clsShowLoginRegisterScreen::ShowLoginRegisterScreen();
	}
	
	static void _ShowCurrencyMainScreen()
	{
		clsShowCurrencyMainScreen::ShowCurrencyMainScreen();
	}
	  
	static void _Logout()
	{
		CurrentUser = clsUser::Find("", "");
	}

	static void _PerfromMainMenueOption(enMainMenueOptions MainMenueOptions)
	{
		switch (MainMenueOptions)
		{
		case clsMainScreen::enShow:
			system("cls");
			_ShowAllClientsScreen();
			_GoBackToMainMenue();
			break;
		case clsMainScreen::enAdd:
			system("cls");
			_ShowAddNewClientsScreen();
			_GoBackToMainMenue();
			break;
		case clsMainScreen::enDelete:
			system("cls");
			_ShowDeleteClientScreen();
			_GoBackToMainMenue();
			break;
		case clsMainScreen::enUpdate:
			system("cls");
			_ShowUpdateClientScreen();
			_GoBackToMainMenue();
			break;
		case clsMainScreen::enFind:
			system("cls");
			_ShowFindClientScreen();
			_GoBackToMainMenue();
			break;
		case clsMainScreen::enTransactions:
			system("cls");
			_ShowTransactionsMenue();
			_GoBackToMainMenue();
			break;
		case clsMainScreen::enManageUsers:
			system("cls");
			_ShowManageUsersMenue();
			_GoBackToMainMenue();
			break;
		case clsMainScreen::enLoginRegister:
			system("cls");
			_ShowLoginRegisterScreen();
			_GoBackToMainMenue();
		case clsMainScreen::enCurrencyExchange:
			system("cls");
			_ShowCurrencyMainScreen();
			_GoBackToMainMenue();
		case clsMainScreen::enLogout:
			system("cls");
			_Logout();
			break;
		default:
			break;
		}
	}

public:
	static void ShowMainMenue()
	{
		system("cls");
		_DrawScreenHeader("\t\tMain Screen");
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
		cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
		cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
		cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
		cout << setw(37) << left << "" << "\t[5] Find Client.\n";
		cout << setw(37) << left << "" << "\t[6] Transactions.\n";
		cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
		cout << setw(37) << left << "" << "\t[8] Login Register.\n";
		cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
		cout << setw(37) << left << "" << "\t[10] Logout.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerfromMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());
	}
};

