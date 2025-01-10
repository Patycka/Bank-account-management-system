#include <account.hpp>

////////////////////////////////////////////////////////////////////////
// Represents individual transactions.
////////////////////////////////////////////////////////////////////////

class Transaction : public db::Account
{
private:
    std::string transactionId;
    uint8_t transactionType;
    double amount;
    std::string timestamp;    
public:
    Transaction(std::string transactionType, double amount, std::string date);
    void DisplayTransaction();
}