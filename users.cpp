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

void Blockchain::print_users()
{
  cout << "Users:\n";
  for (auto u : generated_users)
  {
    cout << u.name << '\n';
    cout << u.public_key << '\n';
    cout << u.time_created << '\n';
    //cout << u.time_created << '\n';
  }
}

void Blockchain::print_transactions()
{
  cout << "Transactions:\n";
  for (auto t : generated_transactions)
  {
    cout << "Transaction id: "<< t.id << '\n';
    cout << "From: "<< t.from << '\n';
    cout << "To: "<< t.to << '\n';
    cout << "Amount: "<< t.amount << '\n';
    cout << "Transaction time: "<< t.time << '\n';
    //cout << u.time_created << '\n';
  }
}