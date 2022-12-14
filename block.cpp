#include "block.h"

Block::Block(int indx, TransactionData t, string prevHash)
{
  index = indx;
  data = t;
  previousHash = prevHash;
  blockHash = generateHash();
}

string Block::generateHash()
{
  hash<string> hash1;
  hash<string> hash2;
  hash<string> hash3;
}