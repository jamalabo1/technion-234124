//
// Created by jamal on 19/06/2024.
//
#include "BlockChain.h"
#include "Transaction.h"

using std::endl;
using std::to_string;

void splitBlockchainLine(string line, string data[4]);

int BlockChainGetSize(const BlockChain &blockChain) {
    return blockChain.size;
}

int BlockChainPersonalBalance(const BlockChain &blockChain,
                              const string &name) {

    unsigned int balance = 0;
    blockChainBlock *currentBlock = blockChain.head;

    for (int i = 0; i < BlockChainGetSize(blockChain); i++) {
        if (currentBlock == nullptr) break;
        if (currentBlock->transaction.receiver == name) {
            balance += currentBlock->transaction.value;
        }
        if (currentBlock->transaction.sender == name) {
            balance -= currentBlock->transaction.value;
        }
        currentBlock = currentBlock->chain;
    }
    return balance;
}

void
BlockChainAppendTransaction(BlockChain &blockChain, unsigned int value,
                            const string &sender, const string &receiver,
                            const string &timestamp) {

    Transaction transaction = {
            value,
            sender,
            receiver
    };

    BlockChainAppendTransaction(blockChain, transaction, timestamp);
}

void BlockChainAppendTransaction(BlockChain &blockChain,
                                 const Transaction &transaction,
                                 const string &timestamp) {


    blockChainBlock *block = new blockChainBlock{
            transaction,
            timestamp,
            blockChain.head
    };

    blockChain.head = block;
    blockChain.size++;
}


void splitBlockchainLine(string line, string data[4]) {
    string tempString;
    int currentIndex = 0;
    for (int i = 0; i < (int) line.length(); i++) {

        if (line[i] == ' ') {
            data[currentIndex++] = tempString;
            tempString = "";
            continue;
        }
        tempString += line[i];
    }
    data[currentIndex] = tempString;
}

BlockChain BlockChainLoad(ifstream &file) {
    BlockChain blockChain{0, nullptr};
    string line;
    blockChainBlock *currentBlock = nullptr;
    while (!file.eof()) {
        getline(file, line);
        string data[4] = {""};
        splitBlockchainLine(line, data);
        Transaction transaction = {
                /*.value =*/    (unsigned int) atoi(data[2].c_str()), data[0],
                /*.receiver =*/ data[1],
        };
        string timestamp = data[3];
        blockChainBlock *x = new blockChainBlock{transaction,
                /*    .timestamp = */timestamp,
                /*    .chain = */nullptr
        };
        if (currentBlock == nullptr) {
            currentBlock = x;
            blockChain.head = currentBlock;
        } else {
            currentBlock->chain = x;
            currentBlock = x;
        }
        blockChain.size++;
    }
    return blockChain;
}

void BlockChainDump(const BlockChain &blockChain, ofstream &file) {
    file << "BlockChain Info:" << endl;

    blockChainBlock *currentBlock = blockChain.head;

    int size = BlockChainGetSize(blockChain);
    for (int i = 1; i <= size; i++) {
        if (currentBlock == nullptr) break;

        file << to_string(i) + "." << endl;
        TransactionDumpInfo(currentBlock->transaction, file);

        file << "Transaction timestamp: " + currentBlock->timestamp;
        if (i != size) {
            file << endl;
        }
        currentBlock = currentBlock->chain;
    }
}

void BlockChainDumpHashed(const BlockChain &blockChain, ofstream &file) {
    blockChainBlock *currentBlock = blockChain.head;

    int size = BlockChainGetSize(blockChain);
    for (int i = 1; i <= size; i++) {
        if (currentBlock == nullptr) break;

        file << TransactionHashedMessage(currentBlock->transaction);
        if (i != size) {
            file << endl;
        }

        currentBlock = currentBlock->chain;
    }
}


// private function implementation, to preserve original function signature.
bool BlockChainVerifyFile(const BlockChain &blockChain, ifstream &file) {
    blockChainBlock *currentBlock = blockChain.head;

    int size = BlockChainGetSize(blockChain);
    string line;

    for (int i = 1; i <= size; i++) {
        if (currentBlock == nullptr) return false;

        if (file.eof()) return false;

        getline(file, line);

        if (!TransactionVerifyHashedMessage(currentBlock->transaction, line)) {
            return false;
        }


        currentBlock = currentBlock->chain;
    }

    return true;
}


void BlockChainCompress(BlockChain &blockChain) {
    blockChainBlock *currentBlock = blockChain.head;

    int size = BlockChainGetSize(blockChain);
    if (size == 1 || currentBlock == nullptr) return;

    // previous block
    blockChainBlock *pBlock = currentBlock;

    currentBlock = currentBlock->chain;

    for (int i = 2; i <= size; i++) {
        if (currentBlock == nullptr) break;

        Transaction &currentTransaction = currentBlock->transaction;

        if (pBlock->transaction.sender == currentTransaction.sender &&
            pBlock->transaction.receiver == currentTransaction.receiver) {
            pBlock->transaction.value += currentTransaction.value;
            pBlock->chain = currentBlock->chain;
            delete currentBlock;
            blockChain.size--;
            currentBlock = pBlock->chain;
        } else {
            pBlock = currentBlock;
            currentBlock = currentBlock->chain;
        }
    }
}

void BlockChainTransform(BlockChain &blockChain, updateFunction function) {
    blockChainBlock *currentBlock = blockChain.head;

    int size = BlockChainGetSize(blockChain);

    for (int i = 1; i <= size; i++) {
        if (currentBlock == nullptr) break;

        currentBlock->transaction.value =
                function(currentBlock->transaction.value);

        currentBlock = currentBlock->chain;
    }
}
