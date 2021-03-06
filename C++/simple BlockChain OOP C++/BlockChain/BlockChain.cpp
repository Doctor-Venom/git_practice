#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include "Block.h"
#include "BlockChain.h"
using namespace std;

BlockChain::BlockChain()
{
	Block genesis = createGenesisBlock();
	chain.push_back(genesis);
}

std::vector<Block> BlockChain::getChain()
{
	return chain;
}

Block BlockChain::createGenesisBlock()
{
	std::time_t current;

	TransactionData d(0, "Genesis", "Genesis", time(&current));

	Block genesis(0, d, 0);

	return genesis;
}

Block *BlockChain::getLatestBlock()
{
	return &chain.back();
}

void BlockChain::addBlock(TransactionData d)
{
	int index = (int)chain.size();
	std::size_t previousHash = (int)chain.size() > 0 ? getLatestBlock()->getHash() : 0;
	Block newBlock(index, d, previousHash);
	chain.push_back(newBlock);
}

bool BlockChain::isChainValid()
{
	std::vector<Block>::iterator it;
	for (it = chain.begin(); it != chain.end(); ++it)
	{
		Block currentBlock = *it;

		if (!currentBlock.isHashValid())
		{
			return false;
		}

		if (it != chain.begin())
		{
			Block previousBlock = *(it - 1);
			if (currentBlock.getPreviousHash() != previousBlock.getHash())
			{
				return false;
			}
		}
	}
	return true;
}

void BlockChain::printChain()
{
	std::vector<Block>::iterator it;

	for (it = chain.begin(); it != chain.end(); ++it)
	{
		Block currentBlock = *it;
		cout << "\n===========================Block===========================";
		cout << "\nIndex: " << currentBlock.getIndex();
		cout << "\nAmount: " << currentBlock.data.amount;
		cout << "\nSenderKey: " << currentBlock.data.senderKey.c_str();
		cout << "\nReceiverKey: " << currentBlock.data.receiverKey.c_str();
		cout << "\nTimestamp: " << currentBlock.data.timestamp;
		cout << "\nHash: " << currentBlock.getHash();
		cout << "\nPrevious Hash: " << currentBlock.getPreviousHash();
		cout << "\nIs Block Valid?: " << currentBlock.isHashValid();
		cout << "\n===========================================================";

	}
}