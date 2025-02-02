#include "transaction.hpp"
#include <Poco/Data/RecordSet.h>

using namespace Poco::Data::Keywords;

Transaction::Transaction(std::string transactionType, double amount, std::string date, std::string accountNumber)
    : transactionType{transactionType}, amount{amount}, timestamp{date}, accountNumber{accountNumber}
{
}

TransactionDAO::TransactionDAO(Poco::Data::Session& session) : m_session{session}
{
}

void TransactionDAO::InsertLog(const Transaction& transaction) //todo why needed to delete const
{
    try {
        Poco::Data::Statement insertStatement{m_session};
        insertStatement << "INSERT INTO transactions (account_number, transaction_type, amount, transaction_timestamp) VALUES (?, ?, ?, ?)", 
                        useRef(transaction.accountNumber),
                        useRef(transaction.transactionType),
                        useRef(transaction.amount),
                        useRef(transaction.timestamp);
        const std::size_t rowsAffected{insertStatement.execute()};
        auto ins = insertStatement.getStorage();

        if (rowsAffected == 0) {
            std::cerr << "rowsAffected == 0!\n";
            return;
        }

        if (!insertStatement.done()) {
            std::cerr << "insertStatement.done()!\n";
            return;
        }
    }
    catch ([[maybe_unused]] const Poco::Exception& exception) {
        std::cout << exception.message() << std::endl; 
        return;
    }
}

std::vector<Transaction> TransactionDAO::GetTransactions(std::string accountNumber, Poco::Data::Session& session)
{
    std::vector<Transaction> vector{};
    try {
        Poco::Data::Statement selectStatement{session};
        selectStatement << "SELECT * FROM transactions WHERE account_number = ?", useRef(accountNumber);
        selectStatement.execute();
        Poco::Data::RecordSet recordSet{selectStatement};
        if (recordSet.rowCount() == 0) {
            // Nothing found
            return {};
        }

        do {
            std::uint64_t id{recordSet["transaction_id"].convert<std::uint64_t>()};
            // TODO: Also add account number
            std::string type{recordSet["transaction_type"].convert<std::string>()};
            double amount{recordSet["amount"].convert<double>()};
            std::string timestamp{recordSet["transaction_timestamp"].convert<std::string>()};
            std::cout << "Transaction ID: " << id << " Type: " << type << " Amount: " << amount << " Timestamp: " << timestamp << std::endl;
            vector.push_back(Transaction(type, amount, timestamp, accountNumber));
        } while (recordSet.moveNext());
        return vector;
    }
    catch ([[maybe_unused]] const Poco::Exception& exception) {
        std::cout << exception.message() << std::endl; 
        return {}; //return empty vector
    }
}



