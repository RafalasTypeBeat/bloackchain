#include "blockchain.h"

bool Blockchain::generate_first_block() 
{
  if (blockchain_height != 0)
  {
    cout << "First block is already created!" << endl;
    return false;
  }
  long time = get_current_time();
  string hashed_values = convert(to_string(blockchain_height) + to_string(time) + version);
  block first_block {hashed_values, blockchain_height, "first_block", time, version, }
}


