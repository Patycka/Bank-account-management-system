#include <iostream>
#include <vector>

using namespace std;

class Account
{
private:
    struct ClientData
    {
        string name;
        int number;
        float saldo;
    };

    ClientData clientData;
    int number;

    vector <ClientData> clientStructVect;

public:
    void CreateNew();
    void Delete();
    void PrintAccount();
    void DepositMoney(float money);
    void WithdrawMoney(float money);

};





