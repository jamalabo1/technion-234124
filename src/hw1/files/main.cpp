//
// Created by jamal on 19/06/2024.
//

#include <iostream>
#include "Utilities.h"
#include "BlockChain.h"

using std::cout;
using std::endl;

void printErrorMessage() {
    cout << getErrorMessage() << endl;
}

void freeBlockchain(BlockChain &blockChain) {
    blockChainBlock *c = blockChain.head;
    for (int i = 0; i < blockChain.size; ++i) {
        if (c == nullptr) return;
        blockChainBlock *next = c->chain;
        delete c;
        c = next;
    }

    delete c;
}

int main(int argc, char **argv) {

    if (argc != 4) {
        printErrorMessage();
        return 1;
    }

    string op = argv[1];
    string source = argv[2];
    string target = argv[3];


    ifstream sourceFile(source);

    BlockChain blockchain = BlockChainLoad(sourceFile);


    if (op == "format") {
        ofstream outputFile(target);
        BlockChainDump(blockchain, outputFile);

    } else if (op == "hash") {
        ofstream outputFile(target);
        BlockChainDumpHashed(blockchain, outputFile);

    } else if (op == "compress") {
        ofstream outputFile(target);
        BlockChainCompress(blockchain);
        BlockChainDump(blockchain, outputFile);

    } else if (op == "verify") {
        ifstream verifyFile(target);
        if (BlockChainVerifyFile(blockchain, verifyFile)) {
            cout << "Verification passed" << endl;
        } else {
            cout << "Verification failed" << endl;
        }
    } else {
        printErrorMessage();
        return 1;
    }

    freeBlockchain(blockchain);

    return 0;
}