#pragma once
#include <iostream>
#include <iomanip>

using namespace std;

class clsScreen
{
protected:

    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << right << setw(82) << "___________________________________________\n";
        cout << "\n\t\t\t\t\t  " << Title << endl;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle << endl;
        }
        //cout << "\n\t\t\t\t\t______________________________________\n\n";
        cout <<  right << setw(82) << "___________________________________________\n\n";

    }
};

