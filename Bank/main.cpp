#include <iostream>
#include "models.hpp"

int main() {
    std::cout << "Bienvenue dans votre banque !" << std::endl;

    Location myLocation("123 Main Street");
    Bank myBank("Banque Exemplaire");
    Advisor myAdvisor("Advisor1", myBank);
    Client myClient("Client1", myAdvisor);

    GoldCard myGoldCard;
    Account myAccount(myClient, myGoldCard, 1000.0);
    myBank.add_client(myClient);
    myBank.add_account(myAccount);

    ATM myATM(myBank, myLocation);
    bool withdrawalSuccess = myATM.perform_withdrawal(myAccount, 100.0);
    if (withdrawalSuccess) {
        std::cout << "Retrait reussi !" << std::endl;
    } else {
        std::cout << "Retrait echoue !" << std::endl;
    }

    std::cout << "Le solde de votre compte est maintenant de " << myAccount.get_balance() << " euros." << std::endl;
    return 0;
}
