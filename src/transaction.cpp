#include "transaction.hpp"

using namespace Poco::Data::Keywords;

Transaction::Transaction(std::string transactionType, double amount, std::string date, std::string accountNumber)
    : transactionType{transactionType}, amount{amount}, timestamp{date}, accountNumber{accountNumber}
{
}

TransactionDAO::TransactionDAO(Poco::Data::Session& session) : m_session{session}
{
}

void TransactionDAO::InsertLog(Transaction& transaction) //todo why needed to delete const
{
    try {
        Poco::Data::Statement insertStatement{m_session};
        insertStatement << "INSERT INTO transactions VALUES (?, ?, ?, ?, ?)", 
                        use(transaction.transactionId),
                        use(transaction.accountNumber),
                        use(transaction.transactionType),
                        use(transaction.amount),
                        use(transaction.timestamp);
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