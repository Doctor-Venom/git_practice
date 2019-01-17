#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <vector>
#include "TransactionData.h"
#include "Block.h"
#include "BlockChain.h"
using namespace std;

int main()
{
	BlockChain testchain;

	time_t data1Time;
	TransactionData data1(1.5, "mansour", "aws", time(&data1Time));
	testchain.addBlock(data1);

	time_t data2Time;
	TransactionData data2(0.5, "aws", "mansour", time(&data2Time));
	testchain.addBlock(data2);

	testchain.printChain();

	cout << "\nIs chain still valid? " << testchain.isChainValid() << endl;

	Block *hackBlock = testchain.getLatestBlock();
	hackBlock->data.amount = 1000;
	hackBlock->data.receiverKey = "mansour";

	testchain.printChain();

	cout << "\nIs chain still valid? " << testchain.isChainValid() << endl;

	return 0;
}

