//
// Created by jamal on 19/06/2024.
//
#include "Transaction.h"
#include "Utilities.h"

void TransactionDumpInfo(const Transaction &transaction, ofstream &file) {
    file << "Sender Name: " + transaction.sender << std::endl;
    file << "Receiver Name: " + transaction.receiver << std::endl;
    file << "Transaction Value: " + std::to_string(transaction.value) << std::endl;
}

string TransactionHashedMessage(const Transaction &transaction) {
    return hash(transaction.value, transaction.sender, transaction.receiver);
}

bool TransactionVerifyHashedMessage(const Transaction &transaction, string hashedMessage) {
    return TransactionHashedMessage(transaction) == hashedMessage;
}
