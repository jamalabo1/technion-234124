//
// Created by jamal on 19/06/2024.
//

#include <iostream>
#include "Utilities.h"
#include "BlockChain.h"

using std::cout;
using std::endl;

void printErrorMessage() {
    std::cout << getErrorMessage() << std::endl;
}

void freeBlockchain(BlockChain &blockChain) {
    BlockChainBlock *c = blockChain.head;
    for (int i = 0; i < blockChain.size; ++i) {
        if (c == nullptr) return;
        BlockChainBlock *next = c->chain;
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


    ifstream source_file(source);

    BlockChain blockchain = BlockChainLoad(source_file);


    if (op == "format") {
        ofstream output_file(target);
        BlockChainDump(blockchain, output_file);

    } else if (op == "hash") {
        ofstream output_file(target);
        BlockChainDumpHashed(blockchain, output_file);

    } else if (op == "compress") {
        ofstream output_file(target);
        BlockChainCompress(blockchain);
        BlockChainDump(blockchain, output_file);

    } else if (op == "verify") {
        ifstream verify_file(target);
        if (BlockChainVerifyFile(blockchain, verify_file)) {
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