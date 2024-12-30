#include <account.hpp>

////////////////////////////////////////////////////////////////////////
// A basic account with fewer restrictions on withdrawals
////////////////////////////////////////////////////////////////////////

class CheckingAccount : public Account 
{
public:
    CheckingAccount(std::string number, std::string name, double interestRate);
    void OverrideWithdraw(); // To allow unlimited transactions or to check for overdrafts (if overdraft protection is needed).
};
