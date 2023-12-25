#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "Global.h"

class clsLoginScreen :protected clsScreen
{

private:

    static  void _Login()
    {
        bool LoginFaild = false;
        short Trials = 3;
        string Username, Password;
        do
        {
            if (Trials == 0)
            {
                cout << "\n\nYou have locked after 3 failed trials\n";
                return;
            }

            if (LoginFaild)
            {
                cout << "\nInvlaid Username/Password!\n";
                cout << "You  have " << Trials << " to login." << endl;
            }

            Trials--;

            cout << "\nEnter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;

            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();

        } while (LoginFaild);

        clsMainScreen::ShowMainMenue();

    }

public:


    static void ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");
        _Login();

    }

};

