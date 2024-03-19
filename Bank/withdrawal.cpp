#include "withdrawal.hpp"

template<typename TCard>
int Withdrawal<TCard>::operator()(int amount) {
    if (amount <= creditcard.max_withdrawal()) {
        return amount;
    }
    return 0;
}

template class Withdrawal<GoldCard>;
template class Withdrawal<PlatiniumCard>;
template class Withdrawal<BlackCard>;
