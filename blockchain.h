#include "header.h"
#include "block.h"

class Blockchain
{
  private:
    Block createGenesisBlock();

  public:
    vector<Block> chain; 

    Blockchain(); //constructor

    void addBlock(TransactionData data);
    void isChainValid();

    Block *getLatestBlock(); //for testing
};