#include "header.h"

class Block
{
  private:
    int index;
    string blockHash;
    string previousHash;
    string generateHash;

  public:
    Block(int indx, TransactionData t, string prevHash); //Constructor

    string getHash();
    string getPreviousHash();
    TransactionData data;
    bool isHashValid();
};