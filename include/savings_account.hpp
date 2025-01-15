#include <account.hpp>

class SavingsAccount : public db::Account 
{
public:
    SavingsAccount(std::string number, std::string name, db::AccountDAO &accountDao, double interestRate, double balance);
    void ApplyInterest(); //to add interest to the balance periodically
};

