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
    generated_users.push_back(new_user);
}

vector<Blockchain::user> Blockchain::get_users()
{
  return generated_users;
}
