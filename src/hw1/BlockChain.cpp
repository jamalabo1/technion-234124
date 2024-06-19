//
// Created by jamal on 19/06/2024.
//
#include "BlockChain.h"
#include "Transaction.h"

// although it ought not to occur, since the blockchain size
// is determined by the available chains.

#define CurrentBlockGuard(x) if (x == nullptr) break
#define MoveNextBlock(x) x = x->chain


using std::endl;

int BlockChainGetSize(const BlockChain &blockChain) {
    return blockChain.size;
}

int BlockChainPersonalBalance(const BlockChain &blockChain, const string &name) {

    int balance = 0;
    BlockChainBlock *current_block = blockChain.head;

    for (int i = 0; i < BlockChainGetSize(blockChain); i++) {
        CurrentBlockGuard(current_block);

        if (current_block->transaction.receiver == name) {
            balance += current_block->transaction.value;
        }
        if (current_block->transaction.sender == name) {
            balance -= current_block->transaction.value;
        }
        MoveNextBlock(current_block);
    }
    return balance;
}

void
BlockChainAppendTransaction(BlockChain &blockChain, unsigned int value, const string &sender, const string &receiver,
                            const string &timestamp) {

    Transaction transaction = {
            .value= value,
            .sender= sender,
            .receiver = receiver
    };

    BlockChainAppendTransaction(blockChain, transaction, timestamp);
}

void BlockChainAppendTransaction(BlockChain &blockChain, const Transaction &transaction, const string &timestamp) {


    BlockChainBlock *block = new BlockChainBlock{
            .transaction = transaction,
            .timestamp = timestamp,
            .chain = blockChain.head
    };

    blockChain.head = block;
    blockChain.size++;
}


BlockChain BlockChainLoad(ifstream &file) {

    BlockChain blockChain{
            .head=nullptr
    };

    string line;

    BlockChainBlock *current_block = nullptr;

    while (!file.eof()) {
        getline(file, line);

        string data[4] = {""};

        string temp_string = "";
        int current_index = 0;
        for (int i = 0; i < line.length(); i++) {

            if (line[i] == ' ') {
                data[current_index++] = temp_string;
                temp_string = "";
                continue;
            };
            temp_string += line[i];
        }
        data[current_index] = temp_string;

        Transaction transaction = {
                .value = (unsigned int) atoi(data[2].c_str()),
                .sender = data[0],
                .receiver = data[1],
        };


        string timestamp = data[3];

        BlockChainBlock *x = new BlockChainBlock{
                .transaction = transaction,
                .timestamp = timestamp,
                .chain = nullptr
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
        CurrentBlockGuard(current_block);

        file << std::to_string(i) + "." << endl;
        TransactionDumpInfo(current_block->transaction, file);

        file << "Transaction timestamp: " + current_block->timestamp;
        if (i != size) {
            file << endl;
        }
        MoveNextBlock(current_block);
    }
}

void BlockChainDumpHashed(const BlockChain &blockChain, ofstream &file) {
    BlockChainBlock *current_block = blockChain.head;

    int size = BlockChainGetSize(blockChain);
    for (int i = 1; i <= size; i++) {
        CurrentBlockGuard(current_block);

        file << TransactionHashedMessage(current_block->transaction);
        if (i != size) {
            file << endl;
        }

        MoveNextBlock(current_block);
    }
}


// private function implementation, to preserve original function signature.
bool _blockChainVerifyFile(const BlockChain &blockChain, ifstream &file, bool printMessage) {
    BlockChainBlock *current_block = blockChain.head;

    int size = BlockChainGetSize(blockChain);
    string line;

    for (int i = 1; i <= size; i++) {
        if (current_block->chain == nullptr) return false;

        if (file.eof()) return false;

        getline(file, line);

        if (line != TransactionHashedMessage(current_block->transaction)) {
            if (printMessage) {
                printf("Verification failed");
            }
            return false;
        }
        if (printMessage) {
            printf("Verification passed");
        }

        MoveNextBlock(current_block);
    }

    return true;
}

bool BlockChainVerifyFile(const BlockChain &blockChain, ifstream &file) {
    return _blockChainVerifyFile(blockChain, file, false);
}

bool BlockChainVerifyFileDetailed(const BlockChain &blockChain, ifstream &file) {
    return _blockChainVerifyFile(blockChain, file, true);
}


void BlockChainCompress(BlockChain &blockChain) {
    BlockChainBlock *current_block = blockChain.head;

    int size = BlockChainGetSize(blockChain);
    if (size == 1 || current_block == nullptr) return;

    BlockChainBlock *previous_block = current_block;

    MoveNextBlock(current_block);

    for (int i = 2; i <= size; i++) {
        CurrentBlockGuard(current_block);

        Transaction &current_transaction = current_block->transaction;

        if (previous_block->transaction.sender == current_transaction.sender &&
            previous_block->transaction.receiver == current_transaction.receiver) {
            previous_block->transaction.value += current_transaction.value;
            previous_block->chain = current_block->chain;
            delete current_block;
            blockChain.size--;
            current_block = previous_block->chain;
        } else {
            previous_block = current_block;
            current_block = current_block->chain;
        }
    }
}

void BlockChainTransform(BlockChain &blockChain, updateFunction function) {
    BlockChainBlock *current_block = blockChain.head;

    int size = BlockChainGetSize(blockChain);

    for (int i = 1; i <= size; i++) {
        CurrentBlockGuard(current_block);

        current_block->transaction.value = function(current_block->transaction.value);

        MoveNextBlock(current_block);
    }
}
