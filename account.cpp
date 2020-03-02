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
    cout << "Name: " << this-> name << endl;
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

int Account::SearchByName(string nameToSearch)
{
    ifstream file;
    string line;
    int line_number=0;

    //ios_base to klasa bazowa dla kasy ios, ios z kolei to klasa bazowa dla iostream
    //ustawienie justowania, wyswietlanie w formie szesnastkowej, dziesietnej
    //http://staff.elka.pw.edu.pl/~rnowak2/zprwiki/doku.php?id=klasy_bazowe_dla_strumieni
    file.open((char *)fileToWriteData.c_str(), ios::in);
    if (file.is_open())
    {
        while (!file.eof())
        {
            line_number++;
            getline(file, line);



            if (line.find(nameToSearch, 0) != string::npos)
            {
                cout << "Found " << nameToSearch << endl;
                this->name = nameToSearch;
                file >> this->saldo;
                file >> this->number;
                this->PrintAccount();
                return line_number;
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

void Account::EditName(string nameToEdit)
{
    fstream file;
    string line;
    int line_number;
    int i=1;

    line_number = SearchByName(nameToEdit);

    file.open((char *)fileToWriteData.c_str(), ios::in | ios::out);

    if (file.is_open())
    {
        //while (!file.eof())
        {
            file.seekp(1, ios::beg);
            file << "Marcelina" << endl;
            file.seekp(-9, ios::cur);
//            if(i == line_number)
//            {
//                cout << "Nowe imie" << endl;
//                file << "Marcelina" << endl;
//            }
//            else
//            {
//                getline(file, line);
//            }
//            i++;

        }
    }
    file.close();
}

void Account::Delete()
{

}


