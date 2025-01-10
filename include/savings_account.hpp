#include <account.hpp>

class SavingsAccount : public db::Account 
{
public:
    SavingsAccount(std::string number, std::string name, db::AccountDAO &accountDao, double interestRate);
    void ApplyInterest(); //to add interest to the balance periodically
    void OverrideWithdraw(); //to ensure a minimum balance requirement, if desired.
};

