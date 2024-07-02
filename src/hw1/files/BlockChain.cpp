//
// Created by jamal on 19/06/2024.
//
#include "BlockChain.h"
#include "Transaction.h"

using std::endl;
using std::to_string;

int BlockChainGetSize(const BlockChain &blockChain) {
    return blockChain.size;
}

int BlockChainPersonalBalance(const BlockChain &blockChain,
                              const string &name) {

    int balance = 0;
    BlockChainBlock *current_block = blockChain.head;

    for (int i = 0; i < BlockChainGetSize(blockChain); i++) {
        if (current_block == nullptr) break;
        if (current_block->transaction.receiver == name) {
            balance += current_block->transaction.value;
        }
        if (current_block->transaction.sender == name) {
            balance -= current_block->transaction.value;
        }
        current_block = current_block->chain;
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


    BlockChainBlock *block = new BlockChainBlock{
            transaction,
            timestamp,
            blockChain.head
    };

    blockChain.head = block;
    blockChain.size++;
}


void splitBlockchainLine(string line, string data[4]) {
    string temp_string = "";
    int current_index = 0;
    for (int i = 0; i < (int) line.length(); i++) {

        if (line[i] == ' ') {
            data[current_index++] = temp_string;
            temp_string = "";
            continue;
        };
        temp_string += line[i];
    }
    data[current_index] = temp_string;
}

BlockChain BlockChainLoad(ifstream &file) {
    BlockChain blockChain{0, nullptr};
    string line;
    BlockChainBlock *current_block = nullptr;
    while (!file.eof()) {
        getline(file, line);
        string data[4] = {""};
        splitBlockchainLine(line, data);
        Transaction transaction = {
                /*.value =*/    (unsigned int) atoi(data[2].c_str()), data[0],
                /*.receiver =*/ data[1],
        };
        string timestamp = data[3];
        BlockChainBlock *x = new BlockChainBlock{transaction,
                /*    .timestamp = */timestamp,
                /*    .chain = */nullptr
        };
        if (current_block == nullptr) {
            current_block = x;
            blockChain.head = current_block;
        } else {
            current_block->chain = x;
            current_block = x;
        }
        blockChain.size++;
    }
    return blockChain;
}

void BlockChainDump(const BlockChain &blockChain, ofstream &file) {
    file << "BlockChain Info:" << endl;

    BlockChainBlock *current_block = blockChain.head;

    int size = BlockChainGetSize(blockChain);
    for (int i = 1; i <= size; i++) {
        if (current_block == nullptr) break;

        file << to_string(i) + "." << endl;
        TransactionDumpInfo(current_block->transaction, file);

        file << "Transaction timestamp: " + current_block->timestamp;
        if (i != size) {
            file << endl;
        }
        current_block = current_block->chain;
    }
}

void BlockChainDumpHashed(const BlockChain &blockChain, ofstream &file) {
    BlockChainBlock *current_block = blockChain.head;

    int size = BlockChainGetSize(blockChain);
    for (int i = 1; i <= size; i++) {
        if (current_block == nullptr) break;

        file << TransactionHashedMessage(current_block->transaction);
        if (i != size) {
            file << endl;
        }

        current_block = current_block->chain;
    }
}


// private function implementation, to preserve original function signature.
bool BlockChainVerifyFile(const BlockChain &blockChain, ifstream &file) {
    BlockChainBlock *current_block = blockChain.head;

    int size = BlockChainGetSize(blockChain);
    string line;

    for (int i = 1; i <= size; i++) {
        if (current_block == nullptr) return false;

        if (file.eof()) return false;

        getline(file, line);

        if (!TransactionVerifyHashedMessage(current_block->transaction, line)) {
            return false;
        }


        current_block = current_block->chain;
    }

    return true;
}


void BlockChainCompress(BlockChain &blockChain) {
    BlockChainBlock *current_block = blockChain.head;

    int size = BlockChainGetSize(blockChain);
    if (size == 1 || current_block == nullptr) return;

    // previous block
    BlockChainBlock *p_block = current_block;

    current_block = current_block->chain;

    for (int i = 2; i <= size; i++) {
        if (current_block == nullptr) break;

        Transaction &current_transaction = current_block->transaction;

        if (p_block->transaction.sender == current_transaction.sender &&
            p_block->transaction.receiver == current_transaction.receiver) {
            p_block->transaction.value += current_transaction.value;
            p_block->chain = current_block->chain;
            delete current_block;
            blockChain.size--;
            current_block = p_block->chain;
        } else {
            p_block = current_block;
            current_block = current_block->chain;
        }
    }
}

void BlockChainTransform(BlockChain &blockChain, updateFunction function) {
    BlockChainBlock *current_block = blockChain.head;

    int size = BlockChainGetSize(blockChain);

    for (int i = 1; i <= size; i++) {
        if (current_block == nullptr) break;

        current_block->transaction.value =
                function(current_block->transaction.value);

        current_block = current_block->chain;
    }
}
