#include <iostream>
#include <sys/stat.h>
#include <fstream>
#include <string>
#include <stdio.h>
#include "minigit.hpp"
using namespace std;
void displayMenu()
{
    cout << "==================== MENU ====================" << endl;
    cout << "Pick and option:" << endl;
    cout << "1) Initialize" << endl;
    cout << "2) Add File" << endl;
    cout << "3) Remove File " << endl;
    cout << "4) Commit File" << endl;
    cout << "5) Checkout File" << endl;
    cout << "6) Print Status" << endl;
    cout << "7) Quit" << endl;
}
int main()
{
    string USI;
    int options;
    string FN;
    string dir = ".minigit";
    string a;
    Minigit repo1;
    ifstream read;
    fstream EF;
    bool check = false;
    int number;
    string warning;
    cout << "Created by: Ben Xiang, Khoi Phan, and Samia Juras" << endl;
    while (options != 7)
    {
        displayMenu();
        cout << "You chose option: ";
        cin >> USI;
        options = stoi(USI);
        switch (options)
        {
        case 1:
            mkdir(".minigit", 0777);
            EF.open(".minigit/readme.txt", ios::out);
            repo1.Initialize();
            check = true;
            break;

        case 2:
            if (check == false)
            {
                cout << "ERROR: Not initialized, please initialize first!" << endl;
                break;
            }
            cout << "Enter a file name" << endl;
            cin >> FN;
            read.open(FN);
            while (!read.is_open())
            {
                cout << "FILE ERROR: File " << FN << " either can't be opened at this time or it does not exist. Try again!" << endl;
                cout << "_______________________________________________________________________________________" << endl;
                cout << endl;
                cout << "Enter a file name" << endl;
                cin >> FN;
                read.open(FN);
            }
            if (read.is_open())
            {
                cout << "File " << FN << " will be added into the list." << endl;
            }
            cout << FN << endl;
            repo1.addFile(FN);
            break;

        case 3:
            if (check == false)
            {
                cout << "ERROR: Not initialized, please initialize first!" << endl;
                break;
            }
            cout << "Enter the files you want to remove" << endl;
            cin >> FN;
            cout << "File " << FN << " will be removed" << endl;
            repo1.removeFile(FN);
            break;

        case 4:
            if (check == false)
            {
                cout << "ERROR: Not initialized, please initialize first!" << endl;
                break;
            }
            cout << "File " << FN << " will be committed to the directory " << dir << endl;
            repo1.Commit("00", FN);
            break;

        case 5:
            if (check == false)
            {
                cout << "ERROR: Not initialized, please initialize first!" << endl;
                break;
            }
            cout << "Warning: Running a checkout will lose your current changes unless you make a commit." << endl;
            cout << "Would you like to continue?" << endl;
            cout << "Enter Y or N." << endl;
            getline(cin, warning);

            while (warning[0] != 'Y' || warning[0] != 'n' || warning[0] != 'y' || warning[0] != 'n')
            {
                getline(cin, warning);

                if (warning[0] == 'y' || warning[0] == 'Y')
                {
                    break;
                }
                if (warning[0] == 'n' || warning[0] == 'N')
                {
                    break;
                }
                else
                {
                    cout << "Invalid option, please choose Y or N" << endl;
                }
            }
            if (warning[0] == 'n' || warning[0] == 'N')
            {
                break;
            }
            cout << "Please Enter the Commit You Would Like to Access" << endl;
            cin >> number;
            repo1.checkout(number);
            break;

        case 6:
            repo1.printrepo();
            break;

        case 7:
            cout << "Closing..." << dir << endl;
            a = "rm -r ./.minigit";
            system(a.c_str());
            break;
            return 0;

        default:
            cout << "Invalid Option" << endl;
            break;
        }
    }
}