#include <iostream>

using namespace std;

class Account
{
private:
    string fileToWriteData;
    string name;
    int accountNumber;
    float saldo;

public:
    Account(const string& file);
    void createNew();
    void editExisting();
    void Delete();
    Account searchByName(string nameToSearch);
    makeMoneyTransfer(float money, string name);
    addMoney(float money);
    getMoney(float money);

};





