#pragma once // prevent multiple inclusion of header files, the same #ifndef #define #endif

#include <cstdint>
#include <iosfwd>
#include <string>
#include <account.hpp>
#include <Poco/Data/Session.h>

////////////////////////////////////////////////////////////////////////
// Represents individual transactions.
////////////////////////////////////////////////////////////////////////

class Transaction 
{
    friend class TransactionDAO;
private:
    int transactionId;
    std::string transactionType;
    double amount;
    std::string timestamp;
    std::string accountNumber;    
public:
    Transaction(std::string transactionType, double amount, std::string date, std::string accountNumber);
    void GetTransaction(int transactionId);
};

class TransactionDAO
{
public:
    explicit TransactionDAO(Poco::Data::Session& session);
    void InsertLog(Transaction& transaction);
private:
    Poco::Data::Session& m_session;

};