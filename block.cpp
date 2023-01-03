#include "blockchain.h"

void Blockchain::generate_first_block() 
{
  if (blockchain_height != 0)
  {
    cout << "First block is already created!" << endl;
  }
  else {
  cout << "Started generating first block\n";
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
    coinbase_transactions.push_back(new_transaction.id);
    i.utx_ids.push_back(transaction_id);
  }
  string prev_block_hash = convert("first_block");
  long time = get_current_time();
  vector<string> tx_ids;
  
  string merkleroot = get_merkleroot(coinbase_transactions);
  block first_block;
  first_block.height = blockchain_height;
  first_block.prev_block_hash = prev_block_hash;
  first_block.time = time;
  first_block.version = version;
  first_block.merkleroot = merkleroot;
  first_block.nonce = 0;
  first_block.difficulity_target = difficulity_target;
  first_block.tx = coinbase_transactions;
  string hashed_data = to_string(blockchain_height) + prev_block_hash + to_string(time) + version
  + merkleroot + to_string(first_block.nonce) + to_string(difficulity_target);
  first_block.hash = convert(hashed_data);
  blockchain.push_back(first_block);
  cout << "Finished generating first block\n";
  }
}

void Blockchain::print_block(int block_height)
{
    block chosen_block = get_block(block_height);
    cout << "Printing block: " << chosen_block.height << '\n';
    cout << "Block hash: " << chosen_block.hash << '\n';
    cout << "Prev block hash: " << chosen_block.prev_block_hash << '\n';
    cout << "Block creation time: " << chosen_block.time << '\n';
    cout << "Block version: " << chosen_block.version << '\n';
    cout << "Block merkleroot: " << chosen_block.merkleroot << '\n';
    cout << "Block nonce: " << chosen_block.nonce << '\n';
    cout << "Block difficulity target: " << chosen_block.difficulity_target << '\n';
    cout << "Block transactions: " << chosen_block.difficulity_target << '\n';
}

Blockchain::block Blockchain::get_block(int block_height)
{
    if (block_height > blockchain_height)
    {
        cout << "No such block exists!";
        return blockchain[0]; // change to latest block
    }
    auto it = find_if(blockchain.begin(), blockchain.end(), [&](const block& b)
    {
        return b.height == block_height;
    });
    block found_block = *it;
    return found_block;
}
