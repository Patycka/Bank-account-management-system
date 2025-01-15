#include <account.hpp>
#include "account_dao.hpp"

////////////////////////////////////////////////////////////////////////
// A basic account with fewer restrictions on withdrawals
////////////////////////////////////////////////////////////////////////

class CheckingAccount : public db::Account 
{
public:
    CheckingAccount(std::string number, std::string name, db::AccountDAO &accountDao, double interestRate);
    void WithdrawMoney(double amount) override; // To allow unlimited transactions or to check for overdrafts (if overdraft protection is needed).
};
