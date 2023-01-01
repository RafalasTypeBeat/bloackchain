#include "blockchain.h"
#include "hash.cpp"

bool Blockchain::generate_first_block() 
{
  if (blockchain_height != 0)
  {
    cout << "First block is already created!" << endl;
    return false;
  }

  vector<user> users;
  users = generated_users;
  long unsigned int seed = get_current_time();
  mt.seed(seed);
  uniform_int_distribution<int> amount_distribution(1000, 10000);

  for (user i:users)
  {
    string from = "Coinbase";
    string to = i.public_key;
    int amount = amount_distribution(mt);
    long time = get_current_time();
    string hashed_data = from + to + to_string(amount) + to_string(time);
    string transaction_id = convert(hashed_data);

    vector<txo> input;
    vector<txo> output;

    txo tx_output;
    tx_output.transaction_id = transaction_id;
    tx_output.to = to;
    tx_output.amount = amount;
    output.push_back(tx_output);

    transaction new_transaction {transaction_id, from, to, amount, time, input, output};
    generated_transactions[new_transaction.id] = new_transaction;
  }
  
}


