#include <iostream>
#include <vector>

using namespace std;

class Account
{
private:
    struct Data
    {
        string name;
        int number;
        float saldo;
    };
    string fileToWriteData;

    vector<Data> accountData;

public:
    Account(const string& file);
    void CreateNew();
    void EditName(string nameToEdit);
    void Delete();
    void PrintAccount();
    static Account& SearchAccountByName(string nameToSearch);
    int SearchByName(string nameToSearch);
    makeMoneyTransfer(float money, string name);
    addMoney(float money);
    getMoney(float money);

};


class Database
{
public:
    void SaveAccount();
    void ReadAccount();
};




