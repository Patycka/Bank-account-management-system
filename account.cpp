#include <iostream>
#include "account.hpp"
#include <fstream>

using namespace std;


void Account::createNew()
{
    cout << "Name: ";
    getline(cin,this->name);
    cout << "Saldo: ";
    cin >> this->saldo;
    cin.ignore();

    ofstream file;
    file.open((char*)fileToWriteData.c_str(), std::ios_base::app);
    if(file.is_open())
    {
        file << "Name: " << this->name << endl;
        file << "Saldo: " << this->saldo << endl;

        file.close();
    }
    else
    {
        cout << "Problem with file" << endl;
    }

}

Account::Account(const string& file)
{
    this->fileToWriteData = file;
}





