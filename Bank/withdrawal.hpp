#pragma once

class Card {
public:
    virtual int max_withdrawal() const = 0;
    virtual int max_credit() const = 0;
};

class GoldCard : public Card {
public:
    int max_withdrawal() const override;
    int max_credit() const override;
};

class PlatiniumCard : public Card {
public:
    int max_withdrawal() const override;
    int max_credit() const override;
};

class BlackCard : public Card {
public:
    int max_withdrawal() const override;
    int max_credit() const override;
};

template<typename TCard>
class Withdrawal {
private:
    TCard &creditcard;

public:
    Withdrawal(TCard &card) : creditcard(card) {}
    int operator()(int amount);
};
