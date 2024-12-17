#include <iostream>

#include <Poco/Data/MySQL/Connector.h>
#include <Poco/Data/Session.h>
#include <Poco/Data/SessionFactory.h>

#include "account_dao.hpp"
#include "scope_guard.hpp"
#include "account.hpp"

int main()
{
  Poco::Data::MySQL::Connector::registerConnector();
  const std::string connectionString{
    "host=127.0.0.1;user=root;password=Patrycja1234;db=accountdb;compress=true;auto-"
    "reconnect="
    "true"};
  Poco::Data::Session session{Poco::Data::SessionFactory::instance().create(
    Poco::Data::MySQL::Connector::KEY, connectionString)};

  if (!session.isConnected()) {
    std::cerr << "session is not connected!\n";
    return EXIT_FAILURE;
  }

  if (!session.isGood()) {
    std::cerr << "session is bad!\n";
    return EXIT_FAILURE;
  }

  auto scopeGuard{db::makeScopeGuard([&session] {
    session.commit();
    session.close();
  })};

  db::AccountDAO accountDAO{session};
  std::optional<db::Account> optionalAccount{
    accountDAO.CreateAccount("Anna Smith")};

  if (!optionalAccount.has_value()) {
    std::cerr << "Couldn't create Anna Smith!\n";
    return EXIT_FAILURE;
  }

  db::Account& account{*optionalAccount};
  std::cout << "Successfully created \"" << account << "\"!\n";

  // if (!accountDAO.updateAccount(account, "John Smith")) {
  //   std::cerr << "Couldn't update Account name.\n";
  //   return EXIT_FAILURE;
  // }

  // std::cout << "Successfully updated Account to \"" << account << "\"!\n";

  std::optional<db::Account> optional{accountDAO.ReadAccount("1234")};

  if (!optional.has_value()) {
    std::cerr << "Couldn't find client with account number 1234 \n";
    return EXIT_FAILURE;
  }

  // std::cout << "read \"" << *optional << "\" from the database.\n";

  // if (!accountDAO.DeleteAccount(account)) {
  //   std::cerr << "Couldn't delete customer.\n";
  //   return EXIT_FAILURE;
  // }

  // std::cout << "Managed to delete customer.\n";
  return EXIT_SUCCESS;
}
