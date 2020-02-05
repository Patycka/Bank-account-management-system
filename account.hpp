#include <iostream>

using namespace std;

class Account
{
private:
    string fileToWriteData;
    string name;
    int number;
    float saldo;

public:
    Account(const string& file);
    void CreateNew();
    void editExisting();
    void Delete();
    void PrintAccount();
    static Account& SearchAccountByName(string nameToSearch);
    void SearchByName(string nameToSearch);
    makeMoneyTransfer(float money, string name);
    addMoney(float money);
    getMoney(float money);

};





