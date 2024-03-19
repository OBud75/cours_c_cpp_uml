#pragma once

#include <string>
#include <vector>

class Bank;
class Card;
class Advisor;
class Client;
class Account;

class User {
public:
    User(const std::string& name);
protected:
    std::string name;
};

class Advisor : public User {
public:
    Advisor(const std::string& name, Bank& bank);
private:
    Bank& bank;
};

class Client : public User {
public:
    Client(const std::string& name, Advisor& advisor);
private:
    Advisor& advisor;
};

class Card {
public:
    virtual int max_withdrawal() const = 0;
};

class GoldCard : public Card {
public:
    int max_withdrawal() const override;
};

class PlatinumCard : public Card {
public:
    int max_withdrawal() const override;
};

class BlackCard : public Card {
public:
    int max_withdrawal() const override;
};

class Account {
public:
    Account(Client& client, Card& card, double initial_balance);
    void deposit(double amount);
    bool withdraw(double amount);
    double get_balance() const;
private:
    Client& client;
    Card& card;
    double balance;
};

class Bank {
public:
    Bank(const std::string& name);
    void add_client(Client& client);
    void add_account(Account& account);
    std::string get_name() const;
private:
    std::string name;
    std::vector<Client*> clients;
    std::vector<Account*> accounts;
};

class Location {
public:
    explicit Location(const std::string& address);
private:
    std::string address;
};

class ATM {
public:
    ATM(Bank& bank, const Location& location);
    bool perform_withdrawal(Account& account, double amount);
private:
    Bank& bank;
    Location location;
};
