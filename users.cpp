#include "blockchain.h"

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
    cout << "User name: " << u.name << '\n';
    cout << "User public key: " << u.public_key << '\n';
    for (auto utx : u.utx_ids)
    {
      cout << "UTXO's : " << utx << '\n';
    }
    //cout << u.time_created << '\n';
  }
}

int Blockchain::get_user_utx_amount(int availabe_funds, user current_user)
{
  for (auto tx_id : current_user.utx_ids)
  {
    int size = validated_transactions.size();
    for (int i = 0; i < size; i++)
    {
      if (validated_transactions[i].to == tx_id || validated_transactions[i].from == tx_id)
      {
        for (auto to_utxo : validated_transactions[i].out)
        {
          if (to_utxo.to == current_user.public_key && to_utxo.unspent == true) availabe_funds += to_utxo.amount;
        }
      } //amount from transactions sent to current user and amount user sent to himself
    }
  }
  return availabe_funds;
}