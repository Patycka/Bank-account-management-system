#include <iostream>
#include <vector>

using namespace std;

class Account
{
private:
    std::string m_accountNumber;
    std::string m_accountHolderName;
    double m_balance;

public:
    Account(std::string m_accountNumber, std::string m_accountHolderName);
    friend std::ostream& operator<<(std::ostream& os, const Account& account);
    void DepositMoney(double money);
    void WithdrawMoney(double money);

};





