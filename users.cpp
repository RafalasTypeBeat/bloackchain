#include "blockchain.h"

void Blockchain::create_transaction(const string& from, const string& to, const int& amount)
{
  long current_time = get_current_time();

  string hashed_data = from + to + to_string(amount) + to_string(current_time);
  string transaction_id = convert(hashed_data);
  transaction new_transacion {transaction_id, from, to, amount, current_time};
  generated_transactions.push_back(new_transacion);
}

void Blockchain::create_user(const string& name) {
    long current_time = get_current_time();
    string hashed_data = name + to_string(current_time);
    string public_key = convert(hashed_data);
    user new_user {name, public_key, current_time};
    txo fisrt_txo = generate_starting_balances(public_key);
    new_user.utxos.push_back(fisrt_txo);
    generated_users.push_back(new_user);
}

Blockchain::txo Blockchain::generate_starting_balances(const string& public_key)
{
  long unsigned int seed = get_current_time();
  mt.seed(seed);
  uniform_int_distribution<int> amount_distribution(1000, 10000);
  int amount = amount_distribution(mt);
  long time = get_current_time();
  string to = public_key;
  string hashed_data = to + to_string(amount) + to_string(time);
  txo new_txo {hashed_data, to, amount};
  return new_txo;
} 

vector<Blockchain::user> Blockchain::get_users()
{
  return generated_users;
}
