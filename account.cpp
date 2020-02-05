#include <iostream>
#include "account.hpp"
#include <fstream>

using namespace std;

Account::Account(const string &file)
{
    this->fileToWriteData = file;
}


void Account::PrintAccount()
{
    cout << "Name: " << this->name << endl;
    cout << "Number: " << this->number << endl;
    cout << "Saldo: " << this->saldo << endl;
}

void Account::CreateNew()
{
    cout << "Name: ";
    getline(cin, this->name);
    cout << "Account number: ";
    cin >> this->number;
    cout << "Saldo: ";
    cin >> this->saldo;
    cin.ignore();

    ofstream file;
    file.open((char *)fileToWriteData.c_str(), std::ios_base::app); //append instead of overwrite
    if (file.is_open())
    {
        file << this->name << endl;
        file << this->saldo << endl;
        file << this->number << endl;
        file.close();
    }
    else
    {
        cout << "Problem with file" << endl;
    }
}

void Account::SearchByName(string nameToSearch)
{
    ifstream file;
    string line;


    file.open((char *)fileToWriteData.c_str(), std::ios_base::app);
    if (file.is_open())
    {
        while (!file.eof())
        {
            getline(file, line);
            if (line.find(nameToSearch, 0) != string::npos)
            {
                cout << "Found " << nameToSearch << endl;
                this->name = nameToSearch;
                file >> this->saldo;
                file >> this->number;
            }
        }
    }
    file.close();
}


Account &Account::SearchAccountByName(string nameToSearch)
{
    Account* searchedAccount = new Account("dane.txt");

    searchedAccount->SearchByName(nameToSearch);

    return *searchedAccount;
}
