
#include "models.hpp"

User::User(const std::string& name) : name(name) {}

Advisor::Advisor(const std::string& name, Bank& bank) : User(name), bank(bank) {}

Client::Client(const std::string& name, Advisor& advisor) : User(name), advisor(advisor) {}

Account::Account(Client& client, Card& card, double initial_balance)
    : client(client), card(card), balance(initial_balance) {}

void Account::deposit(double amount) {
    balance += amount;
}

bool Account::withdraw(double amount) {
    if (amount <= balance && amount <= card.max_withdrawal()) {
        balance -= amount;
        return true;
    }
    return false;
}

double Account::get_balance() const {
    return balance;
}

Bank::Bank(const std::string& name) : name(name) {}

void Bank::add_client(Client& client) {
    clients.push_back(&client);
}

void Bank::add_account(Account& account) {
    accounts.push_back(&account);
}

std::string Bank::get_name() const {
    return name;
}

Location::Location(const std::string& address) : address(address) {}

ATM::ATM(Bank& bank, const Location& location) : bank(bank), location(location) {}

bool ATM::perform_withdrawal(Account& account, double amount) {
    return account.withdraw(amount);
}
