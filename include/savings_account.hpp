#include <account.hpp>

class SavingsAccount : public Account 
{
public:
    SavingsAccount(std::string number, std::string name, double interestRate);
    void ApplyInterest(); //to add interest to the balance periodically
    void OverrideWithdraw(); //to ensure a minimum balance requirement, if desired.
};

