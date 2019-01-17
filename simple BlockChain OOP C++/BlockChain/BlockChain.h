#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include <vector>

class BlockChain
{
private:
	Block createGenesisBlock();
	std::vector<Block> chain;

public:
	BlockChain();
	std::vector<Block> getChain();
	Block *getLatestBlock();
	bool isChainValid();
	void addBlock(TransactionData data);
	void printChain();
};
#endif