The recommended way to build POCO is via CMake.
For windows users. In case of troubles with building the project:


Use shell from Developer Command Prompt for VS 2022 (run as administrator)
mkdir build 
cd build
cmake -G "Visual Studio 17 2022" -A x64 .. 
cmake --build . --config Debug --parallel 2

For windows users also copy file libmysql.dll from MySQL Server / lib to project folder build/bin


Bank Account Management System
Create a simple banking system where users can create accounts,
deposit/withdraw money, and view transaction histories.
Object oriented programming.

1. Account (Base Class):

This class will serve as the base for different types of accounts.
Attributes:
	accountNumber (string or int)
	accountHolderName (string)
	balance (double)
	transactionHistory (vector of strings or a custom Transaction class)
Methods:
	deposit(double amount)
	withdraw(double amount)
	viewBalance()
	viewTransactionHistory()
	addTransaction(string transactionDetails) (to store transaction details)

2. SavingsAccount (Derived Class from Account):

A basic account type with interest.
Additional Attributes:
	interestRate (double)
Methods:
	applyInterest() (to add interest to the balance periodically)
	Override withdraw() to ensure a minimum balance requirement, if desired.

3. CheckingAccount (Derived Class from Account):
A basic account with fewer restrictions on withdrawals.
Methods:
Override withdraw() to allow unlimited transactions or to check for overdrafts (if overdraft protection is needed).


4. Transaction (Helper Class):
Represents individual transactions.
Attributes:
transactionID (int or string)
transactionType (Deposit, Withdrawal)
amount (double)
timestamp (date/time)
This class can be used to create a detailed transaction history for each account.