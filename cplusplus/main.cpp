
class ATMState {// has same interface as ATM
};
class NoCardState : public ATMState {};
class NoPinState : public ATMState {};
class VerifiedState : public ATMState {};

class ATM {
public:
  ATM();
  void ReadCard();
  void Withdraw();
  void Deposit();
  void Transfer();
  void Inquiry();
private:
  
  // State Pattern
  ATMStatePtr m_atm_state_ptr;
 
  // ATM components
  CashDispenserPtr m_cash_dispenser_ptr;
  CustomerConsolePtr m_customer_console_ptr;
  CardReaderPtr m_card_reader_ptr;
  CashReaderPtr m_cash_reader_ptr;
  CheckReaderPtr m_check_reader_ptr;
  LogPtr m_log_ptr;
  PrinterPtr m_printer_ptr;
};


class Transaction {
public:
  Transaction(AccountPtr account_ptr) : m_account_ptr(account_ptr) {}
  virutal ~Transaction() {}
  virtual void Execute() = 0;
  virtual void Cancel() = 0;
private:
  AccountPtr m_account_ptr;
};

class Withdraw : public Transaction() {}
class Deposit : public Transaction() {}
class Inquiry : public Transaction() {}
class Transfer : public Transaction() {}

class Account {
public:
  virtual ~Account(){}
private:
  std::string m_account_number;
  double m_balance;
};
class CheckingAccount : public Account{};
class SavingAccount : public Account{};

class User {
public:
  User();
private:
  std::vector<AccountPtr> m_accounts;
  
};

class BankDatabaseProxy {
public:
  void Execute(TransactionPtr transaction_ptr);
};



