#include <iostream>
#include "account.hpp"
#include <fstream>
#include <algorithm>
#include <sqlite3.h>

using namespace std;

Account::Account(const string &file)
{
    this->fileToWriteData = file;
}


void Account::PrintAccount()
{
    cout << "Name: " << this->clientData.name << endl;
    cout << "Number: " << this->clientData.number << endl;
    cout << "Saldo: " << this->clientData.saldo << endl;
}

void Account::CreateNew()
{
//    cout << "Name: ";
//    getline(cin, this->clientData.name);
//    cout << "Account number: ";
//    cin >> this->clientData.number;
//    cout << "Saldo: ";
//    cin >> this->clientData.saldo;
//    cin.ignore();

    vector <int> dane;
    dane.push_back(10);

    cout << dane[0] << endl;

//    this->clientStructVect.push_back(this->clientData);
//
    ofstream file;
    file.open((char *)fileToWriteData.c_str(), std::ios_base::app); //append instead of overwrite
    if (file.is_open())
    {
        file << dane[0] << endl;
//        file << this->clientStructVect[number].name << endl;
//        file << this->clientStructVect[number].saldo << endl;
//        file << this->clientStructVect[number].number << endl;

        file.close();
    }
    else
    {
        cout << "Problem with file" << endl;
    }

    number++;
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

            //open connection to SQLite database
            //rc = sqlite3_open("test.db", &db);

            //find_if() takes a predicate, and returns the first position where the predicates returns true

        //const auto p = std::find_if( clientStructVect.begin(), clientStructVect.end(),
        //                             [nameToSearch] ( const ClientData& a ) { return a.name == nameToSearch ; } ) ;
            {
                //cout << "Found " << nameToSearch << endl;
//                this->clientData.name = nameToSearch;
//                file >> this->clientData.saldo;
//                file >> this->clientData.number;
//                this->PrintAccount();
//                return line_number;
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
